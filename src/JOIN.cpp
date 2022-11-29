#include "Server.hpp"

bool        isClientInChannel(Channel chan, std::string name)
{
    for (unsigned int i = 0; i < chan.getClients().size(); i++)
    {
        if (chan.getClients()[i].getNickname() == name)
            return true;
    }
    return false;
}
std::string     RPL_NAMREPLY(Client &cl, std::string chan_name, std::string users)
{
    std::string ret = "353 " + cl.getNickname() + " = " + chan_name + " :" + users;
    std::cout << "namereply " << ret << std::endl;
    return (ret);
}
std::string     RPL_ENDOFNAMES(Client &cl, std::string chan_name)
{
    return ("366 " + cl.getNickname() + " " + chan_name + " :End of /NAMES list.");

}
void        join(Channel &chan, Client &cl)
{
    std::string users;
    for(unsigned int i = 0; i < chan.getClients().size(); i++)
    {
        users += chan.getClients()[i].getNickname() + " ";
    }
    cl.reply(RPL_NAMREPLY(cl, chan.getName(), users));
	cl.reply(RPL_ENDOFNAMES(cl, chan.getName()));
    chan.broadcast(cl.getPrefix() + " JOIN :" + chan.getName());
}

int         Server::cmdJoin(std::vector<String> params, Client &cl)
{
    std::cout << "JOIN COMMAND" << std::endl;
    String  name;
    if (cl.getState() != REGISTERED)
    {
        cl.reply("you need to finalize your registration first");
        return -1;
    }
    if (params.size() < 2)
    {
       // cl->reply()errorneedmoreparams
        return -1;
    }
    name = erasebr(params[1]);
    try
    {
        Channel chan = findChannel(name);
        if (isClientInChannel(chan, cl.getNickname()))
        {
            std::cout << "isinclient" << std::endl;
            return -1;
        }
        chan.addClient(cl);
        join(chan, cl);
       // return 0;
    }
    catch(const std::exception& e)
    {

        std::cerr << e.what() << '\n';
        Channel new_chan(name);
        new_chan.addClient(cl);
        _channels.push_back(new_chan);
        join(new_chan, cl);
        //return 0;
    }
    return 0;
}
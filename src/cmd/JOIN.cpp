#include "Server.hpp"


std::string     RPL_NAMREPLY(Client &cl, std::string chan_name, std::string users)
{
    std::string ret = "353 " + cl.getNickname() + " = " + chan_name + " :" + users;
    std::cout << "namereply " << ret << std::endl;
    return (ret);
}

std::string     RPL_ENDOFNAMES(Client &cl, std::string chan_name) {
    return ("366 " + cl.getNickname() + " " + chan_name + " :End of /NAMES list.");
}

void        join(Channel &chan, Client &cl)
{
    std::string users;
    for(unsigned int i = 0; i < chan.getClients().size(); i++)
    {
        users += chan.getClients()[i].getNickname() + " ";
    }
    chan.broadcast(cl.getPrefix() + " JOIN :" + chan.getName());
    cl.reply(RPL_TOPIC(cl, chan.getName(), chan.getTopic()));
    cl.reply(RPL_NAMREPLY(cl, chan.getName(), users));
	cl.reply(RPL_ENDOFNAMES(cl, chan.getName()));
}

int         Server::cmdJoin(std::vector<String> params, Client &cl)
{
    if (cl.getState() != REGISTERED)
    {
        cl.reply("you need to finalize your registration first");
        return -1;
    }
    if (params.size() < 2)
    {
        cl.reply(ERR_NEEDMOREPARAMS(cl, "JOIN"));
        return -1;
    }
    String name = erasebr(params[1]);
    try
    {
        std::vector<Channel>::iterator chan = findChannelIt(name);
        if (isClientInChannel(*chan, cl.getFd()))
        {
            std::cout << "is already in channel" << std::endl;
            return -1;
        }
        chan->addClient(cl);
        join(*chan, cl);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "New chan open : " << name << std::endl;
        Channel new_chan(name);
        new_chan.addClient(cl);
        new_chan.setFdOp(cl.getFd());
        _channels.push_back(new_chan);
        join(new_chan, cl);
    }
    _channels[0].debug();
    return 0;
}
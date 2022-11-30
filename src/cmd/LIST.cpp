#include "Server.hpp"

int Server::cmdList(std::vector<String> args, Client &cl) {
    for (size_t i = 0; i < args.size(); i++)
        std::cout << "TEST ICI [" << args.at(i)<< "] "<< std::endl;
    

    if (args.size() == 1 || (args.size() == 2 && args.at(1) == "\r"))
    {
        if (_channels.size() == 0)
        {

            cl.reply(":NO SUCHCHANNEL"); // je reply 403???
            return -1;
        }
        for (size_t i = 0; i < _channels.size(); i++)
        {
            std::stringstream ss;
            ss << _channels.at(i).getClients().size();
            String size = ss.str();
            cl.reply("322 " + cl.getNickname() + " " + _channels.at(i).getName() + " " + size + " :" + _channels.at(i).getTopic());
        }
        return 0;
    }
    if (args.size() > 1)
    {
        for (size_t i = 1; i < args.size(); i++)
        {
            size_t j = 0;
            for (; j < _channels.size() ; j++)
            {
                if (args.at(i) == _channels.at(j).getName())
                {
                    std::stringstream ss;
                    ss << _channels.at(j).getClients().size();
                    String size = ss.str();
                    cl.reply("322 " + cl.getNickname() + " " + _channels.at(j).getName() + " " + size + " :" + _channels.at(j).getTopic());
                    j = 0;
                    break ;

                }
            }
            if (j + 1 == _channels.size())
            {
                cl.reply("403 " + cl.getNickname() + " " + args.at(i) + " :No such channel");
                return -1;
            }
            
        }
        
    }
    return 0;
}
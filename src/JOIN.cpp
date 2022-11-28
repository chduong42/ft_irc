#include "Server.hpp"

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
    if(cl.getNickname() == "debug")
        return -1;
    return 0;
}
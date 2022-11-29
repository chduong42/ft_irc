#include "Server.hpp"

int         Server::cmdJoin(std::vector<String> params, Client &cl)
{
    std::cout << "JOIN COMMAND" << std::endl;
    if (params.size() < 2)
        return -1;
    if(cl.getNickname() == "debug")
        return -1;
    return 0;
}
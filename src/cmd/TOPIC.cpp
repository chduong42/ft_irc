#include "Server.hpp"


int	cmdTopic(std::vector<String> args, Client &cl) {
    if (args.size() < 2)
    {
        cl.reply(ERR_NEEDMOREPARAMS(cl, "TOPIC"));
		return -1;
    }
    else if (args.size() == 2)
    {

    }
    else
    {

    }
    return (0);
}

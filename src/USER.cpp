#include "Server.hpp"

int Server::cmdUser(std::vector<String> args, Client *cl) {
	// for (size_t i = 0; i < args.size(); i++)
	// 	std::cout << args.at(i) << std::endl;
	String cmd = args.at(0);
	std::cout << cl->getNickname() << std::endl;
	if (args.size() < 5)
	{
		cl->reply("461 " + cl->getNickname() + " " + cmd + " :Not enough parameters");
	}
	else if (cl->getUsername() == args.at(1))
	{
		cl->reply("462 " + cl->getNickname() + " " + cmd + " :Unauthorized command (already registered)");
	}
	else if (args.size() == 5)
		cl->setUsername(args.at(1));
	return 0;
}
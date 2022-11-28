#include "Server.hpp"

int Server::cmdUser(std::vector<String> args, Client &cl) {
	String tmp;
	String cmd = args.at(0);
	if (args.size() < 5)
	{
		cl.reply(ERR_NEEDMOREPARAMS(cl, "USER"));
		return -1;
	}
	else if (cl.getUsername() == args.at(1))
	{
		cl.reply("462 " + cl.getNickname() + " " + cmd + " :Unauthorized command (already registered)");
		return -1;
	}
	else if (args.size() == 5)
	{
		cl.setUsername(args.at(1));
		tmp = args.at(1) + " " + args.at(2) + " " + args.at(3) + " " + args.at(4);
		cl.setRealname(tmp);
	}
	cl.welcome();
	return 0;
}
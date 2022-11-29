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
	else if (args.size() >= 5)
	{
		cl.setUsername(args.at(1));
		size_t i;
		for (i = 1; i < args.size() - 1; i++)
		{
			if (args.at(i)[0] == ':')
				break ;
		}
		tmp = args.at(i).substr(1);
		if (i + 1 == args.size())
		{
			cl.setRealname(tmp);
			cl.welcome();
			return 0;
		}
		i++;
		tmp += " ";
		for (; i < args.size() - 1; i++)
			tmp += args.at(i) + " ";
		tmp += args.at(i);
		cl.setRealname(tmp);
	}
	cl.welcome();
	return 0;
}
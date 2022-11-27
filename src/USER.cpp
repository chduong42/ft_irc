#include "Server.hpp"

bool	validUsername(String str) {
	for (size_t i = 1; i < str.size(); ++i)
	{
		if (str[i] == 0x00 && str[i] == 0x0A && str[i] == 0x0D && str[i] == 0x20 && str[i] == 40)
			return false;
	}
	return true;
}

int Server::cmdUser(std::vector<String> args, Client &cl) {
	String tmp;
	String cmd = args.at(0);
	if (args.size() < 5)
	{
		cl.reply("461 " + cl.getNickname() + " " + cmd + " :Not enough parameters");
		return -1;
	}
	//else if (validUsername(args.at(1)) == false)
	//{
	//	cl.reply
	//}
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
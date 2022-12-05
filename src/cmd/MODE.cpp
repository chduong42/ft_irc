#include <Server.hpp>

int Server::cmdMode(std::vector<String> args, Client &cl) {
	if (args.size() < 4) //pas sur suivant les cmd qu'on implemente
	{
		cl.reply("461 " + args.at(0) + " :Not enough parameters");
		return -1;
	}
	if (isChannel(args.at(1)) == false)
	{
		cl.reply("403 " + cl.getNickname() + " " + args.at(1) + " :No such channel");
		return -1;
	}
	/*if (args.at(2) == "-l")
	{
		if ()
	}*/
	return 0;
}
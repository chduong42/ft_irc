#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int	giveOprivilege() {}

int	setLimit(int limit) {}

int setPassword(String password) {}

int	parseLimit(char *arg) {
	char	*buff;

	if (*arg == '\0')
		return (0);

	long int limit = strtol(arg, &buff, 10);

	if (*buff != '\0')
		return (0);
	return (limit);
}

int	check_flag(std::vector<String> args, Client &cl) {
	std::string flags[7] = {"O","+o","-o","+l","-l","+k","-k"};
	int i = 0;
	
	while (args[2] != flags[i] && i < 7)
		++i;

	switch (i) {
		case 0:
			return (giveOprivilege());
		case 1:
			return (giveOprivilege());
		case 2:
			cl.reply(ERR_CHANOPRIVSNEEDED());
			return;
		case 3:
			return (setLimit(parseLimit(args[4])));
		case 4:
			return (setLimit(0));
		case 5:
			return (setPassword(erasebr(args[4])));
		case 6:
			return (setPassword(""));
		default:
			std::cout << "This flag is not used on our channels" << std::endl;
			return;
	}
}


int Server::cmdMode(std::vector<String> args, Client &cl) {
	if (args.size() < 4) //pas sur suivant les cmd qu'on implemente
	{
		cl.reply(ERR_NEEDMOREPARAMS(cl, ));
		return -1;
	}
	if (isChannel(args.at(1)) == false)
	{
		cl.reply(ERR_NOSUCHCHANNEL(cl, args[1]));
		return -1;
	}
<<<<<<< HEAD
	/*if (args.at(2) == "-l")
	{
		if ()
	}*/
	return 0;
=======
//	if (args.at(2) == "-l")
//	{
//		if ()
//	}
	return 1;
>>>>>>> d6e0d81f1ebda40cb9b731a2641c2bdb888b8a83
}
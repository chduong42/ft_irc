#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int	giveOprivilege() {
	std::cout << "givOp privilege" << std::endl;
	return 0;}


int setPassword(String password) {
	if (password.empty())
		return -1;
	return 0;
	}


int	parseLimit(std::string arg) {
	char	*buff;

	if (arg.empty())
		return (0);

	long int limit = strtol(arg.c_str(), &buff, 10);

	if (*buff != '\0')
		return (0);
	return (limit);
}

int	setLimit(int limit)
{
	std::cout << "limit == " << limit << std::endl;

	return 0;
}

int	check_flag(std::vector<String> args, Client &cl) {
	if (cl.getFd() == 100)
		return -42;
	std::string flags[7] = {"O","+o","-o","+l","-l","+k","-k"};
	int i = 0;
	
	while (args[2] != flags[i] && i < 7)
		++i;
	std::cout << "IN CHECK_FLAG" << std::endl;
	switch (i) {
		case 0:
			return (giveOprivilege());
		case 1:
			return (giveOprivilege());
		case 2:
			std::cout << "case 2" << std::endl;
			//cl.reply(ERR_CHANOPRIVSNEEDED());
			return -1;
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
			return -1;
	}
	return 0;
}


int Server::cmdMode(std::vector<String> args, Client &cl) {
	std::cout << "in MODE->args = " << std::endl;
	for (unsigned int i = 0; i < args.size(); i++)
	{
		std::cout << args[i] << std::endl ;
	}
	std::cout << std::endl;

	if (args.size() < 4) //pas sur suivant les cmd qu'on implemente
	{
		cl.reply(ERR_NEEDMOREPARAMS(cl, "mode"));
		return -1;
	}
	if (isChannel(args.at(1)) == false)
	{
		cl.reply(ERR_NOSUCHCHANNEL(cl, args[1]));
		return -1;
	}
	check_flag(args, cl);
//	if (args.at(2) == "-l")
//	{
//		if ()
//	}
	return 1;
}
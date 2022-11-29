#include "Server.hpp"

		/*KICK    - Eject a client from the channel
        MODE    - Change the channel's mode
        INVITE  - Invite a client to an invite-only channel (mode +i)
        TOPIC   - Change the channel topic in a mode +t channel*/

int	Server::cmdOper(std::vector<String> args, Client &cl)
{
	for (size_t i = 0; i < args.size(); i++)
		std::cout << args.at(i) << std::endl;
	
	String cmd = args.at(0);
	if (args.size() < 3)
	{
		cl.reply("461 " + cl.getNickname() + " " + cmd + " :Not enough parameters");
		return -1;
	}
	String pswd = erasebr(args.at(2));
	if (this->_operPassword != pswd)
	{
		cl.reply("464 " + cl.getNickname() + " " + cmd + " :Password incorrect");
		return -1;
	}
	else
	{
		cl.setisoper(true);
		cl.reply("381 " + cl.getNickname() + " " + cmd + " :you are now an operator");
	}
	return 0;
}
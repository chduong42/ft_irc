#include "Server.hpp"

bool	Server::already_used(String name, Client cl)
{
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		if (it->getNickname() == name && it->getFd() != cl.getFd())
			return (true);
	}
	return (false);
}

bool	isSpecial(char c) {
	if (c >= 0x5B && c <= 0x60)
		return (true);
	else if (c >= 0x7B && c <= 0x7D)
		return (true);
	else
		return (false);
}

bool	valid_nickname(String name) {
	if (name.size() > 9)
		return (false);
	if (!isSpecial(name[0]) && !isalpha(name[0]))
		return (false);
	for (int i = 1; i < name.size(); ++i)
	{
		if (!isalnum(name[i] && !isSpecial(name[i]) && name[i] != '-'))
			return (false);
	}
	return (true);
}

int Server::cmdNick(std::vector<String> args, Client cl) {
	if (args[1].empty())
		std::cout << "431 ERR_NONICKNAMEGIVEN" << std::endl;
	if (args[1] == cl.getNickname())
		return (0);
	if (already_used(args[1], cl) == true)
		std::cout << "433 ERR_NICKNAMEINUSE" << std::endl;
	if (valid_nickname(args[1]) == false)
		std::cout << "432 ERR_ERRONEUSNICKNAME" << std::endl;
	return 0;
}

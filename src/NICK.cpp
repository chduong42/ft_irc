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
	if (!(isSpecial(name[0]) || isalpha(name[0])))
		return (false);
	for (size_t i = 1; i < name.size(); ++i)
	{
		if (!(isalnum(name[i]) || isSpecial(name[i]) || name[i] == '-'))
			return (false);
	}
	return (true);
}

String	ERR_NONICKNAMEGIVEN(Client cl) {
	return ("431 " + cl.getNickname() + " :No nickname given");
}

String	ERR_ERRONEUSNICKNAME(Client cl, String newNick) {
	return ("432 " + cl.getNickname() + " " + newNick + " :Erroneus nickname");
}

String	ERR_NICKNAMEINUSE(Client cl, String newNick) {
	return ("433 " + cl.getNickname() + " " + newNick + " " + newNick + " :Nickname is already in use");
}

String	SUCCESS_NICK(Client cl, String newNick) {
	return (cl.getNickname() + "!" + cl.getUsername() + "@" + cl.getHostname() + " NICK " + newNick);
}

int Server::cmdNick(std::vector<String> args, Client &cl)
{
	String newNick = args[1].substr(0, args[1].size() - 1); // enleve le \r a la fin de pass

	if (newNick == cl.getNickname())
		return (0);
	if (newNick.empty())
	{
		cl.reply(ERR_NONICKNAMEGIVEN(cl));
		return (-1);
	}
	if (valid_nickname(newNick) == false)
	{
		cl.reply(ERR_ERRONEUSNICKNAME(cl, newNick));
		return (-1);
	}
	if (already_used(newNick, cl) == true)
	{
		cl.reply(ERR_NICKNAMEINUSE(cl, newNick));
		return (-1);
	}
	if (cl.getState() == REGISTERED)
        cl.reply(SUCCESS_NICK(cl, newNick));
	cl.setNickname(newNick);
	displayClient();
	return 0;
}

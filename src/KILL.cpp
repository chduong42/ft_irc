#include "Server.hpp"

int	Server::cmdKill(std::vector<String> args, Client &cl)
{
	String cmd = args.at(0);
	size_t	i = 0;
	int		check = 0;

	if (cl.getisoper() == false)
	{
		cl.reply("481 " + cl.getNickname() + " " +  cmd + " :you are not an oper");
		return -1;
	}
	if (args.size() < 2)
	{
		cl.reply("461 " + cl.getNickname() + " " + cmd + " :Not enough parameters");
		return -1;
	}
	for (std::vector<Client>::iterator it = this->_clients.begin() ; it != this->_clients.end(); ++it)
		i++;
	i -=1;
	for (size_t j = 0; j < i; i++)
	{
		if (args.at(1) == _clients.at(i).getNickname())
		{
			check = 1;
			break ;
		}
	}
	if (check != 1)
	{
		cl.reply("401" + cl.getNickname() + " " + cmd + " " + args.at(1) + " :doesn't exist");
		return -1;
	}
	clientDisconnect(_clients.at(i).getFd());
	return 0;
}
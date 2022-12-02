#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

String	erasebr(String str) {
	if (str.empty())
		return NULL;
	if (str[str.size() - 1] == '\r')
		return str.substr(0, (str.size() - 1));
	return str;
}

String	ERR_NEEDMOREPARAMS(Client &client, String cmd) {
	return ("461 " + client.getNickname() + " " + cmd + " :Not enough parameters");
}

String  RPL_TOPIC(Client cl, String channel, String topic) {
	return ("332 " + cl.getNickname() + " " + channel + " " + topic);
}

bool	isClientInChannel(Channel &chan, int fd)
{
	for (unsigned int i = 0; i < chan.getClients().size(); i++)
	{
		if (chan.getClients()[i].getFd() == fd)
			return true;
	}
	return false;
}

bool	isOperInChannel(Client cl, Channel chan)
{
	if (chan.getFdOp() == cl.getFd())
		return true;
	return false;
}


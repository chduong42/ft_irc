#include "Server.hpp"

String  ERR_NOSUCHCHANNEL(Client cl, String channel) {
	return ("403 " + cl.getNickname() + " " + channel +" :No such channel");
}

String  RPL_NOTOPIC(Client cl, String channel) {
	return ("331 " + cl.getNickname() + " " + channel +" :No topic is set");
}

String  RPL_TOPIC(Client cl, String channel, String topic) {
	return ("332 " + cl.getNickname() + " " + channel + " :" + topic);
}

String  ERR_CHANOPRIVSNEEDED(Client cl, String channel) {
	return ("482 " + cl.getNickname() + " " + channel + " :You're not channel operator");
}

String  ERR_NOTONCHANNEL(Client cl, String channel) {
	return ("442 " + cl.getNickname() + " " + channel + " :You're not on that channel");
}

int	changeTopic(Channel &chan, String newTopic) {
	chan.setTopic(newTopic);
	return (0);
}



int		Server::cmdTopic(std::vector<String> args, Client &cl)
{
	if (args.size() < 2)
	{
		cl.reply(ERR_NEEDMOREPARAMS(cl, "TOPIC"));
		return -1;
	}

	String chan_name = erasebr(args[1]);
	std::cout << "[" << chan_name << "]" << std::endl;

	try {
		if (chan_name.empty())
		{
			cl.reply(ERR_NEEDMOREPARAMS(cl, "TOPIC"));
			return (-1);
		}

		std::vector<Channel>::iterator chan = findChannelIt(chan_name);

		if (isClientInChannel(*chan, cl.getFd()))
		{
			if (args.size() == 2)
			{
				if (chan->getTopic().empty())
					cl.reply(RPL_NOTOPIC(cl, chan_name));
				else
					cl.reply(RPL_TOPIC(cl, chan_name, chan->getTopic()));
				return (0);
			}

			if (isOperInChannel(cl, *chan))
				return (changeTopic(*chan, chan_name));
			else
				cl.reply(ERR_NOTONCHANNEL(cl, chan_name));
		}
		else
			cl.reply(ERR_NOTONCHANNEL(cl, chan_name));
		return (-1);
	}
	catch (const std::exception& e)
	{
		cl.reply(ERR_NOSUCHCHANNEL(cl, chan_name));
		return (-1);
	}

}

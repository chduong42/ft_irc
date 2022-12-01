#include <Server.hpp>

int	Server::cmdNames(std::vector<String> args, Client &cl) {
	for (size_t i = 0; i < args.size(); i++)
	{
		std::cout << args.at(i) << " ";
	}
	
	if (args.size() == 1)
	{
		std::vector<String> tmp;
		tmp.push_back("LIST");
		cmdList(tmp, cl);
	}
	else if (args.size() >= 1)
	{
		size_t i = 1;
		for (; i < args.size(); i++)
		{
			for (size_t j = 0; j < _channels.size(); j++)
			{
				if (erasebr(args.at(i)) == _channels.at(j).getName())
				{
					String str;
					size_t x = 0;
					for (; x < _channels.at(j).getClients().size() - 1; x++)
						str += _channels.at(j).getClients().at(x).getNickname() + " ";
					str += _channels.at(j).getClients().at(x).getNickname();
					cl.reply("353 " + cl.getNickname() + " = " + _channels.at(j).getName() + " :" + str);
					str.clear();
					cl.reply("366 " + cl.getNickname() + " " + _channels.at(j).getName() + " :End of /NAMES list");
					
				}
			}
			
		}
		
		
	}
	return 0;
}
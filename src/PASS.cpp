#include "Server.hpp"

int Server::cmdPass(std::vector<String> arg, Client cl) {
	if (arg.size() < 2) {
		cl.reply("ERR_NEEDMOREPARAMS");
		return 461;
	}
	if ()
}

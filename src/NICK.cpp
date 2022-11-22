#include "Server.hpp"

int Server::cmdNick(std::vector<String> pass, Client cl) {
	std::cout << "Je parse NICK" << std::endl;
	(void)cl;
	(void)pass;
	return 0;
}

#include "Server.hpp"

int Server::cmdPass(std::vector<String> args, Client cl) {
	std::cout << "Je parse PASS" << std::endl;
	(void)cl;
	(void)args;
	return 0;
}

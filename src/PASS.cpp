#include "Server.hpp"

int Server::cmdPass(std::vector<String> pass, Client cl) {
	std::cout << "Je parse PASS" << std::endl;
	(void)cl;
	(void)pass;
	return 0;
}

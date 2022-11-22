#include "Server.hpp"

int Server::cmdUser(std::vector<String> pass, Client cl) {
	std::cout << "Je parse USER" << std::endl;
	(void)pass;
	(void)cl;
	return 0;
}
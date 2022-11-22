#include "Server.hpp"

int Server::cmdUser(std::vector<String> args, Client cl) {
	std::cout << "Je parse USER" << std::endl;
	(void)args;
	(void)cl;
	return 0;
}
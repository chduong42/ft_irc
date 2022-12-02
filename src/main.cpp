#include "Server.hpp"
#include "Colors.hpp"
#include <signal.h>

//	Interruption statut (global var) 
bool	g_interrupt = false;

//	Gestion du CTRL+C
void	sigintHandler(int const sig) {
	(void)sig;
	g_interrupt = true;
	std::cout << "\b\b";
	// exit(0);
}

//	Verification et recuperation du port
bool	getport(char *arg, int &port) {
	char	*buff;

	if (*arg == '\0')
		return (false);
	port = strtol(arg, &buff, 10);
	if (*buff != '\0')
	{
		std::cout << RED << "Error input: port must contain only digits" << RESET << std::endl;
		return (false);
	}
	if (port < 0 || port > 65535)
	{
		std::cout << RED << "Error input: port is out of range [0; 65535]" << RESET << std::endl;
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	int port;

	signal(SIGINT, sigintHandler);
	if (ac != 3)
	{
		std::cout << BWHT << "Usage: ./ircserv <port> <password>" << RESET << std::endl;
		return (1);
	}
	if (getport(av[1], port) == false)
		return (1);
	
	try
	{
		Server	server(port, av[2]);
		server.launch();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

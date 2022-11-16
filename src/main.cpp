#include "Server.hpp"
#include "colors.hpp"

int	check_port(char *arg) {
	int		port;
	char	*buff;

	if (*arg == '\0')
		return (-1);
	port = strtol(arg, &buff, 10);
	if (*buff != '\0')
	{
		std::cout << RED << "Error input: port must contain only digits" << RESET << std::endl;
		return (-1);
	}
	if (port < 0 || port > 65535)
	{
		std::cout << RED << "Error input: port is out of range [0; 65535]" << RESET << std::endl;
		return (-1);
	}
	return (port);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << BWHT << "Usage: ./ircserv <port> <password>" << RESET << std::endl;
		return (1);
	}
	int port = check_port(av[1]);
	if (port < 0)
		return (1);
	try	{
		Server	server(port, av[2]);
		server.launch();
	}
	catch(const std::exception& e)	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

#include "Server.hpp"


int		main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	try
	{
		Server	server(av[1], av[2]);
		server.launch();
	}
	catch(const std::invalid_argument &ex)
	{
		std::cout << "error in " << ex.what() << std::endl;
		std::cout << "error in port" << std::endl; 
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	

	return 0;
}
// mettre un try catch

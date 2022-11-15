/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:03:13 by chduong           #+#    #+#             */
/*   Updated: 2022/11/15 19:51:32 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	check_port(char *port)
{
	long l = strtol(s, &port, 10);
	if (*port) {
		// conversion failed because the input wasn't a number
	}
	else {
		// use converted
	}
}

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
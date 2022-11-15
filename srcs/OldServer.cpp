/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:49:33 by chduong           #+#    #+#             */
/*   Updated: 2022/11/15 15:40:36 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


Server::Server(int port) {
	std::cout << "Server Init..." << std::endl;
	_sock = socket(AF_INET, SOCK_STREAM, 0);
	_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	std::cout << "Server's Socket: " << _sock << std::endl;
	std::cout << "Server's IP: " << _sin.sin_addr.s_addr << std::endl;
	std::cout << "Server's Port: " << _sin.sin_port << std::endl;

	if (bind(_sock, (SOCKADDR*)&_sin, sizeof(_sin)) == -1)
	{
		printf( "bind() error %d\n", errno);
		exit(1);
	}
	if (listen(_sock, SOMAXCONN) == -1)
	{
		printf( "listen() error %d\n", errno);
		exit(1);
	}
}

Server::~Server() {}


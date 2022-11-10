/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:49:33 by chduong           #+#    #+#             */
/*   Updated: 2022/11/10 03:42:41 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {
	_hSocket = socket(PF_INET, SOCK_STREAM, 0 );
	if(_hSocket == -1)
	{
		printf( "socket() error %d\n", errno);
		exit(1);
	}
	_addr.sin_family = AF_INET ;
	_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	_addr.sin_port = htons ((unsigned short)0);
	if (bind(_hSocket, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
	{
		printf( "bind() error %d\n", errno);
		exit(1);
	}
	if (listen(_hSocket, SOMAXCONN) == -1)
	{
		printf( "listen() error %d\n", errno);
		exit(1);
	}
	_hAccept = accept(_hSocket, NULL, NULL);
}
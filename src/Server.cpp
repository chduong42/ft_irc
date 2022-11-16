#include "Server.hpp"
#include <cstring>

Server::Server(int port, const String &pass)
	: _loop(1), _port(port), _host("127.0.0.1"), _password(pass) {
	_sock = createSocket();
}

Server::~Server() {}

int		Server::createSocket()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket.");

	// Attaching socket to the port
	int val = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");

	/** Set the socket to NON-BLOCKING mode */
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) 
		throw std::runtime_error("Error while setting socket to NON-BLOCKING.");

	SOCKADDR_IN serv_address = {};
	bzero((char *) &serv_address, sizeof(serv_address));
	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_address.sin_port = htons(_port);

	// Bind the socket to the current IP address on selected port
	if (bind(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0)
		throw std::runtime_error("Error while binding socket.");
	if (listen(sockfd, 1000) < 0)
		throw std::runtime_error("Error while listening on socket.");
	return sockfd;
}

void	Server::newClient()
{
	int new_fd;
	std::cout << "POLLiN events" << std::endl;
	new_fd = accept(_sock, NULL, NULL);
	if (new_fd < 0)
		std::cout << " normal" << std::endl;
	else
		std::cout << "connection established" << new_fd << std::endl;

	pollfd pollfd = {new_fd, POLLIN, 0};
	_pollfds.push_back(pollfd);
}

String	Server::readMsg(int fd) {
	String	msg;
	char	buff[256];
	bzero(buff, 256);
	while (!std::strstr(buff, "\r\n"))
	{
		bzero(buff, 256);
		if (recv(fd, buff, 256, 0) < 0)
		{
			if (errno != EWOULDBLOCK)
				throw std::runtime_error("error in recv");
		}
		msg = buff;
	}
	std::cout << "test" << std::endl;
	return msg;
}

void	Server::handleMessage(int fd) {
	std::cout << readMsg(fd) << std::endl;
}

void	Server::launch()
{
	pollfd fd_server = {_sock, POLLIN, 0};
	_pollfds.push_back(fd_server);
	
	std::cout << _pollfds.size() << std::endl;
	while (_loop)
	{
		if (poll(_pollfds.begin().base(), _pollfds.size(), -1) < 0)
			throw std::runtime_error("Error while polling");

		for (unsigned int i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents == 0)
			{
				//std::cout << "okok" << std::endl;
				continue ;
			}
			//	std::cout << "test" << std::endl;
			//get connection pollfds[i].revents == POLLIN
			if ((_pollfds[i].revents  & POLLIN ) == POLLIN)
			{
				if (_pollfds[i].fd == _sock)
				{
					newClient();
					break;
				}
			}

			//get deconnection ''          ''   == POLLOUT
			handleMessage(_pollfds[i].fd);
		}
		
		//read and handle messages
	}
}

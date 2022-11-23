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
	sockaddr_in s_address = {};
	socklen_t s_size = sizeof(s_address);

	new_fd = accept(_sock, (sockaddr *) &s_address, &s_size);
	if (new_fd < 0)
		throw std::runtime_error("Error while accepting new client.");
	std::cout << "POLLiN events" << std::endl;

	char hostname[2048];
	if (getnameinfo((struct sockaddr *) &s_address, sizeof(s_address), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) !=
		0)
		throw std::runtime_error("Error while getting hostname on new client.");
	//std::cout << hostname << std::endl;
	_clients.push_back(Client(new_fd, hostname));
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
	return msg;
}

std::vector<String>	Server::infClient(String msg) {
	std::vector<String> inf;
	String tmp;
	std::stringstream str(msg);
	int i = 0;
	while (std::getline(str, tmp, '\n')) {
		inf.push_back(tmp);
		std::cout << inf.at(i++) << std::endl;
	}
	return inf;
}

void	Server::handleMessage(int fd) {
	/*try
	{
		Client	client = findClient(fd);
		client.debug();
		std::cout << "HandleMsg" << std::endl;
		std::cout << readMsg(fd) << std::endl;
		//client.execute(readMsg(fd))
	}

	catch (std::out_of_range &e)
	{

	}*/
	//std::cout << "HandleMsg" << std::endl;
	//std::cout << readMsg(fd) << std::endl;
	String	str = readMsg(fd);
	this->_inf = infClient(str);
	return ;
}

void	Server::test(int fd) {
	if (this->_inf.empty())
		return ;
	Client cl = findClient(fd);
	for (std::vector<String>::iterator it = this->_inf.begin(); it != this->_inf.end(); it++)
		callClient(*it, cl);
	return ;
}

void	Server::callClient(String str, Client cl) {
	String tmp;
	std::vector<String>	pass;
	std::stringstream ss(str);
	std::getline(ss, tmp, ' ');
	pass.push_back(tmp);
	std::cout << "tmp = " << tmp << std::endl;
	std::string cmds[3] = {"PASS", "NICK", "USER"};

	int		(Server::*monpointeur[3])(std::vector<String> pass, Client cl) = {
			&Server::cmdPass,
			&Server::cmdNick,
			&Server::cmdUser,
	};
	int i = 0;
	while (tmp != cmds[i] && i <= 2)
		i++;
	if (tmp == cmds[i])
	{
		std::getline(ss, tmp, '\0');
		pass.push_back(tmp);
		(this->*monpointeur[i])(pass, cl);
	}
	else
		std::cout << "on gere pas ca" << std::endl;
	
}

void	Server::launch()
{
	pollfd fd_server = {_sock, POLLIN, 0};
	_pollfds.push_back(fd_server);
	
	std::cout << "size struct pollfds " << _pollfds.size() << std::endl;
	while (_loop)
	{
		if (poll(_pollfds.begin().base(), _pollfds.size(), -1) < 0)
			throw std::runtime_error("Error while polling");

		for (unsigned int i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents == 0)
				continue ;
			if ((_pollfds[i].revents  & POLLIN ) == POLLIN)
			{
				if (_pollfds[i].fd == _sock)
				{
					newClient();
					std::cout << "size ==" <<_clients.size() << std::endl;
					if (_clients.size())
						_clients[_clients.size() - 1].debug();
					break;
				}
			}

			//get deconnection ''          ''   == POLLOUT
			handleMessage(_pollfds[i].fd);
			test(_pollfds[i].fd);
		}
		//read and handle messages
	}
}

Client		Server::findClient(int fd)
{
	for (unsigned int i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getFd() == fd)
			return (_clients[i]);
	}
	throw(std::out_of_range("Error while searching for user"));
}



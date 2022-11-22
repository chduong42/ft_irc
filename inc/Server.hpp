#ifndef SERVER_HPP
# define SERVER_HPP
# include <algorithm>
# include <sys/poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include <vector>
# include <map>
# include <poll.h>
# include <unistd.h>
# include <cstdlib>
# include <string>
# include <strings.h>
# include <iostream>
# include <cerrno>
# include "Client.hpp"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(param) close(param)

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

class Server {
	private:
		int						_loop;
		int						_port;
		String					_host;
		String					_password;
		std::vector<pollfd>		_pollfds;
		std::vector<Client>		_clients;
		int						_sock;
		// SOCKADDR_IN			_sin;

	public:
		Server(int port, const String &password);
		~Server();

		int			createSocket();
		void		launch();
		void		newClient();
		void		handleMessage(int fd);
		String		readMsg(int fd);
		Client		findClient(int fd);

		// COMMANDE IRC
		
};

#endif

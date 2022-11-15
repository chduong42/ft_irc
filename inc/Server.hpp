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

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(param) close(param)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

class Server {
	private:
		int						_loop;
		SOCKET					_sock;
		SOCKADDR_IN				_sin;
		String					_host;
		String					_port;
		String					_password;
		std::vector<pollfd>		_pollfds;

	public:
		Server(const String &port, const String &password);
		~Server();

		int		createSocket();
		void	launch();
		void	newClient();
		void	handleMessage(int fd);
		String	readMsg(int fd);
};

#endif

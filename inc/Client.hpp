#ifndef CLIENT_HPP
# define CLIENT_HPP
#include <iostream>
# include <sys/socket.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

class Client {
	private:
		int			_sockfd;
		String		_nickname;
		String		_username;
		String		_realname;
		String		_hostname;
		String		_message;
		
	public:
		Client(int fd, String host);
		~Client();
		void	reply(String msg);
		void	welcome();
		int		getFd();
		void	debug();
};

#endif

#ifndef CLIENT_HPP
# define CLIENT_HPP
#include <iostream>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

class Client {
	private:
		int			_sockfd;
		String		_host;
		String		_nickname;
		String		_username;
		String		_realname;
		String		_message;
		
	public:
		Client(int _sockfd, String nickname, String username);
		~Client();
};

#endif
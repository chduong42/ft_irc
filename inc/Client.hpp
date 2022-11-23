#ifndef CLIENT_HPP
# define CLIENT_HPP
#include <iostream>
#include <vector>
#include <sstream>
# include <sys/socket.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

enum State{
	HANDSHAKE,
	LOGIN
};

class Client {
	private:
		int			_sockfd;
		String		_nickname;
		String		_username;
		String		_realname;
		String		_hostname;
		String		_msg;
		State		_state;
		
	public:
		Client(int fd, String host);
		~Client();

		void	reply(String msg);
		void	welcome();
		int		getFd();
		void	debug();

		String		getNickname() const;
		String		getUsername() const;
		String		getRealname() const;
		String		getHostname() const;
		String		getMsg() const;
		
		void		setNickname(String newName);
		void		setUsername(String newName);
		void		setRealname(String newName);
		void		setHostname(String newName);
		void		setMsg(String newMsg);
		void		setState(State newState);

		int cmdPass(String str);
		int cmdNick(String str);
		int cmdUser(String str);

};

#endif

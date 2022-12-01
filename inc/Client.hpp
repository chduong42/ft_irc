#ifndef CLIENT_HPP
# define CLIENT_HPP

class Client;

# include <iostream>
# include <vector>
# include <sstream>
# include <sys/socket.h>
# include <Channel.hpp>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

enum State{
	HANDSHAKE,
	LOGIN,
	REGISTERED
};

class Channel;

class Client {
	private:
		int			_sockfd;
		String		_nickname;
		String		_username;
		String		_realname;
		String		_hostname;
		String		_msg;
		State		_state;
		bool		_isoper;
		std::vector<Channel>	_channels;

		
	public:
		Client(int fd, String host);
		~Client();

		void		reply(String msg);
		void		welcome();
		void		debug();

		int			getFd() const;
		String		getNickname() const;
		String		getUsername() const;
		String		getRealname() const;
		String		getHostname() const;
		String		getMsg() const;
		String		getPrefix();
		State		getState() const;
		bool		getisoper() const;
		
		void		setNickname(String newName);
		void		setUsername(String newName);
		void		setRealname(String newName);
		void		setHostname(String newName);
		void		setMsg(String newMsg);
		void		setState(State newState);
		void		setisoper(bool isoper);

};

#endif

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
# include <sstream>

# include "Client.hpp"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

class Server {
	private:
		int						_loop;
		int						_port;
		String					_host;
		String					_password;
		std::vector<String>		_cmd;
		std::vector<pollfd>		_pollfds;
		std::vector<Client>		_clients;
		int						_sock;

	public:
		Server(int port, const String &password);
		~Server();

		int						createSocket();
		void					launch();
		void					newClient();
		void					clientDisconnect(int fd);
		void					eraseClient(int fd);
		void					handleMessage(int fd);
		void					parseCmd(String str, Client &cl);
		void					displayClient();

		std::vector<String>		splitCmd(String msg);
		String					readMsg(int fd);
		Client					&findClient(int fd);

		bool					already_used(String name, Client cl);

		// COMMANDE IRC
		int						cmdPass(std::vector<String> pass, Client &cl);
		int						cmdNick(std::vector<String> pass, Client &cl);
		int						cmdUser(std::vector<String> pass, Client &cl);

};

// enum    numRepl {
// 	RPL_WELCOME = 001,
// 	RPL_YOURHOST = 002,
// 	RPL_CREATED = 003,
// 	RPL_MYINFO = 004,

// 	RPL_UMODEIS = 221,
// 	RPL_AWAY = 301,
// 	RPL_WHOISREGNICK = 307,
// 	RPL_WHOSIUSER = 311,
// 	RPL_WHOISOPERATOR = 313,
// 	RPL_ENDOFWHOIS = 318,
// 	RPL_CHANNELMODEIS = 324,
// 	RPL_TOPIC = 332,
// 	RPL_WHOISMODES = 379,
// 	RPL_YOUREOPER = 381,

// 	ERR_NOSUCHNICK = 401,
// 	ERR_NOSUCHCHANNEL = 403,
// 	ERR_CANTSENDTOCHAN = 404,
// 	ERR_NORECIPENT = 411,
// 	ERR_NOTEXTTOSEND = 412,
// 	ERR_NONICKNAMEGIVEN = 431,
// 	ERR_ERRONEUSNICKNAME = 432,
// 	ERR_NICKNAMEINUSE = 433,
// 	ERR_NEEDMOREPARAMS = 461,
// 	ERR_ALREADYREGISTRED = 462,
// 	ERR_PASSWDMISMATCH = 464,
// 	ERR_UNKNOWNMODE = 472,
// 	ERR_NOPRIVILEGES = 481,
// 	ERR_UMODEUNKNOWNFLAG = 501,
// 	ERR_USERSDONTMATCH = 502
// };

#endif

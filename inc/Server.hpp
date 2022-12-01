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
# include "Channel.hpp"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef std::string String;

class Channel;

class Server {
	private:
		int									_loop;
		int									_port;
		String								_host;
		String								_password;
		String								_operPassword;
		std::vector<String>					_cmd;
		std::vector<pollfd>					_pollfds;
		std::vector<Client>					_clients;
		int									_sock;
		std::vector<Channel>				_channels;

	public:
		Server(int port, const String &password);
		~Server();

		// Server utils
		int									createSocket();
		int									chanMessage(std::vector<String> params, Client &cl);

		void								launch();
		void								newClient();
		void								clientDisconnect(int fd);
		void								eraseClient(int fd);
		void								handleMessage(int fd);
		void								parseCmd(String str, Client &cl);
		void								displayClient();
		void								eraseClientChannel(Client &cl);
		
		bool								already_used(String name, Client cl);
		
		std::vector<String>					splitCmd(String msg);
		String								readMsg(int fd);

		// Finder
		Client								&findClient(int fd);
		Client								&findClient(String nickname);
		std::vector<Client>::iterator		findClientIt(int fd);
		
		Channel								&findChannel(String name);
		std::vector<Channel>::iterator		findChannelIt(String name);

		// COMMANDE IRC
		int									cmdPass(std::vector<String> pass, Client &cl);
		int									cmdNick(std::vector<String> pass, Client &cl);
		int									cmdUser(std::vector<String> pass, Client &cl);
		int									cmdPrvMsg(std::vector<String> pass, Client &cl);
		int									cmdPing(std::vector<String> args, Client &cl);
		int									cmdJoin(std::vector<String> args, Client &cl);
		int									cmdOper(std::vector<String> args, Client &cl);
		int									cmdKill(std::vector<String> args, Client &cl);
		int									cmdPart(std::vector<String> args, Client &cl);
        int                     			cmdList(std::vector<String> args, Client &cl);
        int                     			cmdNames(std::vector<String> args, Client &cl);
		int									cmdTopic(std::vector<String> args, Client &cl);
};

//	UTILS
String										erasebr(String str);
String										ERR_NEEDMOREPARAMS(Client &client, String cmd);
bool        								isClientInChannel(Channel &chan, int fd);
bool        								isOperInChannel(Client cl, Channel chan);

#endif

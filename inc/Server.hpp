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
# include "Colors.hpp"

typedef std::string String;

class Client;
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

	// Server init
		int									createSocket();
		void								launch();
	// Server display
		void								handleMessage(int fd);
		void								displayClient();
	// Server receipt 
		std::vector<String>					splitCmd(String msg);
		void								parseCmd(String str, Client &cl);
		String								readMsg(int fd);
	// Manage Clients
		void								newClient();
		void								eraseClient(int fd);
		void								eraseClientChannel(Client &cl);
		void								clientDisconnect(int fd);

	// Server utils
		int									chanMessage(std::vector<String> params, Client &cl);
		bool								already_used(String name, Client cl);

		Client								&findClient(int fd);
		Client								&findClient(String nickname);
		std::vector<Client>::iterator		findClientIt(int fd);

		bool     							isChannel(std::string name);
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
		int									cmdKick(std::vector<String> args, Client &cl);
};

// Utils.cpp
	String								erasebr(String str);
	String								ERR_NEEDMOREPARAMS(Client &client, String cmd);
	String								RPL_TOPIC(Client cl, String channel, String topic);
	
	bool        						isClientInChannel(Channel &chan, int fd);
	bool        						isOperInChannel(Client cl, Channel chan);

#endif

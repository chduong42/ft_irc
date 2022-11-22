#include "Client.hpp"

Client::Client(int sockfd, std::string nickname, std::string Clientname) 
    : _sockfd(sockfd), _nickname(nickname), _hostname(Clientname)
{
    
}

Client::~Client()
{
}

void    Client::reply(String msg)
{
    String prefix = _nickname + (_username.empty() ? "" : "!" + _username) + (_hostname.empty() ? "" : "@" + _hostname);
    String paquet = ":" + prefix + " " + msg + "\r\n";
    if (send(_sockfd, paquet.c_str(), paquet.length(), 0) < 0)
        throw(std::out_of_range("Error while sending"));
}

void    Client::welcome()
{
    reply("001 " + _nickname + " :Welcome " +_nickname +  " into our irc network");
}

/*int	Client::cmdNick(String str) {
	std::vector<String> inf;
	String tmp;
	std::stringstream s(str);
	int i = 0;
	while (std::getline(s, tmp, ' ')) {
		inf.push_back(tmp);
	if (inf.at(0) != "NICK")
		return -1;
	else
		_nickname = inf.at(1);
	return 1;
}
*/
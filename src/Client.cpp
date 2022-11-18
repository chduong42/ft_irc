#include "Client.hpp"

Client::Client(int sockfd, std::string nickname, std::string Clientname) 
    : _sockfd(sockfd), _nickname(nickname), _hostname(Clientname) {}

Client::~Client() {}

void    Client::reply(String msg) 
{
    String prefix = _nickname + (_username.empty() ? "" : "!" + _username) + (_hostname.empty() ? "" : "@" + _hostname);
    String paquet = ":" + prefix + " " + msg + "\r\n";
    if (send(_sockfd, paquet.c_str(), paquet.length(), 0) < 0)
        throw(std::out_of_range("Error while sending"));
}

void    Client::welcome() {
    reply("001 " + _nickname + " :Welcome " +_nickname +  " into our irc network");
}

String  Client::getNickname() const {
    return _nickname;
}

String  Client::getUsername() const {
    return _username;
}

String  Client::getRealname() const {
    return _realname;
}

String  Client::getHostname() const {
    return _hostname;
}

String  Client::getMsg() const {
    return _msg;
}
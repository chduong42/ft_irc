#include "Client.hpp"

Client::Client(int sockfd, std::string hostname) : _sockfd(sockfd), _hostname(hostname) {}

Client::~Client() {}

void    Client::debug() {
    std::cout << "[" << _sockfd << "]" << std::endl;
    std::cout << "[" << _hostname << "]" << std::endl;
    std::cout << "[" << _nickname<<"]" << std::endl;
}

void    Client::reply(String msg) {
    String prefix = _nickname + (_username.empty() ? "" : "!" + _username) + (_hostname.empty() ? "" : "@" + _hostname);
    String paquet = ":" + prefix + " " + msg + "\r\n";
    if (send(_sockfd, paquet.c_str(), paquet.length(), 0) < 0)
        throw(std::out_of_range("Error while sending"));
}

void    Client::welcome() {
    reply("001 " + _nickname + " :Welcome " +_nickname +  " into our irc network");
}

int     Client::getFd() const {return _sockfd;}
String  Client::getNickname() const {return _nickname;}
String  Client::getUsername() const {return _username;}
String  Client::getRealname() const {return _realname;}
String  Client::getHostname() const {return _hostname;}
String  Client::getMsg() const {return _msg;}

void  Client::setNickname(String newName) {_nickname = newName;}
void  Client::setUsername(String newName) {_username = newName;}
void  Client::setRealname(String newName) {_realname = newName;}
void  Client::setHostname(String newName) {_hostname = newName;}
void  Client::setMsg(String newMsg) {_msg = newMsg;}


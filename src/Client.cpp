#include "Client.hpp"

Client::Client(int sockfd, std::string nickname, std::string Clientname) 
    : _sockfd(sockfd), _nickname(nickname), _Clientname(Clientname)
{
    
}

Client::~Client()
{
}
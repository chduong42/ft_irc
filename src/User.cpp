#include "User.hpp"

User::User(int sockfd, std::string nickname, std::string username) : _sockfd(sockfd), _nickname(nickname), _username(username)
{
}

User::~User()
{
}
#ifndef USER_HPP
# define USER_HPP
#include <iostream>

class User
{
private:
	int			_sockfd;
	std::string _nickname;
	std::string _username;
	User();
public:
	User(int _sockfd, std::string nickname, std::string username);
	~User();
};

#endif
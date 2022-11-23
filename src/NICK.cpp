#include "Server.hpp"

/*bool	Server::setNickname(Client &client, String const &params)
{
	String	nickname;

	nickname = params;



	return true;
}
*/
int Server::cmdNick(std::vector<String> pass, Client cl) {
	std::cout << "Je parse NICK" << std::endl;
	(void)cl;
	(void)pass;
	return 0;
}

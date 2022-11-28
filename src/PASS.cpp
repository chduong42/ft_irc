#include "Server.hpp"

String	erasebr(String str) {
	if (str[str.size() - 1] == '\r')
		return str.substr(0, (str.size() - 1));
	return str;
}

String	ERR_PASSWDMISMATCH(Client &client) {
	return ("464 " + client.getNickname() + " :Password incorrect");
}

String	ERR_NEEDMOREPARAMS(Client &client, String cmd) {
	return ("461 " + client.getNickname() + " " + cmd + " :Not enough parameters");
}

int		teststring(String test)
{
	const char *tst = test.c_str();
	int		i = 0;
	while (tst[i])
	{
		if (tst[i] == '\r')
		{
			std::cout << "charatere numero : " << i << " RETOUR A LA LIGNE\n";
			return (1);
		}
		i++;
	}
	return 0;
}

//enlever le /r de pass

int Server::cmdPass(std::vector<String> pass, Client &cl) {
	std::cout << "Je parse PASS" << std::endl;
	//std::cout << pass.size() << std::endl;
	
	if (pass.size() < 2)
	{
		cl.reply(ERR_NEEDMOREPARAMS(cl, "PASS"));
		return -1;
	}
	String mdp = erasebr(pass[1]); // enleve le \r a la fin de pass
	if (mdp != _password)
	{
		std::cout <<"pass[1] : " << "[" << mdp << "]"<< std::endl;
		std::cout << "password : " << "[" << _password << "]" << std::endl;
		teststring(pass[1]);
		cl.reply(ERR_PASSWDMISMATCH(cl));
		return -1;
	}
	cl.setState(LOGIN);
	return 0;
}

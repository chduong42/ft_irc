#include "Channel.hpp"
#include "Server.hpp"

Channel::Channel(String Name) : _name(Name), _topic(), _fdOp(0) {}

Channel::~Channel(){}

std::vector<Client>		&Channel::getClients(){return _clients;}
String					Channel::getName() const {return _name;}
String					Channel::getTopic() const {return _topic;}
int						Channel::getFdOp() const {return _fdOp;}

void					Channel::setTopic(String newTopic) {_topic = newTopic;}
void					Channel::setFdOp(int fd) {_fdOp = fd;}
void					Channel::addClient(Client &cl) {_clients.push_back(cl);}

std::string     RPL_PART(std::string prefix, std::string name_chan) {
	return (prefix + " PART :" + name_chan);
}

void    Channel::eraseClient(Client &cl)
{
	std::vector<Client>::iterator   it;
	for(it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << it->getNickname() << "==" << cl.getNickname() << std::endl;
		if (it->getNickname() == cl.getNickname())
		{
			std::cout << "erasing client" << std::endl;
			broadcast(RPL_PART(cl.getPrefix(), _name));
			_clients.erase(it);
			return ;
		}
	}
	std::cout << "not realy erasing client" << _clients.size() << std::endl;
}

void                    Channel::broadcast(std::string message)
{
	message += "\r\n";
	std::cout << "----> " << message << std::endl;
	for (unsigned int i = 0; i < _clients.size(); i++)
	{
		if (send(_clients[i].getFd(), message.c_str(), message.length(), 0) < 0)
			throw std::out_of_range("error while broadcasting");
	}
}

void                    Channel::broadcast(std::string message, Client &cl)
{
	message += "\r\n";
	for (unsigned int i = 0; i < _clients.size(); i++)
	{
		if (cl.getFd() != _clients[i].getFd())
		{
			if (send(_clients[i].getFd(), message.c_str(), message.length(), 0) < 0)
				throw std::out_of_range("error while broadcasting");
		}
	}
}

void          Channel::debug()
{
	for (unsigned int i = 0; i < _clients.size(); i++)
	{
		std::cout << "#client " << i << " " << _clients[i].getNickname() << std::endl;
	}
}




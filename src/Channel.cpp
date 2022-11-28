#include "Channel.hpp"
#include "Server.hpp"

Channel     &Server::findChannel(std::string name)
{
    for (unsigned int i = 0; i < _channels.size(); i++)
    {
        if (_channels[i].getName() == name)
            return (_channels[i]);
    }
    throw (std::out_of_range("didnt find channel"));
}


Channel::Channel(String Name) : _name(Name){}

Channel::~Channel(){}

std::vector<Client>     &Channel::getClients(){return _clients;}

String                  Channel::getName() const {return _name;}

void                    Channel::addClient(Client &cl)
{
    _clients.push_back(cl);
}

void                    Channel::eraseClient(Client &cl)
{
    std::vector<Client>::iterator   it;
    for(it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->getNickname() == cl.getNickname())
        {
            _clients.erase(it);
            return ;
        }
    }
}

void                    Channel::broadcast(std::string message)
{
    for (unsigned int i = 0; i < _clients.size(); i++)
    {
        _clients[i].reply(message);
    }
}




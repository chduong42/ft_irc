#include "Channel.hpp"

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




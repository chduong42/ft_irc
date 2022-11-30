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

std::vector<Channel>::iterator Server::findChannelIt(std::string name)
{
    std::vector<Channel>::iterator  ret = _channels.begin();
    std::vector<Channel>::iterator  it_end = _channels.end();
    while (ret != it_end)
    {
        if (ret->getName() == name)
            return (ret);
        ret++;
    }
    throw (std::out_of_range("didnt find channel"));
}

void    Server::eraseClientChannel(Client &cl)
{
    for (unsigned int i = 0; i < _channels.size(); i++)
    {
        _channels[i].eraseClient(cl);
    }

    std::vector<Channel>::iterator   it = _channels.begin();
    while (it != _channels.end())
    {
        if (it->getClients().empty())
            it = _channels.erase(it);
        else
            it++;
    }
    std::cout << "eraseClientChannel" << std::endl;
}

Channel::Channel(String Name) : _name(Name){}

Channel::~Channel(){}

std::vector<Client>     &Channel::getClients(){return _clients;}

String                  Channel::getName() const {return _name;}

void                    Channel::addClient(Client &cl) {_clients.push_back(cl);}

std::string     RPL_PART(std::string prefix, std::string name_chan)
{
    return (":" + prefix + " PART :" + name_chan);
}

void                    Channel::eraseClient(Client &cl)
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




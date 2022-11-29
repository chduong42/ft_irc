#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel;

# include "Client.hpp"
# include "Server.hpp"

class Channel 
{
    private:
        std::string                  _name;
        std::vector<Client>     _clients;
    public:
        Channel(std::string _name);
        ~Channel();

        std::string  getName()       const;
        std::vector<Client>     &getClients();
        void                    addClient(Client &client);
        void                    eraseClient(Client &cl);
        void                    broadcast(std::string message);
        void                    broadcast(std::string message, Client &cl);




};

#endif
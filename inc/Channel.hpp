#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel;

# include "Client.hpp"
# include "Server.hpp"

class Channel 
{
    private:
        String                  _name;
        std::vector<Client>     _clients;
    public:
        Channel(String _name);
        ~Channel();

        String  getName()       const;
        std::vector<Client>     &getClients();
        void                    addClient(Client &client);
        void                    eraseClient(Client &cl);
        void                    broadcast();



};

#endif
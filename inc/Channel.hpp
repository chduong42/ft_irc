#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel;

# include "Client.hpp"
# include "Server.hpp"

class Channel 
{
    private:
        std::string                  _name;
        std::vector<Client>          _clients;
        std::string                  _topic;
    public:
        Channel(std::string _name);
        ~Channel();

        std::string             getName() const;
        std::vector<Client>     &getClients();
        std::string             getTopic() const;
        void                    addClient(Client &client);
        void                    eraseClient(Client &cl);
        void                    broadcast(std::string message);
        void                    broadcast(std::string message, Client &cl);
        void                debug();

};

#endif
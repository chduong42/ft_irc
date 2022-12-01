#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "Client.hpp"
# include "Server.hpp"

typedef std::string String;

class Channel 
{
	private:
		String						_name;
		String						_topic;
		int							_fdOp;
		std::vector<Client>			_clients;

	public:
		Channel(std::string _name);
		~Channel();

		int						getFdOp() const; 
		String					getName() const;
		String					getTopic() const;
		std::vector<Client>		&getClients();

		void					setTopic(String newTopic);
		void					setFdOp(int fd);
		
		void					addClient(Client &client);
		void					eraseClient(Client &cl);
		void					broadcast(std::string message);
		void					broadcast(std::string message, Client &cl);
		void					debug();
};

#endif
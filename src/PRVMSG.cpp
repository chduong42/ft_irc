#include "Server.hpp"

String      getMessage(std::vector<String> params)
{
    String message;

    unsigned int i = 3;
    message = params[2];
    if (message[0] == ':')
        message = message.substr(1);
    while (i < params.size())
    {
        message += " ";
        message += params[i];
        i++;
    }
    message = message.substr(0, message.size() - 1); //enleve le \r
    return message;

}
//Faire le neddmoreparams
int Server::cmdPrvMsg(std::vector<String> params, Client &cl)
{
    std::cout << "ENTER IN PRIVMSG" << std::endl;
    if (!cl.getFd())
        return -1;
    if (params.size() < 2)
        return -1;
    try
    {
        Client  recipient = findClient(params[1]);      
        String  msg = getMessage(params);
        std::cout << "message = " << "[" << msg << "]" << std::endl;
        /* code */
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    

    return 0;
}
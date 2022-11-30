#include "Server.hpp"

int         Server::cmdPart(std::vector<String> params, Client &cl)
{
    if (cl.getState() != REGISTERED){
        cl.reply("u need to register first");
        return -1;
    }
    if (params.size() < 2)
    {
        //errneedmorparams
        return -1;
    }
    try
    {
        String chan_name = erasebr(params[1]);
        std::vector<Channel>::iterator chan = findChannelIt(chan_name);
        chan->eraseClient(cl);
    }
    catch(const std::exception& e)
    {
        cl.reply(" no such channel");
    }
    
    return 0;
}
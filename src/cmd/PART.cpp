#include "Server.hpp"

int         Server::cmdPart(std::vector<String> params, Client &cl)
{
    if (cl.getState() != REGISTERED){
        cl.reply("u need to register first");
        return -1;
    }
    if (params.size() < 2)
    {
        cl.reply("error : PART :need more params");//errneedmorparams
        return -1;
    }
    try
    {
        String chan_name = erasebr(params[1]);
        std::vector<Channel>::iterator chan = findChannelIt(chan_name);
        if (chan->getFdOp() == cl.getFd())
            chan->setFdOp(0);
        chan->eraseClient(cl);
        if (chan->getClients().empty())
            _channels.erase(chan);
    }
    catch(const std::exception& e)
    {
        cl.reply(" no such channel");
    }
    
    return 0;
}
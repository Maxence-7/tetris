#pragma once
#include "NetworkCore.hpp"
#include "../game/GameCore.hpp"


#include <map>


class ClientCore : public NetworkCore
{
private:
    sf::TcpSocket m_sock; 
    std::map<sf::IpAddress, std::string> m_names;
    std::map<sf::IpAddress, GameCore> m_games;
public:

    ClientCore(const std::string, const NetworkCore::port_t);
    ~ClientCore();

    bool initConnection(sf::IpAddress);
    inline virtual void onAwait() {

        sf::Packet pack;
        m_sock.receive(pack);
        int tmp;
        pack >> tmp;
        if (((PacketHeader) tmp) == PacketHeader::SHAPES) {
            pack >> m_curShape >> m_nextShape;
        } 


        sf::Packet sendPack;
        sendPack << PacketHeader::GAME << *this; 
        m_sock.send(sendPack);
        
        
        receiveAllGames();
    }  
    bool receiveAllGames();    
};
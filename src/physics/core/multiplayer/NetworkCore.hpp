#pragma once
#include "SFML/Network.hpp"
#include "../game/GameCore.hpp"
#include <array>
#include <string>
#include <memory>

class NetworkCore : public GameCore
{
public:
    using port_t = unsigned short;
    const static port_t DEFAULT_PORT;
protected:
    sf::IpAddress m_myIp = sf::IpAddress::getPublicAddress();
    const port_t m_port; 
    const std::string m_name; 
public:

    enum PacketHeader {ALL_GAMES,GAME,SHAPES,QUIT,SIZE};

    NetworkCore(); 
    explicit NetworkCore(const port_t port);
    NetworkCore(const std::string name);
    NetworkCore(const std::string name, const port_t port);
    explicit NetworkCore(GameCore::Size_t size);
    NetworkCore(GameCore::Size_t size, const port_t port);
    NetworkCore(GameCore::Size_t size, const std::string name);
    NetworkCore(GameCore::Size_t size, const std::string name, const port_t port);
    ~NetworkCore();


    const std::string getName() const;
    const sf::IpAddress getIp() const;
    port_t getPort() const;

};


inline sf::Packet& operator<< (sf::Packet& packet, const sf::IpAddress& ip)
{
    return packet << ip.toInteger();
}
inline sf::Packet& operator >>(sf::Packet& packet, sf::IpAddress& ip)
{
    sf::Uint32 tmp;
    packet >> tmp;
    ip = sf::IpAddress(tmp);
    return packet;
}


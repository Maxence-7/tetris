#pragma once
#include "NetworkCore.hpp"
#include <vector>

class ServerCore : public NetworkCore {

    using size_t = unsigned; // Override size_t (std::size_t can't be sent using sfml networking, size_t have a non constant number of bits depending on the computer )
private:
    size_t m_n;
    std::vector<sf::TcpSocket> m_sockets;
    std::map<sf::IpAddress, std::string> m_names;
    std::map<sf::IpAddress, GameCore> m_games;
    sf::SocketSelector m_selector;
    
public:
    ServerCore(GameCore::Size_t size,size_t n) : NetworkCore(size), m_n(n), m_sockets(std::vector<sf::TcpSocket>(n)) {};
    ServerCore(GameCore::Size_t size, const port_t port,size_t n) : NetworkCore(size,port), m_n(n),m_sockets(std::vector<sf::TcpSocket>(n)) {};
    ServerCore(GameCore::Size_t size, const std::string name, const port_t port, size_t n) : NetworkCore(size,name,port), m_n(n),m_sockets(std::vector<sf::TcpSocket>(n)) {};
    ~ServerCore() {};

    bool connectToClients();

    private: 
        inline virtual void onAwait() {
            this->switchShape();
            sf::Packet pack;
            pack << PacketHeader::SHAPES << m_curShape << m_nextShape;
            sendToAll(pack);

            awaitForAllGameUpdates();
            
            sendAllGamesToAll();

        }
        
        void sendAllGamesToAll();
        void awaitForAllGameUpdates();
        void sendToAll(sf::Packet&);



};

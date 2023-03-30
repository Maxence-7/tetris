#include "ClientCore.hpp"

ClientCore::ClientCore(const std::string name, const NetworkCore::port_t port) : NetworkCore(name, port) {};
ClientCore::~ClientCore() {};

 bool ClientCore::initConnection(sf::IpAddress target) {
        sf::Socket::Status status = m_sock.connect(target,m_port);
        if (status == sf::Socket::Done) {
            int tmp; 
            sf::Packet pack;
            m_sock.receive(pack);
            pack >> tmp;
            if ((PacketHeader) tmp == PacketHeader::SIZE) { 
                pack >> m_size;
            } else {
                return false;
            }
            
            sf::Packet namePack;
            namePack << m_name;
            m_sock.send(namePack);
            receiveAllGames();
            std::cout << "Connected !" << std::endl;
            return true;
        } 
        
        std::cout << " A problem occured while connecting to " << target << std::endl;
        return false;
    }


bool ClientCore::receiveAllGames() {
    int tmp;
    sf::Packet allGamePacket;
    m_sock.receive(allGamePacket);
    allGamePacket >> tmp;
    if (((PacketHeader) tmp) == PacketHeader::ALL_GAMES) {
        sf::IpAddress ip;
        while (!(allGamePacket >> ip)) {
            if (ip != m_myIp) {
                allGamePacket >> m_games[ip];
            } else {
                GameCore gc; 
                allGamePacket >> gc;
            }
        }
        return true;
    }
    return false;

}
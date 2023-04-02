#include "ServerCore.hpp"

bool ServerCore::connectToClients() {
    sf::TcpListener listener;
    std::cout << "Listening on port "<<m_port<< " on ip "<< sf::IpAddress::getLocalAddress()<<std::endl;
    if (listener.listen(m_port) != sf::Socket::Done) {
        std::cout << "Can't listen on this port" << std::endl;
        return false;
    } else {
        size_t rank = 0;
        while (rank < m_n) {
            
            if (listener.accept(m_sockets[rank]) != sf::Socket::Done ) {
                std::cout << "Can't establish connection with "<< m_sockets[rank].getRemoteAddress() << std::endl; 
                return false;
            } else {
                std::cout << "Connection established with "<< m_sockets[rank].getRemoteAddress() << std::endl;
                m_selector.add(m_sockets[rank]);

                sf::Packet sendPack;
                sendPack << ((unsigned) SIZE) << m_size;
                m_sockets[rank].send(sendPack);
                

                sf::IpAddress ip = m_sockets[rank].getRemoteAddress();
                m_games.insert(std::make_pair(ip,GameCore(m_size)));
                m_games[ip].setCurrentShape(m_curShape);
                m_games[ip].setNextShape(m_nextShape);
                

                std::string name;
                sf::Packet namePack;
                m_sockets[rank].receive(namePack);
                namePack >> name;
                m_names.insert(std::make_pair(ip,name));
                rank++;
            }
        }
        sendAllGamesToAll();
        return true;
    }
}


void ServerCore::sendAllGamesToAll() {
    sf::Packet sendPack;
    sendPack << PacketHeader::ALL_GAMES << this->m_myIp << *this;

    for (auto const& [key,game] : m_games) {
        sendPack << key << game;
    } 

    sendToAll(sendPack);
}

void ServerCore::awaitForAllGameUpdates() {
    size_t nbResponses = 0;
    while (nbResponses < m_n) {
        if (m_selector.wait(sf::seconds(1))) {
            for (auto& sock : m_sockets) {
                if (m_selector.isReady(sock)) {
                    sf::Packet pack;
                    sock.receive(pack);
                    int tmp; 
                    pack >> tmp;
                    if ((PacketHeader) tmp == PacketHeader::GAME) {
                        pack >> m_games[sock.getRemoteAddress()];
                        nbResponses++;
                    } else if ((PacketHeader) tmp == PacketHeader::QUIT) {
                        //m_games[sock.getRemoteAddress()] = NULL;
                        nbResponses++;

                    } else {
                        std::cout <<" PROB" << std::endl;
                    }
                }
            }
        }
    }
    
}

void ServerCore::sendToAll(sf::Packet& pack) {
    for (size_t i = 0; i < m_n; i++) {
        m_sockets[i].send(pack);
    }
}
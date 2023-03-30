#include "NetworkCore.hpp"


const NetworkCore::port_t NetworkCore::DEFAULT_PORT = 50937;

NetworkCore::NetworkCore() : GameCore(), m_port(NetworkCore::DEFAULT_PORT), m_name(m_myIp.toString()) {};
NetworkCore::NetworkCore(const NetworkCore::port_t port) : GameCore(), m_port(port), m_name(m_myIp.toString()) {};
NetworkCore::NetworkCore(const std::string name) : GameCore(), m_port(DEFAULT_PORT), m_name(name) {};
NetworkCore::NetworkCore(const std::string name, const port_t port) : GameCore(), m_port(port), m_name(name) {};
NetworkCore::NetworkCore(GameCore::Size_t size) : GameCore(size), m_port(DEFAULT_PORT), m_name(m_myIp.toString()) {};
NetworkCore::NetworkCore(GameCore::Size_t size, const NetworkCore::port_t port) : GameCore(size), m_port(port), m_name(m_myIp.toString()) {};
NetworkCore::NetworkCore(GameCore::Size_t size, const std::string name) : GameCore(size), m_port(DEFAULT_PORT), m_name(name) {};
NetworkCore::NetworkCore(GameCore::Size_t size, const std::string name, const NetworkCore::port_t port) : GameCore(size), m_port(port), m_name(name) {};
NetworkCore::~NetworkCore() {};

const std::string NetworkCore::getName() const {
    return m_name;
}

const sf::IpAddress NetworkCore::getIp() const {
    return m_myIp;
}

NetworkCore::port_t NetworkCore::getPort() const {
    return m_port;
}
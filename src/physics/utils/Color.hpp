#pragma once
#include <SFML/Network.hpp>
class Color {
    public:
        using Color_t = double; 
        friend class sf::Packet;
    public:
        Color_t r;
        Color_t g; 
        Color_t b;
    public:
        Color();
        Color(Color_t,Color_t,Color_t);
        ~Color();

};

inline sf::Packet& operator<< (sf::Packet& packet, const Color& col)
{
    return packet << col.r << col.g << col.b;
}


inline sf::Packet& operator >>(sf::Packet& packet, Color& col)
{
    return packet >> col.r >> col.g >> col.b;
}

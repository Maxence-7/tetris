#include "Color.hpp"

Color::Color() : r(0), g(0), b(0) {}
Color::Color(Color_t r, Color_t g, Color_t b) :r(r), g(g), b(b) {} 
Color::~Color() {}


sf::Packet& operator << (sf::Packet& packet, const Color& col)
{
    return packet << col.r << col.g << col.b;
}


sf::Packet& operator >> (sf::Packet& packet, Color& col)
{
    return packet >> col.r >> col.g >> col.b;
}

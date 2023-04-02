#pragma once
#include <SFML/Network.hpp>
/**
 * @brief Color Class stand to represent RGB color system. 
 * Here, RGB color are encoded between 0 to 1 values used by OpenGL. 
 * @attention There is no check at all to verify R,G and B values are between 0 and 1. This is the Developer responsability to instanciate a correct Color Object.  
 */
class Color {
    public:
        using Color_t = double; 
        friend class sf::Packet;
    public:
        Color_t r;
        Color_t g; 
        Color_t b;
    public:
        
        /**
         * @brief Default constructor, will create perfect black color.
         */
        Color();

        /**
         * @brief Default constructor, will create perfect black color.
         * @param r : Value of the red component between 0 and 1.
         * @param g : Value of the green component between 0 and 1.
         * @param b : Value of the blue component between 0 and 1.
         */
        Color(Color_t,Color_t,Color_t);

        ~Color();


        /**
         * @brief Compatibility with SFML Networking. 
         * @param pack : An SFML packet 
         * @param col : Color to be added to the packet.
         * @return Updated SFML Packet with data of the BlockContainer append to it.
         */
        friend sf::Packet& operator<< (sf::Packet&, const Color&);

        /**
         * @brief Compatibility with SFML Networking. 
         * @param pack : An SFML packet with a BlockContainer to be extracted. 
         * @param col : extacted Color from the Packet
         * @return Updated SFML Packet without the data of the Color.
         */
        friend sf::Packet& operator >>(sf::Packet&, Color&);

};
#pragma once
#include <type_traits>
#include <SFML/Network.hpp>   


template<typename T>
class Vector3D {
    public:
        using Coordinate_t = T;
        T x;
        T y;
        T z;
        Vector3D() : x(0), y(0), z(0) {};
        Vector3D(const Vector3D<Coordinate_t>&) = default;

        /**
         * @brief Casting operator
         * @tparam newType 
         * @param vec : A vector with an other type
         */
        template<typename U>
        Vector3D(const Vector3D<U>& vec) : x(static_cast<Coordinate_t>(vec.x)), y(static_cast<Coordinate_t>(vec.y)), z(static_cast<Coordinate_t>(vec.z)) {};
        Vector3D(Coordinate_t x,Coordinate_t y,Coordinate_t z) : x(x), y(y), z(z) {};
        ~Vector3D() = default;

        template<typename U>
        Vector3D& operator = (const Vector3D<U>& vec) {
            this->x = static_cast<Coordinate_t>(vec.x);
            this->y = static_cast<Coordinate_t>(vec.y);
            this->z = static_cast<Coordinate_t> (vec.z);
            return *this;
        }

        Vector3D<Coordinate_t> operator + (const Vector3D<Coordinate_t>& pos) const {
            return Vector3D<Coordinate_t>(x+pos.x,y+pos.y,z+pos.z);
        }

        Vector3D<Coordinate_t> operator- (const Vector3D<T>& pos) const {
            return Vector3D<Coordinate_t>(x-pos.x,y-pos.y,z-pos.z);
        }

        Vector3D<Coordinate_t> operator- () const {
            return Vector3D<Coordinate_t>(-x,-y,-z);
        }

        Vector3D<Coordinate_t>& operator+= (const Coordinate_t nb) {
            this->x += nb;
            this->y += nb;
            this->z += nb;
            return *this;
        }

        Vector3D<Coordinate_t>& operator+= (const Vector3D<Coordinate_t>& pos) {
            this->x += pos.x;
            this->y += pos.y;
            this->z += pos.z;
            return *this;
        }

        Vector3D<Coordinate_t>& operator-= (const Coordinate_t nb) {
            this->x -= nb;
            this->y -= nb;
            this->z -= nb;
            return *this;
        }

        Vector3D<Coordinate_t>& operator-= (const Vector3D<Coordinate_t>& pos) {
            this->x -= pos.x;
            this->y -= pos.y;
            this->z -= pos.z;
            return *this;
        }

        Vector3D<Coordinate_t>& operator*= (const Coordinate_t nb) {
            this->x *= nb;
            this->y *= nb;
            this->z *= nb;
            return *this;
        }

        Vector3D<Coordinate_t>& operator/= (const Coordinate_t nb) {
            this->x /= nb;
            this->y /= nb;
            this->z /= nb;
            return *this;
        }

        Coordinate_t operator * (const Vector3D<Coordinate_t>& pos) const {
            return x*pos.x + y*pos.y + z*pos.z;
        }

        template <typename U>
        bool operator == (const Vector3D<U>& pos) const {
            if (std::is_same<Coordinate_t,U>::value) {
                return x==pos.x && y==pos.y && z==pos.z;
            }
            return false;
        }

        bool operator < (const Vector3D<Coordinate_t>& pos) const {
            if (x >= pos.x)
            {
                if (y >= pos.y)
                {
                    if (z >= pos.z) {
                        return false;
                    }
                }
                
            }
            return true;
        }

    /**
     * @brief Compatibility with SFML Networking. 
     * @tparam Type for Vector
     * @param pack : An SFML packet 
     * @param vec : Vector to be added to the packet.
     * @return Updated SFML Packet with data of the Vector append to it.
     */
    template<typename U>
    friend sf::Packet& operator <<(sf::Packet& pack, const Vector3D<U>& vec);
    /**
     * @brief Compatibility with SFML Networking. 
     * @tparam Type for vector
     * @param pack : An SFML packet with a Vector with type U to be extracted. 
     * @param vec : extacted Vector with type U from the Packet
     * @return Updated SFML Packet without the data of the Vector.
     */
    template<typename U>
    friend sf::Packet& operator >>(sf::Packet& pack, Vector3D<U>& vec);
};      
        
template<typename U>
sf::Packet& operator <<(sf::Packet& pack, const Vector3D<U>& vec) {
    return pack << vec.x << vec.y << vec.z;
} 

template<typename U>
sf::Packet& operator >>(sf::Packet& pack, Vector3D<U>& vec) {
    return pack >> vec.x >> vec.y >> vec.z;
}
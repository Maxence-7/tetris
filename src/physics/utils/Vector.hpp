#pragma once
#include<array>
/* template<typename T> requires std::integral<T> */

class Vector {
    public:
        using Coordinate_t = int;
    public:
        Coordinate_t x;
        Coordinate_t y;
        Coordinate_t z;
    public:


        // Constructors
        Vector() {}
        Vector(Coordinate_t x, Coordinate_t y, Coordinate_t z) : x(x), y(y), z(z) {};

        template<typename T> requires std::integral<T>
        explicit Vector(std::array<T,3> arr) {Vector(arr[0],arr[1],arr[2]);}

        template<typename T> requires std::integral<T>
        explicit Vector(T arr[3]) {Vector(arr[0],arr[1],arr[2]);}

        ~Vector() {}

        /*static const Vector& UnitVector_X(1,0,0);
        static const Vector& UnitVector_Y(0,1,0);
        static const Vector& UnitVector_Z(0,0,1);*/ 

        Vector operator+ (const Vector& pos) const {
            return Vector(x+pos.x,y+pos.y,z+pos.z);
        }

        Vector operator- (const Vector& pos) const {
            return Vector(x-pos.x,y-pos.y,z-pos.z);
        }

        Vector operator- () const {
            return Vector(-x,-y,-z);
        }

        Coordinate_t operator * (const Vector& pos) const {
            return x*pos.x + y*pos.y + z*pos.z;
        }

        /**
         * @brief Comparaison overload. Since using c++20, we don't have to define operator != 
         * @param pos (const Vector&) 
         * @return (bool) Boolean true if all coordinates are the same. If one or multiple coordinates are differents, return false. 
         */
        bool operator == (const Vector& pos) const {
            return x==pos.x && y==pos.y && z==pos.z;
        } 

};


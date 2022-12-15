#include "Vector.hpp"

Vector::Vector() : x(0), y(0), z(0) {}
Vector::Vector(Vector::Coordinate_t x, Vector::Coordinate_t y, Vector::Coordinate_t z) : x(x), y(y), z(z) {}

Vector Vector::operator + (const Vector& pos) const {
    return Vector(x+pos.x,y+pos.y,z+pos.z);
}

Vector Vector::operator- (const Vector& pos) const {
    return Vector(x-pos.x,y-pos.y,z-pos.z);
}

Vector Vector::operator- () const {
    return Vector(-x,-y,-z);
}

Vector::Coordinate_t Vector::operator * (const Vector& pos) const {
    return x*pos.x + y*pos.y + z*pos.z;
}
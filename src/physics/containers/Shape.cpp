#include "Shape.hpp"


Shape::Shape() : m_pos(Vector()), m_data(Shape::Container_t()) {}
Shape::Shape(Vector pos) : m_pos(pos) {}
Shape::Shape(Vector pos, Shape::Container_t data) : m_pos(pos), m_data(data) {}
//Shape::Shape(const Shape&) = default;
Shape::~Shape() {}

/*
Shape Shape::operator =(const Shape& s){
    this->m_data = s.m_data;
    this->m_pos = s.m_pos;
}*/

Shape::operator BlockContainer() const {
    BlockContainer::Container_t map;
    for (auto const& [key,val] : m_data) {
        map.insert(std::make_pair(key+m_pos,val));
    }
    return BlockContainer(map);
}



// Translation move
void Shape::translate(const Vector& v) {
    m_pos = m_pos + v;
}

// Rotation move

void Shape::rotate(Shape::ROTATION_AXIS ax,Shape::ROTATION_DIRECTION dir) {
    Shape::Container_t copy;
    for (const auto& [key, value] : m_data) {
        Vector newKey;
        switch (ax) {
            case ROTATION_AXIS::X:
                newKey.x = key.x;
                newKey.y = -((Vector::Coordinate_t) dir)*key.z;
                newKey.z = ((Vector::Coordinate_t) dir)*key.y;
                break;
            case ROTATION_AXIS::Y:
                newKey.x = ((Vector::Coordinate_t) dir)*key.z;
                newKey.y = key.y;
                newKey.z = -((Vector::Coordinate_t) dir)*key.x;
                break;
            case ROTATION_AXIS::Z:
                newKey.x = -((Vector::Coordinate_t) dir)*key.y;
                newKey.y = ((Vector::Coordinate_t) dir)*key.x;
                newKey.z = key.z;
                break;
        }
        //if(!func(getAbsolutePosition(newKey))) return;
        copy.insert(std::make_pair(newKey,value));
    }

    m_data = copy;
}


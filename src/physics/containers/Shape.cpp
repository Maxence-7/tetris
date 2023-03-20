#include "Shape.hpp"


// Shape::Shape() : m_pos(Vector3D<Absolute_t>()), m_data(Shape::Container_t()) {};
Shape::Shape(Vector3D<Absolute_t> pos) : m_pos(pos) {};
Shape::Shape(Vector3D<Absolute_t> pos, Shape::Container_t data) : m_pos(pos), m_data(data) {}
Shape::~Shape() {}



Shape::operator BlockContainer() const {
    BlockContainer::Container_t map;
    for (auto const& [key,val] : m_data) {
        map.insert(std::make_pair(key+m_pos,val));
    }
    return BlockContainer(map);
}



// Translation move
void Shape::translate(const Vector3D<Relative_t>& v) {
    m_pos = Vector3D<Absolute_t>(Vector3D<Relative_t>(m_pos) + v);
}

// Rotation move

void Shape::rotate(Shape::ROTATION_AXIS ax,Shape::ROTATION_DIRECTION dir) {
    Shape::Container_t copy;
    for (const auto& [key, value] : m_data) {
        Vector3D<Relative_t> newKey;
        switch (ax) {
            case ROTATION_AXIS::X:
                newKey.x = key.x;
                newKey.y = -((Relative_t) dir)*key.z;
                newKey.z = ((Relative_t) dir)*key.y;
                break;
            case ROTATION_AXIS::Y:
                newKey.x = ((Relative_t) dir)*key.z;
                newKey.y = key.y;
                newKey.z = -((Relative_t) dir)*key.x;
                break;
            case ROTATION_AXIS::Z:
                newKey.x = -((Relative_t) dir)*key.y;
                newKey.y = ((Relative_t) dir)*key.x;
                newKey.z = key.z;
                break;
        }
        //if(!func(getAbsolutePosition(newKey))) return;
        copy.insert(std::make_pair(newKey,value));
    }

    m_data = copy;
}


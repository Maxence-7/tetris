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

bool Shape::canTranslate(const Vector3D<Relative_t>& translation,const BlockContainer& blocks, const Vector3D<Relative_t>& gridSize) {
    //bool b = true;
    for (auto const& [key, value] : (BlockContainer) *this) {
        Vector3D<Relative_t> translated = Vector3D<Relative_t>(key) + translation;
        if (!((translated.x >= 0 && translated.x < gridSize.x) && (translated.y >= 0 && translated.y < gridSize.y) && (translated.z >= 0))) {
            return false;
        }
    }
    return ! (this->toBlockContainer(translation).isCollidingWith(blocks));
}

// Rotation move

bool Shape::canRotate(ROTATION_AXIS& ax, ROTATION_DIRECTION& dir, const BlockContainer& blocks, const Vector3D<Relative_t>& gridSize) {
    Shape cpy = *this;
    cpy.rotate(ax,dir);
    for (auto const& [key, value] : cpy.m_data) {
        Vector3D<Relative_t> rotated = Vector3D<Relative_t>(key) + Vector3D<Relative_t>(cpy.m_pos);
        if (!((rotated.x >= 0 && rotated.x < gridSize.x) && (rotated.y >= 0 && rotated.y < gridSize.y) && (rotated.z >= 0))) {
            return false;
        }
    }
    return !blocks.isCollidingWith((BlockContainer) cpy);
}

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


Shape Shape::getRandomShape(Vector3D<BlockContainer::Absolute_t> gridSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    Shape::Container_t map;
    int upperBound = 6;
    if (gridSize.y == 1) {
        upperBound = 6;
    }
    std::uniform_int_distribution<char> typeDistrib(0,6);
    std::uniform_int_distribution<char> nbRotDistrib(0,3);

    Color c;
    switch (typeDistrib(gen)) {
        case 0: // Bar
            c = Color(0.1,0.91,0.95);
            map.insert(std::make_pair(Vector3D<Shape::Relative_t>(2,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(-1,0,0),c));
            break;
        case 1: // T
            c = Color(0.66,0.1,0.95);
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,1),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,0),c));             
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(-1,0,0),c));
            break;
        case 2: // -_
            c = Color (0,0,1);
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,1),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,1),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(-1,0,0),c));
            break;
        case 3: // TODO -_
            c = Color(0,0,1);
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,1),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,1),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,0),c));
            break;
        case 4: // L
            c = Color(0.95,0.55,0.10);
            map.insert(std::make_pair(Vector3D<Relative_t>(2,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,1),c));
            break;
        case 5: // L inv 
            c = Color(1,0,0);
            map.insert(std::make_pair(Vector3D<Relative_t>(2,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,-1),c));
            break;
        case 6: // Cube
            c = Color(0.95,0.83,0.1);
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,1),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(1,0,0),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,1),c));
            map.insert(std::make_pair(Vector3D<Relative_t>(0,0,0),c));
            break;
        default:
            break;
    }
    
    Shape s(Vector3D<Absolute_t>(floor(gridSize.x/2),floor(gridSize.y/2),gridSize.z+4), map);
    
    for (ROTATION_AXIS ax :  {ROTATION_AXIS::X,ROTATION_AXIS::Y,ROTATION_AXIS::Z}) {
        if (gridSize.y != 1 || ax == ROTATION_AXIS::Y) {
            char nbRot = nbRotDistrib(gen);
            for (char i = 0; i < nbRot; i++) {
                s.rotate(ax,ROTATION_DIRECTION::L);
            }
        }                
    }
    return s;
}

bool Shape::isOccupied(const Vector3D<Absolute_t>& pos) const {
    return ((BlockContainer) *this).isOccupied(pos);   
}

sf::Packet& operator<< (sf::Packet& packet, const Shape& shape)
{
    packet << shape.m_pos << ((unsigned) shape.size());
    for (auto const &[key, value] : shape.m_data) {
        packet << key << value;
    }
    
    return packet;
}


sf::Packet& operator >>(sf::Packet& packet, Shape& shape) {
    unsigned tmp; 
    packet >> shape.m_pos >> tmp;
    size_t size = (size_t) tmp;
    Vector3D<Shape::Relative_t> key;
    Shape::Value_t value;
    for (size_t i = 0; i < size; i++) {
        packet >> key >> value;
        shape.m_data.insert(std::make_pair(key,value));
    }
    return packet;
}

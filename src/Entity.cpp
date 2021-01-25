#include <Entity.hpp>

Entity::Entity(sf::Vector2f pos, sf::Vector2f dir, float r, float s)
: _pos(pos)
, _dir(dir)
, _isAlive(true)
, _radius(r)
, _speed(s)
{
    
}

Entity::~Entity()
{}


void Entity::kill()
{
	_isAlive = false; // setter
}

std::ostream& operator<<(std::ostream& os, const Entity& e) // Parcequ'il faut bien être sujet compliant
{
    os << '(' << e._pos.x << ',' << e._pos.y << ')';
    return os;
}
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
{
	
}

void Entity::update(sf::Time dt)
{
    
}

void Entity::kill()
{
	_isAlive = false;
}
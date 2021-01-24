#include <Character.hpp>

#include <algorithm>

Character::Character(sf::Vector2f pos, sf::Vector2f dir, int health, float r, float s)
: Entity(pos, dir, r, s)
, _health(health)
{}

Character::~Character() {}

void Character::takeDamage(int damage)
{
	_health = std::max(_health-damage, 0);
	if(_health==0)
		_isAlive=false;
}

bool Character::isVisible() const
{
	if (_pos.x<1600 && _pos.x>0 && _pos.y<900 && _pos.y>0)
	{
		return true;
	}
	return false;
}
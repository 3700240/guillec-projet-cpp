#include <Character.hpp>

Character::Character(sf::Vector2f pos, sf::Vector2f dir, int health, float r, float s)
: Entity(pos, dir, r, s)
, _health(health)
{

}

Character::~Character()
{

}

void Character::takeDamage(int damage)
{
	_health-=damage;
	if(_health<=0)
		_isAlive=false;
}
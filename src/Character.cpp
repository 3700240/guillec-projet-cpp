#include <Character.hpp>

#include <algorithm>

Character::Character(sf::Vector2f pos, sf::Vector2f dir, int health, float r, float s)
: Entity(pos, dir, r, s)
, _health(health)
{}

Character::~Character() {}

void Character::takeDamage(int damage) // subit des dommages
{
	_health = std::max(_health-damage, 0); // on réuit la vie et on vérifie qu'elle ne descend pas en dessous de 0
	if(_health==0)
		_isAlive=false; // si 0 alors kapout
}

bool Character::isVisible() const // est-il visibile ?
{
	if (_pos.x<1600 && _pos.x>0 && _pos.y<900 && _pos.y>0) // si dans l'écran
	{
		return true; // oui
	}
	return false; // sinon on
}
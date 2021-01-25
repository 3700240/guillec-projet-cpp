#include <Projectile.hpp>

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f dir, int damage, float r, float s)
: Entity(pos, dir, r, s)
, _damage(damage)
{}

Projectile::~Projectile()
{}

void Projectile::inflictDamage(Character *c) // pas grand chose à dire
{
	c->takeDamage(_damage);
	_isAlive=false;
}
#include <Bullet.hpp>
#include <ResourceManager.hpp>
#include <cmath>

#include <SFML/Window/Mouse.hpp>

#include <Utility.hpp>

#include <iostream>

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir,  const TextureManager& textures)
: Projectile(pos, dir, 20, 7.f, 800.f)
, _sprite(textures.get(Textures::Bullet))

{
    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
    _sprite.setPosition(_pos);
}

Bullet::~Bullet()
{
	//std::cout << "depassement" << std::endl;
}

void Bullet::update(sf::Time dt)
{
    _pos += _dir*_speed*dt.asSeconds();
    _sprite.setPosition(_pos);
    float angle = std::atan2(_dir.y, _dir.x);
    _sprite.setRotation(toDegree(angle) + 90.f);

    if(_pos.x<0 || _pos.x>1600 || _pos.y<0 || _pos.y>900)
    	_isAlive=false;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}
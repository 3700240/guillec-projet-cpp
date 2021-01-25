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
    sf::FloatRect bounds = _sprite.getLocalBounds(); // Forme du sprite
    _sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f)); // On modifie sont centre de masse pour qu'il soit au milieu du sprite (plus facile à manipuler)
    _sprite.setPosition(_pos); // Position souhaitée
}

Bullet::~Bullet()
{}

void Bullet::update(sf::Time dt)
{
    _pos += _dir*_speed*dt.asSeconds(); // Intégration parl a méthode des rectangles
    _sprite.setPosition(_pos);          // On modifie la pos du sprite
    float angle = std::atan2(_dir.y, _dir.x);       
    _sprite.setRotation(toDegree(angle) + 90.f);   // on met le sprite dans la bonne direction

    if(_pos.x<0 || _pos.x>1600 || _pos.y<0 || _pos.y>900)
    	_isAlive=false;                                     // OUPS, sortie d'écran sans toucher personne donc à supprimer !
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}
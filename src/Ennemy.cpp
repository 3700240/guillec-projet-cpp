#include <Ennemy.hpp>

#include <cmath>

#include <ResourceManager.hpp>
#include <ResourceIdentifier.hpp>
#include <Utility.hpp>

Ennemy::Ennemy(sf::Vector2f pos, sf::Vector2f dir, const TextureManager& textures)
: Character(pos, dir, 100, 32.f, 150.f)
, _sprite(textures.get(Textures::Ennemy))
{
    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
    _sprite.setPosition(_pos);
}

void Ennemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}

void Ennemy::goTo(sf::Vector2f targetPos)
{
    sf::Vector2f relTargetPos = targetPos-_pos;

    float dot = _dir.x*relTargetPos.x + _dir.y*relTargetPos.y;
    float det = _dir.x*relTargetPos.y - _dir.y*relTargetPos.x;

    float angle = toDegree(std::atan2(det, dot));
    float rot = (angle>0) ? std::min(angle, 0.5f) : std::max(angle, -0.5f); 

    _dir = sf::Vector2f(std::cos(toRadian(rot))*_dir.x-std::sin(toRadian(rot))*_dir.y, std::sin(toRadian(rot))*_dir.x+std::cos(toRadian(rot))*_dir.y);

}

void Ennemy::update(sf::Time dt)
{
    _pos += _dir*_speed*dt.asSeconds();
    _sprite.setPosition(_pos);
    float angle = std::atan2(_dir.y, _dir.x);
    _sprite.setRotation(toDegree(angle) + 90.f);
}

bool Ennemy::allowedToFire()
{
    if(isVisible() && std::rand()%100==0)
        return true;
    return false;
}
#include <Player.hpp>

#include <cmath>
#include <algorithm>

#include <ResourceManager.hpp>
#include <ResourceIdentifier.hpp>
#include <Utility.hpp>

#include <iostream>


Player::Player(sf::Vector2f pos, sf::Vector2f dir, const TextureManager& textures)
: Character(pos, dir, 100, 32.f, 100.f)
, _sprite(textures.get(Textures::Plane))
, _cooldown(0)
{
    sf::FloatRect bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
    _sprite.setPosition(_pos);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}

void Player::goTo(sf::Vector2f targetPos)
{
    sf::Vector2f relTargetPos = targetPos-_pos;

    float dot = _dir.x*relTargetPos.x + _dir.y*relTargetPos.y;
    float det = _dir.x*relTargetPos.y - _dir.y*relTargetPos.x;

    float angle = toDegree(std::atan2(det, dot));
    float anglemax = 4.f + (400.f-_speed)/300.f*3.f;
    float rot = (angle>0) ? std::min(angle, anglemax) : std::max(angle, -anglemax); 

    _dir = sf::Vector2f(std::cos(toRadian(rot))*_dir.x-std::sin(toRadian(rot))*_dir.y, std::sin(toRadian(rot))*_dir.x+std::cos(toRadian(rot))*_dir.y);
    _speed = std::max(std::min(2*magnitude(relTargetPos),400.f) ,100.f);
}

void Player::update(sf::Time dt)
{
    if(_cooldown>0)
        --_cooldown;
    _pos += _dir*_speed*dt.asSeconds();
    _sprite.setPosition(_pos);
    float angle = std::atan2(_dir.y, _dir.x);
    _sprite.setRotation(toDegree(angle) + 90.f);
}


bool Player::allowedToFire()
{
    if(_cooldown==0)
    {
        _cooldown = 10;
        return true;
    }
    return false;
}
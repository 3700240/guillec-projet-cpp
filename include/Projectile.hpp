#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

#include <Entity.hpp>
#include <Character.hpp>

class Projectile : public Entity
{
    public:
        Projectile(sf::Vector2f pos, sf::Vector2f dir, int damage, float r, float s);
        virtual ~Projectile()=0;

    public:
        void inflictDamage(Character *c);
        int getDamage() const {return _damage;}

    protected:
        

    protected:
        int _damage;
};

#endif // __PROJECTILE_HPP__
#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

#include <Entity.hpp>
#include <Character.hpp>

class Projectile : public Entity
{
    public:
        Projectile(sf::Vector2f pos, sf::Vector2f dir, int damage, float r, float s); // Constructeur
        virtual ~Projectile()=0;               // Virtual pure

    public:
        void inflictDamage(Character *c);         // Inflige des dégats à un Character (i.e ennemy ou player)
        int getDamage() const {return _damage;}   // Quel sont les degats causes par tel projectile ?

    protected:
        int _damage;                              // Ses dégats
};

#endif // __PROJECTILE_HPP__
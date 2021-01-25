#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <Entity.hpp>

class Character : public Entity
{
    public:
        Character(sf::Vector2f pos, sf::Vector2f dir, int health, float r, float s);
        virtual ~Character()=0;

    public:
        virtual bool allowedToFire()=0;             // Le Character est-il en mesure de tirer ?
        int getHealth() const {return _health;}     // Retourne la vie du Character
        void takeDamage(int damage);                // Le Character subit des dégâts

    protected:
    	bool isVisible() const;                     // Le character est-il visible sur l'écran ?

    private:
        int _health;                                // HP du Character
};

#endif // __CHARACTER_HPP__
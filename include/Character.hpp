#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <Entity.hpp>

class Character : public Entity
{
    public:
        Character(sf::Vector2f pos, sf::Vector2f dir, int health, float r, float s);
        virtual ~Character()=0;


    public:
        virtual bool allowedToFire()=0;
        int getHealth() const {return _health;}
        void takeDamage(int damage);

    protected:
    	bool isVisible() const;

    private:
        int _health;
};

#endif // __CHARACTER_HPP__
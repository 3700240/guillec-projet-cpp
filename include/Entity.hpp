#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <ResourceIdentifier.hpp>


class Entity : public sf::Drawable, sf::Transformable
{

    public:
        Entity(sf::Vector2f pos, sf::Vector2f dir, float r, float s);
        virtual ~Entity()=0;
        virtual void update(sf::Time dt)=0;

    public:
        sf::Vector2f getPos()      const {return _pos;}
        sf::Vector2f getDir()      const {return _dir;}
        float        getSpeed()    const {return _speed;}
        float        getRadius()   const {return _radius;}
        bool         isAlive()     const {return _isAlive;}
        void kill();
   
    protected:
        sf::Vector2f _pos;
        sf::Vector2f _dir;
        bool _isAlive;
        float _radius;
        float _speed;
};

#endif // __ENTITY_HPP__
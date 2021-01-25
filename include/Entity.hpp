#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <iostream>

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
        Entity(sf::Vector2f pos, sf::Vector2f dir, float r, float s);  // Constructeur
        virtual ~Entity()=0;                   // Pour rendre la classe virtual pure
        virtual void update(sf::Time dt)=0;    // Met à jour l'entité

    public:
        sf::Vector2f getPos()      const {return _pos;}     // Ou est l'entité ?
        sf::Vector2f getDir()      const {return _dir;}     // Dans quelle direction va t-elle ?
        float        getSpeed()    const {return _speed;}   // A quelle vitesse ?
        float        getRadius()   const {return _radius;}  // Par quel cercle approxime t-on sa hitbox ?
        bool         isAlive()     const {return _isAlive;} // Est-elle en vie (au sens encore utile) ?
        void kill();                                        // Permet de tuer/détruire une entité

        friend std::ostream& operator<<(std::ostream& os, const Entity& e); // Surcharge de l'opérateur <<
   
    protected:
        sf::Vector2f _pos;             // Sa position
        sf::Vector2f _dir;             // Sa direction
        bool _isAlive;                 // Son état
        float _radius;                 // Son rayon
        float _speed;                  // Sa vitesse
};

#endif // __ENTITY_HPP__
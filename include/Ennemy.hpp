#ifndef __ENNEMY_HPP__
#define __ENNEMY_HPP__

#include <Character.hpp>

class Ennemy : public Character
{
    public:
        Ennemy(sf::Vector2f pos, sf::Vector2f dir, const TextureManager& textures);
        void update(sf::Time dt);
        void goTo(sf::Vector2f targetPos);
        bool allowedToFire();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Nécessaire par héritage de sf::drawable
        sf::Sprite _sprite;                // La texture de l'ennemi

};

#endif // __ENNEMY_HPP__
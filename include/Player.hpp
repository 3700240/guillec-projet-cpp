#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <Character.hpp>

class Player : public Character
{
    public:
        Player(sf::Vector2f pos, sf::Vector2f dir, const TextureManager& textures); // Copnstructeur

    public:
        void update(sf::Time dt);              // Met à jour le joueur
        void goTo(sf::Vector2f targetPos);     // Ordre : va vers targetPos
        bool allowedToFire();                  // Put-il tirer ? (délai rechargement écoulé)

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Nécessaire par héritage de sf::drawable
        sf::Sprite _sprite;                    // Sa texture
        int _cooldown;                         // Temps de rechargement
};

#endif // __PLAYER_HPP__
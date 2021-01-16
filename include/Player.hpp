#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <Character.hpp>

class Player : public Character
{
    public:
        Player(sf::Vector2f pos, sf::Vector2f dir, const TextureManager& textures);
        void update(sf::Time dt);
        void goTo(sf::Vector2f targetPos);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite _sprite;
};

#endif
#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include <Projectile.hpp>

class Bullet : public Projectile
{
    public:
        Bullet(sf::Vector2f pos, sf::Vector2f dir,  const TextureManager& textures);
        ~Bullet();
    public:
        virtual void update(sf::Time dt);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    private:
        sf::Sprite _sprite;

};

#endif // __BULLET_HPP__


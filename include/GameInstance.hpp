#ifndef __GAMEINSTANCE_HPP__
#define __GAMEINSTANCE_HPP__

#include <ResourceManager.hpp>
#include <ResourceIdentifier.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Entity.hpp>
#include <Player.hpp>
#include <Ennemy.hpp>
#include <Bullet.hpp>

#include <list>

class GameInstance
{
    public:
        GameInstance();
        ~GameInstance();
        void run();

    private: // private methods
        void manageEnnemies();
        void manageBullets();
        void manageNewEvents();
        void render();
        void update(sf::Time dt);
        void renderHud();

    private: // private attributes
        sf::RenderWindow _win;
        TextureManager _textures;
        FontManager _fonts;

        Player* _player;
        std::list<Ennemy *> _ennemyList;
        std::list<Bullet *> _bulletList;

        sf::Sprite _background;

        static const sf::Time _frameduration;
};



#endif // __GAMEINSTANCE_HPP__
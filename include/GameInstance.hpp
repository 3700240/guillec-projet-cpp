#ifndef __GAMEINSTANCE_HPP__
#define __GAMEINSTANCE_HPP__

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include <ResourceManager.hpp>
#include <ResourceIdentifier.hpp>

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

        void updateEnnemies();
        void updateBullets();
        void updatePlayer();
        void addBullet(sf::Vector2f pos, sf::Vector2f dir);

        void update(sf::Time dt);

        void render();
        void renderHud();
        void renderEndScreen();
        void renderEntities();

    private: // private attributes
        sf::RenderWindow _win;
        TextureManager _textures;
        FontManager _fonts;
        SoundManager _sounds;

        Player* _player;
        std::list<Ennemy *> _ennemyList;
        std::list<Bullet *> _bulletList;

        sf::Sprite _background;
        sf::Sound  _sound;
        int _score;

        static const sf::Time _frameduration;
};



#endif // __GAMEINSTANCE_HPP__
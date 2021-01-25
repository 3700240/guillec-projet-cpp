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
        GameInstance();               // Constructeur pour créer une nouvelle partie
        ~GameInstance();              // Destructeur (il faut supprimer le contenu des listes, etc)

    public:
        void run();                   // Boucle (infinie) de jeu. En bref on gère les événement, on update() puis on render()
        friend std::ostream& operator<<(std::ostream& os, const GameInstance& e); // Surcharge opérateur << pour afficher des infos sur une partie

    private:
        void manageEnnemies();        // Ajout d'ennemis pour qu'ils soient toujours au nombre de 4
        void manageBullets();         // Ajout des balles tirées par le joueurs / ennemis
        void manageNewEvents();       // I/O, le joueur a t-il fermé la fenêtre ?

        void updateEnnemies();        // Met à jour la position des ennemis, supprime ceux qui sont morts, gère les collisions
        void updateBullets();         // Met à jour la position des balles, supprime ceux qui sont détruits, vérifie si la balle a touché une cible
        void updatePlayer();          // Met à jour la position du joueur

        void addBullet(sf::Vector2f pos, sf::Vector2f dir); // Ajoute une balle à la position / direction souhaitée

        void update(sf::Time dt);

        void render();                // Met à jour l'affichage
        void renderHud();             // Affiche le HUD, i.e le score et les HP
        void renderEndScreen();       // Si le joueur est mort, on affiche GAME OVER
        void renderEntities();        // Affiche les entités

    private:
        sf::RenderWindow _win;                  // Fenêtre SFML pour l'affichage

        TextureManager _textures;               // ResourceManager<sf::Texture, Textures::ID> pour lmes textures
        FontManager _fonts;                     // ResourceManager<sf::Font, Fonts::ID> pour les polices d'écriture
        SoundManager _sounds;                   // ResourceManager<sf::SoundBuffer, Sounds::ID> pour les sons

        Player* _player;                        // Pointeur vers le joueur
        std::list<Ennemy *> _ennemyList;        // CONTAINER des ennemis
        std::list<Bullet *> _bulletList;        // CONTAINER des balles

        sf::Sprite _background;                 // Image de fond
        sf::Sound  _sound;                      // Bruit de tir, etc
        sf::Music  _music;                      // Musique d'ambiance
        int _score;                             // Score du joueur
 
        static const sf::Time _frameduration;   // Durée d'une frame logique, ici égale à 1/60s
};



#endif // __GAMEINSTANCE_HPP__
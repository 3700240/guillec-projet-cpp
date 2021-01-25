#include <GameInstance.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <Bullet.hpp>
#include <Utility.hpp>
#include <Entity.hpp>

const sf::Time GameInstance::_frameduration = sf::seconds(1.f/60.f);

GameInstance::GameInstance()
: _win(sf::VideoMode(1600, 900), "Space Invader v2", sf::Style::Close)
, _textures()
, _fonts()
, _score(0)
{
    std::srand(std::time(nullptr));

    _fonts.load(Fonts::Gameplay, 	 "assets/fonts/gameplay.ttf"); // On charge les polices d'écritures
    
	_textures.load(Textures::Plane,  "assets/textures/plane.png"); // On charge les textures
    _textures.load(Textures::Bullet, "assets/textures/bullet.png");
    _textures.load(Textures::Ennemy, "assets/textures/ennemy.png");
    _textures.load(Textures::Background, "assets/textures/background.png");

    _sounds.load(Sounds::Fire, "assets/sound/fire.ogg");            // On charge les sons

    _player = new Player(sf::Vector2f(800.f,450.f), sf::Vector2f(0.f,1.f), _textures); // Notre joeur (unique)
    
    _background = sf::Sprite(_textures.get(Textures::Background));         // Le fond d'écran

    if (!_music.openFromFile("assets/sound/theme.ogg")) // On charge la musique (pas besoin de manager pour elle car elle est unique)
        throw std::runtime_error("Failed to load assets/sound/theme.ogg"); // Petit problème pendant le chargement ? :(
    _music.play();                      // On lance la musique
    _music.setVolume(255);              // a fond !!
    _music.setLoop(true);               // ad vitam æternam

}

GameInstance::~GameInstance()
{
    while(!_ennemyList.empty()) delete _ennemyList.front(), _ennemyList.pop_front(); // On supprime tous les ennemis
    while(!_bulletList.empty()) delete _bulletList.front(), _bulletList.pop_front(); // idem Bullet
    delete _player; // On supprime le joueur
}

void GameInstance::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(_win.isOpen())
    {
        sf::Time dt = clock.restart(); // Doc: sf::Clock::restart() This function puts the time counter back to zero. It also returns the time elapsed since the clock was started.
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > _frameduration) // On maintient la durée de la frame logique à _frameduration i.e 1/60e sec
        {
            timeSinceLastUpdate -= _frameduration;
            manageNewEvents();                      // I/O clavier, souris
            if(_player->isAlive())                  // si joueur encore en vie
                update(_frameduration);             // on met à jour les entités
        }
        render(); // On affiche ! le taux de rafraichissement est variable lui (aussi élevé que possible!)
    }
}

void GameInstance::manageNewEvents()
{
    sf::Event event;
	while (_win.pollEvent(event))
	{
        switch(event.type)
        {   
            case sf::Event::Closed:             // L'utilisateur a fermé la fenêtre
                _win.close();
                std::cout << *this << std::endl; // Moment honneteté : je ne savais pas quoi faire des surcharges alors affichons l'état de la partie à la fin de l'éxécution !
                break;

            default:
                break;
        }
	}
}

void GameInstance::render()
{
    _win.clear();                   // On remet à zéro le buffer écran
    _win.draw(_background);         // On commence par le fond
 
    renderEntities();               // Puis les entités
    renderHud();                    // puis le HUD
    if(!_player->isAlive())         // Si joueur mort, on rajoute l'écran de fin (GAME OVER)
        renderEndScreen();

    _win.display();                 // On affiche!
}

void GameInstance::renderEntities()
{
    for (Ennemy* e : _ennemyList) // pour chaque ennemi (merci C++ 11)
        _win.draw(*e);            // On l'affiche
    for (Bullet* b : _bulletList) // idem (encore merci)
        _win.draw(*b);
    _win.draw(*_player);          // On affiche le joueur
}

void GameInstance::update(sf::Time dt)
{
    manageBullets();     // Faut il ajouter des balles ?
    manageEnnemies();    // Faut-il ajouter de nouveaux ennemis ?
    updateEnnemies();    // On met à jour les ennemis
    updateBullets();     // On met à jour les balles
    updatePlayer();      // On met à jour le joueur
}


void GameInstance::manageBullets() // Doit on ajouter des balles ?
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _player->allowedToFire()) // Si le joueur veut ET peut tirer
        addBullet(_player->getPos()+40.f*_player->getDir(), _player->getDir()); // Nouvelle balle devant lui

    for (std::list<Ennemy*>::iterator it=_ennemyList.begin(); it!=_ennemyList.end(); ++it) // Pour chaque ennemi
    {
        Ennemy *e = *it;
        if(e->isAlive() && e->allowedToFire())                      // si il peut tirer
            addBullet(e->getPos()+40.f*e->getDir(), e->getDir());   // feu !

    }
}

void GameInstance::addBullet(sf::Vector2f pos, sf::Vector2f dir) // Ajoute une balle à l'emplacement/direction souhaité(e)
{
    _bulletList.emplace_back(new Bullet(pos, dir, _textures));  // une balle de plus dans notre liste
    _sound.setBuffer(_sounds.get(Sounds::Fire));                // On charge le son de tir
    _sound.play(); // pew pew!
}

void GameInstance::manageEnnemies() // faut-il ajouter des ennemis ?
{
    if(_ennemyList.size()<4) // si leur nombre <4 alors oui
    {
        int azimuth = std::rand()%360;                                              // De quelle direction vient notree nouvel ennemi ?
        sf::Vector2f newPos(800.f*unitVector(azimuth)+sf::Vector2f(800.f,450.f));   // Calcul de sa pos de départ
        sf::Vector2f newDir = dirTo(newPos,_player->getPos());                      // on lui donné une direction initiale vers le joueur
        _ennemyList.emplace_back(new Ennemy(newPos, newDir, _textures));            // On l'ajoute à notre liste d'ennemis
    }
}



void GameInstance::updateEnnemies() // mise à jour des ennemis
{   
    // Pour chaque ennemi
    for (std::list<Ennemy*>::iterator it=_ennemyList.begin(); it!=_ennemyList.end(); ++it)
    {
        Ennemy *e = *it;
        if(e->isAlive())
        {
            e->goTo(_player->getPos()); // On change la direction de l'ennemi
            e->update(_frameduration);  // On met à jour sa position

            // Gestion des collisions
            if(distance(e->getPos(), _player->getPos()) < e->getRadius() + _player->getRadius())
            {
                _player->takeDamage(40); // Le joueur prend des dégâts
                e->kill(); // L'ennemi meurt
            }
        }
        else // Garbage collector
        {
            _score++;
            delete(e);
            it = _ennemyList.erase(it);
        }

    }
}

void GameInstance::updateBullets() // Mise à jour des balles
{
    for (std::list<Bullet *>::iterator it=_bulletList.begin(); it!=_bulletList.end(); ++it) // Pour chaque balle
    {
        Bullet *b = *it;
        if(b->isAlive()) // si la balle est active
        {
            b->update(_frameduration);  // Elle avance
            for (std::list<Ennemy*>::iterator it2=_ennemyList.begin(); it2!=_ennemyList.end(); ++it2) // Pour chaque ennemi
            {
                Ennemy *e = *it2;
                if(distance(b->getPos(), e->getPos()) < b->getRadius() + e->getRadius()) // Collision avec un ennemi ?
                {
                    b->inflictDamage(e); // L'ennemi prend des degats
                    b->kill();           // La balle est marquée pour suppression
                }
            }
            if(distance(b->getPos(), _player->getPos()) < b->getRadius() + _player->getRadius()) // Collision avec le joueur ?
            {
                b->inflictDamage(_player); // Le joueur  prend des degats
                b->kill();                 // La balle est marquée pour suppression
            }

        }
        else
        {
            delete(b);                    // Garbage collector : la balle est marquée comme HS dont on la supprime
            it = _bulletList.erase(it);   // et on la retire de la liste
        }

    }
}

void GameInstance::updatePlayer()
{
    _player->goTo((sf::Vector2f) sf::Mouse::getPosition(_win)); // Le joeuur change de direction
    _player->update(_frameduration);                            // il avance
}


void GameInstance::renderHud() // Fonction inintéressante, on affiche le HUD
{
    sf::Text text;
    text.setFont(_fonts.get(Fonts::Gameplay));
    text.setString("HP: " + std::to_string((_player->getHealth())));
    text.setCharacterSize(40);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left, textRect.top);
    text.setFillColor(sf::Color::Red);
    _win.draw(text);

    text.setString("Score: " + std::to_string(_score));
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left+textRect.width, textRect.top);
    text.setPosition(sf::Vector2f(1600.f,0.f));
    _win.draw(text);

    for (Ennemy* e : _ennemyList)
    {
        text.setCharacterSize(12);
        text.setString("HP: " + std::to_string((e->getHealth())));
        textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f - 50.f);
        text.setPosition(e->getPos());
        _win.draw(text);
    }
}

void GameInstance::renderEndScreen() // Fonction inintéressante, on affiche GAME OVER au milieu de l'écran
{
    sf::Text text;
    text.setFont(_fonts.get(Fonts::Gameplay));
    text.setString("GAME OVER");
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(800.f,450.f));
    _win.draw(text);
}

std::ostream& operator<<(std::ostream& os, const GameInstance& g) // Surcharge d'opérateur pour être conforme avec les contraintes ! (sans grande utilité :( )
{
    os << "Score final: " << g._score;
    return os;
}
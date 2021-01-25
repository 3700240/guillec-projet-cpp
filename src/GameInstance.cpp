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

    _fonts.load(Fonts::Gameplay, 	 "assets/fonts/gameplay.ttf");
    
	_textures.load(Textures::Plane,  "assets/textures/plane.png");
    _textures.load(Textures::Bullet, "assets/textures/bullet.png");
    _textures.load(Textures::Ennemy, "assets/textures/ennemy.png");
    _textures.load(Textures::Background, "assets/textures/background.png");

    _sounds.load(Sounds::Fire, "assets/sound/fire.ogg");

    _player = new Player(sf::Vector2f(800.f,450.f), sf::Vector2f(0.f,1.f), _textures);
    
    _background = sf::Sprite(_textures.get(Textures::Background));

    if (!_music.openFromFile("assets/sound/theme.ogg"))
        throw std::runtime_error("Failed to load assets/sound/theme.ogg");
    _music.play();
    _music.setVolume(255);
    _music.setLoop(true);

}

GameInstance::~GameInstance()
{
    while(!_ennemyList.empty()) delete _ennemyList.front(), _ennemyList.pop_front();
    while(!_bulletList.empty()) delete _bulletList.front(), _bulletList.pop_front();
    delete _player;
}

void GameInstance::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(_win.isOpen())
    {
        sf::Time dt = clock.restart(); // Doc: sf::Clock::restart() This function puts the time counter back to zero. It also returns the time elapsed since the clock was started.
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > _frameduration) // logic frame rate is kept constant (equal to 1/__frameduration)
        {
            timeSinceLastUpdate -= _frameduration;
            manageNewEvents();
            if(_player->isAlive())
                update(_frameduration);
        }
        render(); // the rendering rate is variable
    }
}

void GameInstance::manageNewEvents()
{
    sf::Event event;
	while (_win.pollEvent(event))
	{
        switch(event.type)
        {   
            case sf::Event::Closed:
                _win.close();
                break;

            default:
                break;
        }
	}
}

void GameInstance::render()
{
    _win.clear();
    _win.draw(_background);

    renderEntities();
    renderHud();
    if(!_player->isAlive())
        renderEndScreen();

    _win.display();
}

void GameInstance::renderEntities()
{
    for (Ennemy* e : _ennemyList)
            _win.draw(*e);
    for (Bullet* b : _bulletList)
            _win.draw(*b);
    _win.draw(*_player);
}

void GameInstance::update(sf::Time dt)
{
    manageBullets();     // Faut il ajouter des balles ?
    manageEnnemies();    // Faut-il ajouter de nouveaux ennemis ?
    updateEnnemies();    // On met à jour les ennemis
    updateBullets();     // On met à jour les balles
    updatePlayer();      // On met à jour le joueur
}


void GameInstance::manageBullets()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _player->allowedToFire())
        addBullet(_player->getPos()+40.f*_player->getDir(), _player->getDir());

    for (std::list<Ennemy*>::iterator it=_ennemyList.begin(); it!=_ennemyList.end(); ++it)
    {
        Ennemy *e = *it;
        if(e->isAlive() && e->allowedToFire())
            addBullet(e->getPos()+40.f*e->getDir(), e->getDir());

    }
}

void GameInstance::addBullet(sf::Vector2f pos, sf::Vector2f dir)
{
    _bulletList.emplace_back(new Bullet(pos, dir, _textures));
    _sound.setBuffer(_sounds.get(Sounds::Fire));
    _sound.play();
}

void GameInstance::manageEnnemies()
{
    if(_ennemyList.size()<4)
    {
        int azimuth = std::rand()%360;
        sf::Vector2f newPos(800.f*unitVector(azimuth)+sf::Vector2f(800.f,450.f));
        sf::Vector2f newDir = dirTo(newPos,_player->getPos());
        _ennemyList.emplace_back(new Ennemy(newPos, newDir, _textures));
    }
}



void GameInstance::updateEnnemies()
{
    for (std::list<Ennemy*>::iterator it=_ennemyList.begin(); it!=_ennemyList.end(); ++it)
    {
        Ennemy *e = *it;
        if(e->isAlive())
        {
            e->goTo(_player->getPos());
            e->update(_frameduration);

            if(distance(e->getPos(), _player->getPos()) < e->getRadius() + _player->getRadius())
            {
                delete(e);
                it = _ennemyList.erase(it);
                _player->takeDamage(40);
            }
        }
        else
        {
            _score++;
            delete(e);
            it = _ennemyList.erase(it);
        }

    }
}

void GameInstance::updateBullets()
{
    for (std::list<Bullet *>::iterator it=_bulletList.begin(); it!=_bulletList.end(); ++it)
    {
        Bullet *b = *it;
        if(b->isAlive())
        {
            b->update(_frameduration);
            for (std::list<Ennemy*>::iterator it2=_ennemyList.begin(); it2!=_ennemyList.end(); ++it2)
            {
                Ennemy *e = *it2;
                if(distance(b->getPos(), e->getPos()) < b->getRadius() + e->getRadius())
                {
                    b->inflictDamage(e);
                    b->kill();
                }
            }
            if(distance(b->getPos(), _player->getPos()) < b->getRadius() + _player->getRadius())
            {
                b->inflictDamage(_player);
                b->kill();
            }

        }
        else
        {
            delete(b);
            it = _bulletList.erase(it);
        }

    }
}

void GameInstance::updatePlayer()
{
    _player->goTo((sf::Vector2f) sf::Mouse::getPosition(_win));
    _player->update(_frameduration);
}


void GameInstance::renderHud()
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

void GameInstance::renderEndScreen()
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
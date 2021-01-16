#include <GameInstance.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

#include <Bullet.hpp>
#include <Utility.hpp>
#include <Entity.hpp>

const sf::Time GameInstance::_frameduration = sf::seconds(1.f/60.f);

GameInstance::GameInstance()
: _win(sf::VideoMode(1600, 900), "My game", sf::Style::Close)
, _textures()
, _fonts()
{
    //_win.setKeyRepeatEnabled(false);
    _fonts.load(Fonts::Gameplay, 	 "assets/fonts/gameplay.ttf");
    
	_textures.load(Textures::Plane,  "assets/textures/plane.png");
    _textures.load(Textures::Bullet, "assets/textures/bullet.png");
    _textures.load(Textures::Ennemy, "assets/textures/ennemy.png");

    _player = new Player(sf::Vector2f(800.f,450.f), sf::Vector2f(0.f,1.f), _textures);
    
    _ennemyList.push_back(new Ennemy(sf::Vector2f(0.f,200.f), sf::Vector2f(0.f,1.f), _textures));
    _ennemyList.push_back(new Ennemy(sf::Vector2f(200.f,200.f), sf::Vector2f(0.f,1.f), _textures));
    _ennemyList.push_back(new Ennemy(sf::Vector2f(400.f,200.f), sf::Vector2f(0.f,1.f), _textures));
    _ennemyList.push_back(new Ennemy(sf::Vector2f(600.f,200.f), sf::Vector2f(0.f,1.f), _textures));
}

GameInstance::~GameInstance()
{
    std::cout << "cya world\n" << std::endl;
    while(!_ennemyList.empty()) delete _ennemyList.front(), _ennemyList.pop_front();
    while(!_bulletList.empty()) delete _bulletList.front(), _bulletList.pop_front();
    delete _player;
    _win.close();
}

void GameInstance::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(_win.isOpen())
    {
        sf::Time dt = clock.restart(); // Doc: sf::Clock::restart() This function puts the time counter back to zero. It also returns the time elapsed since the clock was started.
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > _frameduration && _player->isAlive()) // logic frame rate is kept constant (equal to 1/__frameduration)
        {
            timeSinceLastUpdate -= _frameduration;
            manageNewEvents();
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

            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                    //std::cout << "Left Click" << std::endl;
                    ;
                else
                {
                    //std::cout << "Right Click" << std::endl;
                    _player->kill();
                }
                break;

            default:
                break;
        }
	}
}

void GameInstance::render()
{
    _win.clear();

    for (Ennemy* e : _ennemyList) {
        //if(e->isAlive())
            _win.draw(*e);
    }

    for (Bullet* b : _bulletList) {
        //if(e->isAlive())
            _win.draw(*b);
    }

    _win.draw(*_player);

    if(!_player->isAlive())
    {
        sf::Text text;
        text.setFont(_fonts.get(Fonts::Gameplay));
        text.setString("GAME OVER");
        text.setCharacterSize(80);
        text.setFillColor(sf::Color::Red);
        _win.draw(text);

    }


    _win.display();
}

void GameInstance::update(sf::Time dt)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        _bulletList.emplace_back(new Bullet(_player->getPos()+30.f*_player->getDir(), _player->getDir(), _textures));

    for (std::list<Ennemy*>::iterator it=_ennemyList.begin(); it!=_ennemyList.end(); ++it)
    {
    //for (Ennemy* e : _ennemyList) {
        Ennemy *e = *it;
        if(e->isAlive())
        {
            e->goTo(_player->getPos());
            e->update(_frameduration);

            if(distance(e->getPos(), _player->getPos()) < e->getRadius() + _player->getRadius())
            {
                delete(e);
                it = _ennemyList.erase(it);
            }
        }
        else
        {
            delete(e);
            it = _ennemyList.erase(it);
        }

    }

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
                    goto destroyed;
                }
            }
            if(distance(b->getPos(), _player->getPos()) < b->getRadius() + _player->getRadius())
            {
                b->inflictDamage(_player);
                goto destroyed;
            }

        }
        else
        {
            destroyed:
            delete(b);
            it = _bulletList.erase(it);
        }

    }

    _player->goTo((sf::Vector2f) sf::Mouse::getPosition(_win));
    _player->update(_frameduration);
}
#ifndef __RESOURCEIDENTIFIER_HPP__
#define __RESOURCEIDENTIFIER_HPP__

namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
        Plane,
        Bullet,
		Ennemy,
		Background

	};
}

namespace Fonts
{
	enum ID
	{
		Gameplay,
	};
}

namespace Sounds
{
	enum ID
	{
		Music,
		Fire
	};
}

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
typedef ResourceManager<sf::SoundBuffer, Sounds::ID> SoundManager;

#endif // __RESOURCEIDENTIFIER_HPP__
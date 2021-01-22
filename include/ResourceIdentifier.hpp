#ifndef __RESOURCEIDENTIFIER_HPP__
#define __RESOURCEIDENTIFIER_HPP__

namespace sf
{
	class Texture;
	class Font;
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

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;

#endif // __RESOURCEIDENTIFIER_HPP__
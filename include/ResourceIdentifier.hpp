#ifndef __RESOURCEIDENTIFIER_HPP__
#define __RESOURCEIDENTIFIER_HPP__

/*
*    Ici, on stocke les identifiants de nos ressources
*    On définit aussi les différents type de Resource Manager dont on a besoin
*/


// Pour dire au compilo que ces classes existent ailleurs
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
		Ennemy,                // EXEMPLE: on peut récupérer la texture de l'ennemi grâce à l'ID Textures::Ennemy
		Background             // Voir constructeur de Ennemy

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

// Ici, on définit de nouveaux types de ResourceManager. Un pour chacun des types de ressources manipulés.

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
typedef ResourceManager<sf::SoundBuffer, Sounds::ID> SoundManager;

#endif // __RESOURCEIDENTIFIER_HPP__
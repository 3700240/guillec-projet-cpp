#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <SFML/System/Vector2.hpp>

// Quelques outils pour manipuler les sf::vector2f, faire de la trigo

float toDegree(float radian); // Explicite
float toRadian(float degree); // Explicite

float magnitude(sf::Vector2f vector);  // Norme d'un vecteur

sf::Vector2f normalized(sf::Vector2f vector); // Retourne un vecteur unitaire d'un veteur donné
sf::Vector2f unitVector(float angle);         // Retourne un vecteur unitaire d'un angle donné

float distance(sf::Vector2f v1, sf::Vector2f v2); // Distance entrre deux points

sf::Vector2f dirTo(sf::Vector2f from, sf::Vector2f to); // Vecteur direction entre deux points

#endif // __UTILITY_HPP__
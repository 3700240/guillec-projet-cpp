#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <SFML/System/Vector2.hpp>

float toDegree(float radian);

float toRadian(float degree);

float magnitude(sf::Vector2f vector);

sf::Vector2f normalized(sf::Vector2f vector);

sf::Vector2f unitVector(float angle);

float distance(sf::Vector2f v1, sf::Vector2f v2);

sf::Vector2f dirTo(sf::Vector2f from, sf::Vector2f to);

#endif // __UTILITY_HPP__
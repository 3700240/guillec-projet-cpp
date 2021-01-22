#include <Utility.hpp>

#include <cassert>
#include <cmath>

float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

float magnitude(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f normalized(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / magnitude(vector);
}

sf::Vector2f unitVector(float angle)
{
	return sf::Vector2f(-std::sin(toRadian(angle)), std::cos(toRadian(angle)));
}

float distance(sf::Vector2f v1, sf::Vector2f v2)
{
	return magnitude(v1-v2);
}

sf::Vector2f dirTo(sf::Vector2f from, sf::Vector2f to)
{
	sf::Vector2f relTargetPos = to-from;
	return normalized(relTargetPos);
}
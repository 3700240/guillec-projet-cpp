#include <GameInstance.hpp>

#include <iostream>
#include <stdexcept>

#include <vector>

#include <SFML/System/Vector2.hpp>


int main(void)
{
    try
	{
		GameInstance game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
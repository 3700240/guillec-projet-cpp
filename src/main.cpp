#include <GameInstance.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

int main(void) // Point d'entrée du programme
{
    try
	{
		GameInstance game;
		game.run();           // style minimaliste
	}
	catch (std::exception& e) // pq pas ?
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
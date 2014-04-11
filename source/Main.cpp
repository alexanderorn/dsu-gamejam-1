#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Box2D/Box2D.h>

int main( int argc, char ** argv )
{
	// Print the program arguments
	for( int i = 0; i < argc; i++ )
	{
		std::cout << argv[ i ] << std::endl << std::endl;
	}

	// Close the program
	std::cin.get( );
	return 0;
}
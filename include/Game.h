#pragma once

// Forward declaractions
namespace sf
{
	class RenderWindow;
}

class Game
{

public:

	virtual ~Game( );

	virtual int Run( int argv, char ** argc ) = 0;
	virtual sf::RenderWindow & GetWindow( ) = 0;

};
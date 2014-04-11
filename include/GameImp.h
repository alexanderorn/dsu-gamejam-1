#pragma once
#include <Game.h>
#include <StateManager.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class GameImp : public Game
{

public:

	GameImp( );
	~GameImp( );

	// Public functions
	virtual int Run( int argv, char ** argc );
	virtual sf::RenderWindow & GetWindow( );

private:

	// Private functions
	bool Load( );
	int Unload( );
	bool Update( float deltaTime );
	void Render( );

	// Private varaibles
	sf::RenderWindow m_Window;
	StateManager  m_StateManager;
	float m_GameSpeed;
	sf::Clock m_DeltaTimer;

};
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class GameImp
{

public:

	GameImp( );
	~GameImp( );

	// Public functions
	virtual int Run( int argv, char ** argc );

private:

	// Private functions
	bool Load( );
	int Unload( );
	bool Update( float deltaTime );
	bool HandleEvents( float deltaTime );
	void Render( );

	// Private varaibles
	sf::RenderWindow m_Window;
	float m_GameSpeed;
	sf::Clock m_DeltaTimer;

};
#include <GameImp.h>
#include <ResourceManager.h>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <MemoryLeak.h>

GameImp::GameImp( )
{
}

GameImp::~GameImp( )
{
}

int GameImp::Run( int argv, char ** argc )
{
	// Load the game
	if( Load( ) == false )
	{
		return Unload( );
	}

	// Game loop
	m_DeltaTimer.restart( );
	while( m_Window.isOpen( ) )
	{

		// Get the delta time
		float deltaTime = m_DeltaTimer.getElapsedTime( ).asSeconds( );
		m_DeltaTimer.restart( );

		// Update
		Update( deltaTime );

		// Render
		Render( );
	}

	// Close the game
	return Unload( );
}

bool GameImp::Load( )
{
	// Create the game window
	const sf::Vector2i windowSize( 800, 600 );
	const sf::VideoMode videoMode( windowSize.x, windowSize.y );
	const sf::Uint32 style =	sf::Style::Close |
								sf::Style::Titlebar;

	m_Window.create( videoMode, style );
	if( m_Window.isOpen( ) == false )
	{
		std::cout << "[GameImp::Load] Can not create the window" << std::endl;
		return false;
	}
	m_Window.setTitle( "Ninja game" );

	// Initialize the resource manager
	if( ResourceManager::Initialize( ) == false )
	{
		std::cout << "[GameImp::Load] Can not initialize the resoruce manager." << std::endl;
		return false;
	}

	return true;
}

int GameImp::Unload( )
{

	// Unload the resource manager
	ResourceManager::Unload( );

	// Succeeded
	return 0;
}

bool GameImp::Update( float deltaTime )
{
	// Handle events
	HandleEvents( deltaTime );

	// Update the game
	// ...

	return true;
}

bool GameImp::HandleEvents( float deltaTime )
{
	// Poll the events
	sf::Event e;
	while( m_Window.pollEvent( e ) )
	{
		switch( e.type )
		{
			case sf::Event::Closed:
			{
				m_Window.close( );
			}
			break;
			case sf::Event::KeyReleased:
			{
				switch( e.key.code )
				{
					case sf::Keyboard::Escape:
					{
						m_Window.close( );
					}
					break;
				}
			}
			break;
		}
	}

	// Return true if succeeded
	return true;
}

void GameImp::Render( )
{
	// Clear the color
	m_Window.clear( );

	// Draw primitives
	// ...

	// Dislay the window
	m_Window.display( );
}
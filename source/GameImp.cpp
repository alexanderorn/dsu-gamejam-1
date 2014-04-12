#include <GameImp.h>
#include <ResourceManager.h>
#include <SFML/Window/Event.hpp>
#include <MenuState.h>
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
		if( Update( deltaTime ) == false )
		{
			break;
		}

		// Render
		Render( );
	}

	// Close the game
	return Unload( );
}

sf::RenderWindow & GameImp::GetWindow( )
{
	return m_Window;
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

	// Load the start state
	m_StateManager.Push( new MenuState( this ) );
	m_StateManager.Update( );

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
	// Update the state manager
	m_StateManager.Update( );

	// Update the current state
	State * pState = m_StateManager.GetCurrentState( );
	if( pState == NULL )
	{
		return false;
	}

	// Poll window events to the state
	sf::Event e;
	while( m_Window.pollEvent( e ) )
	{
		// Send the event to the state
		if( pState->HandleEvent( e ) == false )
		{
			return false;
		}
	}

	// Update the state
	if( pState->Update( ) == false )
	{
		return false;
	}

	return true;
}

void GameImp::Render( )
{
	// Render the current state
	State * pState = m_StateManager.GetCurrentState( );
	if( pState )
	{
		pState->Render( );
	}

}
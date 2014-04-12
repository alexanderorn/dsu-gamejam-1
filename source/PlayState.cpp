#include <PlayState.h>
#include <StateManager.h>
#include <Game.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <MemoryLeak.h>

// Constructors/destructors
PlayState::PlayState( Game * pGame, std::string & levelPath ) :
	m_Loaded( false ),
	m_pGame( pGame )
{
	if( pGame )
	{
		m_Loaded = true;
	}

	m_pLevel = new Level( levelPath );
}

PlayState::~PlayState( )
{
	if( m_pLevel )
	{
		delete m_pLevel;
		m_pLevel = NULL;
	}
}

// Public functions
bool PlayState::Update( )
{
	m_pLevel->update( 0.01666f );
	return true;
}

void PlayState::Render( )
{
	// Clear the window
	m_pGame->GetWindow( ).clear( sf::Color( 242, 39, 39, 255 ) );

	// Render the level
	m_pLevel->draw( m_pGame->GetWindow( ) );

	// Display the window
	m_pGame->GetWindow( ).display( );
}

bool PlayState::Enter( )
{
	return true;
}

void PlayState::Leave( )
{

}

bool PlayState::HandleEvent( const sf::Event & p_Event )
{
	switch( p_Event.type )
	{
		case sf::Event::KeyPressed:
		{
			if( p_Event.key.code == sf::Keyboard::Escape )
			{
				GetStateManager( )->Pop( );
				return true;
			}
		}
		break;
	}

	return true;
}

// Get functions
bool PlayState::IsLoaded( ) const
{
	return m_Loaded;
}
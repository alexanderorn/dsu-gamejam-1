#include <PlayState.h>
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
}

PlayState::~PlayState( )
{
}

// Public functions
bool PlayState::Update( )
{
	return true;
}

void PlayState::Render( )
{
	m_pGame->GetWindow( ).clear( sf::Color( 255, 0, 255, 255 ) );

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
	return true;
}

// Get functions
bool PlayState::IsLoaded( ) const
{
	return m_Loaded;
}
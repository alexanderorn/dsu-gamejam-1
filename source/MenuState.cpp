#include <MenuState.h>
#include <stdio.h>
#include <Game.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <MemoryLeak.h>

// Constructors/destructors
MenuState::MenuState( Game * pGame ) :
	m_Loaded( false ),
	m_pGame( pGame )
{
	if( pGame )
	{
		m_Loaded = true;
	}
}

MenuState::~MenuState( )
{
}

// Public functions
bool MenuState::Update( )
{
	return true;
}

void MenuState::Render( )
{
	m_pGame->GetWindow( ).clear( sf::Color( 255, 0, 0, 255 ) );

	m_pGame->GetWindow( ).display( );
}

bool MenuState::Enter( )
{
	return true;
}

void MenuState::Leave( )
{

}

bool MenuState::HandleEvent( const sf::Event & p_Event )
{
	return true;
}

// Get functions
bool MenuState::IsLoaded( ) const
{
	return m_Loaded;
}
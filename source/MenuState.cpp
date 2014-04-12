#include <MenuState.h>
#include <PlayState.h>
#include <ResourceManager.h>
#include <StateManager.h>
#include <Game.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
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

	// Load the header text
	m_HeaderText.setFont( ResourceManager::GetFont( "data/fonts/visitor1.ttf" ) );
	m_HeaderText.setColor( sf::Color( 255, 255, 255, 220 ) );
	m_HeaderText.setCharacterSize( 30 );
	m_HeaderText.setScale( 3, 3 );
	m_HeaderText.setPosition( 260, 10 );
	const_cast<sf::Texture&>( m_HeaderText.getFont( )->getTexture( 30 )).setSmooth( false );
	m_HeaderText.setString( "Levels" );

	// Load the button text
	m_ButtonText.setFont( ResourceManager::GetFont( "data/fonts/visitor1.ttf" ) );
	m_ButtonText.setColor( sf::Color( 255, 255, 255, 220 ) );
	m_ButtonText.setCharacterSize( 30 );
	m_ButtonText.setScale( 3, 3 );
	m_ButtonText.setPosition( 260, 10 );
	const_cast<sf::Texture&>( m_ButtonText.getFont( )->getTexture( 30 )).setSmooth( false );
	m_ButtonText.setString( "0123456789" );

	// Load the button frames
	m_ButtonFrameSprite.setTexture( ResourceManager::GetTexture( "data/textures/menuButtonFrame.png" ) );
	
	const_cast<sf::Texture*>( m_ButtonFrameSprite.getTexture( ) )->setSmooth( false );
	m_ButtonFrameSprite.setScale( 9, 9 );

	// Add the buttons
	const sf::Vector2f butStart( 160, 160 );
	m_Buttons.push_back( Button( "1", "data/levels/level1.txt", butStart + sf::Vector2f( 0, 0 ) ) );
	m_Buttons.push_back( Button( "2", "data/levels/level1.txt", butStart + sf::Vector2f( 120, 0 ) ) );
	m_Buttons.push_back( Button( "3", "data/levels/level1.txt", butStart + sf::Vector2f( 120 * 2, 0 ) ) );
	m_Buttons.push_back( Button( "4", "data/levels/level1.txt", butStart + sf::Vector2f( 120 * 3, 0 ) ) );
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
	// Clear the screen
	m_pGame->GetWindow( ).clear( sf::Color( 242, 39, 39, 255 ) );

	// Render the header text
	m_pGame->GetWindow( ).draw( m_HeaderText );

	// Render all the buttons
	for( int i = 0; i < m_Buttons.size( ); i++ )
	{
		// Render the button frame
		m_ButtonFrameSprite.setPosition( m_Buttons[ i ].Position.x, m_Buttons[ i ].Position.y );
		m_pGame->GetWindow( ).draw( m_ButtonFrameSprite );

		// Render the button label
		m_ButtonText.setString( m_Buttons[ i ].Label );
		m_ButtonText.setPosition( m_Buttons[ i ].Position.x + 30, m_Buttons[ i ].Position.y - 20 );
		m_pGame->GetWindow( ).draw( m_ButtonText );
	}

	/*
		
	// Do not make the texture smooth
	//pFont->getTexture( ).setSmooth( false );
	*/

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
	switch( p_Event.type )
	{
		case sf::Event::KeyPressed:
		{
			if( p_Event.key.code == sf::Keyboard::Escape )
			{
				return false;
			}
		}
		break;
		case sf::Event::MouseButtonPressed:
		{
			// Check if we pressed any button
			sf::Vector2f mousePos( p_Event.mouseButton.x, p_Event.mouseButton.y );
			for( int i = 0; i < m_Buttons.size( ); i++ )
			{
				sf::FloatRect buttonRect(	m_Buttons[ i ].Position.x,
											m_Buttons[ i ].Position.y,
											m_ButtonFrameSprite.getTexture( )->getSize( ).x * m_ButtonFrameSprite.getScale( ).x,
											m_ButtonFrameSprite.getTexture( )->getSize( ).y * m_ButtonFrameSprite.getScale( ).y );
				sf::FloatRect intersection;
				if( buttonRect.intersects( sf::FloatRect( mousePos, sf::Vector2f( 1.0f, 1.0f ) ), intersection ) == true )
				{
					GetStateManager( )->Push( new PlayState( m_pGame, m_Buttons[ i ].LevelPath ) );
					return true;
				}
			}

		}
		break;

	}

	return true;
}

// Get functions
bool MenuState::IsLoaded( ) const
{
	return m_Loaded;
}
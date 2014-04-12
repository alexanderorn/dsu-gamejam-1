#include <MenuState.h>
#include <Game.h>
#include <PlayState.h>
#include <ResourceManager.h>
#include <StateManager.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Json/reader.h>
#include <Json/value.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <MemoryLeak.h>

// Constructors/destructors
MenuState::MenuState( Game * pGame ) :
	m_Loaded( false ),
	m_pGame( pGame ),
	m_FinishedLevels( false )
{
	if( pGame )
	{
		m_Loaded = true;
	}

	// Alpha color
	sf::Uint8 alpha = 180;

	// Load the header text
	m_HeaderText.setFont( ResourceManager::GetFont( "data/fonts/visitor1.ttf" ) );
	m_HeaderText.setColor( sf::Color( 255, 255, 255, alpha ) );
	m_HeaderText.setCharacterSize( 30 );
	m_HeaderText.setScale( 5, 5 );
	m_HeaderText.setString( "Levels" );
	int headerWidth = m_HeaderText.getGlobalBounds( ).width;
	m_HeaderText.setPosition( 1920 / 2.0f - headerWidth / 2.0f, 10 );
	const_cast<sf::Texture&>( m_HeaderText.getFont( )->getTexture( 30 )).setSmooth( false );

	// Load the button text
	m_ButtonText.setFont( ResourceManager::GetFont( "data/fonts/visitor1.ttf" ) );
	m_ButtonText.setColor( sf::Color( 255, 255, 255, alpha ) );
	m_ButtonText.setCharacterSize( 30 );
	m_ButtonText.setScale( 3, 3 );
	m_ButtonText.setPosition( 260, 10 );
	const_cast<sf::Texture&>( m_ButtonText.getFont( )->getTexture( 30 )).setSmooth( false );
	m_ButtonText.setString( "0123456789" );

	// Set the button frame texture
	m_ButtonFrameSprite.setTexture( ResourceManager::GetTexture( "data/textures/menuButtonFrame.png" ) );
	const_cast<sf::Texture*>( m_ButtonFrameSprite.getTexture( ) )->setSmooth( false );
	m_ButtonFrameSprite.setColor( sf::Color( 255, 255, 255, alpha ) );
	m_ButtonFrameSprite.setScale( 9, 9 );

	// Get the button real size
	sf::Vector2i buttonSize;
	buttonSize.x = m_ButtonFrameSprite.getTexture( )->getSize( ).x * m_ButtonFrameSprite.getScale( ).x;
	buttonSize.y = m_ButtonFrameSprite.getTexture( )->getSize( ).y * m_ButtonFrameSprite.getScale( ).y;

	// Read in the level file
	if( ReadLevelFile( "data/levels.txt" ) == false )
	{
		std::cout << "[MenuState::MenuState] Can not load the levels file." << std::endl;
		return;
	}

	// Fix the positions of the buttons.
	const int buttonsPerRow = 4;
	const int buttonOffset = 30;
	const int buttonLineWidth = ( buttonsPerRow * buttonSize.x ) + ( ( buttonsPerRow - 1 ) * buttonOffset );
	const sf::Vector2i buttonStartPos( 1920 / 2 - buttonLineWidth / 2 - 7, 200 );
	for( int i = 0; i < m_Buttons.size( ); i++ )
	{
		int x = i % buttonsPerRow;
		int y = i / buttonsPerRow;
		m_Buttons[ i ].Position.x = buttonStartPos.x;
		m_Buttons[ i ].Position.y = buttonStartPos.y;
		m_Buttons[ i ].Position.x += ( x * buttonSize.x ) + ( x * buttonOffset );
		m_Buttons[ i ].Position.y += ( y * buttonSize.y ) + ( y * buttonOffset );
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
	// Clear the screen
	m_pGame->GetWindow( ).clear( sf::Color( 242, 39, 39, 255 ) );

	// Render the header text
	m_pGame->GetWindow( ).draw( m_HeaderText );

	// Render all the buttons
	sf::Vector2i buttonSize;
	buttonSize.x = m_ButtonFrameSprite.getTexture( )->getSize( ).x * m_ButtonFrameSprite.getScale( ).x;
	buttonSize.y = m_ButtonFrameSprite.getTexture( )->getSize( ).y * m_ButtonFrameSprite.getScale( ).y;

	for( int i = 0; i < m_Buttons.size( ); i++ )
	{
		// Render the button frame
		m_ButtonFrameSprite.setPosition( m_Buttons[ i ].Position.x, m_Buttons[ i ].Position.y );
		m_pGame->GetWindow( ).draw( m_ButtonFrameSprite );

		// Render the button label
		m_ButtonText.setString( m_Buttons[ i ].Label );
		int labelWidth = m_ButtonText.getGlobalBounds( ).width;

		sf::Vector2f position( m_Buttons[ i ].Position.x, m_Buttons[ i ].Position.y - 14 );
		position.x += buttonSize.x /2 - labelWidth / 2 + 5;
		m_ButtonText.setPosition( position );
		m_pGame->GetWindow( ).draw( m_ButtonText );
	}

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

bool MenuState::ReadLevelFile( const std::string & filename )
{
	// Open the file
	std::ifstream fin( filename.c_str( ) );
    if( !fin.is_open() )
    {
         return false;
    }
	
	// Read the file
	std::string input = "";
    while( !fin.eof() )
    {
        // Get and add the line
        std::string line;
        std::getline( fin, line );
        input += line + "\n";
    }

	// Parse the json file
	Json::Value jsonRoot;
	Json::Reader jsonReader;
	if( jsonReader.parse( input, jsonRoot ) == false )
	{
		std::cout << "[MenuState::ReadLevelFile] Can not parse the level file." << std::endl;
		return false;
	}

	// Get the level value
	Json::Value jsonLevels = jsonRoot[ "Levels" ];
	for( int i = 0; i < jsonLevels.size( ); i++ )
	{
		// Get and error check the path
		std::string path = jsonLevels[ i ].asString( );
		if( path.size( ) == 0 )
		{
			std::cout << "[MenuState::ReadLevelFile] Wrong path." << std::endl;
			continue;
		}

		// Create the label
		std::stringstream label;
		label << m_Buttons.size( ) + 1;

		// Add the button
		m_Buttons.push_back( Button( label.str( ), path, sf::Vector2f( 0, 0 ) ) );
	}

	// closes the file
	fin.close( );

	return true;
}

bool MenuState::ReadSaveFile( const std::string & filename )
{
	// Open the file
	std::ifstream fin( filename.c_str( ) );
    if( !fin.is_open() )
    {
         return false;
    }
	
	// Read the value
	unsigned int finishedLevels;
	fin >> finishedLevels;
	if( finishedLevels > 64 )
	{
		return false;
	}

	// Set the finsihed levels
	m_FinishedLevels = finishedLevels;

	// closes the file
	fin.close();

	// Succeeded.
	return true;
}
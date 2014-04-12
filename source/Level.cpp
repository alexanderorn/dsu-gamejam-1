#include <Level.h>
#include <Platform.h>
#include <Json/reader.h>
#include <Json/value.h>
#include <fstream>
#include <MemoryLeak.h>


Level::Level( const std::string & filename ) :
	m_Loaded( false ),
	m_World(b2Vec2( 0.f, 9.82f ) )

{
	loadFromFile( filename );
	m_World.SetContactListener(&m_ContactListener);
}

Level::~Level( )
{
	unload( );
}

void Level::update(float delta)
{

	m_World.Step( delta * 3.0f, 8, 3 );
	m_pNinja->update();
}

void Level::draw( sf::RenderTarget& target )
{
	//target.draw( stuff... );
	m_pNinja->draw( target );

	// Render the platform
	for( int i = 0; i < m_Platforms.size( ); i++ )
	{
		m_Platforms[ i ]->draw( target );
	}
	
	//render throwingstars
	for( int i = 0; i < m_Throwingstars.size( ); i++ )
	{
		m_Throwingstars[ i ]->draw( target );
	}
}
void Level::unload()
{
	if( m_pNinja )
	{
		delete m_pNinja;
		m_pNinja = NULL;
	}

	// Delete the platforms
	for( int i = 0; i < m_Platforms.size( ); i++ )
	{
		delete m_Platforms[ i ];
	}
	m_Platforms.clear( );
}

bool Level::loadFromFile( const std::string & filename )
{
	// Load the ninja
	m_pNinja = new Ninja( m_World, m_Throwingstars);
	m_pNinja->getBody()->setPosition(b2Vec2( 100/PPM , 100/PPM));

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

	// closes the file
	fin.close();

	// Get the root
	Json::Value jsonRoot;
	Json::Reader jsonReader;
	if( jsonReader.parse( input, jsonRoot ) == false )
	{
		std::cout << "[Level::loadFromFile] Failed to parse level file." << std::endl;
		return false;
	}

	// Get the platforms
	Json::Value jsonPlatforms = jsonRoot[ "Platforms" ];
	if( jsonPlatforms.isArray( ) == false )
	{
		std::cout << "[Level::loadFromFile] Platforms are not an array." << std::endl;
		return false;
	}

	// Go thrugh the platforms
	for( int i = 0; i < jsonPlatforms.size( ); i++ )
	{
		// Get the current platform
		Json::Value jsonCurrentPlatform = jsonPlatforms[ i ];

		// Get the position
		Json::Value jsonPosition = jsonCurrentPlatform[ "Position" ];
		if( jsonPosition.isObject( ) == false )
		{
			std::cout << "[Level::loadFromFile] Platform position is not a object." << std::endl;
			return false;
		}

		// Get the size
		Json::Value jsonSize = jsonCurrentPlatform[ "Size" ];
		if( jsonSize.isObject( ) == false )
		{
			std::cout << "[Level::loadFromFile] Platform size is not a object." << std::endl;
			return false;
		}

		// Get the position and size from the json values.
		sf::Vector2i position;
		sf::Vector2i size;

		position.x = jsonPosition.get( "X", 0 ).asInt( );
		position.y = jsonPosition.get( "Y", 0 ).asInt( );
		size.x = jsonSize.get( "X", 0 ).asInt( );
		size.y = jsonSize.get( "Y", 0 ).asInt( );

		// Append the platform
		m_Platforms.push_back( new Platform( m_World, size.x, size.y, position.x, position.y ) );

	}

	// Succeeded
	m_Loaded = true;
	return true;
}

#include <Level.h>
#include <Json/reader.h>
#include <Json/value.h>
#include <fstream>
#include <MemoryLeak.h>


Level::Level( const std::string & filename ) :
	m_Loaded( false ),
	m_World(b2Vec2( 0.f, 9.82f ) ),
	m_Platform(m_World, 100.0f, 300.0f, 0, 3, 0, 1, 1, true, 600, 200)
{
	loadFromFile( filename );
}

Level::~Level( )
{
	unload( );
}

void Level::update(float delta)
{
	m_World.Step( 1.0f / 300.0f, 8, 3 );
	m_pNinja->update();
}

void Level::draw( sf::RenderTarget& target )
{
	//target.draw( stuff... );
	m_pNinja->draw( target );

	// Render the platform
	target.draw( m_PlatformShape );
}
void Level::unload()
{
	if( m_pNinja )
	{
		delete m_pNinja;
		m_pNinja = NULL;
	}
}

bool Level::loadFromFile( const std::string & filename )
{
	// Load the ninja
	m_pNinja = new Ninja( m_World );
	m_pNinja->getBody()->setPosition(b2Vec2( 100 , 100));

	// Add default platform
	m_PlatformShape.setPosition( m_Platform.getPosition().x , m_Platform.getPosition().y  );
	m_PlatformShape.setSize( sf::Vector2f( 600.0f, 200) );
	m_PlatformShape.setFillColor( sf::Color( 50, 50, 50, 255 ) );
	



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

	// Succeeded
	m_Loaded = true;
	return true;
}
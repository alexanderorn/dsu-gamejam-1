#include <Level.h>
#include <MemoryLeak.h>


Level::Level( ):
	m_World(b2Vec2( 0.f, 9.82f ) ),
	m_Platform(m_World, 000.0f, 300.0f, 0, 1, 1, 1, 1, true, 600, 50)
{
	m_pNinja = new Ninja( m_World );
	m_pNinja->setPosition( 800.f, 350.f );

	m_PlatformShape.setPosition( 000.0f, 300.0f );
	m_PlatformShape.setSize( sf::Vector2f( 600.0f, 50) );
	m_PlatformShape.setFillColor( sf::Color( 50, 50, 50, 255 ) );
}

Level::~Level( )
{
	if( m_pNinja )
	{
		delete m_pNinja;
		m_pNinja = NULL;
	}

}

void Level::update(float delta)
{
	m_World.Step( 0.01666f / 2.0f, 8, 3 );
	m_pNinja->update();
}

void Level::draw( sf::RenderTarget& target )
{
	//target.draw( stuff... );
	m_pNinja->draw( target );

	// Render the platform
	target.draw( m_PlatformShape );
}

void Level::load()
{

}

void Level::unload()
{

}

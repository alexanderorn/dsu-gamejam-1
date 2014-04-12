#include <Level.h>
#include <MemoryLeak.h>


Level::Level( ):
	m_World(b2Vec2( 0.f, 9.82f ) ),
	m_Platform(m_World, 100.0f, 300.0f, 0, 3, 0, 1, 1, true, 600, 200)
{
	m_pNinja = new Ninja( m_World );
	m_pNinja->getBody()->setPosition(b2Vec2( 100 , 100));

	m_PlatformShape.setPosition( m_Platform.getPosition().x , m_Platform.getPosition().y  );
	m_PlatformShape.setSize( sf::Vector2f( 600.0f, 200) );
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

void Level::load()
{

}

void Level::unload()
{

}

#include <Level.h>
#include <MemoryLeak.h>

Level::Level( ):
	m_World(b2Vec2( 0.f, 9.82f ) ),
	test(m_World, 600, 200, 100, 300)
{
	m_pNinja = new Ninja( m_World );
	m_pNinja->getBody()->setPosition(b2Vec2( 100 , 100));

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
	test.draw(target);
}

void Level::load()
{

}

void Level::unload()
{

}

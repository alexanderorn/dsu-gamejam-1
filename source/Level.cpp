#include <Level.h>
#include <MemoryLeak.h>


Level::Level( Ninja* ninja):
	m_World(b2Vec2( 0.f , 9.82f )),
	m_Platform(m_World, 800.0f, 300.0f, 0, 1, 1, 1, 1, true, 600, 50)
{
	m_pNinja->setPosition( 800.f, 350.f );
}



void Level::update(float delta)
{
	m_World.Step(delta/1000.f, 8, 3 );
	m_pNinja->update();
}

void Level::draw( sf::RenderTarget& target )
{
	//target.draw( stuff... );
}

void Level::load()
{

}

void Level::unload()
{

}

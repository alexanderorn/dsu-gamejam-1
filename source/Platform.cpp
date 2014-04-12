#include <Platform.h>
#include <SFML/System/Vector2.hpp>
#include <MemoryLeak.h>

Platform::Platform( b2World& world, int width, int height, float x, float y ):
	m_Body(world, x/PPM , y/PPM, 0, 3, 0, 1.1f, 0, true, (float32)width/PPM, (float32)height/PPM, true)
{
	m_Shape.setSize(sf::Vector2f( (float)width, (float)height) );
	m_Shape.setPosition( x, y );
	m_Shape.setFillColor( sf::Color( 255, 255, 255, 180 ) );
}

Platform::~Platform( )
{

}

void Platform::draw( sf::RenderTarget& target )
{
	target.draw(m_Shape);
}

void Platform::update( )
{

}

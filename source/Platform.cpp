#include <Platform.h>
#include <SFML/System/Vector2.hpp>
#include <MemoryLeak.h>

Platform::Platform( b2World& world, int width, int height, float x, float y ):
	m_Body(world, x, y, 0, 3, 0, 1, 0, true, (float32)width, (float32)height, false)
{
	m_Shape.setSize(sf::Vector2f( (float)width, (float)height) );
	m_Shape.setPosition( x, y );
	m_Shape.setFillColor( sf::Color( 242, 39, 39, 255 ) );
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

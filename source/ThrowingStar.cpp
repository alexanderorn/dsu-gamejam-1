#include <ThrowingStar.h>
#include <MemoryLeak.h>

ThrowingStar::ThrowingStar( b2World& world, float x, float y, b2Vec2 dir, float32 force ):
	m_Body(world, x, y, 0, 1, -200, 2, 0, false, 10, 10, true)
{
	m_Shape.setFillColor(sf::Color(255,240,300,255));
	m_Shape.setSize(sf::Vector2f(10,10));
	m_Body.applyLinearImpulse(b2Vec2(dir.x*force, dir.y*force), m_Body.getWorldCenter(), true);
}

ThrowingStar::~ThrowingStar( )
{

}

void ThrowingStar::update( )
{

	
}

void ThrowingStar::draw( sf::RenderTarget& target )
{
	m_Shape.setPosition( m_Body.getPosition().x,  m_Body.getPosition().y );
	m_Shape.setRotation( m_Body.getAngle( ) * RADIANS_TO_DEGREES );
	target.draw(m_Shape);
}

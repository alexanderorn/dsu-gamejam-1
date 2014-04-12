#include <ThrowingStar.h>
#include <MemoryLeak.h>

ThrowingStar::ThrowingStar( b2World& world, float x, float y, b2Vec2 dir, float32 force ):
	m_Body(world, x, y, 0, 1, 1.0f, 2, 0, false, 10.0f/PPM, 10.0f/PPM, true, -2)
{
	m_Shape.setFillColor(sf::Color(255,240,300,255));
	m_Shape.setSize(sf::Vector2f(10,10));
	m_Body.applyLinearImpulse(b2Vec2(dir.x*force, dir.y*force), m_Body.getWorldCenter(), true);
	//m_Body.applyAngularImpulse( 1.0f, true );
}

ThrowingStar::~ThrowingStar( )
{

}

void ThrowingStar::update( )
{

	
}

void ThrowingStar::draw( sf::RenderTarget& target )
{
	m_Shape.setPosition( m_Body.getPosition().x*PPM,  m_Body.getPosition().y*PPM );
	m_Shape.setRotation( m_Body.getAngle( ) * RADIANS_TO_DEGREES );
	target.draw(m_Shape);
}

Entity::e_Type ThrowingStar::getType()
{
	return Entity::THROWINGSTAR;
}

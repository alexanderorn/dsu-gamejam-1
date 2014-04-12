#include <Ninja.h>
#include <ResourceManager.h>



Ninja::Ninja(b2World& world) :
	m_Body( world, 0.0f, 0.0f, 1, 1, 1, 1, 1, false, 32, 32)
{
	m_Sprite.setTexture(ResourceManager::GetTexture("data/textures/ninja.png"));
}

Ninja::~Ninja( )
{
	
}

void Ninja::update( )
{
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_Body.applyLinearImpulse(b2Vec2( 400 , 0 ), m_Body.getWorldCenter(), true);
	}
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Body.applyLinearImpulse(b2Vec2( -400 , 0 ), m_Body.getWorldCenter(), true);
	}

	m_Sprite.setPosition( m_Body.getPosition( ).x / 30, m_Body.getPosition( ).y / 30 );
	m_Sprite.setRotation( m_Body.getAngle( ) );
	
}

void Ninja::draw( sf::RenderTarget& target )
{
	//m_Sprite.setPosition( 100, 100 );
	target.draw(m_Sprite);
}

void Ninja::setPosition( float32 x, float32 y)
{
	m_Body.setPosition(b2Vec2( x , y ));
}

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
		m_Body.applyLinearImpulse(b2Vec2( 20 , 0 ), m_Body.getWorldCenter(), true);
	}
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Body.applyLinearImpulse(b2Vec2( -20 , 0 ), m_Body.getWorldCenter(), true);
	}
}

void Ninja::draw( sf::RenderTarget& target )
{
	target.draw(m_Sprite);
}

void Ninja::setPosition( float32 x, float32 y)
{
	m_Body.setPosition(b2Vec2( x , y ));
}

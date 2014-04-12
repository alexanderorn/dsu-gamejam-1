#include <Ninja.h>
#include <ResourceManager.h>
#include <iostream>
#include <MemoryLeak.h>


Ninja::Ninja(b2World& world) :
	m_Legs( world, 0.0f, 0.0f, 0, 3, 0, 1, 1, false, 32, 32, true),
	m_JumpCooldown(1),
	m_MaxSpeed(50)
{
	m_Sprite.setTexture(ResourceManager::GetTexture("data/textures/ninja.png"));
}

Ninja::~Ninja( )
{
	
}

void Ninja::update( )
{
	keepUpright( );
	speedlimit( );

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_Legs.applyLinearImpulse(b2Vec2( 200.0f , 0 ), m_Legs.getWorldCenter(), true);
	}
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Legs.applyLinearImpulse(b2Vec2( -200.0f , 0 ), m_Legs.getWorldCenter(), true);
	}
	//jump
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !m_Jumping )
	{
		m_Jumping = true;
		m_JumpClock.restart();
		m_Legs.applyLinearImpulse(b2Vec2( 0 , -120000.0f ), m_Legs.getWorldCenter(), true);
	}

	//reset jumpcooldown;
	if( m_JumpClock.getElapsedTime().asSeconds() > m_JumpCooldown )
	{
		m_Jumping = false;
	}


	std::cout<<m_Legs.getBody()->GetMass() << std::endl;
}

void Ninja::draw( sf::RenderTarget& target )
{
	m_Sprite.setPosition( m_Legs.getPosition( ).x, m_Legs.getPosition( ).y);
	m_Sprite.setRotation( m_Legs.getAngle( ) * RADIANS_TO_DEGREES );
	

	target.draw(m_Sprite);
}

DynamicBody* Ninja::getBody()
{
	return &m_Legs;
}

void Ninja::keepUpright( )
{
	if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES > 5 )
	{
		m_Legs.applyTorque( -1000000 , true );
	}
	if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES < -5 )
	{
		m_Legs.applyTorque( 1000000 , true );
	}

}

void Ninja::speedlimit( )
{
	//Speed limit
		if(m_Legs.getLinearVelocity().x < -m_MaxSpeed)
		{
			m_Legs.setLinearVelocity( b2Vec2(-m_MaxSpeed, m_Legs.getLinearVelocity().y));
		}

		if(m_Legs.getLinearVelocity().x >m_MaxSpeed)
		{
			m_Legs.setLinearVelocity( b2Vec2(m_MaxSpeed, m_Legs.getLinearVelocity().y));
		}

		if(m_Legs.getLinearVelocity().y > m_MaxSpeed)
		{
			m_Legs.setLinearVelocity(b2Vec2(m_Legs.getLinearVelocity().x, m_MaxSpeed));
		}

		if(m_Legs.getLinearVelocity().y < -m_MaxSpeed)
		{
			m_Legs.setLinearVelocity(b2Vec2(m_Legs.getLinearVelocity().x, -m_MaxSpeed));
		}
}

#include <Ninja.h>
#include <ResourceManager.h>
#include <iostream>
#include <MemoryLeak.h>


Ninja::Ninja(b2World& world, std::vector<ThrowingStar*>& vector) :
	m_Legs( world, 0.0f, 0.0f, 0, 2, 0, 1, 1, false, 32, 32, true, -2 ),
	m_World(world),
	m_JumpCooldown(1),
	m_ThrowCooldown(1),
	m_MaxSpeed(50),
	m_Dead(false),
	m_ThrowingStars(vector)
{
	m_Sprite.setTexture(ResourceManager::GetTexture("data/textures/ninja.png"));
}

Ninja::~Ninja( )
{
	for( int i = 0; i < m_ThrowingStars.size( ); i++ )
	{
		delete m_ThrowingStars[ i ];
	}
}

void Ninja::update( )
{

	if( !m_Dead )
	{
		keepUpright( );
		updateMovement( );
		speedlimit( );
		shoot( );
	}
	
	//reset cooldowns;
	if( m_JumpClock.getElapsedTime().asSeconds() > m_JumpCooldown )
	{
		m_Jumping = false;
	}
	if( m_ThrowClock.getElapsedTime().asSeconds() > m_ThrowCooldown )
	{
		m_Shot = false;
	}

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

	//die
	if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES > 45 )
	{
		m_Dead = true;
	}
	if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES < -45 )
	{
		m_Dead = true;
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

void Ninja::jump( )
{
	m_Jumping = true;
	m_JumpClock.restart();
	m_Legs.applyLinearImpulse(b2Vec2( 0 , -120000.0f ), m_Legs.getWorldCenter(), true);
}

void Ninja::shoot( )
{
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !m_Shot)
	{
		m_Shot = true;
		m_ThrowClock.restart();
		m_ThrowingStars.push_back( new ThrowingStar(m_World, m_Legs.getPosition().x, m_Legs.getPosition().y, b2Vec2(1,1), 300000));
	}
}

void Ninja::updateMovement( )
{
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_Legs.applyLinearImpulse(b2Vec2( 3000.0f , 0 ), m_Legs.getWorldCenter(), true);
	}
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Legs.applyLinearImpulse(b2Vec2( -3000.0f , 0 ), m_Legs.getWorldCenter(), true);
	}
	

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !m_Jumping )
	{
		jump( );
	}
}

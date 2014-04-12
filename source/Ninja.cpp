#include <Ninja.h>
#include <ResourceManager.h>
#include <iostream>
#include <MemoryLeak.h>


Ninja::Ninja(b2World& world, std::vector<ThrowingStar*>& vector) :
	m_Legs( world, 0.0f/PPM, 0.0f/PPM, 0, 1.f, 0, 0.8f, 1, false, 32.0f/PPM, 32.0f/PPM, true, -2 ),
	m_World(world),
	m_JumpCooldown(0.8f),
	m_ThrowCooldown(1.f),
	m_MaxSpeed(10),
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
	m_Sprite.setPosition( m_Legs.getPosition( ).x * PPM, m_Legs.getPosition( ).y * PPM);
	m_Sprite.setRotation( m_Legs.getAngle( ) * RADIANS_TO_DEGREES );
	target.draw(m_Sprite);
}

Entity::e_Type Ninja::getType()
{
	return Entity::PLAYER;
}


DynamicBody* Ninja::getBody()
{
	return &m_Legs;
}

void Ninja::keepUpright( )
{
	if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES > 5 )
	{
		m_Legs.applyTorque( -9.f , true );
	}
	if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES < -5 )
	{
		m_Legs.applyTorque( 9.f , true );
	}

	//die
	/*if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES > 45 )
	{
		m_Dead = true;
	}
	if( m_Legs.getAngle( ) * RADIANS_TO_DEGREES < -45 )
	{
		m_Dead = true;
	}*/
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
	//jump
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !m_Jumping )
	{
		m_Jumping = true;
		m_JumpClock.restart();
		m_Legs.applyLinearImpulse(b2Vec2( 0 , -12.0f ), m_Legs.getWorldCenter(), true);
	}
}

void Ninja::shoot( )
{
	//Throw
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !m_Shot)
	{
		m_Shot = true;
		m_ThrowClock.restart();
		m_ThrowingStars.push_back( new ThrowingStar(m_World, m_Legs.getPosition().x, m_Legs.getPosition().y, b2Vec2(1,-0.2), 3));
	}
}

void Ninja::updateMovement( )
{
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_Legs.applyLinearImpulse(b2Vec2( 1.f , 0 ), m_Legs.getWorldCenter(), true);
	}
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Legs.applyLinearImpulse(b2Vec2( -1.f , 0 ), m_Legs.getWorldCenter(), true);
	}
	

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !m_Jumping )
	{
		jump( );
	}
}

#pragma once
#include <DynamicBody.h>
#include <MemoryLeak.h>

DynamicBody::DynamicBody(b2World& world, 
						 float x, 
						 float y,
						 float32 angle,
						 int density,
						 int restitution,
						 int friction,
						 int angularDamping,
						 bool isStatic,
						 float32 width,
						 float32 height,
						 bool originCenter)
   :m_SpawnPointX(x),
	m_SpawnPointY(y),
	m_SpawnAngle(angle),
	m_Density(density),
	m_Restitution(restitution),
	m_Friction(friction),
	m_AngularDamping(angularDamping),
	m_Static(isStatic),
	m_Width(width),
	m_Height(height),
	m_OriginCenter(originCenter)
{
	initBody(world);
}

DynamicBody::~DynamicBody()
{
	mBody->GetWorld()->DestroyBody(mBody);
}

const b2Vec2 DynamicBody::getLinearVelocity()
{
	return mBody->GetLinearVelocity();
}

const b2Vec2 DynamicBody::getWorldCenter()
{
	return mBody->GetWorldCenter();
}

const b2Vec2 DynamicBody::getPosition()
{
	return mBody->GetPosition();
}

float32 DynamicBody::getAngularVelocity()
{
	return mBody->GetAngularVelocity();
}

float32 DynamicBody::getAngle()
{
	return mBody->GetAngle();
}

b2Body* DynamicBody::getBody()
{
	return mBody;
}

void DynamicBody::applyAngularImpulse(float32 impulse, bool wake)
{
	mBody->ApplyAngularImpulse( impulse , wake );
}

void DynamicBody::applyTorque(float32 impulse, bool wake)
{
	mBody->ApplyTorque( impulse, wake );
}


void DynamicBody::applyLinearImpulse(b2Vec2 impulse , b2Vec2 point , bool wake)
{
	mBody->ApplyLinearImpulse( impulse , point , wake);
}


void DynamicBody::setAngularVelocity(float32 velocity)
{
	mBody->SetAngularVelocity(velocity);
}

void DynamicBody::setLinearVelocity( const b2Vec2 vector )
{
	mBody->SetLinearVelocity( vector );
}

void DynamicBody::setRotation(float32 angle)
{
	mBody->SetTransform( mBody->GetPosition( ) , DEGREES_TO_RADIANS * angle );
}

void DynamicBody::setPosition(b2Vec2 pos)
{
	mBody->SetTransform( pos, mBody->GetAngle( ) );
}

void DynamicBody::initBody(b2World& world)
{
	if( m_Static )
	{
		mBodyDef.type = b2_staticBody;
	}
	else
	{
		mBodyDef.type = b2_dynamicBody;
	}

	mBodyDef.position.Set( m_SpawnPointX , m_SpawnPointY );

	b2PolygonShape * pPolygoneShape = new b2PolygonShape;
	if( m_OriginCenter )
	{
		pPolygoneShape->SetAsBox( (m_Width/2), (m_Height/2), b2Vec2( m_Width/2, m_Height/2), m_SpawnAngle * RADIANS_TO_DEGREES );
	} else
	{
		pPolygoneShape->SetAsBox( (m_Width/2), (m_Height/2), b2Vec2( 0, 0), m_SpawnAngle * RADIANS_TO_DEGREES );
	}


	pPolygoneShape->SetAsBox( (m_Width/2), (m_Height/2), b2Vec2( m_Width/2, m_Height/2), m_SpawnAngle * RADIANS_TO_DEGREES );
	mBodyFix.shape = pPolygoneShape;
	mBodyFix.density = m_Density;
	mBodyFix.restitution = m_Restitution;
	mBodyFix.friction = m_Friction;
	mBody = world.CreateBody(&mBodyDef);
	mBody->CreateFixture(&mBodyFix);
	mBody->SetAngularDamping(m_AngularDamping);
}
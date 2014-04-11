#pragma once
#include <DynamicBody.h>

DynamicBody::DynamicBody(b2World& world, 
						 float x, 
						 float y,
						 int angle,
						 int density,
						 int restitution,
						 int friction,
						 int angularDamping)
   :m_SpawnPointX(x),
	m_SpawnPointY(y),
	m_SpawnAngle(angle),
	m_Density(density),
	m_Restitution(restitution),
	m_Friction(friction),
	m_AngularDamping(angularDamping)
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
	mBody->SetTransform( mBody->GetPosition() , DEGREES_TO_RADIANS * angle );
}

void DynamicBody::initBody(b2World& world)
{

	mBodyDef.type = b2_dynamicBody;
	mBodyDef.position.Set( m_SpawnPointX/PPM , m_SpawnPointY/PPM );
	mBodyDef.angle = m_SpawnAngle;
	
	mBodyFix.density = m_Density;
	mBodyFix.restitution = m_Restitution;
	mBodyFix.friction = m_Friction;
	mBody = world.CreateBody(&mBodyDef);
	mBody->CreateFixture(&mBodyFix);
	mBody->SetAngularDamping(m_AngularDamping);
}
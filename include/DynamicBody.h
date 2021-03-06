#pragma once
#include <Box2D/Box2D.h>

#define PPM 30
#define DEGREES_TO_RADIANS 0.0174532925
#define RADIANS_TO_DEGREES 57.2957795

class DynamicBody
{

public:
	DynamicBody(b2World& world, float x, float y,
		float32 angle, float density, float restitution, 
		float friction, float angularDamping, bool isStatic,
		float32 width, float32 height, bool originCenter,
		int layer = 0 );
	~DynamicBody();

	//get functions
	const b2Vec2 getLinearVelocity();
	const b2Vec2 getWorldCenter();
	const b2Vec2 getPosition();
	float32 getAngularVelocity();
	float32 getAngle();
	b2Body* getBody();

	//set functions
	void applyAngularImpulse(float32 impulse, bool wake);
	void applyTorque( float32 impulse, bool wake);
	void applyLinearImpulse(b2Vec2 impulse, b2Vec2 point, bool wake);
	void setAngularVelocity(float32 velocity);
	void setLinearVelocity(const b2Vec2 vector);
	void setRotation(float32 angle);
	void setPosition(b2Vec2);

private:
	float m_Width;
	float m_Height;
	bool m_Static;
	float m_SpawnAngle;
	float m_Density;
	float m_Restitution;
	float m_Friction;
	float m_AngularDamping;
	bool m_OriginCenter;


	DynamicBody(const DynamicBody& b2b);

	float m_SpawnPointX;
	float m_SpawnPointY;

	void initBody(b2World& world, int layer);

	b2Body* mBody;
	b2BodyDef mBodyDef;
	b2CircleShape mBodyShape;
	b2FixtureDef mBodyFix;

};
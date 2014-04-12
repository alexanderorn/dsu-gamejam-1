#pragma once
#include <Box2D/Box2D.h>

#define PPM 30
#define DEGREES_TO_RADIANS 0.0174532925

class DynamicBody
{

public:
	DynamicBody(b2World& world, float x, float y,
		float32 angle, int density, int restitution, 
		int friction, int angularDamping, bool isStatic,
		float32 width, float32 height);
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
	void applyLinearImpulse(b2Vec2 impulse, b2Vec2 point, bool wake);
	void setAngularVelocity(float32 velocity);
	void setLinearVelocity(const b2Vec2 vector);
	void setRotation(float32 angle);
	void setPosition(b2Vec2);

private:
	float m_Width;
	float m_Height;
	bool m_Static;
	int m_SpawnAngle;
	int m_Density;
	int m_Restitution;
	int m_Friction;
	int m_AngularDamping;


	DynamicBody(const DynamicBody& b2b);

	void initBody(b2World& world, float scale);

	float m_SpawnPointX;
	float m_SpawnPointY;

	void initBody(b2World& world);

	b2Body* mBody;
	b2BodyDef mBodyDef;
	b2CircleShape mBodyShape;
	b2FixtureDef mBodyFix;

};
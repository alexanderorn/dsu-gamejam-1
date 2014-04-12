#pragma once
#include <DynamicBody.h>
#include <Entity.h>
#include <SFML/Graphics/RectangleShape.hpp>

class ThrowingStar : public Entity
{

public:
	ThrowingStar( b2World& world, float x, float y, b2Vec2 dir, float32 force );
	~ThrowingStar( );

	virtual void update( );
	virtual void draw( sf::RenderTarget& target );

private:
	DynamicBody m_Body;
	sf::RectangleShape m_Shape;
};
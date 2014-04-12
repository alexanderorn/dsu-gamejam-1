#pragma once
#include <Entity.h>
#include <DynamicBody.h>
#include <SFML/Graphics/RectangleShape.hpp>

class Platform : public Entity
{

public:

	Platform( b2World& world, int width, int height, float x, float y );
	~Platform( );

	virtual void draw( sf::RenderTarget& target );
	virtual void update ( );
	virtual e_Type getType();

private:
	DynamicBody m_Body;
	sf::RectangleShape m_Shape;
};
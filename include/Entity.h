#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics/RenderTarget.hpp>

class Entity
{

public:
	Entity(){};
	virtual ~Entity( ) { };
	virtual void update( ) = 0;
	virtual void draw(sf::RenderTarget& target ) = 0;

private:

	//b2Body 

};
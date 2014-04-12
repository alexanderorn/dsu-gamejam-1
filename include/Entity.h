#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics/RenderTarget.hpp>

class Entity
{

public:
	enum e_Type{
		PLAYER,
		PLATFORM,
		THROWINGSTAR
	};

	Entity(){};
	virtual ~Entity( ) { };
	virtual void update( ) = 0;
	virtual void draw(sf::RenderTarget& target ) = 0;
	virtual e_Type getType() = 0;
	virtual void beginContact() = 0;
	virtual void endContact() = 0;


	



private:

	//b2Body 

};
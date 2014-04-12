#pragma once

#include <Ninja.h>
#include <DynamicBody.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Level
{
public:
	Level( );
	~Level( );
	
	void update( float delta );
	void draw( sf::RenderTarget& target );
	void load( );
	void unload( );

private:
	Level( const Level& );

	b2World m_World;
	Ninja* m_pNinja;
	DynamicBody m_Platform;
	sf::RectangleShape m_PlatformShape;


};

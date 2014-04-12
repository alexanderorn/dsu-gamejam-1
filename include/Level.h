#pragma once

#include <Ninja.h>
#include <DynamicBody.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <ThrowingStar.h>

class Platform;

class Level
{
public:
	Level( const std::string & filename );
	~Level( );
	
	void update( float delta );
	void draw( sf::RenderTarget& target );
	void unload( );
	inline bool isLoaded( ) const { return m_Loaded; }

private:

	// Private functions
	bool loadFromFile( const std::string & filename );

	// Make it inpossible to copy this level
	Level( const Level& );
	Level & operator = ( const Level & );

	bool m_Loaded;
	b2World m_World;
	Ninja* m_pNinja;
	typedef std::vector<Platform *> PlatformVector;
	PlatformVector m_Platforms;

	typedef std::vector<ThrowingStar *> StarVector;
	StarVector m_Throwingstars;



};

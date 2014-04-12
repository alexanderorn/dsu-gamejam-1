#pragma once
#include <State.h>
#include <Level.h>
#include <string>

// Forward declaraction
class Game;

class PlayState : public State
{

public:

	// Constructors/destructors
	PlayState( Game * pGame, std::string & levelPath );
	~PlayState( );

	// Public functions
	virtual bool Update( float deltaTime );
	virtual void Render( );
	virtual bool Enter( );
	virtual void Leave( );
	virtual bool HandleEvent( const sf::Event & p_Event );

	// Get functions
	virtual bool IsLoaded( ) const;

private:

	bool m_Loaded;
	Game * m_pGame;
	Level * m_pLevel;

};
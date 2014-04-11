#pragma once
#include <State.h>

// Forward declaraction
class Game;

class MenuState : public State
{

public:

	// Constructors/destructors
	MenuState( Game * pGame );
	~MenuState( );

	// Public functions
	virtual bool Update( );
	virtual void Render( );
	virtual bool Enter( );
	virtual void Leave( );
	virtual bool HandleEvent( const sf::Event & p_Event );

	// Get functions
	virtual bool IsLoaded( ) const;

private:

	bool m_Loaded;
	Game * m_pGame;


};
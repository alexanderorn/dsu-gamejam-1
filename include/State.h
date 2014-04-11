#pragma once

#include <SFML/Window/Event.hpp>

// Foward decalration
class StateManager;

class State
{

public:

	// Friend classes
	friend class StateManager; 

	// Constructors/destructors
	State( );
	virtual ~State( );

	// Public functions
	virtual bool Update( ) = 0;
	virtual void Render( ) = 0;
	virtual bool Enter( ) = 0;
	virtual void Leave( ) = 0;
	virtual bool HandleEvent( const sf::Event & p_Event ) = 0;

	// Get functions
	virtual bool IsLoaded( ) const = 0;
	StateManager * GetStateManager( ) const;

private:

	StateManager * m_pStateManager;

};
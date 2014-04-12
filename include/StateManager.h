#pragma once

#include <stack>
#include <queue>

// Foward decalrations
class State;

class StateManager
{

public:

	// Constructors/destructors
	StateManager( );
	~StateManager( );

	// Public functions
	void Clear( );
	void Update( );
	bool Push( State * p_pState );
	StateManager * Pop( );

	// Get functions
	unsigned int GetStateCount( ) const;
	State * GetCurrentState( ) const;

private:

	// Private enums
	enum eStack
	{
		StackPop,
		StackPush
	};

	// Private typdefs
	typedef std::stack< State * > StateStack;
	typedef std::pair< eStack, State * > StackPair;
	typedef std::queue< StackPair > StateQueue;

	// Private variables
	StateStack m_States;
	StateQueue m_StateQueue; // Temporary store states here until the next update call

};
#include <State.h>
#include <stdio.h>

// WARNING, include this file(MemoryLeak.h) last.
#include <MemoryLeak.h>

// Constructors/destructors
State::State( ) :
	m_pStateManager( NULL )
{
}

State::~State( )
{
}

StateManager * State::GetStateManager( ) const
{
	return m_pStateManager;
}
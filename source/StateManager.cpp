#include <StateManager.h>
#include <State.h>
#include <iostream>

// WARNING, include this file(MemoryLeak.h) last.
#include <MemoryLeak.h>

// Constructors/destructors
StateManager::StateManager( )
{
}

StateManager::~StateManager( )
{
	Clear( );
}

// Public functions
void StateManager::Clear( )
{
	// Pop and unload all the remaining states
	while( m_States.empty( ) == false )
	{
		// Get the top state
		State * pState = m_States.top( );
		
		// Unload and delete the state
		delete pState;

		// Pop the event
		m_States.pop( );
	}

	// Pop and unload all the states in the queue
	while( m_StateQueue.empty( ) == false )
	{
		// Get the state
		State * pState = m_StateQueue.front( ).second;
		m_StateQueue.pop( );

		if( pState )
		{
			delete pState;
		}
	}
}

void StateManager::Update( )
{
	// Go through all our stack pairs
	while( m_StateQueue.empty( ) == false )
	{
		// Get the pair and pop it from the queue stack
		StackPair stackPair = m_StateQueue.front( );
		m_StateQueue.pop( );

		// Check what to do whit this pair
		// Push operator
		if( stackPair.first == StackPush )
		{
			// Leave the current state
			if( m_States.size( ) )
			{
				m_States.top( )->Leave( );
			}

			// Get the state and push it to the state stack
			State * pState = stackPair.second;
			m_States.push( pState );

			// Enter the new state
			pState->Enter( );
		}
		// Pop operator
		else
		{
			// Get the current state and pop it
			State * pState = m_States.top( );
			m_States.pop( );

			// leave and delete the state
			pState->Leave( );
			delete pState;

			// Get he new current one and enter it
			if( m_States.size( ) )
			{
				pState = m_States.top( );
				pState->Enter( );
			}
		}
	}
}

bool StateManager::Push( State * p_pState )
{
	// Check if this state already belongs to another statemanager
	if( p_pState->m_pStateManager )
	{
		std::cout << "[StateManager::Push] The state already belongs to another state manager." << std::endl;
		return false;
	}

	// Check if the state is loaded
	if( p_pState->IsLoaded( ) == false )
	{
		std::cout << "[StateManager::Push] The state is not loaded." << std::endl;

		// Delete the state if it's not loaded,
		delete p_pState; 
		return false;
	}

	// Set the state manager for this state
	p_pState->m_pStateManager = this;

	// Push the state pair to the state queue.
	m_StateQueue.push( StackPair( StackPush, p_pState ) );

	return true;
}

StateManager * StateManager::Pop( )
{
	// Make sure that the stacks size is right for a pop
	if( m_States.size( ) <= 1 )
	{
		return this;
	} 

	// Tell a pop stack operator, NULL the state *, unnecessary
	m_StateQueue.push( StackPair( StackPop, NULL ) );
	return this;
}

// Get functions
unsigned int StateManager::GetStateCount( ) const
{
	// Return the state stack size.
	return static_cast<unsigned int>( m_States.size( ) );
}

State * StateManager::GetCurrentState( ) const
{
	// Make sure that we have any current state
	if( m_States.empty( ) == true )
	{
		return NULL;
	}

	// return the very top state on the stack, that's our current state.
	return m_States.top( );
}
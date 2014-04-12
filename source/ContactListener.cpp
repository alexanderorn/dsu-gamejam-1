#include <ContactListener.h>
#include <iostream>
#include <Entity.h>
#include <Ninja.h>
#include <Platform.h>
#include <MemoryLeak.h>

void ContactListener::BeginContact(b2Contact* contact)
{

	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if ( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->beginContact();
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if ( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->beginContact();
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if ( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->endContact();
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if ( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->endContact();
	}
}


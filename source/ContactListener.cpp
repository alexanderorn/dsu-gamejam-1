#include <ContactListener.h>
#include <MemoryLeak.h>
#include <Entity.h>

void ContactListener::BeginContact(b2Contact* contact)
{
	//checks if body A is an Entity
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->beginContact();
	}

	//checks if body B is an Entity
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->beginContact();
	}

}

void ContactListener::EndContact(b2Contact* contact)
{
	//checks if body A is an Entity
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->endContact();
	}

	//checks if body B is an Entity
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if( bodyUserData )
	{
		static_cast<Entity*>( bodyUserData )->endContact();
	}
}

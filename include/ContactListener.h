#pragma once
#include <Box2D/Box2D.h>

int numFootContacts;

class ContactListener : public b2ContactListener
{
   virtual void beginContact(b2Contact* contact);
   virtual void endContact(b2Contact* contact);


};
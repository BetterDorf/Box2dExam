#include "MyContactListener.h"
#include "Entity.h"

#include <iostream>

void MyContactListener::BeginContact(b2Contact* contact)
{
 	auto dataA = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto dataB = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    //Run collision logic twice, once from the point of view of A and once from B
} 
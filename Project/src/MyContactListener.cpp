#include "MyContactListener.h"
#include "Entity.h"
#include "GameManager.h"

#include <iostream>

void MyContactListener::BeginContact(b2Contact* contact)
{
    if (GameManager::GetInstance()->IsGameOver())
        return;

 	auto dataA = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto dataB = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    //Check that if the collision should be ignored or not
    if (dataA->GetData()->GetTag() == Tag::IGNORE || dataB->GetData()->GetTag() == Tag::IGNORE)
        return;

    //Run collision logic twice, once from the point of view of A and once from B
    for (int i = 0 ; i < 2 ; i++)
    {
        Tag tagB = dataB->GetData()->GetTag();

	    switch (dataA->GetData()->GetTag())
	    {
	    case Tag::PLAYER:
            if (tagB == Tag::DAMAGING)
            {
                GameManager::GetInstance()->GameOver();
            }
            break;
	    case Tag::MOON: break;
	    case Tag::DAMAGING: 
            if (tagB != Tag::DAMAGING)
            {
                GameManager::GetInstance()->AddDeadId(dataA->GetId());
            }
            break;
	    case Tag::IGNORE: break;
	    case Tag::DEFAULT: break;
        default: std::cout << "This shouldn't ever be seen" << std::endl;
	    }
        //Swap who's who
        auto temp = dataA;
        dataA = dataB;
        dataB = temp;
    }
} 
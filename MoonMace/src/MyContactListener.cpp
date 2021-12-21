#include "MyContactListener.h"

#include "DamagingEntity.h"

#include "GameManager.h"
#include "AudioManager.h"

#include <iostream>

void MyContactListener::BeginContact(b2Contact* contact)
{
    if (GameManager::GetInstance()->IsGameOver())
        return;

 	auto dataA = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto dataB = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    //Check that if the collision should be ignored or not
    if (dataA->GetData()->GetCollisionTag() == CollisionTag::IGNORE || dataB->GetData()->GetCollisionTag() == CollisionTag::IGNORE)
        return;

    //Run collision logic twice, once from the point of view of A and once from B
    for (int i = 0 ; i < 2 ; i++)
    {
        CollisionTag CollisionTagB = dataB->GetData()->GetCollisionTag();

	    switch (dataA->GetData()->GetCollisionTag())
	    { 
	    case CollisionTag::PLAYER:
            if (CollisionTagB == CollisionTag::DAMAGING)
            {
                GameManager::GetInstance()->GameOver() ;
            }
            break;
	    case CollisionTag::MOON: break;
	    case CollisionTag::DAMAGING: 
            if (CollisionTagB != CollisionTag::DAMAGING)
            {
                if (auto damaging = static_cast<DamagingEntity*>(dataA))
					GameManager::GetInstance()->AddDeadId(damaging->GetId());
            }
            else
            {
                collisionSound.setBuffer(AudioManager::GetInstance()->RequestBuffer(AudioPath::Bounce));
                collisionSound.play();
            }
            break;
	    case CollisionTag::IGNORE: break;
	    case CollisionTag::DEFAULT: break;
        default: std::cout << "This shouldn't ever be seen" << std::endl;
	    }
        //Swap who's who
        auto temp = dataA;
        dataA = dataB;
        dataB = temp;
    }
} 
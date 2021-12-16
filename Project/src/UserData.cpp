#include "UserData.h"

CollisionTag UserData::GetCollisionTag()
{
	return collisionTag_;
}

UserData::UserData()
{
	collisionTag_ = CollisionTag::DEFAULT;
}
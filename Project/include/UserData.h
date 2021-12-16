#pragma once

enum class CollisionTag : char
{
	DEFAULT = '0',
	PLAYER = 'P',
	MOON = 'M',
	DAMAGING = 'D',
	IGNORE = 'I'
};

class UserData
{
public:
	UserData();
	CollisionTag GetCollisionTag();
	void SetCollisionTag(CollisionTag collisionTag) { collisionTag_ = collisionTag; }
private:
	CollisionTag collisionTag_ = CollisionTag::DEFAULT;
};

#pragma once
#include "Entity.h"

class DamagingEntity : public Entity
{
	DamagingEntity() { userData_.SetTag(Tag::DAMAGING); }
};
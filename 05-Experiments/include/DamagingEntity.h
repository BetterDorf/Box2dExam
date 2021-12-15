#pragma once
#include "Entity.h"

class DamagingEntity : public Entity
{
public:
	DamagingEntity(int id) { id_ = id; }
};
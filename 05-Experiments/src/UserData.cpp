#include "UserData.h"

Tag UserData::GetTag()
{
	return tag_;
}

UserData::UserData()
{
	tag_ = Tag::DEFAULT;
}
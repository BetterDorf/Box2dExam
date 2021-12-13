#pragma once

enum class Tag : char
{
	DEFAULT = '0',
	PLAYER = 'P',
	MOON = 'M',
	DAMAGING = 'D'
};

class UserData
{
public:
	UserData();
	Tag GetTag();
	void SetTag(Tag tag) { tag_ = tag; }
private:
	Tag tag_ = Tag::DEFAULT;
};

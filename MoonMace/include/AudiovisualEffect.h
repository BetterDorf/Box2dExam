#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Window.hpp>
#include <box2d/b2_math.h>

#include "AudioPathes.h"
#include "SpritePathes.h"

class AudiovisualEffect : public sf::Sprite
{
public:
	//Play a sound and an animation
	AudiovisualEffect(SpritePath, b2Vec2 pos, AudioPath, sf::Window&, int loops = 0);

	//Returns true as long as it is animating
	bool Animate();

private:
	sf::Sound sound_;
	//The height of the texture
	int spriteWidth_;
	int loops_;
};
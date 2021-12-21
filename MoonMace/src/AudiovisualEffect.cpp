#include "AudiovisualEffect.h"

#include "AudioManager.h"
#include "Texture_manager.h"
#include "SFML_utilities.h"

AudiovisualEffect::AudiovisualEffect(SpritePath spritePath, b2Vec2 pos, AudioPath audioPath, sf::Window& window, int loops)
{
	loops_ = loops;

	//Set the audio
	sound_.setBuffer(AudioManager::GetInstance()->RequestBuffer(audioPath));
	sound_.play();

	//Set the sprite
	setTexture(Texture_manager::Get_instance()->Request_texture(spritePath));
	// All sprites are squares so spriteWidth is the same as width and we can use it to determine the latter
	spriteWidth_ = getTextureRect().height;
	sf::IntRect rect(0, 0, spriteWidth_, spriteWidth_);
	setTextureRect(rect);

	//Set the position
	setPosition(metersToPixelsCoord(pos, window.getSize()));
}

bool AudiovisualEffect::Animate()
{
	//Check if we are at the end of the animation
	if (getTextureRect().left + spriteWidth_ * 2 > getTexture()->getSize().x)
	{
		//Check if we don't have any loops left
		if (--loops_ <= 0)
		{
			return false;
		}
	}

	//Change the texture rect based on where we are
	sf::IntRect rect(getTextureRect().left + spriteWidth_, 0, spriteWidth_, spriteWidth_);
	setTextureRect(rect);
	return true;
}
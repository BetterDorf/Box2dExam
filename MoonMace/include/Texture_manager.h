#pragma once
#include "SFML/Graphics.hpp"
#include "SpritePathes.h"

class Texture_manager
{
public:
	Texture_manager();

	sf::Texture& Request_texture(const SpritePath&);
	static Texture_manager* Get_instance() { return instance_; }

protected:
	std::map<std::string, sf::Texture> textures_;

	static Texture_manager* instance_;
};
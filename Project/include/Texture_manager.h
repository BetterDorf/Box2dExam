#pragma once
#include "SFML/Graphics.hpp"
#include "SpritePathes.h"

class Texture_manager
{
protected:
	Texture_manager() = default;
	std::map<std::string, sf::Texture> textures_;
	static Texture_manager* instance_;

public:
    //Singletons should not be cloneable.
        Texture_manager(Texture_manager& other) = delete;
	//Singletons should not be assignable.
		void operator=(const Texture_manager&) = delete;

	sf::Texture& Request_texture(const SpritePath&);
	static Texture_manager* Get_instance();
};
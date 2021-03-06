#include "Texture_manager.h"

#include <iostream>

Texture_manager* Texture_manager::instance_ = nullptr;

Texture_manager::Texture_manager()
{
	instance_ = this;
}


sf::Texture& Texture_manager::Request_texture(const SpritePath path)
{
	std::string texture_path = ConvertPathToString(path);

	//Check if we have the texture loaded
	if (!textures_.contains(texture_path)) 	{
		//If not, we load it and return the texture
		sf::Texture texture;
		texture.loadFromFile(texture_path);
		if (texture.getSize().x == 0) //check for invalid path
		{
			std::cerr << "Path is incorrect : " + texture_path;
		}
		textures_.emplace(texture_path, texture);
	}
	
	return  textures_.at(texture_path);
}
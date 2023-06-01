#pragma once
#include <SFML/Graphics.hpp>

#include "Font.h"



class Resources
{
public:
	static sf::Texture CharactersTexture;
	static sf::Texture IconsTexture;
	static sf::Texture TerrainTexture;
	static sf::Texture FontTexture;

	static Font* DefaultFont;
	
	Resources();
};


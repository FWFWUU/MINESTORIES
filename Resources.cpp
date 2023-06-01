#include "Resources.h"


sf::Texture Resources::CharactersTexture;
sf::Texture Resources::IconsTexture;
sf::Texture Resources::TerrainTexture;
sf::Texture Resources::FontTexture;

Font* Resources::DefaultFont = new Font(&FontTexture, sf::Vector2i(8, 8));

Resources::Resources()
{
	CharactersTexture.loadFromFile("Assets/Textures/chars.png");
	
	IconsTexture.loadFromFile("Assets/Textures/icons.png");
	
	TerrainTexture.loadFromFile("Assets/Textures/Terrain.png");
	
	FontTexture.loadFromFile("Assets/Textures/font.png");
}

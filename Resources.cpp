#include "Resources.h"

sf::Texture* Resources::CharactersTexture = new sf::Texture;
sf::Texture* Resources::IconsTexture = new sf::Texture;
sf::Texture* Resources::TerrainTexture = new sf::Texture;
sf::Texture* Resources::FontTexture = new sf::Texture;

Font* Resources::DefaultFont = new Font(FontTexture, sf::Vector2i(8, 8));

Resources::Resources()
{
	CharactersTexture->loadFromFile("Assets/Textures/chars.png");
	
	IconsTexture->loadFromFile("Assets/Textures/icons.png");
	
	TerrainTexture->loadFromFile("Assets/Textures/Terrain.png");
	
	FontTexture->loadFromFile("Assets/Textures/font.png");
}

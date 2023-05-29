#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "SpriteBatch.h"

class Font
{
private:
	sf::Texture* fontTexture = nullptr;
	//std::vector<sf::VertexArray*> vertices;
	//sf::VertexArray* vArr = nullptr;
	sf::Vector2i grid_size;

	const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz0123456789-[]., ><:()";
	const char ESPECIAL_COLOR_RED = '€';
	const char ESPECIAL_COLOR_YELLOW = '©';


public:
	Font(std::string font_filename, sf::Vector2i grid);
	Font(sf::Texture* texture, sf::Vector2i grid);

	void drawString(SpriteBatch& batch, const std::string& text, sf::Vector2f offset, int font_size, sf::Color color = sf::Color::White);
	//void drawChar(SpriteBatch& b, const char c, sf::Vector2f offset, int font_size)
};


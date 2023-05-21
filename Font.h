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

	const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";


public:
	Font(std::string font_filename);

	void drawString(SpriteBatch& batch, const std::string& text, sf::Vector2f offset);
};


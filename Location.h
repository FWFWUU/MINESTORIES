#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "tinyxml2/tinyxml2.h"
#include "SpriteBatch.h"
#include "Resources.h"

class Location
{
private:
	int mapWidth;
	int mapHeight;
	int tileSizeX;
	int tileSizeY;
	std::string data;

public:
	int* level;

	Location();
	void load(const char* location_name);
	void draw(SpriteBatch* b);

	sf::Texture texture;
};


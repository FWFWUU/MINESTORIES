#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "tinyxml2/tinyxml2.h"
#include "SpriteBatch.h"
#include "Resources.h"

struct LocationLayer {
	std::string name;
	std::string data;
	sf::VertexArray vArr;
};

class Location
{
private:
	std::string data;

public:
	static std::vector<Location*> locations;

	sf::VertexArray vArr;

	int* level;
	int mapWidth;
	int mapHeight;
	int tileSizeX;
	int tileSizeY;

	std::vector<LocationLayer*> layers;

	std::string name;


	Location();
	void load(const char* location_file, const char* location_name);
	void draw();
	void drawTile(sf::VertexArray& vArr, sf::Vector2i pos, sf::IntRect region);

	sf::Texture texture;
};

class LocationManager {
public:
	static std::vector<Location*> locations;

	std::string currentLocation;

	LocationManager();

	void loadLocation(const char* filename, const char* name);
	void draw(sf::RenderWindow* window);
};

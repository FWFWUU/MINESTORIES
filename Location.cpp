#include "Location.h"

//sf::Texture* Resources::TerrainTexture;

Location::Location() {
	texture.loadFromFile("Assets/Textures/Terrain.png");
}

void Location::load(const char* location_name)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(location_name);

	//	convert string to int

	mapWidth = std::stoi(doc.FirstChildElement("map")->FindAttribute("width")->Value());
	mapHeight = std::stoi(doc.FirstChildElement("map")->FindAttribute("width")->Value());

	tileSizeX = std::stoi(doc.FirstChildElement("map")->FindAttribute("tilewidth")->Value());
	tileSizeY = std::stoi(doc.FirstChildElement("map")->FindAttribute("tileheight")->Value());

	/*const int size = (mapWidth + mapHeight) * 16;

	level = new int[size] {-1};*/

	data = doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->GetText();

	
	//std::cout << data;
	

	//std::cout << newData << std::endl;

	/*for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {

		}
	}*/

	/*for (size_t index = 0; index < size; index++) {
		if (data[index + 1] != ',') {
			if (data[index] != '\n')
				strTileID += data[index];
		}
		else {
			level[index % size] = std::stoi(strTileID);

			//std::cout << level[index % size];

			strTileID = "";
		}
	}*/

	
}

void Location::draw(SpriteBatch* b)
{
	int xp = 0;
	int yp = 0;

	static std::string strTileID;

	for (size_t index = 0; index < data.size(); index++) {
		if (data[index] != ',' && index + 1 != data.size()) {
			if (data[index] != '\n') {
				strTileID += data[index];
			}
		} else {
			if (std::stoi(strTileID) == 85) {
				b->draw(Resources::TerrainTexture, sf::FloatRect(xp * tileSizeX, yp * tileSizeY, 16, 16), sf::IntRect(0, 0, 16, 16));
			}
			else {
				b->draw(Resources::TerrainTexture, sf::FloatRect(xp * tileSizeX, yp * tileSizeY, 16, 16), sf::IntRect(16, 0, 16, 16));
			}

			if (xp < mapWidth) {
				xp++;
			}
			else {
				xp = 0;
				yp++;
			}

			strTileID = "";
		}

	}
}

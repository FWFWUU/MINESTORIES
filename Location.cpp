#include "Location.h"

//sf::Texture* Resources::TerrainTexture;

std::vector<Location*> LocationManager::locations;

Location::Location() {
	//texture.loadFromFile("Assets/Textures/Terrain.png");
}

void Location::load(const char* location_file, const char* location_name)
{
	name = location_name;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(location_file);

	//	convert string to int

	mapWidth = std::stoi(doc.FirstChildElement("map")->FindAttribute("width")->Value());
	mapHeight = std::stoi(doc.FirstChildElement("map")->FindAttribute("width")->Value());

	tileSizeX = std::stoi(doc.FirstChildElement("map")->FindAttribute("tilewidth")->Value());
	tileSizeY = std::stoi(doc.FirstChildElement("map")->FindAttribute("tileheight")->Value());

	
	
	for (tinyxml2::XMLElement* el = doc.FirstChildElement("map")->FirstChildElement("layer"); el; el = el->NextSiblingElement("layer")) {
		LocationLayer* layer = new LocationLayer;
		layer->data = el->FirstChildElement("data")->GetText();
		layer->name = el->Attribute("name");
		layer->vArr.setPrimitiveType(sf::Quads);
		layer->vArr.resize(mapWidth * mapHeight * 4);

		layers.push_back(layer);
		
		//std::cout << el->Attribute("name") << std::endl;
	}
	

	std::string texturePath = doc.FirstChildElement("map")->FirstChildElement("tileset")->FirstChildElement("image")->Attribute("source");

	while (texturePath.find("..") != std::string::npos)
		texturePath.replace(texturePath.find(".."), 2, "Assets");


	texture.loadFromFile(texturePath);

	

	//vArr.setPrimitiveType(sf::Quads);
	//vArr.resize(mapWidth * mapHeight * 4);
	
}

void Location::build()
{
	for (LocationLayer* layer : layers) {
		int xp = 0;
		int yp = 0;

		static std::string strTileID;

		for (size_t index = 0; index < layer->data.size(); index++) {
			if (layer->data[index] != ',' && index + 1 != layer->data.size()) {
				if (layer->data[index] != '\n') {
					strTileID += layer->data[index];
				}
			}
			else {
				if (std::stoi(strTileID) != 0)
					drawTile(layer->vArr, sf::Vector2i(xp, yp), sf::IntRect((std::stoi(strTileID) - 1) * tileSizeX, 0, 16, 16));
				else
					drawTile(layer->vArr, sf::Vector2i(xp, yp), sf::IntRect((std::stoi(strTileID) - 1) * tileSizeX, 0, 16, 16), sf::Color(0,0,0,0));
				

				if (xp + 1 < mapWidth) {
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
}

void Location::drawTile(sf::VertexArray& vArr, sf::Vector2i pos, sf::IntRect region, sf::Color albedo)
{
	sf::Vertex* v = &vArr[(pos.x + pos.y * mapWidth) * 4]; // vArr[[v0, v1, v2, v3], [v0, v1, v2, v3]]

	v[0].position = sf::Vector2f(0, 0) + sf::Vector2f(pos.x * 16, pos.y * 16);
	v[1].position = sf::Vector2f(tileSizeX, 0) + sf::Vector2f(pos.x * 16, pos.y * 16);
	v[2].position = sf::Vector2f(tileSizeX, tileSizeY) + sf::Vector2f(pos.x * 16, pos.y * 16);
	v[3].position = sf::Vector2f(0, tileSizeY) + sf::Vector2f(pos.x * 16, pos.y * 16);

	v[0].color = albedo;
	v[1].color = albedo;
	v[2].color = albedo;
	v[3].color = albedo;

	//v[0].color.a = 0.0;
	//v[1].color.a = 0.0;
	//v[2].color.a = 0.0;
	//v[3].color.a = 0.0;

	v[0].texCoords = sf::Vector2f(region.left, region.top);
	v[1].texCoords = sf::Vector2f(region.width + region.left, region.top);
	v[2].texCoords = sf::Vector2f(region.width + region.left, region.height + region.top);
	v[3].texCoords = sf::Vector2f(region.left, region.height + region.top);
}

int Location::getTile(const char* layer_name, float x, float y, int replace_tile)
{
	for (int i = 0; i < layers.size(); i++) {
		if (layers[i]->name == layer_name) {
			std::string tileId = "";
			int xT = 0;
			int yT = 0;

			for (int index = 0; index < layers[i]->data.size(); index++) {
				if (layers[i]->data[index] != ',') {
					if (layers[i]->data[index] != '\n')
						tileId += layers[i]->data[index];
				}
				else {
					if (xT == x && yT == y) {
						if (replace_tile > -1) {
							layers[i]->data.replace(index - 1, 1, std::to_string(replace_tile));

							//std::cout << layers[i]->data << std::endl;
						}

						return std::stoi(tileId);
					}

					if (xT + 1 < mapWidth) {
						xT++;
					}
					else {
						xT = 0;
						yT++;
					}

					tileId = "";
				}
			}
		}
	}

	return -1;
}


LocationManager::LocationManager()
{
}

void LocationManager::loadLocation(const char* filename, const char* name)
{
	Location* location = new Location;
	location->load(filename, name);

	locations.push_back(location);
}

void LocationManager::draw(sf::RenderWindow* window)
{
	
}

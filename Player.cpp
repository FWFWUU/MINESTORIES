#include "Player.h"

Player::Player(std::string name, sf::Vector2f i_pos): Character(name, i_pos) {

	Object2D* obj = new Object2D({
		Vector2(-10, -5),
		Vector2(10, -5),
		Vector2(5, 5),
		Vector2(-5, 5),
		}, Vector2(pos_in_world.x, pos_in_world.y), Vector2(0, 0));
	//setObject(*obj);

	hitbox = new BoundingBox(20, 32, pos_in_world.x, pos_in_world.y);
		
	sf::Texture * tex = new sf::Texture();

	tex->loadFromFile("Assets/chars.png");

	this->sprite->AddTextureImage(*tex);
	this->sprite->AddRegion(sf::IntRect(0, 0, 20, 32));
	this->sprite->AddRegion(sf::IntRect(20, 0, 20, 32));
	this->sprite->AddRegion(sf::IntRect(40, 0, 20, 32));
	this->sprite->AddRegion(sf::IntRect(60, 0, 20, 32));
}

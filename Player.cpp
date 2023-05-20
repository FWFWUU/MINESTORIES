#include "Player.h"

Player::Player(): Character("player") {
	Object2D* obj = new Object2D({
		Vector2(-5, -5),
		Vector2(5, -5),
		Vector2(5, 5),
		Vector2(-5, 5),
		}, Vector2(pos_in_world.x, pos_in_world.y));
	setObject(*obj);

	sf::Texture * tex = new sf::Texture();

	tex->loadFromFile("Assets/chars.png");

	this->sprite->AddTextureImage(*tex);
	this->sprite->AddRegion(sf::IntRect(0, 0, 20, 32));
	this->sprite->AddRegion(sf::IntRect(20, 0, 20, 32));
	this->sprite->AddRegion(sf::IntRect(40, 0, 20, 32));
	this->sprite->AddRegion(sf::IntRect(60, 0, 20, 32));
}
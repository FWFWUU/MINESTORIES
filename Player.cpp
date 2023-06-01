#include "Player.h"

//sf::Texture* Resources::CharactersTexture;

Player::Player(std::string name, sf::Vector2f i_pos): Character(name, i_pos) {

	//this->sprite->AddTextureImage(Resources::CharactersTexture);
	
	AnimationFrame* forward = sprite->AddAnimation("forward", Resources::CharactersTexture);
	forward->regions.push_back(sf::IntRect(0, 0, 20, 33));
	forward->regions.push_back(sf::IntRect(20, 0, 20, 33));
	forward->regions.push_back(sf::IntRect(40, 0, 20, 33));
	forward->regions.push_back(sf::IntRect(60, 0, 20, 33));

	AnimationFrame* backward = sprite->AddAnimation("backward", Resources::CharactersTexture);

	backward->regions.push_back(sf::IntRect(0, 33, 20, 33));
	backward->regions.push_back(sf::IntRect(20, 33, 20, 33));
	backward->regions.push_back(sf::IntRect(40, 33, 20, 33));
	backward->regions.push_back(sf::IntRect(60, 33, 20, 33));

	sprite->currentAnimation = "forward";
}

void Player::update(float dt) {
	Character::update(dt);

	sf::Vector2f impulse;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		impulse.x = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		impulse.x = 1;
	else
		impulse.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		impulse.y = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		impulse.y = 1;
	else
		impulse.y = 0;

	if (impulse.y > 0)
		sprite->currentAnimation = "forward";
	if (impulse.y < 0)
		sprite->currentAnimation = "backward";

	if (impulse.y == 0)
		sprite->playing = false;
	else
		sprite->playing = true;

	moveTo(impulse.x, impulse.y);
}
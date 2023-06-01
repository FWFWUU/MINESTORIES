#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "AnimatedSprite.h"
#include "Physics.h"
#include "Resources.h"

class Character {
private:
	static std::vector<Character*> characters;

public:
	sf::Vector2f pos_in_world; //position

	sf::Vector2f localPosition = sf::Vector2f(0, 0); //pivot
	sf::Vector2f globalPosition = sf::Vector2f(0, 0); //position
	
	std::string name;
	
	sf::Vector2f impulse;
	
	sf::Vector2f velocity; //acceleration
	
	AnimatedSprite* sprite;
	
	BoundingBox* hitbox = nullptr;
	
	sf::RectangleShape* rr = nullptr;

	float speed = 2.0f;

	static const enum Faces {
		DirectionForward,
		DirectionBackward,
		DirectionLeft,
		DirectionRught
	};

	uint8_t faceDirection = DirectionBackward;

	Character(std::string name, sf::Vector2f i_pos) : name(name), globalPosition(i_pos) {
		Character::characters.push_back(this);

		sprite = new AnimatedSprite();
		sprite->setPosition(globalPosition);

		rr = new sf::RectangleShape(sf::Vector2f(32, 32));
		rr->setPosition(globalPosition);

		hitbox = new BoundingBox(8, 32 / 2, globalPosition.x - (8 / 2), globalPosition.y);
	};

	void moveTo(float dx, float dy);
	void draw(sf::RenderWindow& window);
	virtual void update(float dt);
	void moveSingleAxis(float dx, float dy);

	sf::Vector2f getPivot();

	static std::vector<Character*> getCharactersList();
};
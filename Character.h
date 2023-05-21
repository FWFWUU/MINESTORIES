#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "AnimatedSprite.h"
#include "Physics.h"

class Character {
private:
	static std::vector<Character*> chars_list;
	Object2D* object = nullptr;

public:
	sf::Vector2f pos_in_world;
	std::string name;
	sf::Vector2f impulse;
	sf::Vector2f velocity;
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

	Character(std::string name, sf::Vector2f i_pos) : name(name), pos_in_world(i_pos) {
		Character::chars_list.push_back(this);

		sprite = new AnimatedSprite();

		rr = new sf::RectangleShape(sf::Vector2f(32, 32));
	};

	void moveTo(float dx, float dy);
	void setObject(Object2D& object);
	void draw(sf::RenderWindow& window);
	void update(sf::Time& dt);
	void moveSingleAxis(float dx, float dy);

	static std::vector<Character*> getCharactersList();
};
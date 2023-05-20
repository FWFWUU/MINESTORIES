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

	float speed = 2.0f;

	Character(std::string name);

	void Show(sf::RenderWindow & window);
	void Move(float dx, float dy);
	void setObject(Object2D& object);
};
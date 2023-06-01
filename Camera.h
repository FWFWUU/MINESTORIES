#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"

class Camera
{
public:
	sf::View view;
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::RectangleShape* rect_draw;

	sf::RenderWindow* window;

	int camera_view_margin = 100;
	float smooth_speed = 5.f;

	Character* target = nullptr;

	Camera(sf::RenderWindow& w);
	void attachTarget(Character& c);
	void update(float dt);
};


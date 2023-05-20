#pragma once
#include "Character.h"
#include <iostream>

class Player :
	public Character
{
public:
	Player(std::string name, sf::Vector2f i_pos);
};


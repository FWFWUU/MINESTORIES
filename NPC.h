#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

class NPC: public Character
{
public:
	NPC(std::string name, sf::Vector2f startPosition);
};


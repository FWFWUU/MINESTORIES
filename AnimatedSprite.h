#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class AnimatedSprite :
	public sf::Sprite
{
public:
	std::vector<sf::IntRect> regions;

	float time = 0.2f;
	int region_index = 0;
	bool playing = true;
	bool alpha = false;

	sf::Clock timer;

	AnimatedSprite();

	void AddRegion(sf::IntRect region);
	void AddTextureImage(sf::Texture &texture);
	void PlayAnimation(bool loop);
};


#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct AnimationFrame {
	std::string name;
	std::vector<sf::IntRect> regions;

	sf::Texture* texture;
};

class AnimatedSprite :
	public sf::Sprite
{
private:
	static std::vector<sf::Sprite*> sprites_list;

public:
	std::vector<AnimationFrame*> frames;
	std::vector<sf::IntRect> regions;

	float time = 0.2f;
	int region_index = 0;
	bool playing = true;
	bool alpha = false;

	std::string currentAnimation = "DEFAULT";

	sf::Clock timer;

	AnimatedSprite();

	AnimationFrame* AddAnimation(const std::string& name, sf::Texture& texture);
	void AddTextureImage(sf::Texture& texture);
	void PlayAnimation(bool loop);

	static std::vector<sf::Sprite*> getSpritesList();
};


#pragma once
#include <SFML/Graphics.hpp>

class SpriteBatch
{
public:
	SpriteBatch(sf::RenderWindow* window);

	void draw(sf::Texture* texture, sf::FloatRect rect, sf::IntRect region, sf::Color color = sf::Color::White);
	void reset();
	void show(sf::RenderWindow& window);
	void display();
	sf::RenderWindow* getWindow();

private:
	sf::VertexArray varray;
	sf::RenderTexture rtext;
	sf::Sprite sprite;
	sf::RenderWindow* rwindow = nullptr;
};

/*
..ready..
Texture texture;
Game.SpriteBatch();

..update..

Game.SpriteBatch.reset();

Game.SpriteBatch.draw(texture, rect, region);

window.draw(Game.SpriteBatch())

*/

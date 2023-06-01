#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Batch {
	sf::Texture texture;

	std::vector<sf::Vertex> vertices;
	
	unsigned int count_v = 0;
	unsigned int in = 0;



	void begin() {
		if (count_v > 0) {
			count_v = 0;
			in = 0;
		}
		else {
			in++;
		}
	};
	void draw(sf::FloatRect& r, sf::IntRect& g, sf::Color& c) {
		size_t count = count_v * 4;

		if (count_v + 4 > vertices.size())
			vertices.resize(vertices.size() + 4);


		vertices[count + 0].position = sf::Vector2f(0, 0) + sf::Vector2f(r.left, r.top);
		vertices[count + 1].position = sf::Vector2f(r.width, 0) + sf::Vector2f(r.left, r.top);
		vertices[count + 2].position = sf::Vector2f(r.width, r.height) + sf::Vector2f(r.left, r.top);
		vertices[count + 3].position = sf::Vector2f(0, r.height) + sf::Vector2f(r.left, r.top);

		vertices[count + 0].color = c;
		vertices[count + 1].color = c;
		vertices[count + 2].color = c;
		vertices[count + 3].color = c;

		vertices[count + 0].texCoords = sf::Vector2f(g.left, g.top);
		vertices[count + 1].texCoords = sf::Vector2f(g.width + g.left, g.top);
		vertices[count + 2].texCoords = sf::Vector2f(g.width + g.left, g.height + g.top);
		vertices[count + 3].texCoords = sf::Vector2f(g.left, g.height + g.top);

		count_v++;
	};
};

class SpriteBatch
{
public:
	std::vector<sf::Vertex> vertices;
	std::vector<Batch*> batchs;

	SpriteBatch(sf::RenderWindow* window);

	void reset();
	void show(sf::RenderWindow& window);
	void display();
	sf::RenderWindow* getWindow();


	void draw(sf::Texture& texture, const sf::FloatRect& rect, const sf::IntRect& region, sf::Color color = sf::Color::White);
	//void applyBuffer();

private:
	sf::VertexArray varr;
	sf::RenderTexture rtext;
	sf::Sprite sprite;
	sf::RenderWindow* rwindow = nullptr;

	unsigned int l_count = 0;
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

#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(sf::RenderWindow* window)
{
	//rtext.create(1024, 600);

	rwindow = window;
}

void SpriteBatch::draw(sf::Texture* texture, sf::FloatRect rect, sf::IntRect region, sf::Color color)
{
	sf::VertexArray varray(sf::Quads, 4);

	sf::RenderStates states;

	varray[0].position = sf::Vector2f(0, 0) + sf::Vector2f(rect.left, rect.top);
	varray[1].position = sf::Vector2f(rect.width, 0) + sf::Vector2f(rect.left, rect.top);
	varray[2].position = sf::Vector2f(rect.width, rect.height) + sf::Vector2f(rect.left, rect.top);
	varray[3].position = sf::Vector2f(0, rect.height) + sf::Vector2f(rect.left, rect.top);

	varray[0].color = color;
	varray[1].color = color;
	varray[2].color = color;
	varray[3].color = color;

	varray[0].texCoords = sf::Vector2f(region.left, region.top);
	varray[1].texCoords = sf::Vector2f(region.width + region.left, region.top);
	varray[2].texCoords = sf::Vector2f(region.width + region.left, region.height + region.top);
	varray[3].texCoords = sf::Vector2f(region.left, region.height + region.top);

	/*states.texture = &texture;
	states.transform = sf::Transform();
	states.transform.translate(position);*/

	rwindow->draw(varray, texture);

	/*sf::Sprite spr(texture);
	spr.setTextureRect(region);

	rtext.draw(spr);*/
}

void SpriteBatch::reset()
{
	//reset vertex
	//rtext.clear();
}

void SpriteBatch::show(sf::RenderWindow& window)
{
	
	//rtext.display();

	//sprite.setTexture(rtext.getTexture());

	//window.draw(sprite);
}

void SpriteBatch::display()
{
	//rtext.display();
}

sf::RenderWindow* SpriteBatch::getWindow() {
	return rwindow;
}
#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(sf::RenderWindow* window)
{
	//rtext.create(1024, 600);

	rwindow = window;
}

void SpriteBatch::draw(sf::Texture& texture, sf::FloatRect rect, sf::IntRect region)
{
	sf::VertexBuffer vbuffer;
	vbuffer.setPrimitiveType(sf::Quads);

	sf::Vertex v[4];
	sf::RenderStates states;

	v[0].position = sf::Vector2f(0, 0) + sf::Vector2f(rect.left, rect.top);
	v[1].position = sf::Vector2f(rect.width, 0) + sf::Vector2f(rect.left, rect.top);
	v[2].position = sf::Vector2f(rect.width, rect.height) + sf::Vector2f(rect.left, rect.top);
	v[3].position = sf::Vector2f(0, rect.height) + sf::Vector2f(rect.left, rect.top);

	//v[0].color = sf::Color::Red;
	//v[1].color = sf::Color::Green;
	//v[2].color = sf::Color::Blue;
	//v[3].color = sf::Color::Cyan;

	v[0].texCoords = sf::Vector2f(region.left, region.top);
	v[1].texCoords = sf::Vector2f(region.width + region.left, region.top);
	v[2].texCoords = sf::Vector2f(region.width + region.left, region.height + region.top);
	v[3].texCoords = sf::Vector2f(region.left, region.height + region.top);
	
	vbuffer.create(4);
	vbuffer.update(v);

	/*states.texture = &texture;
	states.transform = sf::Transform();
	states.transform.translate(position);*/

	rwindow->draw(vbuffer, &texture);

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

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <memory>
#include "Player.h"
#include "Camera.h"
#include "Physics.h"
#include "Font.h"
#include "SpriteBatch.h"

const std::string GAME_NAME = "MINESTORIES";
const std::vector<std::string> SUBTITLES{
	"Revenge", "Subjection Edition", "Go! Go! Go!"
};

class Game {
public:
	sf::RenderWindow* window;
	sf::Sprite curSprite;
	sf::Texture cur_texture;
	sf::Image * window_icon;
	sf::IntRect cur_tex_rect;

	Player* player;

	int count_spr_sort = 0;
	bool paused = false;

	Camera* camera;

	sf::Clock deltaTime;

	Physics physics;

	Font* testFont;

	SpriteBatch* batch;
	

	Game() {
		srand(time(NULL)); //generate random seed

		int rand_subtitle_pos = rand() % SUBTITLES.size();

		window = new sf::RenderWindow(sf::VideoMode(1024, 600), GAME_NAME + ": " + SUBTITLES[rand_subtitle_pos]);
		window->setVerticalSyncEnabled(true);
		window->setFramerateLimit(60.0);

		window_icon = new sf::Image();
		window_icon->loadFromFile("Assets/w_icon.png");
		
		window->setIcon(16, 16, window_icon->getPixelsPtr());

		cur_tex_rect.height = 8;
		cur_tex_rect.width = 8;
		
		cur_texture.loadFromFile("Assets/icons.png", this->cur_tex_rect);

		curSprite.setTexture(cur_texture);
		curSprite.setScale(sf::Vector2f(1.2, 1.2));
		

		player = new Player("player", sf::Vector2f(10, 10));

		camera = new Camera();
		camera->view->setSize(window->getSize().x / 2, window->getSize().y / 2);

		testFont = new Font("Assets/font.png");

		batch = new SpriteBatch(window);
	}

	void sort_sprites() {
		for (int i = 0; i < AnimatedSprite::getSpritesList().size(); i++) {
			if (i + 1 < AnimatedSprite::getSpritesList().size()) {
				if (AnimatedSprite::getSpritesList()[i]->getLocalBounds().intersects(AnimatedSprite::getSpritesList()[i + 1]->getLocalBounds())) {
					if (AnimatedSprite::getSpritesList()[i]->getPosition().y > AnimatedSprite::getSpritesList()[i + 1]->getPosition().y) {
						std::iter_swap(AnimatedSprite::getSpritesList()[i], AnimatedSprite::getSpritesList()[i + 1]);
					}
				}
			}

			window->draw(*AnimatedSprite::getSpritesList()[i]);
		}

	}

	void startWorld() {
		//start world here

		Player* clone;
		clone = new Player("NPC", sf::Vector2f(0, 0));
	}

	void update(sf::Time dt) {
		physics.update(dt);

		camera->FollowCharacter(*player, *window, dt);
		
		sort_sprites();

		sf::Vector2f impulse;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			impulse.x = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			impulse.x = 1;
		else
			impulse.x = 0;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			impulse.y = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			impulse.y = 1;
		else
			impulse.y = 0;
		
		player->moveTo(impulse.x, impulse.y);

		for (Character* chara : Character::getCharactersList()) {
			chara->draw(*window);
			chara->update(dt);
		}

		BoundingBox bb = BoundingBox(3, 3, curSprite.getPosition().x, curSprite.getPosition().y);

		//batch->reset();

		batch->draw(cur_texture, sf::FloatRect(32, 32, 32, 32), sf::IntRect(0, 0, 8, 8));

		if (player->hitbox->intersects(bb)) {
			batch->draw(cur_texture, sf::FloatRect(bb.x - 5, bb.y - 5, 32, 32), sf::IntRect(0, 0, 8, 8));
		}
		
		testFont->drawString(*batch, "haaaaaaaaaai", sf::Vector2f(0, 0));

		//batch->show(*window);
	}

	void Listen(sf::Event& event) {
		if (event.type == sf::Event::Closed) {
			this->window->close();
		}
		if (event.type == sf::Event::Resized) {
			this->camera->view->setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
		}
		if (event.type == sf::Event::MouseEntered) {
			this->window->setMouseCursorVisible(false);
		}
		if (event.type == sf::Event::MouseLeft) {
			this->window->setMouseCursorVisible(true);
		}
		if (event.type == sf::Event::LostFocus) {
			paused = true;
		}
	}

	void run() {
		while (window->isOpen()) {
			sf::Event e;
			
			while (window->pollEvent(e)) {
				Listen(e);
			}

			curSprite.setPosition(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

			window->setView(*camera->view);
			//batch->display();
			window->clear();

			update(deltaTime.restart());

			/*for (int i = 0; i < Object2D::getObjects().size(); i++) {
				Object2D* obj = Object2D::getObjects()[i % Object2D::getObjects().size()];


				sf::VertexArray triangles(sf::Quads, obj->vertices.size());

				for (int j = 0; j < obj->vertices.size(); j++) {
					triangles[j].position = sf::Vector2f(obj->vertices[j].x + obj->position.x, obj->vertices[j].y + obj->position.y);
					
					if (obj->intersection)
						triangles[j].color = sf::Color::Red;
					else
						triangles[j].color = sf::Color::Blue;
				}

				this->window->draw(triangles);
			}*/

			//testFont->drawString(*window, "Hello", sf::Vector2f(0, 0));

			window->draw(curSprite);
			window->display();
		}
	}
};

int main()
{
	
	Game* game = new Game();
	game->startWorld();
	game->run();
	
	return 0;
}
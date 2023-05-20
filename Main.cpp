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

const std::string GAME_NAME = "MINESTORIES";
const std::vector<std::string> SUBTITLES{
	"Revenge", "Subjection Edition", "Go! Go! Go!"
};

class Game {
public:
	sf::RenderWindow* window;
	sf::Sprite cur;
	sf::Texture cur_texture;
	sf::Image * window_icon;
	sf::IntRect cur_tex_rect;

	std::vector<sf::Sprite*> sprites;

	Player* player;
	Player* clone;

	int count_spr_sort = 0;
	bool paused = false;

	Camera* camera;

	sf::Clock deltaTime;

	Physics physics;
	

	Game() {
		srand(time(NULL)); //generate random seed

		int rand_subtitle_pos = rand() % SUBTITLES.size();

		this->window = new sf::RenderWindow(sf::VideoMode(1024, 600), GAME_NAME + ": " + SUBTITLES[rand_subtitle_pos]);
		this->window->setVerticalSyncEnabled(true);
		this->window->setFramerateLimit(60.0);

		this->window_icon = new sf::Image();
		this->window_icon->loadFromFile("Assets/w_icon.png");
		
		this->window->setIcon(16, 16, this->window_icon->getPixelsPtr());

		this->cur_tex_rect.height = 8;
		this->cur_tex_rect.width = 8;

		

		this->cur_texture.loadFromFile("Assets/icons.png", this->cur_tex_rect);

		this->cur.setTexture(this->cur_texture);
		this->cur.setScale(sf::Vector2f(1.2, 1.2));
		

		this->player = new Player;

		this->clone = new Player;

		sprites.push_back(player->sprite);
		sprites.push_back(clone->sprite);

		camera = new Camera();
		camera->view->setSize(window->getSize().x / 2, window->getSize().y / 2);

		
	}

	void sort_sprites() {
		for (int i = 0; i < sprites.size(); i++) {
			if (i + 1 < sprites.size()) {
				if (sprites[i]->getLocalBounds().intersects(sprites[i + 1]->getLocalBounds())) {
					if (sprites[i]->getPosition().y > sprites[i + 1]->getPosition().y) {
						std::iter_swap(sprites[i], sprites[i + 1]);
					}
				}
			}

			window->draw(*sprites[i]);
		}

	}

	void TestWorld(sf::Time dt) {
		physics.update(dt);

		this->camera->FollowCharacter(*player, *window, dt);
		
		player->Show(*window);
		clone->Show(*window);
		
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
		
		this->player->Move(impulse.x, impulse.y);
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

	void Run() {
		while (this->window->isOpen()) {
			sf::Event e;
			
			while (window->pollEvent(e)) {
				this->Listen(e);
			}

			this->cur.setPosition(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)));

			this->window->setView(*this->camera->view); //this->window->setView(this->v);

			this->window->clear();

			this->TestWorld(deltaTime.restart());

			for (int i = 0; i < Object2D::getObjects().size(); i++) {
				Object2D* obj = Object2D::getObjects()[i % Object2D::getObjects().size()];


				sf::VertexArray triangles(sf::Quads, obj->vertices.size());

				for (int j = 0; j < obj->vertices.size(); j++) {
					triangles[j].position = sf::Vector2f(obj->vertices[j].x + obj->position.x, obj->vertices[j].y + obj->position.y);
					triangles[j].color = sf::Color::Red;
				}

				this->window->draw(triangles);
			}

			this->window->draw(this->cur);
			this->window->display();
		}
	}
};

int main()
{
	
	Game* game = new Game();
	game->Run();
	
	return 0;
}
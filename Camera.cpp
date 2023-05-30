#include "Camera.h"

Camera::Camera() {
	view = new sf::View();
	rect_draw = new sf::RectangleShape();
}

void Camera::FollowCharacter(Character& chara, sf::RenderWindow& window, float dt) {
	
	direction = sf::Vector2f(0, 0);

	sf::Vector2f chara_pos_screen(window.mapCoordsToPixel(chara.getPivot()));

	/*if ((chara_pos_screen.x - 32) < std::floor(view->getSize().x - camera_view_margin)) {
		direction.x = -1;
	}
	if ((chara_pos_screen.x + 32) > std::floor(view->getSize().x + camera_view_margin)) {
		direction.x = 1;
	}
	if ((chara_pos_screen.y - 32) < std::floor(view->getSize().y - (camera_view_margin / 2))) {
		direction.y = -1;
	}
	if ((chara_pos_screen.y + 32) > std::floor(view->getSize().y + (camera_view_margin / 2))) {
		direction.y = 1;
	}*/

	if ((chara_pos_screen.x - 32) < 0) {
		direction.x = -1;
	}
	if ((chara_pos_screen.x + 32) > 0) {
		direction.x = 1;
	}
	if ((chara_pos_screen.y - 32) < 0) {
		direction.y = -1;
	}
	if ((chara_pos_screen.y + 32) > 0) {
		direction.y = 1;
	}

	sf::Vector2f diff = chara.getPivot() - view->getCenter();

	if (direction.x != 0 || direction.y != 0) {
		view->move(diff * (dt * smooth_speed * 0.5f));

		diff = chara.getPivot() - view->getCenter();

		if ((std::abs(diff.x) < 1.f && std::abs(diff.y) < 1.f)) {
			view->setCenter(chara.getPivot());
			direction = sf::Vector2f(0, 0);
		}
	}

	//view->setCenter(chara.pos_in_world);

	rect_draw->setSize(sf::Vector2f(view->getSize().x / 2, view->getSize().y / 2));
	rect_draw->setPosition(view->getCenter());
	rect_draw->setOrigin(sf::Vector2f(rect_draw->getSize().x / 2, rect_draw->getSize().y / 2));
	rect_draw->setOutlineColor(sf::Color::Blue);
	rect_draw->setOutlineThickness(1.0);
	rect_draw->setFillColor(sf::Color::Transparent);

	window.draw(*rect_draw);
}
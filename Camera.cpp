#include "Camera.h"

Camera::Camera() {
	view = new sf::View();
	rect_draw = new sf::RectangleShape();
}

void Camera::FollowCharacter(Character& chara, sf::RenderWindow& window, sf::Time dt) {
	
	direction = sf::Vector2f(0, 0);

	sf::Vector2f chara_pos_screen(window.mapCoordsToPixel(chara.pos_in_world));

	if ((chara_pos_screen.x - 32) < view->getSize().x - camera_view_margin) {
		direction.x = -1;
	}
	if ((chara_pos_screen.x + 32) > view->getSize().x + camera_view_margin) {
		direction.x = 1;
	}
	if ((chara_pos_screen.y - 32) < view->getSize().y - (camera_view_margin / 2)) {
		direction.y = -1;
	}
	if ((chara_pos_screen.y + 32) > view->getSize().y + (camera_view_margin / 2)) {
		direction.y = 1;
	}

	sf::Vector2f diff = chara.pos_in_world - view->getCenter();

	if (direction.x != 0 || direction.y != 0) {
		view->move(diff * (dt.asSeconds() * smooth_speed * 0.5f));

		diff = chara.pos_in_world - view->getCenter();

		if ((std::abs(diff.x) < 1.f && std::abs(diff.y) < 1.f)) {
			view->setCenter(chara.pos_in_world);
		}
	}

	//view->setCenter(chara.pos_in_world);

	rect_draw->setSize(sf::Vector2f(camera_view_margin * 2, camera_view_margin));
	rect_draw->setPosition(view->getCenter());
	rect_draw->setOrigin(sf::Vector2f((camera_view_margin * 2) / 2, camera_view_margin / 2));
	rect_draw->setOutlineColor(sf::Color::Blue);
	rect_draw->setOutlineThickness(1.0);
	rect_draw->setFillColor(sf::Color::Transparent);

	window.draw(*rect_draw);
}
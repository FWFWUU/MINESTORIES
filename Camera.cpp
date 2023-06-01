#include "Camera.h"


Camera::Camera(sf::RenderWindow& w)
{
	window = &w;

	rect_draw = new sf::RectangleShape();
}

void Camera::attachTarget(Character& c) {
	
	target = &c;
}

void Camera::update(float dt)
{
	window->setView(view);
	view.setSize(window->getSize().x / 2, window->getSize().y / 2);

	direction = sf::Vector2f(0, 0);

	if (target) {
		sf::Vector2f chara_pos_screen(window->mapCoordsToPixel(target->globalPosition));

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

		sf::Vector2f diff = target->globalPosition - view.getCenter();

		if (direction.x != 0 || direction.y != 0) {
			view.move(diff * (dt * smooth_speed * 0.5f));

			diff = target->globalPosition - view.getCenter();

			if ((std::abs(diff.x) < 1.f && std::abs(diff.y) < 1.f)) {
				view.setCenter(target->globalPosition);
				direction = sf::Vector2f(0, 0);
			}
		}

		/*rect_draw->setSize(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
		rect_draw->setPosition(view.getCenter());
		rect_draw->setOrigin(sf::Vector2f(rect_draw->getSize().x / 2, rect_draw->getSize().y / 2));
		rect_draw->setOutlineColor(sf::Color::Blue);
		rect_draw->setOutlineThickness(1.0);
		rect_draw->setFillColor(sf::Color::Transparent);

		window->draw(*rect_draw);*/
	}
}

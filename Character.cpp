#include "Character.h"

std::vector<Character*> Character::chars_list;


void Character::moveTo(float dx, float dy) {
	if (dx != 0)
		moveSingleAxis(dx, 0);
	if (dy != 0)
		moveSingleAxis(0, dy);
}

void Character::moveSingleAxis(float dx, float dy) {
	velocity.x = dx * speed * 0.05;
	velocity.y = dy * speed * 0.05;

	hitbox->x += velocity.x;
	hitbox->y += velocity.y;

	for (Character* chara : chars_list) {
		if (chara != this) {
			if (hitbox) {
				if (chara->hitbox) {
					if (hitbox->intersects(*chara->hitbox)) {
						if (dx > 0)
							hitbox->x = chara->hitbox->x - chara->hitbox->width;

						if (dx < 0)
							hitbox->x = chara->hitbox->right();
						
						if (dy > 0)
							hitbox->y = chara->hitbox->y - chara->hitbox->height;

						if (dy < 0)
							hitbox->y = chara->hitbox->bottom();
					}
				}
			}
		}
	}
}

void Character::setObject(Object2D& obj)
{
	object = &obj;
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(*rr);
}

void Character::update(sf::Time& dt) {
	if (hitbox) {
		pos_in_world.x = hitbox->x - (hitbox->width / 2);
		pos_in_world.y = hitbox->y - (hitbox->height / 2);

		rr->setPosition(pos_in_world.x, pos_in_world.y);
		rr->setSize(sf::Vector2f(hitbox->width, hitbox->height));
		rr->setFillColor(sf::Color::Transparent);
		rr->setOutlineThickness(1.0);
		rr->setOutlineColor(sf::Color::Green);
	}

	sprite->setPosition(pos_in_world);
	sprite->PlayAnimation(true);
}

std::vector<Character*> Character::getCharactersList() {
	return chars_list;
}
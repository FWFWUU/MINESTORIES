#include "Character.h"

std::vector<Character*> Character::characters;


void Character::moveTo(float dx, float dy) {
	if (dx != 0)
		moveSingleAxis(dx, 0);
	if (dy != 0)
		moveSingleAxis(0, dy);
}

void Character::moveSingleAxis(float dx, float dy) {
	velocity.x = dx * speed;
	velocity.y = dy * speed;

	hitbox->x += velocity.x;
	hitbox->y += velocity.y;

	bool collides = false;

	//hitbox->x = (globalPosition.x - 32);
	//hitbox->y = (globalPosition.y);

	for (Character* chara : characters) {
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
						
						collides = true;
					}
				}
			}
		}
	}

	if (!collides) {
		globalPosition.x += velocity.x;
		globalPosition.y += velocity.y;
	}
}

sf::Vector2f Character::getPivot()
{
	return localPosition;
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(*rr);
}

void Character::update(float dt) {
	//std::cout << name << "=" << localPosition.y << std::endl;

	if (hitbox) {

		//pos_in_world.x = hitbox->x - (hitbox->width / 2);
		//pos_in_world.y = hitbox->y - (hitbox->height / 2);

		//hitbox->x = hitbox->x + (20 / 2);
		//hitbox->x = localPosition.x;
		//hitbox->y = localPosition.y;

		rr->setSize(sf::Vector2f(hitbox->width, hitbox->height));
		rr->setFillColor(sf::Color::Transparent);
		rr->setOutlineThickness(0.5);
		rr->setOutlineColor(sf::Color::Green);
		//rr->setOrigin(globalPosition);

		rr->setPosition(hitbox->x, hitbox->y);
	}

	//sprite->setOrigin(globalPosition.x - sprite.get)
	sprite->setPosition(globalPosition);

	sprite->PlayAnimation(true);
}

std::vector<Character*> Character::getCharactersList() {
	return characters;
}
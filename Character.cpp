#include "Character.h"

std::vector<Character*> Character::chars_list;

Character::Character(std::string name) {
	this->name = name;
	this->pos_in_world.x = 0;
	this->pos_in_world.y = 0;

	//this->sprite = new sf::Sprite();

	Character::chars_list.push_back(this);

	sprite = new AnimatedSprite();
}

void Character::Move(float dx, float dy) {
	velocity.x = dx * speed;
	velocity.y = dy * speed;
}

void Character::setObject(Object2D& obj)
{
	object = &obj;
}

void Character::Show(sf::RenderWindow & window) {
	pos_in_world.x += velocity.x;
	pos_in_world.y += velocity.y;

	if (object != nullptr) {
		object->position = Vector2(pos_in_world.x, pos_in_world.y);

		if (object->intersection != nullptr)
			printf("%a", &object->intersection);
	}
		

	this->sprite->setPosition(this->pos_in_world);

	this->sprite->PlayAnimation(true);
}

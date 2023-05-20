#include "Physics.h"

std::vector<Object2D*> Object2D::objects;

Physics::Physics() {}

void Physics::world() {
	
}

void Physics::update(sf::Time dt) {
	for (Object2D * object: Object2D::getObjects()) {
		object->update(Object2D::getObjects(), dt);
	}
}


#include "Physics.h"

std::vector<Object2D*> Object2D::objects;

Physics::Physics() {}

void Physics::world() {
	//just for tests
	Object2D* a = new Object2D({
		Vector2(0, 0),
		Vector2(2, 0),
		Vector2(2, 2),
		Vector2(0, 2),
		}, Vector2(1, 1));
	
	Object2D* b = new Object2D({
		Vector2(0, 0),
		Vector2(2, 0),
		Vector2(2, 2),
		Vector2(0, 2), 
		}, Vector2(0, 0));


	a->calcAxes();
	b->calcAxes();

	std::cout << a->intersects(*b) << std::endl;
}

void Physics::update(sf::Time dt) {
	for (Object2D * object: Object2D::getObjects()) {
		object->calcAxes();
		object->update(Object2D::getObjects());
	}
}


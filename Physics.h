#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

struct Axis {
	double min = 0;
	double max = 0;
};

struct Vector2 {
	double x;
	double y;

	Vector2(double x, double y): x(x), y(y){}

	Vector2 operator+(Vector2 &vec) {
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 operator-(Vector2 &vec) {
		return Vector2(x - vec.x, y - vec.y);
	}

	double dot(Vector2 &vec) {
		return x * vec.x + y * vec.y;
	}
};


class Physics
{


public:
	Physics();

	void world();
	void update(sf::Time dt);
	
};

struct Object2D {
protected:
	static std::vector<Object2D*> objects;
public:

	std::vector<Vector2> vertices;
	std::vector<Vector2> axes;
	Vector2 position;
	Object2D* intersection;

	Object2D(std::vector<Vector2> vertices, Vector2 position): vertices(vertices), position(position) {
		addObject(*this);
	}

	void calcAxes() {
		axes.clear();

		for (int i = 0; i < vertices.size(); i++) {
			Vector2 pv = vertices[i] + position;
			Vector2 pn = vertices[(i + 1) % vertices.size()] + position;

			double edgeX = pn.x - pv.x;
			double edgeY = pn.y - pv.y;

			Vector2 perpendAxe(-edgeY, edgeX);

			axes.push_back(perpendAxe);
		}
	}

	Axis project(Vector2 &axis) {
		double min = INFINITY;
		double max = -INFINITY;

		for (int i = 0; i < vertices.size(); i++) {
			double proj = (vertices[i] + position).dot(axis);

			if (proj < min)
				min = proj;

			if (proj > max)
				max = proj;
		}

		return Axis{ min, max };
	}

	bool intersects(Object2D& obj) {
		for (int i = 0; i < axes.size(); i++) {
			Vector2 axis = axes[i];

			Axis interA = project(axis);
			Axis interB = obj.project(axis);

			if (!interA.max < interB.min || interB.max < interA.min)
				return false;
		}

		return true;
	}

	void update(static const std::vector<Object2D*>& objects) {
		for (Object2D* other : objects) {
			if (other != this)
				if (intersects(*other))
					intersection = other;
				else
					intersection = nullptr;
		}
	}


	static void addObject(Object2D& obj)
	{
		objects.push_back(&obj);
	}

	static std::vector<Object2D*> getObjects() {
		return objects;
	}
};



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

	Vector2 operator+(const Vector2 &vec) const {
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 operator-(const Vector2 &vec) const {
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 operator+=(const Vector2 &vec) {
		x += vec.x;
		y += vec.y;

		return Vector2(x, y);
	}

	Vector2 operator-=(const Vector2& vec) {
		x -= vec.x;
		y -= vec.y;

		return Vector2(x, y);
	}

	Vector2 operator/(const Vector2& vec) const {
		return Vector2(x / vec.x, y / vec.y);
	}

	Vector2 operator*(const Vector2& vec) const {
		return Vector2(x * vec.x, y * vec.y);
	}

	Vector2 operator*(double d) const {
		return Vector2(x * d, y * d);
	}

	Vector2 operator/(double d) const {
		return Vector2(x / d, y / d);
	}

	Vector2 operator*(int i) const {
		return Vector2(x * i, y * i);
	}

	Vector2 operator/(int i) const {
		return Vector2(x / i, y / i);
	}

	double dot(const Vector2 &vec) const {
		return x * vec.x + y * vec.y;
	}

	double length() const {
		return std::sqrt(x * x + y * y);
	}

	Vector2 normalized() const {
		double len = length();

		return Vector2(x / len, y / len);
	}
};


struct BoundingBox {
	int width;
	int height;
	
	float x;
	float y;


	BoundingBox(int width, int height, float left, float top) : width(width), height(height), x(left), y(top) {}

	float left() const {
		return x;
	}

	float right() const {
		return x + width;
	}

	float bottom() const {
		return y + height;
	}

	float top() const {
		return y;
	}

	bool intersects(BoundingBox& other) {
		return (x < other.right() && right() > other.x) && (y < other.bottom() && bottom() > other.y);
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
	Vector2 position;
	Object2D* intersection;
	Vector2 velocity;

	const int MAX_INTERATIONS = 0;

	Object2D(std::vector<Vector2> vertices, Vector2 position, Vector2 velocity): vertices(vertices), position(position), velocity(velocity) {
		addObject(*this);
	}

	std::vector<Vector2> getCalculedAxes() const {
		//axes.clear();

		std::vector<Vector2> axes;

		for (size_t i = 0; i < vertices.size(); i++) {
			Vector2 pv = vertices[i] + position;
			Vector2 pn = vertices[(i + 1) % vertices.size()] + position;

			double edgeX = pn.x - pv.x;
			double edgeY = pn.y - pv.y;

			Vector2 perpendAxe(-edgeY, edgeX);

			axes.push_back(perpendAxe.normalized());
		}

		return axes;
	}

	Axis project(Vector2 &axis) const {
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

	bool intersects(const Object2D& obj) const {
		std::vector<Vector2> axes = getCalculedAxes();
		axes.reserve(vertices.size() + obj.vertices.size());
		axes.insert(axes.end(), vertices.begin(), vertices.end());
		axes.insert(axes.end(), obj.vertices.begin(), obj.vertices.end());

		for (size_t i = 0; i < axes.size(); i++) {
			Vector2 axis = axes[i];

			Axis interA = project(axis);
			Axis interB = obj.project(axis);

			double overlap = std::min(interA.max, interB.max) - std::max(interA.min, interB.min);

			if (overlap <= 0) {
				return false;
			}

			Vector2 relVel = velocity - obj.velocity;
			double projVel = relVel.dot(axis);

			if (projVel < 0 && std::abs(projVel) > overlap) {
				return false;
			}
				
		}

		return true;
	}

	bool overlap(Axis &a, Axis &b) {
		return !(a.max < b.min || b.max < a.min);
	}

	void update(static const std::vector<Object2D*>& objects, sf::Time dt) {
		position += velocity * dt.asSeconds();
		for (Object2D* other : objects) {
			if (other != this) {
				intersection = nullptr;

				int maxInterations = 10;
				int interations = 0;

				if (intersects(*other)) {
					interations++;
					position = position + velocity;
					intersection = other;
				}
			}
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



#include <iostream>
#include <string>
#include "List.h"

class IShape {
public:
	virtual void size() = 0;
	virtual void draw() = 0;

protected:
	float _size = 0;
};

class Circle : public IShape {
public:
	float r;

	Circle(float r) : r(r) {}

	void size() override {
		_size = r * r * 3.14159265358979f;
	}

	void draw() override {
		printf("circle size : %f\n", _size);
	}
};

class Rectangle : public IShape {
public:
	float x;
	float y;

	Rectangle(float x, float y) : x(x), y(y) {}

	void size() override {
		_size = x * y;
	}

	void draw() override {
		printf("rectangle size : %f\n", _size);
	}
};

int main() {
	IShape* circle = new Circle(2);
	IShape* rect = new Rectangle(5, 3);

	circle->size();
	circle->draw();
	rect->size();
	rect->draw();

	delete circle;
	delete rect;
	system("pause");
	return 0;
}
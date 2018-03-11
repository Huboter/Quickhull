#include "point.h"

#include <iostream>

Point::Point() {
	xPosition = 0;
	yPosition = 0;
}

Point::Point(float x, float y) {
	xPosition = x;
	yPosition = y;
}

Point::~Point() {

}

void Point::setValues(float x, float y) {
	xPosition = x;
	yPosition = y;
}

void Point::setValues(Point& point) {
	setValues(point.xPosition, point.yPosition);
}

bool Point::hasSameValues(float x, float y) const {
	if (xPosition == x && yPosition == y) {
		return true;
	}

	return false;
}

bool Point::hasSameValues(const Point& point) const {
	return hasSameValues(point.xPosition, point.yPosition);
}

void Point::print() const {
	std::cout << xPosition << ", " << yPosition << std::endl;
}
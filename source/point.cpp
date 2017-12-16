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
	xPosition = point.xPosition;
	yPosition = point.yPosition;
}

void Point::print() {
	std::cout << xPosition << ", " << yPosition << std::endl;
}
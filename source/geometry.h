#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>
#include "point.h"

float getDistanceBetweenLineAndPoint(const Point& lineBegin, const Point& lineEnd, const Point& distancePoint);
Point vectorSubtraction(const Point& point1, const Point& point2);
float crossProduct(const Point& point1, const Point& point2);
float orient2D(const Point& point1, const Point& point2, const Point& point3);

float getDistanceBetweenLineAndPoint(const Point& lineBegin, const Point& lineEnd, const Point& distancePoint) {
	float distance = 0;
	Point tempPoint = vectorSubtraction(distancePoint, lineBegin);
	float absoluteValue = crossProduct(tempPoint, lineEnd);
	distance = absoluteValue / sqrt(pow(lineEnd.xPosition, 2) + pow(lineEnd.yPosition, 2));

	return distance;
}

Point vectorSubtraction(const Point& point1, const Point& point2) {
	Point tempPoint;
	tempPoint.xPosition = point1.xPosition - point2.xPosition;
	tempPoint.yPosition = point1.yPosition - point2.yPosition;

	return tempPoint;
}

float crossProduct(const Point& point1, const Point& point2) {
	return abs(point1.xPosition * point2.yPosition - point2.xPosition * point1.yPosition);
}

float orient2D(const Point& point1, const Point& point2, const Point& point3) {
	float a1 = point1.xPosition - point3.xPosition;
	float a2 = point1.yPosition - point3.yPosition;
	float b1 = point2.xPosition - point3.xPosition;
	float b2 = point2.yPosition - point3.yPosition;
	float det = a1 * b2 - a2 * b1;

	return det;
}

#endif

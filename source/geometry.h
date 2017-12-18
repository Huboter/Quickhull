#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>
#include "point.h"

float getDistanceBetweenLineAndPoint(const Point& lineBegin, const Point& lineEnd, const Point& distancePoint);
float orient2D(const Point& point1, const Point& point2, const Point& point3);

float getDistanceBetweenLineAndPoint(const Point& lineBegin, const Point& lineEnd, const Point& distancePoint) {
	float normalLength = hypot(lineEnd.xPosition - lineBegin.xPosition, lineEnd.yPosition - lineBegin.yPosition);
	float distance = (float)((distancePoint.xPosition - lineBegin.xPosition) * (lineEnd.yPosition - lineBegin.yPosition) - (distancePoint.yPosition - lineBegin.yPosition) * (lineEnd.xPosition - lineBegin.xPosition)) / normalLength;
	return abs(distance);
}

float orient2D(const Point& point1, const Point& point2, const Point& point3) {
	float a1 = point1.xPosition - point3.xPosition;
	float a2 = point1.yPosition - point3.yPosition;
	float b1 = point2.xPosition - point3.xPosition;
	float b2 = point2.yPosition - point3.yPosition;
	float det = a1 * b2 - b1 * a2;

	return det;
}

#endif

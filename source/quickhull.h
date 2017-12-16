#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <vector>

#include "geometry.h"

void quickhull(const std::vector<Point>& points, std::vector<Point>& convexHull);
void findhull(std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd);
void getBoundaryPoints(const std::vector<Point>& points, std::vector<Point>& convexHull);
void removePointsInHull(std::vector<Point>& points, const std::vector<Point>& convexHull);

void quickhull(const std::vector<Point>& points, std::vector<Point>& convexHull) {
	getBoundaryPoints(points, convexHull);

	std::vector<Point> tempPoints = points;
	removePointsInHull(tempPoints, convexHull);

	findhull(convexHull, tempPoints, convexHull[0], convexHull[1]);
	findhull(convexHull, tempPoints, convexHull[1], convexHull[2]);
	findhull(convexHull, tempPoints, convexHull[2], convexHull[3]);
	findhull(convexHull, tempPoints, convexHull[3], convexHull[0]);
}

void findhull(std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd) {
	std::vector<Point> outerPoints;

	for (int i = 0; i < points.size(); ++i) {
		if (orient2D(lineBegin, lineEnd, points[i]) < 0) {
			outerPoints.push_back(points[i]);
		}
	}

	if (!outerPoints.empty()) {
		Point farthestPoint;
		// for safety reasons -1 beacuse we are not sure if the point can be on line
		float distance = -1;

		for (int i = 0; i < outerPoints.size(); ++i) {
			float tempDistance = getDistanceBetweenLineAndPoint(lineBegin, lineEnd, outerPoints[i]);

			if (distance < tempDistance) {
				distance = tempDistance;
				farthestPoint = outerPoints[i];
			}
		}

		convexHull.push_back(farthestPoint);

		findhull(convexHull, outerPoints, lineBegin, farthestPoint);
		findhull(convexHull, outerPoints, farthestPoint, lineEnd);
	}
}

void getBoundaryPoints(const std::vector<Point>& points, std::vector<Point>& convexHull) {
	Point leftMostPoint(0, 0);
	Point rightMostPoint(0, 0);
	Point highestPoint(0, 0);
	Point lowestPoint(0, 0);

	for (int i = 0; i < points.size(); ++i) {
		Point tempPoint = points[i];

		if (tempPoint.xPosition <= leftMostPoint.xPosition) {
			leftMostPoint.setValues(tempPoint);
		}
		if (tempPoint.xPosition >= rightMostPoint.xPosition) {
			rightMostPoint.setValues(tempPoint);
		}
		if (tempPoint.yPosition >= highestPoint.yPosition) {
			highestPoint.setValues(tempPoint);
		}
		if (tempPoint.yPosition <= lowestPoint.yPosition) {
			lowestPoint.setValues(tempPoint);
		}
	}

	convexHull.push_back(leftMostPoint);
	convexHull.push_back(lowestPoint);
	convexHull.push_back(rightMostPoint);
	convexHull.push_back(highestPoint);
}

void removePointsInHull(std::vector<Point>& points, const std::vector<Point>& convexHull) {
	std::vector<Point> outerPoints;

	for (int i = 0; i < points.size(); ++i) {
		int counter = 0;

		if (orient2D(convexHull[0], convexHull[1], points[i]) > 0) {
			counter++;
		}
		if (orient2D(convexHull[1], convexHull[2], points[i]) > 0) {
			counter++;
		}
		if (orient2D(convexHull[2], convexHull[3], points[i]) > 0) {
			counter++;
		}
		if (orient2D(convexHull[3], convexHull[0], points[i]) > 0) {
			counter++;
		}

		if (counter != 4) {
			outerPoints.push_back(points[i]);
		}
	}

	points = outerPoints;
}

#endif
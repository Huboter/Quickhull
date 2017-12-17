#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "geometry.h"

void quickhull(const std::vector<Point>& points, std::vector<Point>& convexHull);
void findHull(std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd);

void quickhullVisualized(sf::RenderWindow& window, const std::vector<Point>& points, std::vector<Point>& convexHull);
void findHullVisualized(sf::RenderWindow& window, std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd);

void getBoundaryPoints(const std::vector<Point>& points, std::vector<Point>& convexHull);
void removePointsInHull(std::vector<Point>& points, const std::vector<Point>& convexHull);

void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points, const sf::Color& color);
void watiForInput(sf::RenderWindow& window, sf::Event& event);

sf::CircleShape g_circle(0.2);

void quickhull(const std::vector<Point>& points, std::vector<Point>& convexHull) {
	getBoundaryPoints(points, convexHull);
	std::vector<Point> tempPoints = points;
	removePointsInHull(tempPoints, convexHull);

	findHull(convexHull, tempPoints, convexHull[0], convexHull[1]);
	findHull(convexHull, tempPoints, convexHull[1], convexHull[2]);
	findHull(convexHull, tempPoints, convexHull[2], convexHull[3]);
	findHull(convexHull, tempPoints, convexHull[3], convexHull[0]);
}

void findHull(std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd) {
	if (points.empty()) {
		return;
	}
	
	std::vector<Point> outerPoints;
	Point farthestPoint;
	// for safety reasons -1 beacuse we are not sure if the point can be on line
	float distance = -1;

	for (int i = 0; i < points.size(); ++i) {
		Point tempPoint = points[i];
		if (orient2D(lineBegin, lineEnd, tempPoint) < 0) {
			outerPoints.push_back(tempPoint);

			float tempDistance = getDistanceBetweenLineAndPoint(lineBegin, lineEnd, tempPoint);

			if (distance < tempDistance) {
				distance = tempDistance;
				farthestPoint = tempPoint;
			}
		}
	}

	if (!outerPoints.empty()) {
		convexHull.push_back(farthestPoint);
		findHull(convexHull, outerPoints, lineBegin, farthestPoint);
		findHull(convexHull, outerPoints, farthestPoint, lineEnd);
	}
}

void quickhullVisualized(sf::RenderWindow& window, const std::vector<Point>& points, std::vector<Point>& convexHull) {
	g_circle.setPointCount(50);
	sf::Event event;
	window.clear(sf::Color::Black);
	drawPoints(window, points, sf::Color::Red);

	getBoundaryPoints(points, convexHull);
	std::vector<Point> tempPoints = points;
	removePointsInHull(tempPoints, convexHull);

	watiForInput(window, event);
	drawPoints(window, tempPoints, sf::Color::Red);
	watiForInput(window, event);
	drawPoints(window, convexHull, sf::Color::Green);

	findHull(convexHull, tempPoints, convexHull[0], convexHull[1]);
	findHull(convexHull, tempPoints, convexHull[1], convexHull[2]);
	findHull(convexHull, tempPoints, convexHull[2], convexHull[3]);
	findHull(convexHull, tempPoints, convexHull[3], convexHull[0]);

	watiForInput(window, event);
	drawPoints(window, tempPoints, sf::Color::Red);
	watiForInput(window, event);
	drawPoints(window, convexHull, sf::Color::Green);
	
	while (window.waitEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.key.code == sf::Keyboard::Escape) {
			window.close();
		}
	}
}

void findHullVisualized(sf::RenderWindow& window, std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd) {
	if (points.empty()) {
		return;
	}

	std::vector<Point> outerPoints;
	Point farthestPoint;
	// for safety reasons -1 beacuse we are not sure if the point can be on line
	float distance = -1;

	for (int i = 0; i < points.size(); ++i) {
		Point tempPoint = points[i];
		if (orient2D(lineBegin, lineEnd, tempPoint) < 0) {
			outerPoints.push_back(tempPoint);

			float tempDistance = getDistanceBetweenLineAndPoint(lineBegin, lineEnd, tempPoint);

			if (distance < tempDistance) {
				distance = tempDistance;
				farthestPoint = tempPoint;
			}
		}
	}

	if (!outerPoints.empty()) {
		convexHull.push_back(farthestPoint);
		findHull(convexHull, outerPoints, lineBegin, farthestPoint);
		findHull(convexHull, outerPoints, farthestPoint, lineEnd);
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

void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points, const sf::Color& color) {
	g_circle.setFillColor(color);
	sf::Vector2<float> position;

	for (int i = 0; i < points.size(); ++i) {
		position.x = points[i].xPosition + 1200/2;
		position.y = points[i].yPosition + 800/2;

		g_circle.setPosition(position);
		window.draw(g_circle);
	}

	window.display();
}

void watiForInput(sf::RenderWindow& window, sf::Event& event) {
	while (window.waitEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			break;
		}
		/*
		if (event.key.code == sf::Keyboard::Space) {
			break;
		}
		*/
	}
}

#endif
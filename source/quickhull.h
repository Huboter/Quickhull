#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <vector>
#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "geometry.h"

void quickhull(const std::vector<Point>& points, std::vector<Point>& convexHull);
void findHull(std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd);

void quickhullVisualized(sf::RenderWindow& window, const std::vector<Point>& points, std::vector<Point>& convexHull);
void findHullVisualized(sf::RenderWindow& window, std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd);

void getBoundaryPoints(const std::vector<Point>& points, std::vector<Point>& convexHull);
void removePointsInHull(std::vector<Point>& points, const std::vector<Point>& convexHull);
bool sortByXPosition(const Point& point1, const Point& point2);
void sortConvexHull(std::vector<Point>& convexHull);

void drawPoint(sf::RenderWindow& window, const Point& point, const sf::Color& color);
void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points, const sf::Color& color);
void drawLine(sf::RenderWindow& window, const Point& lineBegin, const Point& lineEnd, const sf::Color& color);
void drawLines(sf::RenderWindow& window, const std::vector<Point>& points, const sf::Color& color);

void watiForInput(sf::RenderWindow& window, sf::Event& event);

const int g_screenWidth = 1200;
const int g_screenHeight = 800;

float g_circleRadius = 0.2;
sf::CircleShape g_circle(g_circleRadius);

std::vector<Point> g_allPoints;

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
	sf::Event event;
	window.clear(sf::Color::Black);
	drawPoints(window, points, sf::Color::Red);
	window.display();

	getBoundaryPoints(points, convexHull);
	std::vector<Point> tempPoints = points;
	removePointsInHull(tempPoints, convexHull);

	g_allPoints = tempPoints;

	watiForInput(window, event);
	window.clear(sf::Color::Black);
	drawPoints(window, tempPoints, sf::Color::Red);
	watiForInput(window, event);
	drawPoints(window, convexHull, sf::Color::Green);
	window.display();

	findHullVisualized(window, convexHull, tempPoints, convexHull[0], convexHull[1]);
	findHullVisualized(window, convexHull, tempPoints, convexHull[1], convexHull[2]);
	findHullVisualized(window, convexHull, tempPoints, convexHull[2], convexHull[3]);
	findHullVisualized(window, convexHull, tempPoints, convexHull[3], convexHull[0]);
	
	std::vector<Point> sortedConvexHull = convexHull;
	sortConvexHull(sortedConvexHull);

	watiForInput(window, event);
	window.clear(sf::Color::Black);
	drawPoints(window, points, sf::Color::Red);
	drawPoints(window, sortedConvexHull, sf::Color::Yellow);
	drawLines(window, sortedConvexHull, sf::Color::Yellow);
	window.display();
}

void findHullVisualized(sf::RenderWindow& window, std::vector<Point>& convexHull, const std::vector<Point>& points, const Point lineBegin, const Point lineEnd) {
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

	std::vector<Point> sortedConvexHull = convexHull;
	sortConvexHull(sortedConvexHull);

	sf::Event event;
	watiForInput(window, event);
	window.clear(sf::Color::Black);
	drawPoints(window, g_allPoints, sf::Color::Red);

	if (!farthestPoint.hasSameValues(0, 0)) {
		drawPoint(window, lineBegin, sf::Color::Green);
		drawPoint(window, farthestPoint, sf::Color::Magenta);
		drawPoint(window, lineEnd, sf::Color::Green);
	}
	
	drawLines(window, sortedConvexHull, sf::Color::Yellow);
	drawLine(window, lineBegin, lineEnd, sf::Color::Green);
	window.display();

	if (!outerPoints.empty()) {
		convexHull.push_back(farthestPoint);
		findHullVisualized(window, convexHull, outerPoints, lineBegin, farthestPoint);
		findHullVisualized(window, convexHull, outerPoints, farthestPoint, lineEnd);
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

bool sortByXPosition(const Point& point1, const Point& point2) {
	return point1.xPosition < point2.xPosition;
}

void sortConvexHull(std::vector<Point>& convexHull) {
	std::vector<Point> tempPoints;
	Point leftestPoint = convexHull[0];
	Point rightesPoint = convexHull[2];
	tempPoints.push_back(convexHull[0]);

	std::vector<Point> leftPoints;
	std::vector<Point> rightPoints;

	for (int i = 0; i < convexHull.size(); ++i) {
		if (orient2D(leftestPoint, rightesPoint, convexHull[i]) > 0) {
			leftPoints.push_back(convexHull[i]);
		}
		else {
			rightPoints.push_back(convexHull[i]);
		}
	}

	std::sort(leftPoints.begin(), leftPoints.end(), sortByXPosition);
	std::sort(rightPoints.begin(), rightPoints.end(), sortByXPosition);

	for (int i = 0; i < leftPoints.size(); ++i) {
		tempPoints.push_back(leftPoints[i]);
	}

	tempPoints.push_back(convexHull[2]);

	for (int i = rightPoints.size() - 1; i > 0; --i) {
		tempPoints.push_back(rightPoints[i]);
	}

	tempPoints.push_back(convexHull[0]);
	convexHull = tempPoints;
}

void drawPoint(sf::RenderWindow& window, const Point& point, const sf::Color& color) {
	g_circle.setFillColor(color);
	sf::Vector2<float> position;
	position.x = point.xPosition;
	// y need to be inverted because sfml coordinate system works with +y in negative y axis
	position.y = -(point.yPosition);
	g_circle.setPosition(g_screenWidth / 2, g_screenHeight / 2);
	g_circle.move(position);
	window.draw(g_circle);
}

void drawPoints(sf::RenderWindow& window, const std::vector<Point>& points, const sf::Color& color) {
	for (int i = 0; i < points.size(); ++i) {
		drawPoint(window, points[i], color);
	}
}

void drawLine(sf::RenderWindow& window, const Point& lineBegin, const Point& lineEnd, const sf::Color& color) {
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(lineBegin.xPosition + g_screenWidth / 2 + g_circleRadius / 2, -lineBegin.yPosition + g_screenHeight / 2 + g_circleRadius / 2);
	line[0].color = color;
	line[1].position = sf::Vector2f(lineEnd.xPosition + g_screenWidth / 2 + g_circleRadius / 2, -lineEnd.yPosition + g_screenHeight / 2 + g_circleRadius / 2);
	line[1].color = color;
	window.draw(line);
}

void drawLines(sf::RenderWindow& window, const std::vector<Point>& points, const sf::Color& color) {
	for (int i = 0; i < points.size()-1; ++i) {
		drawLine(window, points[i], points[i+1], color);
	}
}

void watiForInput(sf::RenderWindow& window, sf::Event& event) {
	while (window.waitEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				break;
			}
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}
	}
}

#endif
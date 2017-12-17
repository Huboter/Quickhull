#include <random>

#include "quickhull.h"

const int g_screenWidth = 1200;
const int g_screenHeight = 800;
bool g_visualize = true;

int main() {
	const float floatMin = -10;
	const float floatMax = 10;
	const int numberOfPoints = 30;
	std::mt19937 randomNumberGenerator;
	randomNumberGenerator.seed(std::random_device()());
	std::uniform_real_distribution<float> distribution(floatMin, floatMax);

	std::vector<Point> points;
	std::vector<Point> convexHull;

	for (int i = 0; i < numberOfPoints; ++i) {
		Point point(distribution(randomNumberGenerator), distribution(randomNumberGenerator));
		points.push_back(point);
		//point.print();
	}

	/*
	points.clear();

	Point p1(-4.5f, 8.5f);
	Point p2(-6.5f, 8.0f);
	Point p3(-4.0f, 7.5f);
	Point p4(4.5f, 9.0f);
	Point p5(5.5f, 7.5f);
	Point p6(2.0f, 7.0f);
	Point p7(-2.0f, 6.0f);
	Point p8(3.0f, 5.5f);
	Point p9(5.0f, 5.5f);
	Point p10(6.0f, 4.0f);
	Point p11(2.5f, 3.5f);
	Point p12(-2.0f, 3.5f);
	Point p13(-4.5f, 2.5f);
	Point p14(-5.0f, -1.5f);
	Point p15(-3.0f, -2.5f);
	Point p16(-4.0f, -3.5f);
	Point p17(-6.0f, -4.5f);
	Point p18(-1.5f, -6.5f);
	Point p19(3.0f, -2.5f);
	Point p20(2.0f, -3.5f);
	Point p21(6.5f, -3.5f);
	Point p22(2.0f, -5.0f);
	Point p23(5.0f, -6.0f);
	Point p24(2.0f, -6.5f);
	Point p25(3.5f, -5.0f);

	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p7);
	points.push_back(p8);
	points.push_back(p9);
	points.push_back(p10);
	points.push_back(p11);
	points.push_back(p12);
	points.push_back(p13);
	points.push_back(p14);
	points.push_back(p15);
	points.push_back(p16);
	points.push_back(p17);
	points.push_back(p18);
	points.push_back(p19);
	points.push_back(p20);
	points.push_back(p21);
	points.push_back(p22);
	points.push_back(p23);
	points.push_back(p24);
	points.push_back(p25);
	*/

	/*
	for (int i = 0; i < convexHull.size(); ++i) {
		convexHull[i].print();
	}
	*/

	if (g_visualize) {
		sf::RenderWindow window(sf::VideoMode(g_screenWidth, g_screenHeight), "Quickhull");
		sf::View view(sf::Vector2f(g_screenWidth / 2, g_screenHeight / 2), sf::Vector2f(50, 50));
		window.setFramerateLimit(30);
		window.setView(view);

		quickhullVisualized(window, points, convexHull);
	}
	else {
		quickhull(points, convexHull);
		std::cout << convexHull.size() << std::endl;
	}

	return 0;
}
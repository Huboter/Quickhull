#include <random>
#include <chrono>
#include <iomanip>
#include <Windows.h>

#include "quickhull.h"

// use nvidia GPU on laptops with hybrid hardware
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

void printTime(double timeInSeconds);

const bool g_visualize = true;
const int g_numberOfPoints = 100;

int main() {
	const float floatMin = -50;
	const float floatMax = 50;
	std::mt19937 randomNumberGenerator;
	randomNumberGenerator.seed(std::random_device()());
	std::uniform_real_distribution<float> distribution(floatMin, floatMax);

	std::vector<Point> points;
	std::vector<Point> convexHull;

	for (int i = 0; i < g_numberOfPoints; ++i) {
		Point point(distribution(randomNumberGenerator), distribution(randomNumberGenerator));
		points.push_back(point);
	}

	if (g_visualize) {
		sf::RenderWindow window(sf::VideoMode(g_screenWidth, g_screenHeight), "Quickhull");
		sf::Event event;
		sf::View view(sf::Vector2f(g_screenWidth / 2, g_screenHeight / 2), sf::Vector2f(150, 150));
		window.setView(view);
		window.setFramerateLimit(30);

		quickhullVisualized(window, points, convexHull);
		std::cout << convexHull.size() << std::endl;

		while (window.waitEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}
	}
	else {
		std::chrono::high_resolution_clock::time_point timeBegin = std::chrono::high_resolution_clock::now();
		quickhull(points, convexHull);
		std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> overallTimeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd - timeBegin);

		std::cout << convexHull.size() << std::endl;

		for (int i = 0; i < convexHull.size(); ++i) {
			convexHull[i].print();
		}

		printTime(overallTimeSpan.count());
		std::cout << "\n";
	}

	return 0;
}

void printTime(double timeInSeconds) {
	int milliseconds = timeInSeconds * 1000;
	int hours = (milliseconds / (1000 * 60 * 60)) % 24;
	milliseconds -= hours * (1000 * 60 * 60);
	int minutes = (milliseconds / (1000 * 60)) % 60;
	milliseconds -= minutes * (1000 * 60);
	int seconds = (milliseconds / 1000) % 60;
	milliseconds -= seconds * 1000;

	std::cout << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds << "." << std::setfill('0') << std::setw(3) << milliseconds;
}
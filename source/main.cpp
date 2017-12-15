#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "quickhull.h"

const int g_screenWidth = 1200;
const int g_ScreenHeight = 800;
bool g_visualize = false;

int main() {
	const float floatMin = -10;
	const float floatMax = 10;
	const int numberOfPoints = 10;
	std::mt19937 randomNumberGenerator;
	randomNumberGenerator.seed(std::random_device()());
	std::uniform_real_distribution<float> distribution(floatMin, floatMax);

	std::vector<Point> points;

	for (int i = 0; i < numberOfPoints; ++i) {
		Point point;
		point.xPosition = distribution(randomNumberGenerator);
		point.yPosition = distribution(randomNumberGenerator);

		points.push_back(point);
	}

	for (int i = 0; i < numberOfPoints; ++i) {
		std::cout << points[i].xPosition << ":" << points[i].yPosition << std::endl;
	}

	if (g_visualize) {
		sf::RenderWindow window(sf::VideoMode(g_screenWidth, g_ScreenHeight), "Quickhull");
		window.setFramerateLimit(60);

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
					}
				}
			}

			window.clear(sf::Color::Black);

			window.display();
		}
	}

	return 0;
}
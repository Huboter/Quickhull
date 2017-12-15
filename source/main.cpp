#include <iostream>
#include <SFML/Graphics.hpp>

const int g_screenWidth = 1200;
const int g_ScreenHeight = 800;

int main() {
	std::cout << "Hello Quickhull" << std::endl;

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

	return 0;
}
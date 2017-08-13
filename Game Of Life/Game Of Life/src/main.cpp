#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "include/gui.hpp"
#include "include/grid.h"


int main()
{
	srand(time(nullptr));
	sf::RenderWindow boardWindow(sf::VideoMode(600, 600), "Conway's Game of Life", sf::Style::Close);
	boardWindow.setPosition({ boardWindow.getPosition().x - 230, boardWindow.getPosition().y });
	sf::RenderWindow settingsWindow(sf::VideoMode(300, 600), "Controls",sf::Style::Close);
	settingsWindow.setPosition({ settingsWindow.getPosition().x + 230, settingsWindow.getPosition().y });

	sf::CircleShape shape(100.f);
	SGui gui(settingsWindow);
	Grid grid;
	bool shouldQuit = false;

	sf::Clock clock;

	while (!shouldQuit)
	{
		auto newSettings = gui.update();
		if (newSettings.has_value()) {
			grid.change(newSettings.value());
		}

		sf::Event event;
		while (boardWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				shouldQuit = true;
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					grid.add(event.mouseButton.x, event.mouseButton.y);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					grid.remove(event.mouseButton.x, event.mouseButton.y);
				}
			}
		}

		while (settingsWindow.pollEvent(event))
		{
			gui.handleEvent(event);
			if (event.type == sf::Event::Closed)
				shouldQuit = true;
		}
		if (clock.getElapsedTime().asSeconds() > 1 / 10.f) {
			clock.restart();
			//Update
			grid.iterate();

			boardWindow.clear(grid.getBackground());
			boardWindow.draw(grid);
			boardWindow.display();
		}
		settingsWindow.clear();
		gui.draw();
		settingsWindow.display();

	}

	return 0;
}

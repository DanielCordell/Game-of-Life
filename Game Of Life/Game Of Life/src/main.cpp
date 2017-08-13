#include <SFML/Graphics.hpp>

#include "include/gui.hpp"
#include "include/grid.h"


int main()
{
	srand(time(nullptr));
	sf::RenderWindow boardWindow(sf::VideoMode(600, 600), "SFML works!");
	sf::RenderWindow settingsWindow(sf::VideoMode(300, 600), "SFML works!",sf::Style::Close);

	sf::CircleShape shape(100.f);
	SGui gui(settingsWindow);
	Grid grid;
	bool shouldQuit = false;

	while (!shouldQuit)
	{
		auto newSettings = gui.update();
		if (newSettings.has_value()) {
			grid.change(newSettings.value());
		}
		grid.iterate();


		sf::Event event;
		while (boardWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				shouldQuit = true;
		}

		while (settingsWindow.pollEvent(event))
		{
			gui.handleEvent(event);
			if (event.type == sf::Event::Closed)
				shouldQuit = true;
		}

		boardWindow.clear();
		boardWindow.draw(grid);
		boardWindow.display();

		settingsWindow.clear();
		gui.draw();
		settingsWindow.display();
	}

	return 0;
}

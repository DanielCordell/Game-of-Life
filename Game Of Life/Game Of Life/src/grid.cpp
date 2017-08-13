#include <SFML/Graphics/RenderTarget.hpp>

#include "include/grid.h"
#include "include/gui.hpp"

Grid::Grid() : maxSize(600,600), gridVertArray(sf::Quads) {
	colorMap = { {"White",sf::Color::White},{"Black",sf::Color::Black},{"Blue",sf::Color::Blue},{"Green",sf::Color::Green},{"Red",sf::Color::Red},{"Yellow",sf::Color::Yellow},{"Cyan",sf::Color::Cyan}, {"Magenta",sf::Color::Magenta} };
	grid.resize(SettingsData::Default.width);
	for (int i = 0; i < SettingsData::Default.width; i++) {
		grid[i].resize(SettingsData::Default.height);
		for (int j = 0; j < SettingsData::Default.height; j++)
			grid[i][j] = rand() % 20 == 0 ? 1 : 0;
	}
	change(SettingsData::Default);
}


void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(gridVertArray);
}

void Grid::change(SettingsData data) {
	foreground = colorMap[data.foreground];
	background = colorMap[data.background];
	speed = data.speed;
	updateVertArray(data.width, data.height);
}


void Grid::updateVertArray(unsigned width, unsigned height) {
	gridVertArray = sf::VertexArray{ sf::Quads,width * height * 4 };
	float cellWidth = (maxSize.x - 4 * width) / static_cast<float>(width);
	float cellHeight = (maxSize.y - 4 * height) / static_cast<float>(height);


	if (grid.size() != width) grid.resize(width);
	for (unsigned int x = 0; x < width; ++x) {
		if (grid[x].size() != height) grid[x].resize(height);
		for (unsigned int y = 0; y < height; ++y) {
			auto on = grid[x][y];
			//Top left corner of cell
			sf::Vector2f cellPos(x * (4 + cellWidth) + 2, y * (4 + cellHeight) + 2);
			for (int i = 0; i < 4; ++i) {
				int index = x * height * 4 + y * 4 + i;
				auto& cell = gridVertArray[index];
				cell.color = on ? foreground : background;
				switch (i) {
					case 0: 
						cell.position = cellPos;
						break;	
					case 1:
						cell.position = { cellPos.x + cellWidth, cellPos.y };
						break;
					case 2:
						cell.position = { cellPos.x + cellWidth, cellPos.y + cellHeight };
						break;
					case 3:
						cell.position = { cellPos.x, cellPos.y + cellHeight };
						break;
				default:
						throw std::exception("Very bad!");
				}
			}
		}
	}
	std::cout << gridVertArray.getVertexCount() << std::endl;
}

void Grid::iterate() {
	
}

#include <SFML/Graphics/RenderTarget.hpp>

#include "include/grid.h"
#include "include/gui.hpp"

Grid::Grid() : maxSize(600, 600), gridVertArray(sf::Quads) {
	colorMap = { { "White",sf::Color::White },{ "Black",sf::Color::Black },{ "Blue",sf::Color::Blue },{ "Green",sf::Color::Green },{ "Red",sf::Color::Red },{ "Yellow",sf::Color::Yellow },{ "Cyan",sf::Color::Cyan },{ "Magenta",sf::Color::Magenta } };
	grid.resize(SettingsData::Default.width);
	for (int i = 0; i < SettingsData::Default.width; i++) {
		grid[i].resize(SettingsData::Default.height);
		for (int j = 0; j < SettingsData::Default.height; j++)
			grid[i][j] = randomizeCell();
	}
	change(SettingsData::Default);

	grid[5][5] = true;
	grid[5][6] = true;
	grid[5][7] = true;
}

void Grid::changeCell(bool alive, int clickX, int clickY)
{
	const int width = grid.size();
	const int height = grid[0].size();
	const float cellWidth = (maxSize.x - 2 * width) / static_cast<float>(width);
	const float cellHeight = (maxSize.y - 2 * height) / static_cast<float>(height);

	for (unsigned int x = 0; x < width; ++x) {
		for (unsigned int y = 0; y < height; ++y) {
			//Top left corner of cell
			sf::Vector2f cellPos(x * (2 + cellWidth) + 1, y * (2 + cellHeight) + 1);
			sf::FloatRect rect{cellPos.x, cellPos.y, cellWidth, cellHeight};
			if (rect.contains(clickX, clickY))
				for (int i = 0; i < 4; ++i) {
					int index = x * height * 4 + y * 4 + i;
					grid[x][y] = alive;
					auto& cell = gridVertArray[index];
					cell.color = alive ? foreground : background;

				}
		}
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(gridVertArray);
}

void Grid::change(SettingsData data) {
	foreground = colorMap[data.foreground];
	background = colorMap[data.background];
	shouldReset = data.doReset;
	shouldClear = data.doClear;
	if (data.doToggle) paused = !paused;

	updateVertArray(data.width, data.height);

}


void Grid::updateVertArray(unsigned width, unsigned height) {
	gridVertArray = sf::VertexArray{ sf::Quads,width * height * 4 };
	const float cellWidth = (maxSize.x - 2 * width) / static_cast<float>(width);
	const float cellHeight = (maxSize.y - 2 * height) / static_cast<float>(height);

	if (grid.size() != width) grid.resize(width);
	for (unsigned int x = 0; x < width; ++x) {
		if (grid[x].size() != height) grid[x].resize(height);
		for (unsigned int y = 0; y < height; ++y) {
			if (shouldClear) 
				grid[x][y] = false;
			else if (shouldReset) 
				grid[x][y] = randomizeCell();
			auto on = grid[x][y];
			//Top left corner of cell
			sf::Vector2f cellPos(x * (2 + cellWidth) + 1, y * (2 + cellHeight) + 1);
			for (int i = 0; i < 4; ++i) {
				int index = x * height * 4 + y * 4 + i;
				auto& cell = gridVertArray[index];
				cell.color = on == 1 ? foreground : background;
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
	shouldClear = false;
	shouldReset = false;
}

bool Grid::randomizeCell() const {
	return rand() % 5 == 0;
}

void Grid::iterate() {
	if (paused) return;
	auto newGrid = grid;
	for (unsigned int x = 0; x < grid.size(); x++) {
		for (unsigned int y = 0; y < grid[x].size(); y++) {
			bool alive = grid[x][y];
			
			std::list<bool> list;

			bool noTouchT = y > 0;
			bool noTouchR = x < grid.size() - 1;
			bool noTouchL = x > 0;
			bool noTouchB = y < grid[x].size() - 1;

			//North
			if (noTouchT)				list.push_back(grid[x][y - 1]);
			//North East
			if (noTouchT && noTouchR)	list.push_back(grid[x + 1][y - 1]);
			//East
			if (noTouchR)				list.push_back(grid[x + 1][y]);
			//South East
			if (noTouchB && noTouchR)	list.push_back(grid[x + 1][y + 1]);
			//South
			if (noTouchB)				list.push_back(grid[x][y + 1]);
			//South West
			if (noTouchB && noTouchL)	list.push_back(grid[x - 1][y + 1]);
			//West
			if (noTouchL)				list.push_back(grid[x - 1][y]);
			//North West
			if (noTouchT && noTouchL)	list.push_back(grid[x - 1][y - 1]);

			int liveNeighbours = count(list.begin(), list.end(), true);

			if (alive) {
				if (liveNeighbours < 2 || liveNeighbours > 3) newGrid[x][y] = false;
			}
			else {
				if (liveNeighbours == 3) newGrid[x][y] = true;
			}
		}
	}
	grid = newGrid;
	updateVertArray(grid.size(), grid[0].size());
}

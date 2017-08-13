#pragma once
#include <vector>
#include <map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

struct SettingsData;

class Grid : public sf::Drawable {
private:
	const sf::Vector2u maxSize;
	// 1 is live, 2 is dead
	std::vector<std::vector<bool>> grid;
	sf::VertexArray gridVertArray;
	sf::Color foreground;
	sf::Color background;
	std::map<std::string, sf::Color> colorMap;
	void changeCell(bool alive, int x, int y);

	bool shouldClear, shouldReset, paused;
public:
	Grid();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void iterate();
	void change(SettingsData data);
	void updateVertArray(unsigned width, unsigned height);
	sf::Color getBackground() const { return background; }

	bool randomizeCell() const;
	void add(int x, int y) { changeCell(true, x, y); }
	void remove(int x, int y) { changeCell(false, x, y); }
};

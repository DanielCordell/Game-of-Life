#pragma once
#include <vector>
#include <map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

struct SettingsData;

class Grid : public sf::Drawable {
private:
	const sf::Vector2u maxSize;
	std::vector<std::vector<char>> grid;
	sf::VertexArray gridVertArray;
	sf::Color foreground;
	sf::Color background;
	int speed;

	std::map<std::string, sf::Color> colorMap;
public:
	Grid();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void iterate();
	void change(SettingsData data);
	void updateVertArray(unsigned int width, unsigned int height);
};

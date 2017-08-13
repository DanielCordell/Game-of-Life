#pragma once
#include <TGUI/Gui.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <TGUI/Widgets/ComboBox.hpp>
#include <optional>

struct SettingsData {
	SettingsData(int width, int height, int speed, std::string foreground, std::string background)
		: width(width), height(height), speed(speed), foreground(foreground), background(background) {}
	const int width, height, speed;
	const std::string foreground, background;
	const static SettingsData Default;
};


class SGui : public tgui::Gui {
private:
	sf::Font font;

	tgui::Slider::Ptr	widthSlider;
	tgui::Label::Ptr	widthLabel;

	tgui::Slider::Ptr	heightSlider;
	tgui::Label::Ptr	heightLabel;

	tgui::Slider::Ptr	speedSlider;
	tgui::Label::Ptr	speedLabel;


	tgui::ComboBox::Ptr foregroundBox;
	tgui::Label::Ptr	foregroundLabel;

	tgui::ComboBox::Ptr backgroundBox;
	tgui::Label::Ptr	backgroundLabel;

	void initialize();
	void setDefaults() const;
	void addComponents();
	bool shouldUpdate;
public:
	SGui(sf::RenderWindow& w);
	std::optional<SettingsData> update();
};

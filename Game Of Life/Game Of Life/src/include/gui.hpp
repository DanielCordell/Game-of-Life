#pragma once
#include <optional>

#include <TGUI/Gui.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <TGUI/Widgets/ComboBox.hpp>
#include <TGUI/Widgets/Button.hpp>

struct SettingsData {
	SettingsData(int width, int height, std::string foreground, std::string background, bool doClear, bool doToggle, bool doReset)
		: width(width), height(height), foreground(foreground), background(background), doClear(doClear), doToggle(doToggle), doReset(doReset) {}
	const int width, height;
	const std::string foreground, background;
	const bool doClear, doToggle, doReset;
	const static SettingsData Default;
};


class SGui : public tgui::Gui {
private:
	bool doReset;
	bool doToggle;
	bool doClear;

	sf::Font font;

	tgui::Slider::Ptr	widthSlider;
	tgui::Label::Ptr	widthLabel;

	tgui::Slider::Ptr	heightSlider;
	tgui::Label::Ptr	heightLabel;

	tgui::ComboBox::Ptr foregroundBox;
	tgui::Label::Ptr	foregroundLabel;

	tgui::ComboBox::Ptr backgroundBox;
	tgui::Label::Ptr	backgroundLabel;

	tgui::Button::Ptr	clearButton;

	tgui::Button::Ptr	resetButton;

	tgui::Button::Ptr	toggleButton;

	void initialize();
	void setDefaults() const;
	void addComponents();
	bool shouldUpdate;
public:
	SGui(sf::RenderWindow& w);
	std::optional<SettingsData> update();
};

#include <functional>

#include "include/gui.hpp"

const SettingsData SettingsData::Default{ 50,50,5,"White","Black" };

SGui::SGui(sf::RenderWindow& w) :
	Gui(w),
	widthSlider(tgui::Slider::create(10,100)),
	widthLabel(tgui::Label::create()),
	heightSlider(tgui::Slider::create(10,100)),
	heightLabel(tgui::Label::create()),
	speedSlider(tgui::Slider::create()),
	speedLabel(tgui::Label::create()),
	foregroundBox(tgui::ComboBox::create()),
	foregroundLabel(tgui::Label::create()),
	backgroundBox(tgui::ComboBox::create()),
	backgroundLabel(tgui::Label::create()),
	shouldUpdate(false)
{
	using namespace std::placeholders;

	font.loadFromFile("C:/Windows/Fonts/arialbd.ttf");

	initialize();
	setDefaults();
	addComponents();
}

void SGui::initialize() {
	tgui::Layout2d sliderSize(200, 20);
	int sliderX = 50;
	int sliderYMult = 70;

	//Creating the width slider
	widthSlider->setSize(sliderSize);
	widthSlider->setPosition({ sliderX, sliderYMult });
	widthSlider->setValue(SettingsData::Default.width);

	widthLabel->setPosition(150 - bindWidth(widthLabel) / 2.f, bindTop(widthSlider) + bindHeight(widthLabel) + 5);
	widthLabel->setFont(font);
	widthLabel->setTextColor(sf::Color::White);
	widthSlider->connect("valuechanged", [](tgui::Label::Ptr& label, bool& shouldUpdate, int value)
	{
	label->setText("Grid Width: " + std::to_string(value));
		shouldUpdate = true;
	}, widthLabel, std::ref(shouldUpdate));

	//Creating the height slider
	heightSlider->setSize(sliderSize);
	heightSlider->setPosition({ sliderX, sliderYMult * 2 });
	heightSlider->setValue(SettingsData::Default.height);

	heightLabel->setPosition(150 - bindWidth(heightLabel) / 2.f, bindTop(heightSlider) + bindHeight(heightLabel));
	heightLabel->setFont(font);
	heightLabel->setTextColor(sf::Color::White);
	heightSlider->connect("valuechanged", [](tgui::Label::Ptr& label, bool& shouldUpdate, int value)
	{
		label->setText("Grid Height: " + std::to_string(value));
		shouldUpdate = true;
	}, heightLabel, std::ref(shouldUpdate));

	//Creating the speed slider
	speedSlider->setSize(sliderSize);
	speedSlider->setPosition({ sliderX, sliderYMult * 3 });
	speedSlider->setValue(SettingsData::Default.speed);

	speedLabel->setPosition(150 - bindWidth(speedLabel) / 2.f, bindTop(speedSlider) + bindHeight(speedLabel));
	speedLabel->setFont(font);
	speedLabel->setTextColor(sf::Color::White);
	speedSlider->connect("valuechanged", [](tgui::Label::Ptr& label, bool& shouldUpdate, int value)
	{
		label->setText("Simulation Speed: " + std::to_string(value));
		shouldUpdate = true;
	}, speedLabel, std::ref(shouldUpdate));

	//Creating the foreground combobox
	foregroundBox->setSize(sliderSize);
	foregroundBox->setPosition({ sliderX, sliderYMult * 4 });
	foregroundBox->addItem("White");
	foregroundBox->addItem("Black");
	foregroundBox->setFont(font);
	foregroundBox->setSelectedItem(SettingsData::Default.foreground);

	foregroundLabel->setPosition(150 - bindWidth(foregroundLabel) / 2.f, bindTop(foregroundBox) + bindHeight(foregroundLabel));
	foregroundLabel->setFont(font);
	foregroundLabel->setTextColor(sf::Color::White);
	foregroundBox->connect("itemselected", [](tgui::Label::Ptr& label, bool& shouldUpdate, sf::String value)
	{
		label->setText("Foreground Color: " + value);
		shouldUpdate = true;
	}, foregroundLabel, std::ref(shouldUpdate));

	//Creating the background combobox
	backgroundBox->setSize(sliderSize);
	backgroundBox->setPosition({ sliderX, sliderYMult * 5 });
	backgroundBox->addItem("White");
	backgroundBox->addItem("Black");
	backgroundBox->setFont(font);
	backgroundBox->setSelectedItem(SettingsData::Default.background);

	backgroundLabel->setPosition(150 - bindWidth(backgroundLabel) / 2.f, bindTop(backgroundBox) + bindHeight(backgroundLabel));
	backgroundLabel->setFont(font);
	backgroundLabel->setTextColor(sf::Color::White);
	backgroundBox->connect("itemselected", [](tgui::Label::Ptr& label, bool& shouldUpdate, sf::String value)
	{
		label->setText("Background Color: " + value);
		shouldUpdate = true;
	}, backgroundLabel, std::ref(shouldUpdate));

}

void SGui::setDefaults() const {
	widthLabel->setText("Grid Width: " + std::to_string(widthSlider->getValue()));
	heightLabel->setText("Grid Height: " + std::to_string(heightSlider->getValue()));
	speedLabel->setText("Simulation Speed: " + std::to_string(speedSlider->getValue()));
	foregroundLabel->setText("Foreground Color: " + foregroundBox->getSelectedItem());
	backgroundLabel->setText("Background Color: " + backgroundBox->getSelectedItem());
}

void SGui::addComponents() {
	add(widthSlider);
	add(widthLabel);
	add(heightSlider);
	add(heightLabel);
	add(speedSlider);
	add(speedLabel);
	add(foregroundBox);
	add(foregroundLabel);
	add(backgroundBox);
	add(backgroundLabel);
}

std::optional<SettingsData> SGui::update() {
	if (shouldUpdate) {
		shouldUpdate = false;
		return SettingsData(widthSlider->getValue(), 
			heightSlider->getValue(), 
			speedSlider->getValue(),
			foregroundBox->getSelectedItem(),
			backgroundBox->getSelectedItem());
	}
	return {};
}

#include <functional>

#include "include/gui.hpp"

const SettingsData SettingsData::Default{ 50,50,"White","Black", false, false, false };

SGui::SGui(sf::RenderWindow& w) :
	Gui(w),
	widthSlider(tgui::Slider::create(10,100)),
	widthLabel(tgui::Label::create()),
	heightSlider(tgui::Slider::create(10,100)),
	heightLabel(tgui::Label::create()),
	foregroundBox(tgui::ComboBox::create()),
	foregroundLabel(tgui::Label::create()),
	backgroundBox(tgui::ComboBox::create()),
	backgroundLabel(tgui::Label::create()),
	resetButton(tgui::Button::create("Reset")),
	toggleButton(tgui::Button::create("Toggle Animation")),
	clearButton(tgui::Button::create("Clear")),
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
	doReset = false;
	doToggle = false;
	doClear = false;

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

	heightLabel->setPosition(150 - bindWidth(heightLabel) / 2.f, bindTop(heightSlider) + bindHeight(heightLabel) + 5);
	heightLabel->setFont(font);
	heightLabel->setTextColor(sf::Color::White);
	heightSlider->connect("valuechanged", [](tgui::Label::Ptr& label, bool& shouldUpdate, int value)
	{
		label->setText("Grid Height: " + std::to_string(value));
		shouldUpdate = true;
	}, heightLabel, std::ref(shouldUpdate));

	//Creating the foreground combobox
	foregroundBox->setSize(sliderSize);
	foregroundBox->setPosition({ sliderX, sliderYMult * 4 });
	foregroundBox->addItem("White");
	foregroundBox->addItem("Black");
	foregroundBox->addItem("Blue");
	foregroundBox->addItem("Green");
	foregroundBox->addItem("Red");
	foregroundBox->addItem("Yellow");
	foregroundBox->addItem("Cyan");
	foregroundBox->addItem("Magenta");

	foregroundBox->setFont(font);
	foregroundBox->setSelectedItem(SettingsData::Default.foreground);

	foregroundLabel->setPosition(150 - bindWidth(foregroundLabel) / 2.f, bindTop(foregroundBox) + bindHeight(foregroundLabel) + 5);
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
	backgroundBox->addItem("Blue");
	backgroundBox->addItem("Green");
	backgroundBox->addItem("Red");
	backgroundBox->addItem("Yellow");
	backgroundBox->addItem("Cyan");
	backgroundBox->addItem("Magenta");

	backgroundBox->setFont(font);
	backgroundBox->setSelectedItem(SettingsData::Default.background);

	backgroundLabel->setPosition(150 - bindWidth(backgroundLabel) / 2.f, bindTop(backgroundBox) + bindHeight(backgroundLabel) + 5);
	backgroundLabel->setFont(font);
	backgroundLabel->setTextColor(sf::Color::White);
	backgroundBox->connect("itemselected", [](tgui::Label::Ptr& label, bool& shouldUpdate, sf::String value)
	{
		label->setText("Background Color: " + value);
		shouldUpdate = true;
	}, backgroundLabel, std::ref(shouldUpdate));

	//Creating the Reset Button
	resetButton->setSize(sliderSize);
	resetButton->setPosition({ sliderX, sliderYMult * 7 });
	resetButton->setFont(font);
	resetButton->connect("pressed", [&] ()
	{
		doReset = true;
		shouldUpdate = true;
	});

	toggleButton->setSize(sliderSize);
	toggleButton->setPosition({ sliderX, sliderYMult * 7.5 });
	toggleButton->setFont(font);
	toggleButton->connect("pressed", [&]()
	{
		doToggle = true;
		shouldUpdate = true;
	});

	clearButton->setSize(sliderSize);
	clearButton->setPosition({ sliderX, sliderYMult * 8 });
	clearButton->setFont(font);
	clearButton->connect("pressed", [&]()
	{
		doClear = true;
		shouldUpdate = true;
	});
}

void SGui::setDefaults() const {
	widthLabel->setText("Grid Width: " + std::to_string(widthSlider->getValue()));
	heightLabel->setText("Grid Height: " + std::to_string(heightSlider->getValue()));
	foregroundLabel->setText("Foreground Color: " + foregroundBox->getSelectedItem());
	backgroundLabel->setText("Background Color: " + backgroundBox->getSelectedItem());
}

void SGui::addComponents() {
	add(widthSlider);
	add(widthLabel);
	add(heightSlider);
	add(heightLabel);
	add(foregroundBox);
	add(foregroundLabel);
	add(backgroundBox);
	add(backgroundLabel);
	add(clearButton);
	add(toggleButton);
	add(resetButton);
}

std::optional<SettingsData> SGui::update() {
	if (shouldUpdate) {
		shouldUpdate = false;
		SettingsData data(widthSlider->getValue(), 
			heightSlider->getValue(), 
			foregroundBox->getSelectedItem(),
			backgroundBox->getSelectedItem(),doClear,doToggle,doReset);
		doClear = false;
		doToggle = false;
		doReset = false;
		return data;
	}
	return {};
}

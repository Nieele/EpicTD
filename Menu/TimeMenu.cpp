#include "TimeMenu.hpp"

TimeMenu::TimeMenu()
{
	sf::Color colorText(0, 191, 255);
	sf::Vector2f startPos(40, 40);

	_background.setTexture(Configuration::backgrounds.get(Configuration::Backgrounds::InfoMenu));
	_background.setPosition(startPos);

	_hp.setFont(Configuration::fonts.get(Configuration::Fonts::GameGUI));
	_hp.setFillColor(colorText);
	_hp.setCharacterSize(14);
	_hp.setPosition(startPos.x + 5, startPos.y + 10); // 25 30

	_balance.setFont(Configuration::fonts.get(Configuration::Fonts::GameGUI));
	_balance.setFillColor(colorText);
	_balance.setCharacterSize(14);
	_balance.setPosition(startPos.x + 5, startPos.y + 30); // 25 50

	_time.setFont(Configuration::fonts.get(Configuration::Fonts::GameGUI));
	_time.setFillColor(colorText);
	_time.setCharacterSize(14);
	_time.setPosition(startPos.x + 5, startPos.y + 50); // 25 70
}

void TimeMenu::update(const int hp, const int balance, const int timeSeconds)
{
	_hp.setString(std::string("HP: ") + std::to_string(hp));

	_balance.setString(std::string("Balance: ") + std::to_string(balance));

	int hours = timeSeconds / 3600;
	int minutes = timeSeconds % 3600 / 60;
	int seconds = timeSeconds % 60;

	_time.setString(std::string("Time: ") + (hours < 10 ? "0" : "") + std::to_string(hours) + ":"
				+ (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":"
				+ (seconds < 10 ? "0" : "") + std::to_string(seconds));
}

void TimeMenu::render(sf::RenderTarget* target)
{
	target->draw(_background);
	target->draw(_hp);
	target->draw(_balance);
	target->draw(_time);
}

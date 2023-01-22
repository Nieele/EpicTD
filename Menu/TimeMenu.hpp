#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"

class TimeMenu
{
public:
	TimeMenu();

	void update(const int hp, const int balance, const int timeSeconds);
	void render(sf::RenderTarget* target);

private:
	sf::Sprite _background;
	sf::Text _hp;
	sf::Text _balance;
	sf::Text _time;
};


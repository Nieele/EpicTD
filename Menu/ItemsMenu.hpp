#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include "SFML/Graphics.hpp"

#include "../SimpleObjects/ItemContainer.hpp"
#include "../GeneralObjects/GameField.hpp"
#include "../GeneralObjects/Tower.hpp"

class Tower;
class Player;
class GameField;

class ItemsMenu
{
public:
	ItemsMenu();

	void processEvent(const sf::Event& event, const sf::Vector2f& mousePos, GameField& gameField,
		std::vector<std::shared_ptr<Tower>>& towers, Player& player);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

private:
	void placeTower(sf::Vector2f& pos, GameField& gameField, std::vector<std::shared_ptr<Tower>>& towers, Player& player);

	sf::Sprite _background;
	ItemContainer _items;

	sf::Vector2f _movingDeltaCord;
	bool _movingItem;
};


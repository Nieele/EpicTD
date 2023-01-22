#pragma once

#include <vector>
#include <fstream>

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"
#include "../SimpleObjects/CellMap.hpp"

class GameField
{
public:
	GameField();
	virtual ~GameField() = default;

	bool isOccupiedCell(const sf::Vector2f& pos);
	void occupyCell(const sf::Vector2f& pos);
	void freeCell(const sf::Vector2f& pos);

	void render(sf::RenderTarget* target);

private:
	void initMap();
	void initBorder();

	sf::RectangleShape _border;

	sf::Vector2f _startPosMap;
	sf::Vector2i _textureSizeMap;
	std::vector<std::vector<CellMap>> _field;
};


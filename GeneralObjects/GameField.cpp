#include "GameField.hpp"

void GameField::initMap()
{
	std::ifstream ifs("Config/gameMap.ini");

	if (!ifs.is_open()) throw std::exception("config gameMap.ini is not found.");

	ifs >> _startPosMap.x >> _startPosMap.y;
	sf::Vector2u sizeMap;
	ifs >> sizeMap.x >> sizeMap.y;
	_field = std::vector<std::vector<CellMap>>(sizeMap.x, std::vector<CellMap>(sizeMap.y));
	ifs >> _textureSizeMap.x >> _textureSizeMap.y;

	sf::Texture* tempTexture = &Configuration::textures.get(Configuration::Textures::GameMap);

	int rectX, rectY;
	ifs.get(); // miss \n
	for (size_t i = 0; i < sizeMap.y; ++i) {
		for (size_t j = 0; j < sizeMap.x; ++j) {
			rectY = ifs.get() - '0'; rectX = ifs.get() - '0';
			_field[i][j].setCell(
				tempTexture, sf::IntRect(
					rectX * _textureSizeMap.x, rectY * _textureSizeMap.y,
					_textureSizeMap.x, _textureSizeMap.y),
				sf::Vector2f(_startPosMap.x + j * _textureSizeMap.x, _startPosMap.y + i * _textureSizeMap.y),
				rectY == 1 ? true : false
			);
			ifs.get(); // miss ,
		}
		ifs.get(); // miss \n
	}

	ifs.close();
}

void GameField::initBorder()
{
	_border.setSize(sf::Vector2f(_field.size() * 64, _field[0].size() * 64));
	_border.setOutlineThickness(10);
	_border.setOutlineColor(sf::Color(54, 40, 29));
	_border.setPosition(_startPosMap);
}

GameField::GameField()
{
	initMap();
	initBorder();
}

bool GameField::isOccupiedCell(const sf::Vector2f& pos)
{
	// TODO _textureSizeMap
	return _field[size_t(pos.y + 64 - _startPosMap.y) / 64][size_t(pos.x - _startPosMap.x) / 64].isOccupied();
}

void GameField::occupyCell(const sf::Vector2f& pos)
{
	// TODO _textureSizeMap
	_field[size_t(pos.y + 64 - _startPosMap.y) / 64][size_t(pos.x - _startPosMap.x) / 64].occupy();
}

void GameField::freeCell(const sf::Vector2f& pos)
{
	_field[(pos.x - _startPosMap.x) / 64][(pos.y + 64 - _startPosMap.y) / 64].free();
}

void GameField::render(sf::RenderTarget* target)
{
	// TODO add _sizeMap (10x10)
	target->draw(_border);
	for (size_t i = 0; i < _field.size(); ++i)
		for (size_t j = 0; j < _field.front().size(); ++j)
			_field[i][j].render(target);
}

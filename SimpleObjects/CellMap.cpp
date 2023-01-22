#include "CellMap.hpp"

CellMap::CellMap(const CellMap& other)
	: Object()
{
	*_sprite = *other._sprite;
	_occupied = other._occupied;
}

CellMap::CellMap(CellMap&& other) noexcept
{
	_sprite = std::move(other._sprite);
	//other._sprite = nullptr;
	_occupied = other._occupied;
}

CellMap& CellMap::operator=(const CellMap& other)
{
	if (this != &other) {
		/*delete _sprite;
		_sprite = new sf::Sprite(*other._sprite);*/
		_sprite = other._sprite;

		_occupied = other._occupied;
	}
	return *this;
}

void CellMap::setCell(const sf::Texture* texture, const sf::IntRect& rectTexture,
	const sf::Vector2f& pos, const bool statusOccupied)
{
	_sprite->setTexture(*texture);
	_sprite->setTextureRect(rectTexture);
	_sprite->setPosition(pos);
	_occupied = statusOccupied;
}

void CellMap::occupy() noexcept
{
	_occupied = true;
}

void CellMap::free() noexcept
{
	_occupied = false;
}

bool CellMap::isOccupied() const noexcept
{
	return _occupied;
}

void CellMap::render(sf::RenderTarget* target)
{
	Object::render(target);
}

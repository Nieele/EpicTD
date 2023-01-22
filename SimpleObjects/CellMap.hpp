#pragma once

#include "SFML/Graphics.hpp"

#include "Object.hpp"

class CellMap
	: protected Object
{
public:
	CellMap() = default;
	virtual ~CellMap() = default;

	CellMap(const CellMap& other);
	CellMap(CellMap&& other) noexcept;
	CellMap& operator=(const CellMap& other);

	void setCell(const sf::Texture* texture, const sf::IntRect& rectTexture,
		const sf::Vector2f& pos, const bool statusOccupied = false);

	void occupy() noexcept;
	void free() noexcept;
	bool isOccupied() const noexcept;

	void render(sf::RenderTarget* target);

private:
	bool _occupied = false;
};


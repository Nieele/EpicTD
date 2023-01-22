#pragma once

#include "SFML/Graphics.hpp"

#include "Item.hpp"

class ItemContainer
{
public:
	ItemContainer();

	size_t size();

	Item& operator[](size_t pos);
	void select(size_t pos);
	void reset();

	void render(sf::RenderTarget* target);

private:
	std::vector<Item> _items;
};


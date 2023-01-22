#include "ItemContainer.hpp"

ItemContainer::ItemContainer()
{
	_items.emplace_back(Item(Configuration::Textures::WoodTower));
	_items.push_back(Item(Configuration::Textures::StoneTower));
	_items.push_back(Item(Configuration::Textures::GalacticTower));
	reset();
}

size_t ItemContainer::size()
{
	return _items.size();
}

Item& ItemContainer::operator[](size_t pos)
{
	return _items[pos];
}

void ItemContainer::select(size_t pos)
{
	// change from the last position for surface display
	std::swap(_items[pos], _items[_items.size() - 1]); 
}

void ItemContainer::reset()
{
	for (size_t i = 0; i <= 2; ++i) {
		for (size_t j = 0; j < 2; ++j)
			if (_items[j].getId() > _items[j + 1].getId())
				std::swap(_items[j], _items[j + 1]);
	}

	// start position in the menu
	sf::Vector2f startPosItem(1090, 185);
	for (size_t i = 0; i < 3; ++i) {
		_items[i].getSprite().setPosition(startPosItem);
		startPosItem.y += 145; // distance between elements
	}
}

void ItemContainer::render(sf::RenderTarget* target)
{
	for (size_t i = 0; i < 3; ++i)
		_items[i].render(target);
}

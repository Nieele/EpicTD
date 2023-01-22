#pragma once

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"

class Item
{
public:
	Item(const Configuration::Textures& idTexture);
	Item(const Configuration::Textures& idTexture, const sf::IntRect& rect);

	Item(const Item& other);
	Item(Item&& other) noexcept;
	Item& operator=(const Item& other);

	~Item();

	sf::Sprite& getSprite();
	int getId();

	void render(sf::RenderTarget* target);

protected:
	static int _count;

	sf::Sprite _sprite;
	int _id;
};


#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

class HpBar
{
public:
	HpBar(int hp, sf::Sprite* parent);
	~HpBar() = default;

	void update(int hp, sf::Sprite* _parent);
	void render(sf::RenderTarget* target);

private:
	const static float _shiftHpBar_x;
	const static sf::Vector2f _sizeHpBar;

	sf::Sprite* _parent;
	sf::RectangleShape _bar;
	int _maxHp;
	int _currentHp;
};


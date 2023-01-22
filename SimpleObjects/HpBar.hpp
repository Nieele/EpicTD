#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

class HpBar
{
public:
	HpBar(int hp, sf::Sprite* parent);
	~HpBar() = default;

	/*HpBar(const HpBar& other);
	HpBar(HpBar&& other);
	HpBar& operator=(const HpBar& other);*/

	void update(int hp);
	void render(sf::RenderTarget* target);

private:
	const static float _shiftHpBar_x;
	const static sf::Vector2f _sizeHpBar;

	sf::Sprite* _parent;
	sf::RectangleShape _bar;
	int _maxHp;
	int _currentHp;
};


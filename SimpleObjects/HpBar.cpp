#include "HpBar.hpp"

const float HpBar::_shiftHpBar_x(10);
const sf::Vector2f HpBar::_sizeHpBar(44, 5);

HpBar::HpBar(int hp, sf::Sprite* parent) : _maxHp(hp), _currentHp(hp), _parent(parent)
{
	_bar.setSize(_sizeHpBar);
	_bar.setFillColor(sf::Color::Red);
}

void HpBar::update(int hp, sf::Sprite* parent)
{
	if (_parent) {
		_bar.setPosition(_parent->getPosition().x + _shiftHpBar_x, _parent->getPosition().y);
		if (_currentHp != hp) {
			_currentHp = hp;
			_parent = parent;
			_bar.setSize(sf::Vector2f(_sizeHpBar.x * (_currentHp / _maxHp), _sizeHpBar.y));
		}
	}
}

void HpBar::render(sf::RenderTarget* target)
{
	target->draw(_bar);
}

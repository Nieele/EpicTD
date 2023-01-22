#include "HpBar.hpp"

const float HpBar::_shiftHpBar_x(10);
const sf::Vector2f HpBar::_sizeHpBar(44, 5);

HpBar::HpBar(int hp, sf::Sprite* parent) : _maxHp(hp), _currentHp(hp), _parent(parent)
{
	_bar.setSize(_sizeHpBar);
	_bar.setFillColor(sf::Color::Red);
}

//HpBar::HpBar(const HpBar& other)
//{
//}
//
//HpBar::HpBar(HpBar&& other)
//{
//}
//
//HpBar& HpBar::operator=(const HpBar& other)
//{
//	// TODO: вставьте здесь оператор return
//}

void HpBar::update(int hp)
{
	if (_parent) {
		_bar.setPosition(_parent->getPosition().x + _shiftHpBar_x, _parent->getPosition().y);
		if (_currentHp != hp) {
			_currentHp = hp;
			_bar.setSize(sf::Vector2f(_sizeHpBar.x * (_currentHp / _maxHp), _sizeHpBar.y));
		}
	}
}

void HpBar::render(sf::RenderTarget* target)
{
	target->draw(_bar);
}

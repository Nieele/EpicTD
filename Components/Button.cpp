#include "Button.hpp"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	: _idleColor(idleColor), _hoverColor(hoverColor), _activeColor(activeColor)
{
	_buttonState = BTN_IDLE;

	_shape.setPosition(sf::Vector2f(x, y));
	_shape.setSize(sf::Vector2f(width, height));

	_font = font;
	_text.setFont(*_font);
	_text.setString(text);
	_text.setFillColor(sf::Color::White);
	_text.setCharacterSize(12);
	_text.setPosition(
		_shape.getPosition().x + (_shape.getGlobalBounds().width / 2.f) - _text.getGlobalBounds().width / 2.f,
		_shape.getPosition().y + (_shape.getGlobalBounds().height / 2.f) - _text.getGlobalBounds().height / 2.f
	);
}

const bool Button::isPressed() const
{
	return _buttonState == BTN_ACTIVE;
}

void Button::update(const sf::Vector2f& mousePos)
{
	updateButtonState(mousePos);
	updateColorButton();
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(_shape);
	target->draw(_text);
}

void Button::updateButtonState(const sf::Vector2f& mousePos)
{
	//Idle
	_buttonState = BTN_IDLE;

	//Hover
	if (_shape.getGlobalBounds().contains(mousePos))
	{
		_buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			_buttonState = BTN_ACTIVE;
		}
	}
}

void Button::updateColorButton()
{
	switch (_buttonState)
	{
	case BTN_IDLE:
		_shape.setFillColor(_idleColor);
		break;

	case BTN_HOVER:
		_shape.setFillColor(_hoverColor);
		break;

	case BTN_ACTIVE:
		_shape.setFillColor(_activeColor);
		break;
	}
}

#pragma once

#include "SFML/Graphics.hpp"

class Button
{
public:
	enum BTN_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_CLICKED };

	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button() = default;

	//Accessors
	const bool isPressed() const;

	// Functions
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

private:
	short unsigned _buttonState;

	sf::RectangleShape _shape;
	sf::Font* _font;
	sf::Text _text;

	sf::Color _idleColor;
	sf::Color _hoverColor;
	sf::Color _activeColor;

	void updateButtonState(const sf::Vector2f& mousePos);
	void updateColorButton();
};

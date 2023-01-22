#pragma once

#include "SFML/Graphics.hpp"

class Object
{
public:
	Object();
	virtual ~Object();

	Object(const sf::Texture& texture);
	Object(const Object& other);
	Object(Object&& other) noexcept;
	Object& operator=(const Object& other);

	virtual sf::Vector2f getPosition() const;

	virtual void setPosition(const float x, const float y);
	virtual void setTexture(const sf::Texture& texture);

	virtual void render(sf::RenderTarget* target);

protected:
	sf::Sprite* _sprite;
};


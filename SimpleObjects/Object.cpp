#include "Object.hpp"

Object::Object()
{
	_sprite = new sf::Sprite();
}

Object::~Object()
{
	delete _sprite;
	_sprite = nullptr;
}

Object::Object(const sf::Texture& texture)
	: Object()
{
	_sprite->setTexture(texture);
}

Object::Object(const Object& other)
{
	_sprite = new sf::Sprite(*other._sprite);
}

Object::Object(Object&& other) noexcept
{
	_sprite = std::move(other._sprite);
	other._sprite = nullptr;
}

Object& Object::operator=(const Object& other)
{
	if (this != &other) {
		delete _sprite;
		_sprite = new sf::Sprite(*other._sprite);
	}

	return *this;
}

sf::Vector2f Object::getPosition() const
{
	return _sprite->getPosition();
}

void Object::setPosition(const float x, const float y)
{
	_sprite->setPosition(x, y);
}

void Object::setTexture(const sf::Texture& texture)
{
	_sprite->setTexture(texture);
}

void Object::render(sf::RenderTarget* target)
{
	target->draw(*_sprite);
}

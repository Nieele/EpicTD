#include "Entity.hpp"

Entity::Entity()
	: Object()
{
	_animationComponent = nullptr;
}

Entity::~Entity()
{
	delete _animationComponent;
	_animationComponent = nullptr;
}

Entity::Entity(const float x, const float y, sf::Texture& texture)
	: Object(texture)
{
	_animationComponent = nullptr;
	_sprite->setPosition(x, y);
}

Entity::Entity(const Entity& other)
{
	_animationComponent = new AnimationHelper(*other._animationComponent);
}

Entity::Entity(Entity&& other) noexcept
{
	_animationComponent = other._animationComponent;
	other._animationComponent = nullptr;
}

Entity& Entity::operator=(const Entity& other)
{
	if (this != &other) {
		delete _animationComponent;
		_animationComponent = new AnimationHelper(*other._animationComponent);
	}
	return *this;
}

void Entity::createAnimationComponent(sf::Sprite* sprite, sf::Texture& textureSheet)
{
	_animationComponent = new AnimationHelper(sprite, textureSheet);
}

void Entity::update() {}

void Entity::render(sf::RenderTarget* target)
{
	Object::render(target);
}

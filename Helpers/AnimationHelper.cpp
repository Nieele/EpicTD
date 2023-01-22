#include "AnimationHelper.hpp"

AnimationHelper::AnimationHelper(sf::Sprite* sprite, sf::Texture textureSheet)
	: _sprite(sprite), _textureSheet(textureSheet)
{
	_sprite->setTexture(_textureSheet);
}

AnimationHelper::~AnimationHelper()
{ 
	for (auto& el : _animations) {
		delete el.second;
		el.second = nullptr;
	}
}

AnimationHelper::AnimationHelper(const AnimationHelper& other)
	: _sprite(other._sprite), _textureSheet(other._textureSheet)
{
	for (auto& el : other._animations)
		_animations[el.first] = new Animation(*el.second);
}

AnimationHelper::AnimationHelper(AnimationHelper&& other) noexcept
	: _sprite(other._sprite), _textureSheet(other._textureSheet)
{
	for (auto& el : other._animations) {
		_animations[el.first] = el.second;
		el.second = nullptr;
	}
}

AnimationHelper& AnimationHelper::operator=(const AnimationHelper& other)
{
	if (this != &other) {
		for (auto& el : _animations) {
			delete el.second;
			el.second = nullptr;
		}

		_sprite = other._sprite;
		_textureSheet = other._textureSheet;

		for (auto& el : other._animations)
			_animations[el.first] = new Animation(*el.second);
	}

	return *this;
}

void AnimationHelper::addAnimation(const std::string& key, float animationTimer, 
	int startFrame_x, int startFrame_y, int frames_x, int frames_y, int width, int height)
{
	_animations[key] = new Animation(
		_sprite, _textureSheet, animationTimer,
		startFrame_x, startFrame_y, frames_x, frames_y,
		width, height
	);
}

void AnimationHelper::play(const std::string& key) noexcept
{
	if (_sprite) {
		if(_animations[key]) 
			_animations[key]->play();
	}
}

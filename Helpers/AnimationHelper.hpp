#pragma once

#include <memory>
#include <string>
#include <map>

#include "SFML/Graphics.hpp"

class AnimationHelper
{
public:
	AnimationHelper(sf::Sprite* sprite, sf::Texture textureSheet);
	virtual ~AnimationHelper();

	AnimationHelper(const AnimationHelper& other);
	AnimationHelper(AnimationHelper&& other) noexcept;
	AnimationHelper& operator=(const AnimationHelper& other);

	void addAnimation(const std::string& key, float animationTimer,
		int startFrame_x, int startFrame_y, int frame_x, int frames_y, int width, int height);

	void play(const std::string& key) noexcept;

private:
	class Animation {
	public:
		Animation(sf::Sprite* sprite, sf::Texture textureSheet, float animationTimer,
			int startFrame_x, int startFrame_y, int frames_x, int frames_y, int width, int height)
			: _sprite(sprite), _textureSheet(textureSheet), _animationTimer(animationTimer),
			_width(width), _height(height), _timer(0.f)
		{
			_startRect = sf::IntRect(startFrame_x * width, startFrame_y * height, width, height);
			_currentRect = _startRect;
			_endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			_sprite->setTexture(_textureSheet, true);
			_sprite->setTextureRect(_startRect);
		}

		void play() noexcept{
			_timer += 10.f; // speed animation
			if (_timer >= _animationTimer) {
				_timer = 0.f;

				if (_currentRect != _endRect)
					_currentRect.left += _width; // animate
				else
					_currentRect.left = _startRect.left; // reset

				_sprite->setTextureRect(_currentRect);
			}
		}

		void reset() noexcept{
			_timer = 0.f;
			_currentRect = _startRect;
		}

	private:
		sf::Sprite* _sprite;
		sf::Texture _textureSheet;
		float _animationTimer;
		float _timer;
		int _width;
		int _height;
		sf::IntRect _startRect;
		sf::IntRect _currentRect;
		sf::IntRect _endRect;
	};

	sf::Sprite* _sprite;
	sf::Texture _textureSheet;
	std::map<std::string, Animation*> _animations;
};


#pragma once

#include <numbers>

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"
#include "Enemy.hpp"

class Enemy;

class Bullet
{
public:
	Bullet(const sf::Texture& texture, const sf::Vector2f& spawnPos, const sf::Vector2f& enemyPos);
	virtual ~Bullet() = default;

	bool isReachedEnemy(std::shared_ptr<Enemy> target);
	bool isReachedEnemy();

	void fix();

	void updateEnemyPos(const sf::Vector2f& enemyPos);
	void update();

	void render(sf::RenderTarget* target);

private:
	sf::Sprite _object;
	float _speedBullet;
	bool _fixed;

	sf::Vector2f _enemyPos;
};


#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f& spawnPos, const sf::Vector2f& enemyPos)
	: _enemyPos(enemyPos), _fixed(false), _speedBullet(3)
{
	_object.setOrigin(16, 16);
	_object.setTexture(texture);
	_object.setScale(1, 1);
	_object.setTextureRect(sf::IntRect(0, 0, 32, 32));
	_object.setPosition(spawnPos);
	_object.setRotation((-(atan2f(spawnPos.x - _enemyPos.x,
		spawnPos.y - _enemyPos.y)) * 180 / std::numbers::pi));
}

Bullet::~Bullet()
{
}

bool Bullet::isReachedEnemy(std::shared_ptr<Enemy> target)
{
	return target->_sprite->getGlobalBounds().contains(_object.getPosition().x, _object.getPosition().y) ||
		sqrt(std::pow(_object.getPosition().x - _enemyPos.x, 2) +
			std::pow(_object.getPosition().y - _enemyPos.y, 2)) < 2;
}

bool Bullet::isReachedEnemy()
{
	return sqrt(std::pow(_object.getPosition().x - _enemyPos.x, 2) +
		std::pow(_object.getPosition().y - _enemyPos.y, 2)) < 4; // 3 - target hitting distance
}

void Bullet::fix()
{
	_fixed = true;
}

void Bullet::updateEnemyPos(const sf::Vector2f& enemyPos)
{
	if (!_fixed) {
		_enemyPos.x = enemyPos.x + 32;
		_enemyPos.y = enemyPos.y + 32;
	}
}

void Bullet::update()
{
	float distance = sqrt(std::pow(_object.getPosition().x - _enemyPos.x, 2) +
		std::pow(_object.getPosition().y - _enemyPos.y, 2));
	sf::Vector2f posBullet = _object.getPosition();
	posBullet.x += _speedBullet * (_enemyPos.x - posBullet.x) / distance;
	posBullet.y += _speedBullet * (_enemyPos.y - posBullet.y) / distance;
	_object.setPosition(posBullet);
}

void Bullet::render(sf::RenderTarget* target)
{
	if (target)
		target->draw(_object);
}

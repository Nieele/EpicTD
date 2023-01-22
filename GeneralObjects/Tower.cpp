#include "Tower.hpp"

#include <numbers>

Tower::Tower(const sf::Vector2f& pos, const Configuration::Textures towerTexture, const Configuration::Textures weaponTexture,
	const Configuration::Textures bulletTexture, int damage, float attackRadius, float attackSpeed, int cost)
	: _damage(damage), _attackRadius(attackRadius), _attackSpeed(attackSpeed), _cost(cost), _targetEnemy(nullptr),
	_bulletTexture(Configuration::textures.get(bulletTexture)), _lastAttack(0)
{
	_towerObject.setPosition(pos);
	_towerObject.setTexture(Configuration::textures.get(towerTexture));

	_weapon = sf::Sprite(Configuration::textures.get(weaponTexture));
	_weapon.setOrigin(48, 48);
	_weapon.setScale(1, 1);
	_weapon.setPosition(sf::Vector2f(pos.x + 32, pos.y + 32 + 24));

	_animationWeapon = new AnimationHelper(&_weapon, Configuration::textures.get(weaponTexture));
	_animationWeapon->addAnimation("Wait", 50.f, 0, 0, 0, 0, 96, 96);
	_animationWeapon->addAnimation("Attack", 160.f, 0, 0, 5, 0, 96, 96);
}

Tower::~Tower()
{
	delete _animationWeapon;
	_animationWeapon = nullptr;
}

Tower::Tower(const Tower& other)
{
	_towerObject = other._towerObject;
	_damage = other._damage;
	_attackRadius = other._attackRadius;
	_attackSpeed = other._attackSpeed;
	_lastAttack = other._lastAttack;
	_cost = other._cost;

	_targetEnemy = other._targetEnemy;
	_weapon = other._weapon;
	_animationWeapon = new AnimationHelper(*other._animationWeapon);

	_bulletTexture = other._bulletTexture;
	_bullets = other._bullets;
}

Tower::Tower(Tower&& other) noexcept
{
	_towerObject = other._towerObject;
	_damage = other._damage;
	_attackRadius = other._attackRadius;
	_attackSpeed = other._attackSpeed;
	_lastAttack = other._lastAttack;
	_cost = other._cost;

	_targetEnemy = other._targetEnemy;
	_weapon = other._weapon;
	_animationWeapon = std::move(other._animationWeapon);
	other._animationWeapon = nullptr;

	_bulletTexture = other._bulletTexture;
	_bullets = std::move(other._bullets);
}

Tower& Tower::operator=(const Tower& other)
{
	if (this != &other) {
		_towerObject = other._towerObject;
		_damage = other._damage;
		_attackRadius = other._attackRadius;
		_attackSpeed = other._attackSpeed;
		_lastAttack = other._lastAttack;
		_cost = other._cost;

		_targetEnemy = other._targetEnemy;
		_weapon = other._weapon;
		_animationWeapon = new AnimationHelper(*other._animationWeapon);

		_bulletTexture = other._bulletTexture;
		_bullets = other._bullets;
	}

	return *this;
}

void Tower::update(const Chronometer& timer, Wave* wave)
{
	if (!_targetEnemy) {
		this->findTarget(wave);
		for (size_t i = 0; i < _bullets.size(); ++i) {
			_bullets[i].fix();
			if (_bullets[i].isReachedEnemy()) {
				_bullets.erase(_bullets.begin() + i);
				--i;
			}
		}
		_animationWeapon->play("Wait");
	}

	if (_targetEnemy) {
		// turn on the enemy
		_weapon.setRotation(-(atan2f(_targetEnemy->getPosition().x + 32 - _weapon.getPosition().x,
			_targetEnemy->getPosition().y + 32 - _weapon.getPosition().y)) * 180 / std::numbers::pi + 180);

		// update flight trajectory
		for (size_t i = 0; i < _bullets.size(); ++i) {
			_bullets[i].updateEnemyPos(_targetEnemy->getPosition());
		}

		// update damage
		for (size_t i = 0; i < _bullets.size(); ++i) {
			if (_bullets[i].isReachedEnemy(_targetEnemy)) {
				_targetEnemy->changeHp(-_damage);
				_bullets.erase(_bullets.begin() + i);
				--i;
			}
		}

		// attack (spawn bullets)
		if (timer.getElapsedTime().asSeconds() - _lastAttack > _attackSpeed) {
			//_animationWeapon->play("Attack");
			_bullets.push_back(Bullet(_bulletTexture, _weapon.getPosition(), _targetEnemy->getPosition()));
			_lastAttack = timer.getElapsedTime().asSeconds();
		}

		// left the attack zone
		if (sqrt(std::pow(_weapon.getPosition().x - _targetEnemy->getPosition().x, 2) +
			std::pow(_weapon.getPosition().y - _targetEnemy->getPosition().y, 2)) > _attackRadius
			|| !_targetEnemy->isAlive())
			_targetEnemy = nullptr;
	}

	for (size_t i = 0; i < _bullets.size(); ++i) {
		_bullets[i].update();
	}
}

void Tower::render(sf::RenderTarget* target)
{
	target->draw(_towerObject);
	target->draw(_weapon);
	for (size_t i = 0; i < _bullets.size(); ++i)
		_bullets[i].render(target);
}

void Tower::findTarget(Wave* wave)
{
	float minDist = 999999;
	for (auto& el : wave->_enemeis) {
		float dist = sqrt(std::pow(_weapon.getPosition().x - el->getPosition().x, 2) +
			std::pow(_weapon.getPosition().y - el->getPosition().y, 2));
		if (dist > _attackRadius || dist > minDist) continue;
		else {
			minDist = dist;
			_targetEnemy = el;
		}
	}
}

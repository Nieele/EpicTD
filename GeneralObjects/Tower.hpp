#pragma once

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"
#include "../Components/Chronometer.hpp"
#include "Enemy.hpp"
#include "Wave.hpp"
#include "Bullet.hpp"
#include "../Menu/ItemsMenu.hpp"

class Wave;
class ItemsMenu;

class Tower
{
	friend class ItemsMenu;
public:
	Tower(const sf::Vector2f& pos, const Configuration::Textures towerTexture, const Configuration::Textures weaponTexture,
		const Configuration::Textures bulletTexture, int damage, float attackRadius, float attackSpeed, int cost);
	~Tower();

	Tower(const Tower& other);
	Tower(Tower&& other) noexcept;
	Tower& operator=(const Tower& other);

	void update(const Chronometer& timer, Wave* wave);
	void render(sf::RenderTarget* target);

private:
	void findTarget(Wave* wave);

	sf::Sprite _towerObject;
	int _damage;
	float _attackRadius;
	float _attackSpeed;
	float _lastAttack;
	int _cost;

	std::shared_ptr<Enemy> _targetEnemy;
	sf::Sprite _weapon;
	AnimationHelper* _animationWeapon;

	sf::Texture _bulletTexture;
	std::vector<Bullet> _bullets;
};


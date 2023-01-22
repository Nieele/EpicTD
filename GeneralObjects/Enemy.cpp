#include "Enemy.hpp"

void Enemy::initAnimations(sf::Texture& textureSheet) {
	this->createAnimationComponent(_sprite, textureSheet);

	_animationComponent->addAnimation("WALK_DOWN", 60, 0, 0, 7, 0, 64, 64);
	_animationComponent->addAnimation("WALK_RIGHT", 60, 0, 1, 7, 1, 64, 64);
	_animationComponent->addAnimation("WALK_LEFT", 60, 0, 2, 7, 2, 64, 64);
	_animationComponent->addAnimation("WALK_UP", 60, 0, 3, 7, 3, 64, 64);
}

Enemy::Enemy(const float x, const float y, sf::Texture& textureSheet, int hp, int loot, int rotation)
	: Entity(x, y, textureSheet), _hp(hp), _rotation(rotation), _idTrajectory(0), _movementSpeed((float)0.5), _loot(loot)
{
	initAnimations(textureSheet);
	_hpBar = new HpBar(hp, _sprite);
}

Enemy::~Enemy()
{
	delete _hpBar;
	_hpBar = nullptr;
}

Enemy::Enemy(const Enemy& other)
{
	/*delete _sprite;
	_sprite = new sf::Sprite(*other._sprite);*/
	_sprite = other._sprite;

	delete _animationComponent;
	_animationComponent = new AnimationHelper(*other._animationComponent);

	_hp = other._hp;
	_rotation = other._rotation;
	_killed = other._killed;
	_reachedEnd = other._reachedEnd;
	_loot = other._loot;

	_hpBar = new HpBar(_hp, _sprite);

	_idTrajectory = other._idTrajectory;
	_movementSpeed = other._movementSpeed;
}

Enemy::Enemy(Enemy&& other) noexcept
{
	_hpBar = std::move(other._hpBar);

	_sprite = std::move(other._sprite);
	//other._sprite = nullptr;

	_animationComponent = other._animationComponent;
	other._animationComponent = nullptr;

	_hp = other._hp;
	_rotation = other._rotation;
	_killed = other._killed;
	_reachedEnd = other._reachedEnd;
	_loot = other._loot;

	//other._hpBar = nullptr;

	_idTrajectory = other._idTrajectory;
	_movementSpeed = other._movementSpeed;
}

Enemy& Enemy::operator=(const Enemy& other)
{
	if (this != &other) {
		/*delete _sprite;
		_sprite = new sf::Sprite(*other._sprite);*/
		_sprite = other._sprite;

		delete _animationComponent;
		_animationComponent = new AnimationHelper(*other._animationComponent);

		_hp = other._hp;
		_rotation = other._rotation;
		_killed = other._killed;
		_reachedEnd = other._reachedEnd;
		_loot = other._loot;

		delete _hpBar;
		_hpBar = new HpBar(_hp, _sprite);

		_idTrajectory = other._idTrajectory;
		_movementSpeed = other._movementSpeed;
	}

	return *this;
}

bool Enemy::isAlive()
{
	return _hp > 0;
}

bool Enemy::isReachedEnd()
{
	return _reachedEnd;
}

void Enemy::changeHp(int hp)
{
	_hp += hp;
}

void Enemy::checkReachedEnd(const std::vector<sf::Vector2f>& movementTrajectory)
{
	if (_sprite->getPosition() == *(movementTrajectory.end() - 1))
		_reachedEnd = true;
}

void Enemy::changeDirectionMovement(const std::vector<sf::Vector2f>& movementTrajectory)
{
	using SIDE = AnimationEnemySide;

	if (_sprite->getPosition() == movementTrajectory[_idTrajectory + 1]) {
		_idTrajectory++;
		sf::Vector2f temp(_sprite->getPosition().x - movementTrajectory[_idTrajectory + 1].x, _sprite->getPosition().y - movementTrajectory[_idTrajectory + 1].y);
		_rotation = temp.x == 0 ? (temp.y > 0 ? SIDE::UP : SIDE::DOWN) : (temp.x > 0 ? SIDE::LEFT : SIDE::RIGHT);
	}
}

void Enemy::moveInDirection(const std::vector<sf::Vector2f>& movementTrajectory)
{
	using SIDE = AnimationEnemySide;

	switch (_rotation) {
	case SIDE::DOWN:
		if (movementTrajectory[_idTrajectory + 1].y - _sprite->getPosition().y > _movementSpeed) _sprite->move(0, _movementSpeed);
		else _sprite->setPosition(movementTrajectory[_idTrajectory + 1]);
		break;
	case SIDE::UP:
		if (_sprite->getPosition().y - movementTrajectory[_idTrajectory + 1].y >= _movementSpeed) _sprite->move(0, -_movementSpeed);
		else _sprite->setPosition(movementTrajectory[_idTrajectory + 1]);
		break;
	case SIDE::LEFT:
		if (_sprite->getPosition().x - movementTrajectory[_idTrajectory + 1].x >= _movementSpeed) _sprite->move(-_movementSpeed, 0);
		else _sprite->setPosition(movementTrajectory[_idTrajectory + 1]);
		break;
	case SIDE::RIGHT:
		if (movementTrajectory[_idTrajectory + 1].x - _sprite->getPosition().x >= _movementSpeed) _sprite->move(_movementSpeed, 0);
		else _sprite->setPosition(movementTrajectory[_idTrajectory + 1]);
		break;
	}
}

void Enemy::moveAlongMotionVector(const std::vector<sf::Vector2f>& movementTrajectory)
{
	// Ñhange sides (set of textures) if the enemy has reached the turn
	changeDirectionMovement(movementTrajectory);
	moveInDirection(movementTrajectory);
	// The enemy has reached the end
	checkReachedEnd(movementTrajectory);
}

void Enemy::animationInDirection()
{
	switch (_rotation)
	{
	case AnimationEnemySide::DOWN:
		_animationComponent->play("WALK_DOWN");
		break;

	case AnimationEnemySide::RIGHT:
		_animationComponent->play("WALK_RIGHT");
		break;

	case AnimationEnemySide::LEFT:
		_animationComponent->play("WALK_LEFT");
		break;

	case AnimationEnemySide::UP:
		_animationComponent->play("WALK_UP");
		break;
	}
}

void Enemy::checkIsAlive()
{
	if (_hp <= 0) _killed = true;
}

void Enemy::update(const std::vector<sf::Vector2f>& movementTrajectory)
{
	moveAlongMotionVector(movementTrajectory);
	animationInDirection();
	checkIsAlive();

	_hpBar->update(_hp, _sprite);
}

void Enemy::render(sf::RenderTarget* target)
{
	Entity::render(target);
	_hpBar->render(target);
}


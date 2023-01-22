#pragma once

#include "SFML/Graphics.hpp"

#include "../SimpleObjects/Entity.hpp"
#include "../SimpleObjects/HpBar.hpp"
#include "../GeneralObjects/Bullet.hpp"

class Bullet;

class Enemy
	: public Entity
{
public:
    friend class Bullet;

	const enum AnimationEnemySide : int { DOWN = 0, RIGHT = 1, LEFT = 2, UP = 3 };

    Enemy(const float x, const float y, sf::Texture& textureSheet,
        int hp, int loot, int rotation = AnimationEnemySide::DOWN);
    virtual ~Enemy();

    Enemy(const Enemy& other);
    Enemy(Enemy&& other) noexcept;
    Enemy& operator=(const Enemy& other);

    bool isAlive();
    bool isReachedEnd();

    void changeHp(int hp);

    void update(const std::vector<sf::Vector2f>& movementTrajectory);
    virtual void render(sf::RenderTarget* target) override;

private:
    int _hp;
    int _rotation;
    bool _killed = false;
    bool _reachedEnd = false;
    int _loot;

    std::shared_ptr<HpBar> _hpBar;

    int _idTrajectory;
    float _movementSpeed;

    void initAnimations(sf::Texture& textureSheet);
    void checkReachedEnd(const std::vector<sf::Vector2f>& movementTrajectory);
    void changeDirectionMovement(const std::vector<sf::Vector2f>& movementTrajectory);
    void moveInDirection(const std::vector<sf::Vector2f>& movementTrajectory);
    void moveAlongMotionVector(const std::vector<sf::Vector2f>& movementTrajectory);
    void animationInDirection();
    void checkIsAlive();
};


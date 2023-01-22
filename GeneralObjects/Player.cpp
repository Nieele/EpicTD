#include "Player.hpp"

Player::Player() : _hp(60), _balance(999999)
{
}

bool Player::isAlive() const noexcept
{
	return _hp > 0;
}

int Player::getHp() const noexcept
{
	return _hp;
}

int Player::getBalance() const noexcept
{
	return _balance;
}

void Player::changeHp(int hp) noexcept
{
	_hp += hp;
}

void Player::changeBalance(int balance) noexcept
{
	_balance += balance;
}

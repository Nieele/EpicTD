#pragma once
class Player
{
public:
	Player();
	~Player() = default;

	bool isAlive() const noexcept;

	int getHp() const noexcept;
	int getBalance() const noexcept;

	void changeHp(int hp) noexcept;
	void changeBalance(int balance) noexcept;

private:
	int _hp;
	int _balance;
};


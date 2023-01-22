#pragma once

#include <memory>
#include <fstream>
#include <vector>
#include <string>

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"
#include "../Components/Chronometer.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Tower.hpp"

class Wave
{
	friend class Tower;
public:
	Wave();
	~Wave() = default;

	void initWave(int id);

	bool isClearSpawning();
	bool isClearEnemies();

	void update(const Chronometer& timer, Player* player);
	void render(sf::RenderTarget* target);

private:
	void initTrajectory();
	void spawnEnemy(const Chronometer& timer);
	void eventProcessingEnemy(Player* player);

	sf::Texture _textureEnemies;
	std::vector<std::shared_ptr<Enemy>> _enemeis;

	std::vector<sf::Vector2f> _movingTrajectory;

	int _count;
	int _hpEnemy;
	int _lootEnemy;
	float _tLastSpawn;
	float _tDeltaSpawn;
};


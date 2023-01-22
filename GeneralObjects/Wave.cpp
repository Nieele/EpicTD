#include "Wave.hpp"

void Wave::initTrajectory()
{
	std::ifstream ifs("Config/trajectory.ini");

	if (!ifs.is_open()) throw std::exception("Trajectory.ini not found");

	int n;
	float x, y;
	ifs >> n;
	for (size_t i = 0; i < n; ++i) {
		ifs >> x >> y;
		_movingTrajectory.emplace_back(sf::Vector2f(x, y));
	}

	ifs.close();
}

Wave::Wave()
	: _tLastSpawn(0), _tDeltaSpawn(5), _count(0), _hpEnemy(0), _lootEnemy(0)
{
	initTrajectory();
}

void Wave::initWave(int id)
{
	std::string filePath = "Config/Waves/" + std::to_string(id) + "_wave.ini";
	std::ifstream ifs(filePath);

	if (!ifs.is_open()) throw std::exception("Wave is not found", id);

	int idTexture;

	ifs >> idTexture >> _count >> _hpEnemy >> _lootEnemy;

	ifs.close();

	_textureEnemies = sf::Texture(Configuration::textures.get(idTexture));
	_enemeis.clear();
}

bool Wave::isClearSpawning()
{
	return _count == 0;
}

bool Wave::isClearEnemies()
{
	return _enemeis.size() == 0;
}

void Wave::update(const Chronometer& timer, Player* player)
{
	spawnEnemy(timer);

	for (auto& el : _enemeis)
		el->update(_movingTrajectory);

	eventProcessingEnemy(player);
}

void Wave::render(sf::RenderTarget* target)
{
	for (auto& en : _enemeis)
		en->render(target);
}

void Wave::spawnEnemy(const Chronometer& timer)
{
	if (_count)
		if (timer.getElapsedTime().asSeconds() - _tLastSpawn > _tDeltaSpawn) {
			_enemeis.push_back(std::make_shared<Enemy>(_movingTrajectory[0].x, _movingTrajectory[0].y,
				_textureEnemies, _hpEnemy, _lootEnemy));
			_tLastSpawn = timer.getElapsedTime().asSeconds();
			--_count;
		}
}

void Wave::eventProcessingEnemy(Player* player)
{
	for (size_t i = 0; i < _enemeis.size(); ++i) {
		if (!_enemeis[i]->isAlive()) {
			player->changeBalance(_lootEnemy);
			_enemeis.erase(_enemeis.begin() + i);
			--i;
		}
		else if (_enemeis[i]->isReachedEnd()) {
			player->changeHp(-1);
			_enemeis.erase(_enemeis.begin() + i);
			--i;
		}
	}
}

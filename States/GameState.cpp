#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	_font = Configuration::fonts.get(Configuration::Fonts::GameGUI);
	_background.setTexture(Configuration::backgrounds.get(Configuration::Backgrounds::GameBack));
	
	_timer.reset();
	_timer.resume();
	_tBalanceUpdater = _timer.getElapsedTime().asMilliseconds();

	_level = 0;
	_countLevels = 3;
}

GameState::~GameState() {}

void GameState::processEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			_timer.pause();
			_states->push(new PauseMenuState(_window, _states, &_font, &_timer));
		}
	}

	/*if (event.type == sf::Event::LostFocus) {
		_timer.pause();
		_states->push(new PauseMenuState(_window, _states, &_font, &_timer));
	}*/

	if (!_player.isAlive()) {
		_states->push(new GameOverState(_window, _states));
		Configuration::musics.get(Configuration::Musics::MainTheme).stop();
		Configuration::musics.get(Configuration::Musics::GameOverTheme).play();
	}

	if (_level == _countLevels && _wave.isClearEnemies() && _wave.isClearSpawning()) {
		_timer.pause();
		_states->push(new WinState(_window, _states));
		// TODO winning song
	}

	_itemMenu.processEvent(event, _mousePosView, _map, _towers, _player);
}

void GameState::update()
{
	this->updateMousePositions();

	if (_timer.getElapsedTime().asMilliseconds() - _tBalanceUpdater > 1000) {
		_player.changeBalance(1);
		_tBalanceUpdater = _timer.getElapsedTime().asMilliseconds();
	}

	if (_level < _countLevels && _wave.isClearEnemies() && _wave.isClearSpawning()) {
		_wave.initWave(_level);
		++_level;
	}
	_wave.update(_timer, &_player);

	for (auto& el : _towers)
		el->update(_timer, &_wave);

	_infoMenu.update(_player.getHp(), _player.getBalance(), (int)_timer.getElapsedTime().asSeconds());
	_itemMenu.update(_mousePosView);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->_window;

	target->draw(_background);
	_map.render(target);

	_wave.render(target);

	for (auto& el : _towers)
		el->render(target);

	_infoMenu.render(target);
	_itemMenu.render(target);
}

#pragma once

#include "SFML/Graphics.hpp"

#include "../Components/Chronometer.hpp"
#include "State.hpp"
#include "PauseMenuState.hpp"
#include "GameOverState.hpp"
#include "WinState.hpp"
#include "../GeneralObjects/Enemy.hpp"
#include "../GeneralObjects/GameField.hpp"
#include "../GeneralObjects/Wave.hpp"
#include "../GeneralObjects/Player.hpp"
#include "../GeneralObjects/Tower.hpp"
#include "../Menu/ItemsMenu.hpp"
#include "../Menu/TimeMenu.hpp"

class GameState : 
	public State
{
public:
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	void processEvents(sf::Event& _event) override;
	void update() override;
	void render(sf::RenderTarget* target = nullptr) override;

private:
	Chronometer _timer;
	sf::Int32 _tBalanceUpdater;
	sf::Font _font;

	Player _player;

	sf::Sprite _background;
	GameField _map;

	std::vector<std::shared_ptr<Tower>> _towers;

	TimeMenu _infoMenu;
	ItemsMenu _itemMenu;

	Wave _wave;
	int _level;
	int _countLevels;
};
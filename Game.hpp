#pragma once

#include <fstream>
#include <stack>

#include "SFML/Graphics.hpp"

#include "Components/Configuration.hpp"
#include "States/State.hpp"
#include "States/MainMenuState.hpp"

class Game
{
public:
	Game();
	virtual ~Game();

	void run();

private:
	sf::RenderWindow* _window;
	sf::Event _event;

	std::stack<State*> _states;

	sf::Clock _clockStab;
	float _fpsLimit;

	void processEvents();
	void update();
	void render();

	void initWindow();
	void initStates();
};


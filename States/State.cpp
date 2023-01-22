#include "State.hpp"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	_window = window;
	_states = states;
	_quit = false;
}

State::~State() {}

void State::quit()
{
	_quit = true;
}

const bool& State::getQuit() const
{
	return _quit;
}

void State::updateMousePositions()
{
	_mousePosScreen = sf::Mouse::getPosition();
	_mousePosWindow = sf::Mouse::getPosition(*_window);
	_mousePosView = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
}

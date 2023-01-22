#include "WinState.hpp"

WinState::WinState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	_background.setTexture(Configuration::backgrounds.get(Configuration::Backgrounds::GameWin));
}

WinState::~WinState()
{
}

void WinState::processEvents(sf::Event& event)
{
}

void WinState::update()
{
	this->updateMousePositions();
}

void WinState::render(sf::RenderTarget* target)
{
	if (!target)
		target = _window;

	target->draw(_background);
}

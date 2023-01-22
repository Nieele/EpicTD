#include "GameOverState.hpp"

GameOverState::GameOverState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	_background.setTexture(Configuration::backgrounds.get(Configuration::Backgrounds::GameOver));
}

void GameOverState::processEvents(sf::Event& _event)
{

}

void GameOverState::update()
{
	this->updateMousePositions();
}

void GameOverState::render(sf::RenderTarget* target)
{
	if (!target) 
		target = _window;

	target->draw(_background);
}

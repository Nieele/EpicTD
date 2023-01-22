#include "PauseMenuState.hpp"

void PauseMenuState::initBackground()
{
	_background.setSize(sf::Vector2f(_window->getSize()));
	_background.setTexture(&Configuration::backgrounds.get(Configuration::Backgrounds::PauseMenu));
}

void PauseMenuState::initButtons()
{
	_buttons["RESUME"] = new Button(550, 240, 180, 60, _font, "Resume",
		sf::Color(70, 70, 70, 200), sf::Color(75, 0, 130, 255), sf::Color(20, 20, 20, 200));
	_buttons["QUIT"] = new Button(550, 360, 180, 60, _font, "Quit",
		sf::Color(70, 70, 70, 200), sf::Color(75, 0, 130, 255), sf::Color(20, 20, 20, 200));
}

PauseMenuState::PauseMenuState(sf::RenderWindow* window, std::stack<State*>* states, sf::Font* font, Chronometer* timer) 
	: State(window, states), _font(font), _timer(timer)
{
	this->initBackground();
	this->initButtons();
}

PauseMenuState::~PauseMenuState()
{
	for (auto el : _buttons)
		delete el.second;
}

void PauseMenuState::processEvents(sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed) {
		if (_event.key.code == sf::Keyboard::Escape) {
			quit();
			_timer->resume();
		}
	}
}

void PauseMenuState::update()
{
	this->updateMousePositions();
	this->updateButtons();
}

void PauseMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = _window;

	target->draw(_background);
	this->renderButtons(_window);
}

void PauseMenuState::updateButtons()
{
	for (auto& el : _buttons)
		el.second->update(_mousePosView);

	if (this->_buttons["RESUME"]->isPressed()) {
		quit();
		_timer->resume();
	}

	if (this->_buttons["QUIT"]->isPressed())
		_window->close();
}

void PauseMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& btn : _buttons)
		btn.second->render(target);
}
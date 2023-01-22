#include "MainMenuState.hpp"

void MainMenuState::initBackground()
{
	//_background.setSize(sf::Vector2f(_window->getSize()));
	_background.setTexture(Configuration::backgrounds.get(Configuration::Backgrounds::MainMenu));
}

void MainMenuState::initButtons()
{
	_buttons["NEW_GAME"] = new Button(382, 240, 180, 60, &_font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(75, 0, 130, 255), sf::Color(20, 20, 20, 200));
	_buttons["SETTINGS"] = new Button(382, 320, 180, 60, &_font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(75, 0, 130, 255), sf::Color(20, 20, 20, 200));
	_buttons["QUIT"] = new Button(382, 450, 180, 60, &_font, "Quit",
		sf::Color(70, 70, 70, 200), sf::Color(75, 0, 130, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) 
	: State(window, states)
{
	_font = Configuration::fonts.get(Configuration::Fonts::MenuGUI);
	initBackground();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto &el : _buttons)
		delete el.second;
}

void MainMenuState::processEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			quit();
}

void MainMenuState::update()
{
	updateMousePositions();
	updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = _window;

	target->draw(_background);
	renderButtons(target);
}

void MainMenuState::updateButtons()
{
	for (auto& el : _buttons)
		el.second->update(_mousePosView);

	if (_buttons["NEW_GAME"]->isPressed())
		_states->push(new GameState(_window, _states));

	if (_buttons["QUIT"]->isPressed())
		quit();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : _buttons)
		it.second->render(target);
}
#include "Game.hpp"

void Game::initWindow()
{
	std::ifstream ifs("Config/window.ini");

	std::string title = "None";
	sf::VideoMode windowBounds(1280, 720);
	bool fullscreen = false;
	unsigned framerateLimit = 60;
	bool verticalSyncEnabled = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> fullscreen;
		ifs >> framerateLimit;
		ifs >> verticalSyncEnabled;
	}

	ifs.close();

	if (fullscreen)
		_window = new sf::RenderWindow(windowBounds, title, sf::Style::Fullscreen);
	else
		_window = new sf::RenderWindow(windowBounds, title, sf::Style::Close);

	_window->setFramerateLimit(framerateLimit);
	_window->setVerticalSyncEnabled(verticalSyncEnabled);

	_fpsLimit = (float)framerateLimit;
}

void Game::initStates()
{
	_states.push(new MainMenuState(_window, &_states));
}

Game::Game()
{
	Configuration::initialize();
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete _window;

	while (!_states.empty()) {
		delete _states.top();
		_states.pop();
	}
}

void Game::run()
{
	sf::Int32 frameDuration = _clockStab.getElapsedTime().asMilliseconds();
	sf::Int32 timeToSleep = int(1000.f / _fpsLimit) - frameDuration;
	while (_window->isOpen()) {
		processEvents();
		update();
		render();

		// Stabilization fps
		frameDuration = _clockStab.getElapsedTime().asMilliseconds();
		timeToSleep = int(1000.f / _fpsLimit) - frameDuration;
		if (timeToSleep > 0)
			sf::sleep(sf::milliseconds(timeToSleep));
		_clockStab.restart();
	}
}

void Game::processEvents()
{
	while (_window->pollEvent(_event)) {
		if (_event.type == sf::Event::Closed)
			_window->close();
		_states.top()->processEvents(_event);
	}
}

void Game::update()
{
	if (!_states.empty()) {
		_states.top()->update();

		if (_states.top()->getQuit()) {
			delete _states.top();
			_states.pop();
		}
	}
	else {
		_window->close();
	}
}

void Game::render()
{
	_window->clear();

	if (!_states.empty())
		_states.top()->render(_window);

	_window->display();
}
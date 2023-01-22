#pragma once

#include <stack>

#include "SFML/Graphics.hpp"

class State
{
public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	virtual void quit();
	const bool& getQuit() const;

	virtual void updateMousePositions();

	virtual void processEvents(sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	std::stack<State*>* _states;
	sf::RenderWindow* _window;
	bool _quit;

	sf::Vector2i _mousePosScreen;
	sf::Vector2i _mousePosWindow;
	sf::Vector2f _mousePosView;
};


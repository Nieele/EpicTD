#pragma once

#include <stack>

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"
#include "State.hpp"

class WinState
	: public State
{
public:
	WinState(sf::RenderWindow* window, std::stack<State*>* states);
	~WinState();

	void processEvents(sf::Event& event) override;
	void update() override;
	void render(sf::RenderTarget* target = nullptr) override;

private:
	sf::Sprite _background;
};


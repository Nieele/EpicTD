#pragma once

#include <stack>

#include "SFML/Graphics.hpp"

#include "../Components/Configuration.hpp"
#include "State.hpp"

class GameOverState 
	: public State
{
public:
	GameOverState(sf::RenderWindow* window, std::stack<State*>* states);

	void processEvents(sf::Event& _event) override;
	void update() override;
	void render(sf::RenderTarget* target = nullptr) override;

private:
	sf::Sprite _background;
};


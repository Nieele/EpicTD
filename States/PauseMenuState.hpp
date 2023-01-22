#pragma once

#include <stack>

#include "SFML/Graphics.hpp"

#include "State.hpp"
#include "../Components/Button.hpp"
#include "../Components/Configuration.hpp"
#include "../Components/Chronometer.hpp"

class PauseMenuState :
	public State
{
public:
	PauseMenuState(sf::RenderWindow* window, std::stack<State*>* states, sf::Font* font, Chronometer* timer);
	virtual ~PauseMenuState();

	void processEvents(sf::Event& _event) override;
	void update() override;
	void render(sf::RenderTarget* target = nullptr) override;

private:
	sf::RectangleShape _background;
	sf::Font* _font;

	std::map<std::string, Button*> _buttons;

	Chronometer* _timer;

	void initBackground();
	void initButtons();

	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
};


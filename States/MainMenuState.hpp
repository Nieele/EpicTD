#pragma once

#include <sstream>

#include "../Components/Configuration.hpp"
#include "../Components/Button.hpp"
#include "State.hpp"
#include "GameState.hpp"

class MainMenuState :
	public State
{
public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();

	void processEvents(sf::Event& _event) override;
	void update() override;
	void render(sf::RenderTarget* target = nullptr) override;

private:
	sf::Sprite _background;
	sf::Font _font;

	std::map<std::string, Button*> _buttons;

	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);

	void initBackground();
	void initButtons();
};


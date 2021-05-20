#include <sstream>
#include <iostream>

#include "RulesState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

namespace gol
{
	RulesState::RulesState(GameDataRef data) : _data(data)
	{

	}

	void RulesState::Init()
	{
		this->_data->assets.LoadTexture("Rules State Background", RULES_STATE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Back Button", BACK_BUTTON_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Rules State Background"));
		_backButton.setTexture(this->_data->assets.GetTexture("Back Button"));

		_backButton.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 35);

	}

	void RulesState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			} 

			if (_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, _data->window))
			{
				// Swtich to Main Menu
				std::cout << "Go to Main Menu" << std::endl;
				_data->machine.RemoveState();

			}

			if (event.type == sf::Event::KeyPressed)
			{
				// Switch to Main Menu
				if (event.key.code == sf::Keyboard::Escape)
				{
					std::cout << "Escaped to Main Menu ;)" << std::endl;
					_data->machine.RemoveState();
				}
			}
		}
	}

	void RulesState::Update(float dt)
	{	}

	void RulesState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(0,0,0,255));

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_backButton);

		this->_data->window.display();
	}
}
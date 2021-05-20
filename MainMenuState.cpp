#include <sstream>
#include <iostream>

#include "RulesState.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

namespace gol
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Main Menu State Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Rules Button", RULES_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Quit Button", QUIT_BUTTON_FILEPATH);



		_background.setTexture(this->_data->assets.GetTexture("Main Menu State Background"));
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		_quitButton.setTexture(this->_data->assets.GetTexture("Quit Button"));
		_rulesButton.setTexture(this->_data->assets.GetTexture("Rules Button"));


		_title.setPosition(SCREEN_WIDTH - _title.getGlobalBounds().width - 10, 10); 
		_playButton.setPosition(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 6);
		_rulesButton.setPosition(SCREEN_WIDTH / 5, _playButton.getPosition().y + _playButton.getGlobalBounds().height + 10);
		_quitButton.setPosition(SCREEN_WIDTH / 5, _rulesButton.getPosition().y + _rulesButton.getGlobalBounds().height + 10);
		

	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				// if closed
				this->_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
			{
				// Switch To Game State

				std::cout << "Go to Game Screen" << std::endl;

				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}

			if (_data->input.IsSpriteClicked(_quitButton, sf::Mouse::Left, _data->window))
			{
				// Shutdown 
				std::cout << "EXIT" << std::endl;
				this->_data->window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{

				// Shutdown
				if (event.key.code == sf::Keyboard::Escape)
				{
					std::cout << "Escaped.." << std::endl;
					this->_data->window.close();
				}
			}

			if (_data->input.IsSpriteClicked(_rulesButton, sf::Mouse::Left, _data->window))
			{
				// Switch to Rules State

				std::cout << "Go to Rules Screen" << std::endl;

				_data->machine.AddState(StateRef(new RulesState(_data)), true);

			}

			if (_data->input.IsSpriteClicked(_title, sf::Mouse::Right, _data->window))
			{
				// lolz
				std::cout << "*easter egg*" << std::endl;
				std::cout << "*easter egg*" << std::endl;
				std::cout << "*easter egg*" << std::endl;
				std::cout << "*easter egg*" << std::endl;
				std::cout << "*easter egg*" << std::endl;
				std::cout << "*easter egg*" << std::endl;
				std::cout << "*xD*" << std::endl;
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
		// nothing to see here
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(0,0,0,255));

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_quitButton);
		this->_data->window.draw(this->_rulesButton);

		this->_data->window.display();
	}
}
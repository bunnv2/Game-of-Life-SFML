#include <sstream>
#include <iostream>
#include <time.h>

#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"



namespace gol
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{

		this->_data->assets.LoadTexture("Game State Background", GAME_STATE_BACKGROUND_FILEPATH);
		
		this->_data->assets.LoadTexture("Quit Button", QUIT_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Start Button", START_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Plus Button", PLUS_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Minus Button", MINUS_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Clean Button", CLEAN_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Randomize Button", RANDOMIZE_BUTTON_FILEPATH);


		_background.setTexture(this->_data->assets.GetTexture("Game State Background"));
		_quitButton.setTexture(this->_data->assets.GetTexture("Quit Button"));
		_startButton.setTexture(this->_data->assets.GetTexture("Start Button"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_plusButton.setTexture(this->_data->assets.GetTexture("Plus Button"));
		_minusButton.setTexture(this->_data->assets.GetTexture("Minus Button"));
		_cleanButton.setTexture(this->_data->assets.GetTexture("Clean Button"));
		_randomizeButton.setTexture(this->_data->assets.GetTexture("Randomize Button"));


		_quitButton.setPosition(10, 10);


		_pauseButton.setPosition(0, SCREEN_HEIGHT - 65);
		_startButton.setPosition(90, SCREEN_HEIGHT - 65);
		_minusButton.setPosition(0, SCREEN_HEIGHT - 126);
		_plusButton.setPosition(90, SCREEN_HEIGHT - 126);
		_cleanButton.setPosition(_startButton.getPosition().x + 130, SCREEN_HEIGHT - 29);
		_randomizeButton.setPosition(_cleanButton.getPosition().x + 100, SCREEN_HEIGHT - 29);


	}

	void GameState::HandleInput()
	{

		while (this->_data->window.pollEvent(event))
		{
			
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			// Go back to Main Menu
			if (event.type == sf::Event::KeyPressed)
			{

				if (event.key.code == sf::Keyboard::Escape)
				{
					std::cout << "Escaped to Main Menu.." << std::endl;
					this->_data->machine.RemoveState();
				}
			}

			// Go back to Main Menu
			if (_data->input.IsSpriteClicked(_quitButton, sf::Mouse::Left, _data->window))
			{
				std::cout << "Go to Main Menu" << std::endl;
				_data->machine.RemoveState();

			}

			// Pause
			if (_data->input.IsSpriteClicked(_pauseButton, sf::Mouse::Left, _data->window))
			{
				std::cout << "Pause the game" << std::endl;
				state=STATES::PAUSE;
			}


			// Speed up 
			if (_data->input.IsSpriteClicked(_plusButton, sf::Mouse::Left, _data->window))
			{
				howFast -= howFastIncrease;
			}
			
			// Slow down
			if (_data->input.IsSpriteClicked(_minusButton, sf::Mouse::Left, _data->window))
			{
				howFast += howFastIncrease;
			}

			// Simulate
			if (_data->input.IsSpriteClicked(_startButton, sf::Mouse::Left, _data->window))
			{
				std::cout << "Starting simulating.." << std::endl;
				state = STATES::SIMULATE;
			}

			// Planning
			if (state == STATES::PAUSE) 
			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left);
					{
						int x = double(event.mouseButton.x) / CELL_SIZE; //COLUMNS
						int y = double(event.mouseButton.y) / CELL_SIZE; //LINES

						// GETTING MOUSE POSITION TO PICK A CELL
						// THESE ARE BUTTONS PARAMETERS, SO WE DONT LIKE TO CLICK THERE
						if (x <= 8 && x < GRID_WIDTH && y <= 29 && y < GRID_HEIGHT
							|| x >= 11 && x <= 14 && x < GRID_WIDTH && y >= 28 && y <= 29 && y < GRID_HEIGHT
							|| x >= 16 && x <= 21 && x < GRID_WIDTH && y >= 28 && y <= 29 && y < GRID_HEIGHT) 
						{
							continue;
						}

						else if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
						{
							grid[x + y * GRID_WIDTH] = !grid[x + y * GRID_WIDTH]; //default = 0 <-- ! = 1
						}
					}
				}

				// BOARD CLEANING
				if (_data->input.IsSpriteClicked(_cleanButton, sf::Mouse::Left, _data->window))
				{
					std::cout << "Cleaning up the board.." << std::endl;

					for (int i = 0; i < cellNumber; i++)
					{
						grid[i] = 0;
					}

				}

				// RANDOMIZING ALL CELLS
				if (_data->input.IsSpriteClicked(_randomizeButton, sf::Mouse::Left, _data->window))
				{

					srand(time(NULL));

					for (int i = 0; i < cellNumber; i++)
					{
						grid[i] = rand() % +2;
					}

				}

			}

		}
	}

	void GameState::Update(float dt)
	{
		// nothing to see here
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear();

		//PLANNER LOGIC AND DRAW
		if (state == STATES::PAUSE)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				for (int y = 0; y < GRID_HEIGHT; y++)
				{

					// CELL DRAWING
					_cell.setPosition((x)*CELL_SIZE, (y)*CELL_SIZE);
					_cell.setSize(CELL_VECTOR);
					_cell.setOutlineThickness(1);
					_cell.setOutlineColor(sf::Color(155, 155, 155));
					
					if (grid[x + y * GRID_WIDTH] == 1)
					{
						_cell.setFillColor(sf::Color::White); // if alive
					}

					else
					{
						_cell.setFillColor(sf::Color::Black); // if dead
					}


					this->_data->window.draw(_cell);
					this->_data->window.draw(this->_cleanButton);
					this->_data->window.draw(this->_randomizeButton);


				}
			}
		}

		drawBorders();

		// SIMULATOR LOGIC AND DRAW
		if (state == STATES::SIMULATE)
		{

			// DRAWING GRID
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				for (int y = 0; y < GRID_HEIGHT; y++)
				{
					// PREPARE NEXT GEN
					prepareNext(x, y);

					// DRAWING CURRENT GRID
					_cell.setPosition((x)*CELL_SIZE, (y)*CELL_SIZE);
					_cell.setSize(CELL_VECTOR);
					if (grid[x + y * GRID_WIDTH] == 1) // if alive
					{
						_cell.setFillColor(sf::Color::White);
						_cell.setOutlineColor(sf::Color::White);

						howManyAlive++;
					}

					else
					{
						_cell.setFillColor(sf::Color::Black); //if dead
						_cell.setOutlineColor(sf::Color::Black);
					}

					this->_data->window.draw(_cell);

				}
			}

			// COPY NEXT GRID TO ACTUAL GRID
			for (int i = 0; i < cellNumber; i++)
			{
				grid[i] = gridNext[i];
			}

			// SOME BASIC INFO
			if (state == STATES::SIMULATE)
			{
				if (howFast == 0 || howFast < 0)
				{
					std::cout << "Speed: Light speed" << std::endl;
				}
				else if (howFast == 50)
				{
					std::cout << "Speed: Fast" << std::endl;
				}
				else if (howFast == 100)
				{
					std::cout << "Speed: Medium" << std::endl;
				}
				else
				{
					std::cout << "Speed: Slow" << std::endl;
				}

				std::cout << "Alive: " << howManyAlive << std::endl;
				std::cout << "Genarations: " << generation << std::endl << std::endl;

				generation++;
				howManyAlive = 0;
			}

		}


		// BUTTONS DRAWING
		this->_data->window.draw(this->_quitButton);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_startButton);
		this->_data->window.draw(this->_minusButton);
		this->_data->window.draw(this->_plusButton);

		this->_data->window.display();
		sf::sleep(sf::milliseconds(howFast));
	}
}

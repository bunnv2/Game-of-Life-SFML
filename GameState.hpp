#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>

#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"

// SOME CONSTS..
const int CELL_SIZE = 20;
const int GRID_WIDTH = (SCREEN_WIDTH)/CELL_SIZE;
const int GRID_HEIGHT = (SCREEN_HEIGHT)/CELL_SIZE;
const int cellNumber = GRID_WIDTH * GRID_HEIGHT;

const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
const sf::Vector2f BORDER_W_VECTOR(SCREEN_WIDTH, 4);
const sf::Vector2f BORDER_H_VECTOR(4, SCREEN_HEIGHT);


namespace gol
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		void drawBorders()
		{
			_bordersW.setSize(BORDER_W_VECTOR);
			_bordersW.setPosition(0, 0);
			_bordersW.setFillColor(sf::Color::White);
			this->_data->window.draw(this->_bordersW);
			_bordersW.setPosition(0, SCREEN_HEIGHT - 4);
			this->_data->window.draw(this->_bordersW);

			_bordersH.setSize(BORDER_H_VECTOR);
			_bordersH.setPosition(0, 0);
			_bordersH.setFillColor(sf::Color::White);
			this->_data->window.draw(this->_bordersH);
			_bordersH.setPosition(SCREEN_WIDTH - 4, 0);
			this->_data->window.draw(this->_bordersH);

		}
		void prepareNext(int x, int y)
		{

			int neighbors = 0;

			if (grid[(x - 1) + (y - 1) * GRID_WIDTH] == 1)
			{
				neighbors++;
			}
			if (grid[x + (y - 1) * GRID_WIDTH] == 1)
			{
				neighbors++;

			}
			if (grid[(x + 1) + (y - 1) * GRID_WIDTH] == 1)
			{
				neighbors++;
			}
			if (grid[(x - 1) + y * GRID_WIDTH] == 1)
			{
				neighbors++;
			}
			if (grid[(x + 1) + y * GRID_WIDTH] == 1)
			{
				neighbors++;
			}
			if (grid[(x - 1) + (y + 1) * GRID_WIDTH] == 1)
			{
				neighbors++;
			}
			if (grid[x + (y + 1) * GRID_WIDTH] == 1)
			{
				neighbors++;
			}
			if (grid[(x + 1) + (y + 1) * GRID_WIDTH] == 1)
			{
				neighbors++;
			}

			if (grid[x + y * GRID_WIDTH] == 1) // FOR A LIVING CELL
			{
				if (neighbors < 2 || neighbors > 3)
				{
					gridNext[x + y * GRID_WIDTH] = 0;
				}
				if (neighbors == 2 || neighbors == 3)
				{
					gridNext[x + y * GRID_WIDTH] = 1;
				}
			}

			if (grid[x + y * GRID_WIDTH] == 0) // FOR A DEAD CELL
			{
				if (neighbors == 3)
				{
					gridNext[x + y * GRID_WIDTH] = 1;
				}
			}
		}

		

		enum class STATES
		{
			PAUSE = 0,
			SIMULATE
		}; STATES state = STATES::PAUSE;

		int howFast = 100;
		int howFastIncrease = 50;
		int howManyAlive = 0;
		int generation = 0;


	private:

		int grid[cellNumber]{};
		int gridNext[cellNumber]{};

		GameDataRef _data;


		sf::Sprite _background;
		sf::Sprite _quitButton;

		sf::Sprite _plusButton;
		sf::Sprite _minusButton;
		sf::Sprite _pauseButton;
		sf::Sprite _startButton;
		sf::Sprite _cleanButton;
		sf::Sprite _randomizeButton;

		sf::RectangleShape _cell;

		sf::RectangleShape _bordersW;
		sf::RectangleShape _bordersH;

		sf::Event event;
	};
}


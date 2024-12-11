#pragma once

#include "InputHandler.h"
#include "Game/Board.h"
#include "Game/Hand.h"

namespace gb
{
	class WaterMelonGame : public Game2D
	{
	public:
		WaterMelonGame()
			:Game2D("WaterMelonGame", 1024, 768, false)
		{
			inputhandler.key_command_map[GLFW_KEY_RIGHT] = new RightCommand;
			inputhandler.key_command_map[GLFW_KEY_LEFT] = new LeftCommand;
		}
		~WaterMelonGame()
		{}
		
		void Update() override
		{
			board.DrawBoard(Colors::blue, 10.f);
			inputhandler.handleInput(*this, hand, GetTimeStep());

			hand.Update(GetTimeStep());
			hand.Draw();

			if (IsKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				hand.ShootFruit();
			}
		}

	private:
		Hand hand;
		InputHandler inputhandler;
		Board board;
	};
}
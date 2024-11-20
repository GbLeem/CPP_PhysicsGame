#pragma once

#include <map>
#include "Command.h"
#include "Game2D.h"

namespace gb
{
	class InputHandler
	{
	public:
		std::map<int, Command*> key_command_map;

		InputHandler()
		{}

		void handleInput(Game2D& game, Actor& actor, float dt)
		{			
			for (auto& m : key_command_map)
			{
				if (game.IsKeyPressed(m.first))
				{					
					m.second->Execute(actor, dt);
				}
			}
		}
	};
}
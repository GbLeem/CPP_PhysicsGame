#pragma once

#include "Game/Water.h"

namespace gb
{
	class WaterExample : public Game2D
	{
	public:
		WaterExample()
			:Game2D("WaterExample", 1024, 768, false)
		{
		}

		void Update() override
		{
			waterball.Update(GetTimeStep());
			waterball.Draw();
		}
	private:
		WaterBall waterball;
	};
}
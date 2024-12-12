#pragma once

#include "Game/Water.h"
#include "Game/WaterTest.h"

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
			waterball.Update();
			waterball.Draw();
		}
	private:
		WaterBall waterball;
	};
}
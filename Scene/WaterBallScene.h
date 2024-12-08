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
			for (auto& w : waterball)
			{
				w.Update();
				w.Draw();
			}
		}
	private:
		std::vector<WaterBall> waterball;

	};
}
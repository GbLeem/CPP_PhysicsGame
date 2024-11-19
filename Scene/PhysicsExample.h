#pragma once

#include "../Game/RigidCircle.h"

namespace gb
{
	class PhysicsExample : public Game2D
	{
	public:
		PhysicsExample()
			:Game2D("window", 1024, 768, false)
		{
			rb0 = RigidCircle(vec2(-0.8f, 0.3f), vec2(10.f, 0.f));

		}

		~PhysicsExample()
		{}
		

		void DrawWall()
		{
			SetLineWidth(5.f);
			DrawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
			DrawLine(Colors::blue, { 1.0f, -1.0f }, Colors::blue, { 1.0f, 1.0f });
			DrawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
		}

		void Update() override
		{
			const float dt = GetTimeStep() * 0.4f;
			
			rb0.Update(dt);
			rb0.Draw();
			DrawWall();
		}

	public:
		RigidCircle rb0;
	};
}
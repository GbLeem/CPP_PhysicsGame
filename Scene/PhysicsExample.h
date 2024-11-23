#pragma once

#include "Actor.h"
#include "InputHandler.h"
#include "../Game/RigidCircle.h"

#include <vector>

namespace gb
{
	class MyBall : public Actor
	{
	public:		
		~MyBall()
		{
			delete myBall;
		}
		void MoveUp(float dt) override
		{
			//
		}
		void MoveDown(float dt) override
		{
			//
		}
		void MoveLeft(float dt) override
		{
			myBall->SetXPos(-0.5f * dt);
		}
		void MoveRight(float dt) override
		{
			myBall->SetXPos(0.5f * dt);
		}
		void Jump(float dt) override
		{
			myBall->SetYPos(0.005f);
		}
		float GetXPos()
		{
			return myBall->GetCenterX();
		}
		float GetYPos()
		{
			return myBall->GetCenterY();
		}
		vec2 GetPos()
		{
			return myBall->GetCenterPos();
		}
		float GetRaius()
		{
			return myBall->GetRadius();
		}
		vec2 GetVelocity()
		{
			return myBall->GetVelocity();
		}
		float GetMass()
		{
			return myBall->GetMass();
		}
		void SetVelocity(vec2 value)
		{
			myBall->SetVelocity(value);
		}
		void Draw()
		{
			myBall->Draw();		
		}

		void Update(float dt)
		{
			myBall->Update(dt);
		}

		
	private:
		vec2 center = vec2(0.f, 0.f);
		RigidCircle* myBall = new RigidCircle(vec2(-0.8f, 0.3f), vec2(0.f, 0.f));
	};


	//game scene
	class PhysicsExample : public Game2D
	{
	public:
		PhysicsExample()
			:Game2D("window", 1024, 768, false)
		{			
			inputhandler.key_command_map[GLFW_KEY_UP] = new UpCommand;
			inputhandler.key_command_map[GLFW_KEY_DOWN] = new DownCommand;
			inputhandler.key_command_map[GLFW_KEY_LEFT] = new LeftCommand;
			inputhandler.key_command_map[GLFW_KEY_RIGHT] = new RightCommand;
			inputhandler.key_command_map[GLFW_KEY_SPACE] = new JumpCommand;

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
			const float dt = GetTimeStep() * 0.2f;
			
			inputhandler.handleInput(*this, myball, GetTimeStep());

			myball.Update(dt);			
			obstacle->Update(dt);

			const float distance = (myball.GetPos() - obstacle->GetCenterPos()).GetMagnitude();
			
			/*printf("my ball : %f, %f\n", myball.GetPos().x, myball.GetPos().y);
			printf("obstacle : %f, %f\n", obstacle->GetCenterPos().x, obstacle->GetCenterPos().y);*/
			
			//printf("my ball : %d\n", myball.GetRaius());
			//printf("obstacle : %d\n", obstacle->GetRadius());

			if (distance <= myball.GetRaius() + obstacle->GetRadius())
			{
				//printf("collision\n");

				const auto vel = myball.GetVelocity() - obstacle->GetVelocity();
				const auto normal = -(obstacle->GetCenterPos() - myball.GetPos()) /
					(obstacle->GetCenterPos() - myball.GetPos()).GetMagnitude();

				if (vel.DotProduct(normal) < 0.0001f)
				{
					const auto impulse = normal * -(1.0f + 0.5f) *
						vel.DotProduct(normal) / ((1.f) / myball.GetMass() + (1.f) / obstacle->GetMass());

					myball.SetVelocity(impulse / myball.GetMass());
					obstacle->SetVelocity(-impulse / obstacle->GetMass());
				}
			}

			DrawWall();
			myball.Draw();
			obstacle->Draw();
		}

	public:
		MyBall myball;
		//std::vector<RigidCircle*> obstacles;
		RigidCircle* obstacle = new RigidCircle(vec2(0.0f, 0.3f), vec2(-5.0f, 0.0f), Colors::black, 0.2f, 5.f);
		InputHandler inputhandler;
	};
}
#pragma once

#include "Actor.h"
#include "InputHandler.h"
#include "../Game/RigidCircle.h"

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

			myball.Draw();
			myball.Update(dt);			
			DrawWall();
		}

	public:
		MyBall myball;
		InputHandler inputhandler;
	};
}
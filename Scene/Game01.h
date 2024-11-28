#pragma once

#include "Actor.h"
#include "InputHandler.h"
#include "Game/Board.h"
//#include <vector>

namespace gb
{
	class Fruit
	{
	public:
		Fruit()
			:pos(0.f, 0.6f)
			, vel(0.f, 0.f)
			, color(Colors::blue)
			, radius(0.1f)
			, mass(0.1f)
			, bMove(true)
			, gravity(0.f, 0.f)
		{}

		void DrawFruit(RGB _color, float _radius)
		{
			BeginTransformation();
			{
				Translate(pos);
				DrawFilledCircle(_color, _radius);
			}
			EndTransformation();
		}

		//setter
		void SetXPos(float value)
		{
			pos.x += value;
		}
		void SetYVelocity()
		{
			vel.y = -0.1f;
			gravity = vec2(0.f, -0.98f);
		}
		void SetVelocity(vec2 value)
		{
			vel.x += value.x;
			vel.y += value.y;
		}
		//getter
		float GetXPos()
		{
			return pos.x;
		}
		vec2 GetPos()
		{
			return pos;
		}
		float GetRadius()
		{
			return radius;
		}
		bool GetMovingState()
		{
			return bMove;
		}
		vec2 GetVelocity()
		{
			return vel;
		}
		float GetMass()
		{
			return mass;
		}
		vec2 GetCurrentFruitVelocity()
		{
			return vel;
		}

		void Collide(Fruit* other)
		{
			const float distance = (other->GetPos(), GetPos()).GetMagnitude();

			if (distance <= other->GetRadius() + GetRadius())
			{
				const auto vel = GetVelocity() - other->GetVelocity();
				const auto normal = -(other->GetPos() - GetPos()) / (other->GetPos() - GetPos()).GetMagnitude();

				if (vel.DotProduct(normal) < 0.f)
				{
					const auto impulse = normal * (-1.0 + 0.5f) * vel.DotProduct(normal) / ((1.f) / GetMass() + (1.f) / other->GetMass());

					SetVelocity(impulse / GetMass());
					other->SetVelocity(-impulse / other->GetMass());
				}
			}
		}

		void Update(const float& dt)
		{			
			static const float coef_res = 0.7f; // coefficient of restitution

			//움직이게 하기
			vel += gravity * dt;
			pos += vel * dt;

			if (vel.y < 0.f)
			{
				bMove = false;
			}
			if (vel.y == 0.f)
			{
				bMove = true;
			}

			//벽에 닿으면 튕기기
			
			//right
			if (0.8f - pos.x <= radius)
			{
				pos.x = 0.8f - radius;

				if (vel.x >= 0.f)
					vel.x *= -1.f * coef_res;
			}

			if (pos.x <= -1.2f + radius) // left wall
			{
				pos.x = -1.2f + radius;

				if (vel.x <= 0.0f)
					vel.x *= -1.0f * coef_res;
			}

			if (pos.y <= -1.0f + radius) // ground
			{
				pos.y = -1.0f + radius;

				if (vel.y <= 0.0f)
					vel.y *= -1.0f * coef_res;
			}				
		}

	private:
		vec2 pos;
		vec2 vel;
		RGB color;
		float radius;
		float mass;
		bool bMove;
		vec2 gravity;
	};

	class Hand : public Actor
	{
	public:	
		~Hand()
		{
			delete currentFruit;
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
			if(currentFruit->GetXPos() > -1.2f && currentFruit->GetMovingState())
				currentFruit->SetXPos(-0.5f * dt);
		}
		void MoveRight(float dt) override
		{
			if (currentFruit->GetXPos() < 0.8f && currentFruit->GetMovingState())
				currentFruit->SetXPos(0.5f * dt);
		}
		void Jump(float dt) override
		{
			//
		}
		void Action(float dt) override
		{
			currentFruit->SetYVelocity();
			fruits.push_back(currentFruit);		
		}



		RGB GetRandomColor()
		{
			return Colors::blue;
		}

		float GetRandomFloat()
		{
			return 0.1f;
		}


		//draw current fruits
		void Draw()
		{
			//currentFruit->DrawFruit(GetRandomColor(), GetRandomFloat());
			for (const auto& f : fruits)
			{
				f->DrawFruit(GetRandomColor(), GetRandomFloat());
			}
		}

		void Update(const float& dt)
		{
			currentFruit->Update(dt);

			/*if (currentFruit->GetVelocity().x == 0.f && currentFruit->GetVelocity().y == 0.f)
			{				
				currentFruit = nullptr;
				currentFruit = new Fruit();
			}*/
			for (auto f : fruits)
			{
				currentFruit->Collide(f);
			}
		}

	private:
		vec2 handPos = vec2(0.f, 0.6f);
		Fruit* currentFruit = new Fruit(); // TODO : 이걸 생성
		std::vector<Fruit*> fruits;
	};

	


	class WaterMelonGame : public Game2D
	{
	public:
		WaterMelonGame()
			:Game2D("WaterMelonGame", 1024, 768, false)
		{
			inputhandler.key_command_map[GLFW_KEY_RIGHT] = new RightCommand;
			inputhandler.key_command_map[GLFW_KEY_LEFT] = new LeftCommand;
			inputhandler.key_command_map[GLFW_KEY_SPACE] = new ActionCommand;
		}
		~WaterMelonGame()
		{}
		

		void Update() override
		{
			board.DrawBoard(Colors::blue, 10.f);
			inputhandler.handleInput(*this, hand, GetTimeStep());

			hand.Draw();
			hand.Update(GetTimeStep());
		}

	private:
		Hand hand;
		InputHandler inputhandler;
		Board board;
	};
}
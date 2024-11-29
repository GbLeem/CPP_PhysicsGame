#pragma once

#include "Actor.h"
#include "Game/Board.h"
#include "InputHandler.h"
#include "RandomNumberGernerator.h"

#include <queue>
#include <stack>

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

		Fruit(RGB _color, float _radius)
			:pos(0.f, 0.6f)
			,vel(0.f,0.f)
			,color(_color)
			,radius(_radius)
			,mass(0.5f)
			,bMove(true)
			,gravity(0.f,0.f)
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
		bool GetMovingState() //키보드 좌우 입력 불가능하게 막는 것
		{
			return bMove;
		}
		bool GetOnGround()
		{
			return bOnGround;
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
		RGB GetColor()
		{
			return color;
		}

		void Collide(Fruit* other)
		{
			const float distance = (GetPos() - other->GetPos()).GetMagnitude();

			if (distance <= other->GetRadius() + GetRadius())
			{
				const auto vel = GetVelocity() - other->GetVelocity();
				const auto normal = -(other->GetPos() - GetPos()) / (other->GetPos() - GetPos()).GetMagnitude();

				if (vel.DotProduct(normal) < 0.f)
				{
					const auto impulse = normal * -(1.0 + 0.5f) * vel.DotProduct(normal) / ((1.f) / GetMass() + (1.f) / other->GetMass());

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
			if (vel.y == 0.f && bOnGround)
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

			if (pos.y == -1.0f + radius)
			{
				bOnGround = true;
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
		bool bOnGround = false;
	};

	class Hand : public Actor
	{
	public:	
		Hand()
		{
			if (nextFruits.empty())
			{
				Fruit* currentFruit = new Fruit;
				nextFruits.push(currentFruit);
			}

			RandomColorContainer.push_back({ Colors::blue, 0.1f });
			RandomColorContainer.push_back({ Colors::red, 0.12f });
			RandomColorContainer.push_back({ Colors::yellow, 0.14f });
			RandomColorContainer.push_back({ Colors::green, 0.16f });
		}
		~Hand()
		{
			//delete currentFruit;
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
			if (!nextFruits.empty())
			{
				if(nextFruits.front()->GetXPos() > -1.2f && nextFruits.front()->GetMovingState())
					nextFruits.front()->SetXPos(-0.5f * dt);
			}
		}
		void MoveRight(float dt) override
		{
			if (!nextFruits.empty())
			{
				if (nextFruits.front()->GetXPos() < 0.8f && nextFruits.front()->GetMovingState())
					nextFruits.front()->SetXPos(0.5f * dt);
			}
		}
		void Jump(float dt) override
		{
			//
		}

		void Action(float dt) override
		{			
			//
		}

		void ShootFruit()
		{
			if (!nextFruits.empty())
			{
				groundFruits.push_back(nextFruits.front());
				groundFruits.back()->SetYVelocity();			
				nextFruits.pop();
			}
		}

		int GetRandomInteger()
		{
			return randomNumberGenerator.getInt(0, RandomColorContainer.size() - 1);
		}	

		//draw current fruits
		void Draw()
		{			
			if (!nextFruits.empty())
				nextFruits.front()->DrawFruit(nextFruits.front()->GetColor(), nextFruits.front()->GetRadius());

			for (const auto& f : groundFruits)
			{
				f->DrawFruit(f->GetColor(), f->GetRadius());
			}
		}

		void Update(const float& dt)
		{
			//시작 처리
			if (nextFruits.empty())
			{
				int randomInt = GetRandomInteger();
				Fruit* currentFruit = new Fruit(RandomColorContainer[randomInt].first, RandomColorContainer[randomInt].second);
				nextFruits.push(currentFruit);
			}

			if (!groundFruits.empty())
			{
				for (const auto& f : groundFruits)
				{
					f->Update(dt);
					for (const auto& other : groundFruits)
					{
						f->Collide(other);
					}
				}
			}			
		}

	private:
		vec2 handPos = vec2(0.f, 0.6f);			
		std::queue<Fruit*> nextFruits;
		std::vector<Fruit*> groundFruits;
		bool bMakeFruit = true;
		std::vector<std::pair<RGB, float>> RandomColorContainer;
		RandomNumberGenerator randomNumberGenerator;
	};

	


	class WaterMelonGame : public Game2D
	{
	public:
		WaterMelonGame()
			:Game2D("WaterMelonGame", 1024, 768, false)
		{
			inputhandler.key_command_map[GLFW_KEY_RIGHT] = new RightCommand;
			inputhandler.key_command_map[GLFW_KEY_LEFT] = new LeftCommand;
			//inputhandler.key_command_map[GLFW_KEY_SPACE] = new ActionCommand;
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
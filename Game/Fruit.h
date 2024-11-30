#pragma once

#include "Game2D.h"
#include "Level.h"
#include "Hand.h"

namespace gb
{
	class Fruit
	{
	public:
		Fruit()
			:pos(0.f, 0.8f)
			, vel(0.f, 0.f)
			, color(Colors::blue)
			, radius(0.1f)
			, mass(0.1f)
			, bMove(true)
			, gravity(0.f, 0.f)
			, level(eFruitLevel::NONE)
		{}

		Fruit(RGB _color, float _radius, eFruitLevel _lvl)
			:pos(0.f, 0.9f)
			, vel(0.f, 0.f)
			, color(_color)
			, radius(_radius)
			, mass(2.f)
			, bMove(true)
			, gravity(0.f, 0.f)
			, level(_lvl)
		{}

		Fruit(vec2 _pos, RGB _color, float _radius, eFruitLevel _lvl)
			:pos(_pos)
			, vel(0.f, 0.f)
			, color(_color)
			, radius(_radius)
			, mass(2.f)
			, bMove(true)
			, gravity(0.f, -0.98f)
			, level(_lvl)
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

		//====setter====
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
		void ReSetFruit(Fruit* other)
		{
			pos = other->GetPos();
			color = other->GetColor();
			radius = other->GetRadius();
		}

		//====getter====
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
		eFruitLevel GetLevel()
		{
			return level;
		}

		void Collide(Fruit* other, std::vector<Fruit*> &groundFruits)
		{
			const float distance = (GetPos() - other->GetPos()).GetMagnitude();

			if (distance <= other->GetRadius() + GetRadius()) //충돌이 된 경우
			{
				if (other->GetLevel() == GetLevel())
				{
					int newLevel = (container.LevelToInt[GetLevel()] + 1) % container.LevelToInt.size();					
					RGB newColor = container.RandomColorContainer[newLevel].first;
					float newRadius = container.RandomColorContainer[newLevel].second;
					eFruitLevel newFruitLevel = container.IntToLevel[newLevel];
					vec2 newPosition = other->GetPos();


					Fruit* newFruit = new Fruit(newPosition, newColor, newRadius, newFruitLevel);
					groundFruits.push_back(newFruit);

					groundFruits.erase(remove(groundFruits.begin(), groundFruits.end(), other), groundFruits.end());
					groundFruits.erase(remove(groundFruits.begin(), groundFruits.end(), this), groundFruits.end());

					delete other;
					delete this;					
				}
				else
				{
					const vec2 vel = GetVelocity() - other->GetVelocity();
					const auto normal = -(other->GetPos() - GetPos()) / (other->GetPos() - GetPos()).GetMagnitude();

					if (vel.DotProduct(normal) < 0.f)
					{
						const auto impulse = normal * -(1.0f) * vel.DotProduct(normal) / ((1.f) / GetMass() + (1.f) / other->GetMass());

						SetVelocity(impulse / GetMass());
						other->SetVelocity(-impulse / other->GetMass());
					}
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
		eFruitLevel level;
		UpgradeContainer container;		
	};
}
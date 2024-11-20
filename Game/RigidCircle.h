#pragma once

#include "Game2D.h"

namespace gb
{
	class RigidCircle
	{
	public:
		RigidCircle()
			: color(Colors::red)
			, radius(0.1f)
			, mass(1.f)
		{}
		
		RigidCircle(vec2 _pos, vec2 _vel)
			: pos(_pos)
			, vel(_vel)
			, color(Colors::red)
			, radius(0.1f)
			, mass(1.f)
		{}

		RigidCircle(const vec2& _pos, const vec2& _vel, const RGB& _color, const float& _radius,
			const float& _mass)
			: pos(_pos)
			, vel(_vel)
			, color(_color)
			, radius(_radius)
			, mass(_mass)
		{}
		
		int GetCenterX()
		{
			return pos.x;
		}
		int GetCenterY()
		{
			return pos.y;
		}
		void SetXPos(float value)
		{
			pos.x += value;
		}

		void SetYPos(float value)
		{
			pos.y += value;
		}

		void Draw()
		{
			BeginTransformation();
			{
				Translate(pos);
				DrawFilledCircle(color, radius);
			}
			EndTransformation();
		}

		void Update(const float & dt)
		{
			static const vec2 gravity = vec2(0.0f, -9.8f);
			static const float coef_res = 0.7f; // coefficient of restitution
			static const float coef_friction = 0.99f; // friction
			
			vel += gravity * dt;
			pos += vel * dt;

			if (1.0f - pos.x <= radius) // right wall
			{
				pos.x = 1.0f - radius;

				if (vel.x >= 0.0f)
					vel.x *= -1.0f * coef_res;
			}

			if (pos.x <= -1.0f + radius) // left wall
			{
				pos.x = -1.0f + radius;

				if (vel.x <= 0.0f)
					vel.x *= -1.0f * coef_res;
			}

			if (pos.y <= -1.0f + radius) // ground
			{
				pos.y = -1.0f + radius;

				if (vel.y <= 0.0f)
					vel.y *= -1.0f * coef_res;

				//vel.x *= coef_friction;
			}
		}

	private:
		vec2 pos;
		vec2 vel;
		RGB color;

		float radius;
		float mass;
	};
}
#pragma once

#include "GeometricObject.h"

namespace gb
{
	class Circle : public GeometricObject
	{
	public:
		Circle(const RGB& _color, const vec2& _pos, const float& _size)
		{
			Init(_color, _pos, _size);
		}

		void Init(const RGB& _color, const vec2& _pos, const float& _size)
		{
			GeometricObject::Init(_color, _pos);
			radius = _size;
		}

		void DrawGeometry() const override
		{
			DrawFilledCircle(color, radius);
		}

	private:
		float radius;
	};
}
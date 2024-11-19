#pragma once

#include "GeometricObject.h"

namespace gb
{
	class Triangle : public GeometricObject
	{
	public:

		Triangle(const RGB& _color, const vec2& _pos, const float& _size)
		{
			Init(_color, _pos, _size);
		}

		void Init(const RGB& _color, const vec2& _pos, const float& _size)
		{
			GeometricObject::Init(_color, _pos);
			size = _size;
		}

		void DrawGeometry() const override
		{
			DrawFilledTriangle(color, size);
		}

	private:
		float size;
	};
}
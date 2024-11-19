#pragma once

#include "GeometricObject.h"

namespace gb
{
	class Box : public GeometricObject
	{
	public:

		Box(const RGB& _color, const vec2& _pos, const float& _width, const float & _height)
		{
			Init(_color, _pos, _width, _height);
		}

		void Init(const RGB& _color, const vec2& _pos, const float& _width, const float& _height)
		{
			GeometricObject::Init(_color, _pos);

			width = _width;
			height = _height;
		}

		void DrawGeometry() const override
		{
			DrawFilledBox(color, width, height);
		}

	private:
		float width;
		float height;
	};
}
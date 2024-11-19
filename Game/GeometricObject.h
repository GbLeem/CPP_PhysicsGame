#pragma once

#include "Game2D.h"

namespace gb
{
	class GeometricObject
	{
	public:
		virtual ~GeometricObject()
		{}

		void Init(const RGB& _color, const vec2& _pos)
		{
			color = _color;
			pos = _pos;
		}

		//pure virtual
		virtual void DrawGeometry() const = 0;

		void Draw()
		{
			BeginTransformation();
			{				
				Translate(pos);
				DrawGeometry();
			}
			EndTransformation();
		}

		//factory pattern
		static GeometricObject* makeTriangle(const RGB& _color, const vec2& _pos, const float& _size);
		static GeometricObject* makeCircle(const RGB& _color, const vec2& _pos, const float& _size);
		static GeometricObject* makeBox(const RGB& _color, const vec2& _pos, const float& _width, const float& _height);


	public:
		vec2 pos;
		RGB color;
	};
}
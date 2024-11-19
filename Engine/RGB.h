#pragma once

#include "Vector3.h"

namespace gb
{
	class RGB : public Vector3<float>
	{
		using BASECOLOR = Vector3<float>;

	public:
		RGB()
		{}

		RGB(const float& fred, const float& fgreen, const float& fblue)
			:BASECOLOR(fred, fgreen, fblue)
		{}

		RGB(const int& ired, const int& igreen, const int& iblue)
			:BASECOLOR(static_cast<float>(ired) / 255.f, static_cast<float>(igreen) / 255.f, static_cast<float>(iblue) / 255.f)
		{}

		RGB(const RGB&rgb)
			:BASECOLOR(rgb.r, rgb.g, rgb.b)
		{}
		~RGB()
		{}
	};
}
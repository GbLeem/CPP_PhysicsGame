#pragma once

#include "Game2D.h"
#include "DrawFunctions.h"
#include "../Game/GeometricObject.h"

#include <memory>
#include <vector>

namespace gb
{
	class Example : public Game2D
	{
	public:
		Example()
			:Game2D("window", 1024, 768, false)
		{
			myObjects.push_back(GeometricObject::makeTriangle(Colors::red, vec2(0.f, 0.f), 0.25f));
			myObjects.push_back(GeometricObject::makeTriangle(Colors::blue, vec2(1.f, 0.f), 0.25f));
			myObjects.push_back(GeometricObject::makeTriangle(Colors::green, vec2(0.f, 1.f), 0.25f));
		}

		~Example()
		{
			for (const auto& obj : myObjects)
				delete obj;
		}

		void Update() override
		{
			for (const auto& obj : myObjects)
				obj->Draw();
		}

	private:
		std::vector<GeometricObject*> myObjects;
	};
}
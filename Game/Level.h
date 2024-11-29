#pragma once

#include <vector>
#include <unordered_map>
#include "RGB.h"

namespace gb
{
	enum class eFruitLevel
	{
		NONE, // 0
		BLUE, // 1
		RED,
		YELLOW,
		GREEN,
		BLACK
	};

	class UpgradeContainer
	{
	public:
		UpgradeContainer()
		{
			//setup color
			RandomColorContainer.push_back({ Colors::blue, 0.1f });
			RandomColorContainer.push_back({ Colors::red, 0.12f });
			RandomColorContainer.push_back({ Colors::yellow, 0.14f });
			RandomColorContainer.push_back({ Colors::green, 0.16f });
			RandomColorContainer.push_back({ Colors::black, 0.18f });

			//setup int to color
			IntToLevel[0] = eFruitLevel::BLUE;
			IntToLevel[1] = eFruitLevel::RED;
			IntToLevel[2] = eFruitLevel::YELLOW;
			IntToLevel[3] = eFruitLevel::GREEN;
			IntToLevel[4] = eFruitLevel::BLACK;

			LevelToInt[eFruitLevel::BLUE] = 0;
			LevelToInt[eFruitLevel::RED] = 1;
			LevelToInt[eFruitLevel::YELLOW] = 2;
			LevelToInt[eFruitLevel::GREEN] = 3;
			LevelToInt[eFruitLevel::BLACK] = 4;

		}

	public:
		std::vector<std::pair<RGB, float>> RandomColorContainer;
		std::unordered_map<int, eFruitLevel> IntToLevel;
		std::unordered_map<eFruitLevel, int> LevelToInt;
	};
}

#pragma once

#include <vector>
#include <unordered_map>
#include "RGB.h"

namespace gb
{
	enum class eFruitLevel
	{
		NONE, // 0
		CHERRY,  // cherry
		MAGENTA, //strawberry
		PURPLE, //grapes
		ORANGE, //orange
		ORANGERED, //persimmon

		RED, //apple
		PEAR, //pear
		PEACH, //peach
		YELLOW, //pineapple
		GREEN, // melon
		BLACK, //water melon
	};

	class UpgradeContainer
	{
	public:
		UpgradeContainer()
			:maxRandomIndex(RandomColorContainer.size() - 6) //11 - 6 = 5
		{
			//setup color
			RandomColorContainer.push_back({ Colors::cherry, 0.1f });
			RandomColorContainer.push_back({ Colors::strawberry, 0.12f });
			RandomColorContainer.push_back({ Colors::purple, 0.14f });
			RandomColorContainer.push_back({ Colors::orange, 0.16f });
			RandomColorContainer.push_back({ Colors::orangered, 0.18f });

			RandomColorContainer.push_back({ Colors::red, 0.21f });
			RandomColorContainer.push_back({ Colors::pear, 0.24f });
			RandomColorContainer.push_back({ Colors::peach, 0.27f });
			RandomColorContainer.push_back({ Colors::yellow, 0.3f });
			RandomColorContainer.push_back({ Colors::green, 0.33f });
			RandomColorContainer.push_back({ Colors::black, 0.36f });

			//setup int to color
			IntToLevel[0] = eFruitLevel::CHERRY;
			IntToLevel[1] = eFruitLevel::MAGENTA;
			IntToLevel[2] = eFruitLevel::PURPLE;
			IntToLevel[3] = eFruitLevel::ORANGE;
			IntToLevel[4] = eFruitLevel::ORANGERED;

			IntToLevel[5] = eFruitLevel::RED;
			IntToLevel[6] = eFruitLevel::PEAR;
			IntToLevel[7] = eFruitLevel::PEACH;
			IntToLevel[8] = eFruitLevel::YELLOW;
			IntToLevel[9] = eFruitLevel::GREEN;
			IntToLevel[10] = eFruitLevel::BLACK;


			LevelToInt[eFruitLevel::CHERRY] = 0;
			LevelToInt[eFruitLevel::MAGENTA] = 1;
			LevelToInt[eFruitLevel::PURPLE] = 2;
			LevelToInt[eFruitLevel::ORANGE] = 3;
			LevelToInt[eFruitLevel::ORANGERED] = 4;

			LevelToInt[eFruitLevel::RED] = 5;
			LevelToInt[eFruitLevel::PEAR] = 6;
			LevelToInt[eFruitLevel::PEACH] = 7;
			LevelToInt[eFruitLevel::YELLOW] = 8;
			LevelToInt[eFruitLevel::GREEN] = 9;
			LevelToInt[eFruitLevel::BLACK] = 10;			
		}

	public:
		std::vector<std::pair<RGB, float>> RandomColorContainer;
		std::unordered_map<int, eFruitLevel> IntToLevel;
		std::unordered_map<eFruitLevel, int> LevelToInt;
		int maxRandomIndex;
	};
}

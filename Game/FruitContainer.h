#pragma once

#include "Game2D.h"
#include "Fruit.h"

#include <queue>
#include <vector>

namespace gb
{
	class FruitContainer
	{
	public:
		static FruitContainer* getInstance();

	private:
		FruitContainer() = default;

		FruitContainer(const FruitContainer&) = delete;

	private:
		static FruitContainer* instance;

	public:
		std::queue<Fruit*> nextFruits;
		std::vector<Fruit*> groundFruits;
	};
}
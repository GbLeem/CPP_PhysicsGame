#include "FruitContainer.h"

namespace gb
{
	FruitContainer* FruitContainer::instance = nullptr;

	FruitContainer* FruitContainer::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new FruitContainer();
		}

		return instance;
	}
}
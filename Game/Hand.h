#pragma once

#include "Actor.h"
#include "Fruit.h"
#include "FruitContainer.h"
#include "RandomNumberGernerator.h"
#include "Level.h";

#include <queue>

namespace gb
{
	class Hand : public Actor
	{
	public:
		Hand()
		{
			auto& fruitContainer = *FruitContainer::getInstance();

			if (fruitContainer.nextFruits.empty())
			{
				int randomInt = GetRandomInteger();
				Fruit* currentFruit = new Fruit(container.RandomColorContainer[randomInt].first, container.RandomColorContainer[randomInt].second, container.IntToLevel[randomInt]);
				fruitContainer.nextFruits.push(currentFruit);
			}			
		}
		~Hand()
		{
			//delete currentFruit;
		}
		void MoveUp(float dt) override
		{
			//
		}
		void MoveDown(float dt) override
		{
			//
		}
		void MoveLeft(float dt) override
		{
			auto& fruitContainer = *FruitContainer::getInstance();
			if (!fruitContainer.nextFruits.empty())
			{
				if (fruitContainer.nextFruits.front()->GetXPos() > -1.2f && fruitContainer.nextFruits.front()->GetMovingState())
					fruitContainer.nextFruits.front()->SetXPos(-0.5f * dt);
			}
		}
		void MoveRight(float dt) override
		{
			auto& fruitContainer = *FruitContainer::getInstance();
			if (!fruitContainer.nextFruits.empty())
			{
				if (fruitContainer.nextFruits.front()->GetXPos() < 0.8f && fruitContainer.nextFruits.front()->GetMovingState())
					fruitContainer.nextFruits.front()->SetXPos(0.5f * dt);
			}
		}
		void Jump(float dt) override
		{
			//
		}

		void Action(float dt) override
		{
			//
		}

		void ShootFruit()
		{
			auto& fruitContainer = *FruitContainer::getInstance();
			if (!fruitContainer.nextFruits.empty())
			{
				fruitContainer.groundFruits.push_back(fruitContainer.nextFruits.front());
				fruitContainer.groundFruits.back()->SetYVelocity();
				fruitContainer.nextFruits.pop();
			}
		}

		

		int GetRandomInteger()
		{
			return randomNumberGenerator.getInt(0, container.RandomColorContainer.size() - 1);
		}

		//draw current fruits
		void Draw()
		{
			auto& fruitContainer = *FruitContainer::getInstance();
			if (!fruitContainer.nextFruits.empty())
				fruitContainer.nextFruits.front()->DrawFruit(fruitContainer.nextFruits.front()->GetColor(), fruitContainer.nextFruits.front()->GetRadius());

			for (const auto& f : fruitContainer.groundFruits)
			{
				f->DrawFruit(f->GetColor(), f->GetRadius());
			}
		}

		void Update(const float& dt)
		{
			auto& fruitContainer = *FruitContainer::getInstance();
			//시작 처리
			if (fruitContainer.nextFruits.empty())
			{
				int randomInt = GetRandomInteger();
				Fruit* currentFruit = new Fruit(container.RandomColorContainer[randomInt].first, container.RandomColorContainer[randomInt].second, container.IntToLevel[randomInt]);
				fruitContainer.nextFruits.push(currentFruit);
			}

			if (!fruitContainer.groundFruits.empty())
			{
				for (const auto& f : fruitContainer.groundFruits)
				{
					f->Update(dt);

					for (auto& other : fruitContainer.groundFruits)
					{
						if (f != other)
						{
							f->Collide(other);
						}
					}
				}
			}
		}

	private:

		UpgradeContainer container;
		RandomNumberGenerator randomNumberGenerator;
	};
}
#pragma once

#include "Actor.h"
#include "Fruit.h"
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
			if (nextFruits.empty())
			{
				int randomInt = GetRandomInteger();
				Fruit* currentFruit = new Fruit(container.RandomColorContainer[randomInt].first, container.RandomColorContainer[randomInt].second, container.IntToLevel[randomInt]);
				nextFruits.push(currentFruit);
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
			if (!nextFruits.empty())
			{
				if (nextFruits.front()->GetXPos() > -1.2f && nextFruits.front()->GetMovingState())
					nextFruits.front()->SetXPos(-0.5f * dt);
			}
		}
		void MoveRight(float dt) override
		{			
			if (!nextFruits.empty())
			{
				if (nextFruits.front()->GetXPos() < 0.8f && nextFruits.front()->GetMovingState())
					nextFruits.front()->SetXPos(0.5f * dt);
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
			if (!nextFruits.empty())
			{
				groundFruits.push_back(nextFruits.front());
				groundFruits.back()->SetYVelocity();
				nextFruits.pop();
			}
		}

		

		int GetRandomInteger()
		{
			return randomNumberGenerator.getInt(0, container.RandomColorContainer.size() - 1);
		}

		//draw current fruits
		void Draw()
		{
			if (!nextFruits.empty())
				nextFruits.front()->DrawFruit(nextFruits.front()->GetColor(), nextFruits.front()->GetRadius());

			for (const auto& f : groundFruits)
			{
				f->DrawFruit(f->GetColor(), f->GetRadius());
			}
		}

		void Update(const float& dt)
		{			
			//시작 처리
			if (nextFruits.empty())
			{
				int randomInt = GetRandomInteger();
				Fruit* currentFruit = new Fruit(container.RandomColorContainer[randomInt].first, container.RandomColorContainer[randomInt].second, container.IntToLevel[randomInt]);
				nextFruits.push(currentFruit);
			}

			if (!groundFruits.empty())
			{
				for (const auto& f : groundFruits)
				{
					f->Update(dt);

					for (auto& other : groundFruits)
					{
						if (f != other)
						{
							f->Collide(other, groundFruits);
						}
					}
				}
			}
		}

	public:
		std::queue<Fruit*> nextFruits;
		std::vector<Fruit*> groundFruits;
	private:
		UpgradeContainer container;
		RandomNumberGenerator randomNumberGenerator;
	};
}
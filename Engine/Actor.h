#pragma once

namespace gb
{
	class Actor
	{
	public:
		virtual void MoveUp(float dt) = 0;
		virtual void MoveDown(float dt) = 0;
		virtual void MoveLeft(float dt) = 0;
		virtual void MoveRight(float dt) = 0;
		virtual void Jump(float dt) = 0;
	};	
}
#pragma once

#include "Actor.h"

namespace gb
{
	class Command
	{
	public:
		virtual ~Command()
		{}

		virtual void Execute(Actor& actor, float dt) = 0;
	};

	class UpCommand : public Command
	{
	public:
		virtual void Execute(Actor& actor, float dt)
		{
			actor.MoveUp(dt);
		}
	};

	class DownCommand : public Command
	{
	public:
		virtual void Execute(Actor& actor, float dt)
		{
			actor.MoveDown(dt);
		}
	};

	class LeftCommand : public Command
	{
	public:
		virtual void Execute(Actor& actor, float dt)
		{
			actor.MoveLeft(dt);
		}
	};

	class RightCommand : public Command
	{
	public:
		virtual void Execute(Actor& actor, float dt)
		{
			actor.MoveRight(dt);
		}
	};

	class JumpCommand : public Command
	{
	public:
		virtual void Execute(Actor& actor, float dt)
		{
			actor.Jump(dt);
		}
	};

	class ActionCommand : public Command
	{
	public:
		virtual void Execute(Actor& actor, float dt)
		{
			actor.Action(dt);
		}
	};
}
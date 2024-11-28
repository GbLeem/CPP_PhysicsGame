#pragma once

#include "Game2D.h"

namespace gb
{
	class Board
	{
	public:
		void DrawBoard(RGB _color, float lineWidth)
		{
			SetLineWidth(lineWidth);
			DrawLine(_color, bottomleft, _color, bottomright); //bottom
			DrawLine(_color, bottomright, _color, topright); //right
			DrawLine(_color, bottomleft, _color, topleft); //left
		}
		void DrawUI()
		{
			//TODO
		}
	private:
		vec2 topleft = { -1.2f, 0.6f };
		vec2 topright = { 0.8f, 0.6f };
		vec2 bottomleft = { -1.2f, -1.f };
		vec2 bottomright = { 0.8f, -1.f };

	};
}
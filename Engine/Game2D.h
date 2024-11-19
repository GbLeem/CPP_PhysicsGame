#pragma once

#include "RGB.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Colors.h"
#include "Timer.h"
#include "DrawFunctions.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>         // std::this_thread::sleep_for
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace gb
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	class Game2D
	{
	public:
		Game2D()
		{}

		Game2D(const std::string& _title, const int& _width, const int& _height,
			const bool& use_full_screen = false, const int& display_ix = 0);

		~Game2D();

		Game2D& Init(const std::string& _title, const int& _width, const int& _height,
			const bool& use_full_screen = false, const int& display_ix = 0);

		void ReportErrorAndExit(const std::string& function_name, const std::string& message);

		bool IsKeyPressed(const int& key);
		bool IsKeyReleased(const int& key);
		bool IsKeyPressedAndReleased(const int& key);

		bool IsMouseButtonPressed(const int& mbtn);
		bool IsMouseButtonReleased(const int& mbtn);
		bool IsMouseButtonPressedAndReleased(const int& mbtn);

		vec2 GetCursorPos(const bool& screen_coordinates = true);

		float GetTimeStep();

		void DrawGrid();

		void Run();

		virtual void Update()
		{
			// draw
			// play sould
			// physics update
			// etc.
		}

	private:
		int width = 640;
		int height = 480;

		GLFWwindow* glfw_window = nullptr;

		Timer timer;

		float spf = 1.0f / 60.0f;		 // second(s) per frame

		// control options
		std::map<int, bool> key_status;  // key_id, is_pressed
		std::map<int, bool> mbtn_status; // mouse_button_id, is_pressed
		bool draw_grid = false;
	};
}
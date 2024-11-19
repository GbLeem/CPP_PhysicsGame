#pragma once

#include "RGB.h"
#include "Vector2.h"
#include "Vector3.h"
#include <GL/glew.h>

namespace gb
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	float GetRadian(const float& degree);

	// Various primitives
	void DrawPoint(const RGB& color, const vec2& position, const float& size); // use drawFilledCircle instead
	void DrawLine(const RGB& color0, const vec2& position0, const vec3& color1, const vec2& position1);
		 
	void DrawWiredBox(const RGB& color, const float& width, const float& height);
	void DrawWiredTriangle(const RGB& color, const float& edge_length);
	void DrawWiredTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2);
	void DrawWiredSquare(const RGB& color, const float& edge_length);
	void DrawWiredRegularConvexPolygon(const RGB& color, const float& radius, const float& start_theta = 0.0f, const int& num_segments = 100);
	void DrawWiredCircle(const RGB& color, const float& radius);
	void DrawWiredPentagon(const RGB& color, const float& radius);
		 
	void DrawFilledBox(const RGB& color, const float& width, const float& height);
	void DrawFilledRegularConvexPolygon(const RGB& color, const float& radius, const float& start_theta = 0.0f, const int& num_segments = 100);
	void DrawFilledCircle(const RGB& color, const float& radius);
	void DrawFilledTriangle(const RGB& color, const float& edge_length);
	void DrawFilledTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2);
	void DrawFilledSquare(const RGB& color, const float& edge_length);
	void DrawFilledPentagon(const RGB& color, const float& radius);
	void DrawFilledStar(const RGB& color, const float& outer_radius, const float& inner_radius);

	void DrawGrid(const RGB& color, const float& dx);

	// Affine transformations
	void BeginTransformation();
	void EndTransformation();
	void Translate(const vec2& dx);
	void Translate(const float& pos_x, const float& pos_y);
	void Rotate(const float& degree);
	void Scale(const float& scale_x, const float& scale_y);

	// Other options
	void SetLineWidth(const int& width);
}

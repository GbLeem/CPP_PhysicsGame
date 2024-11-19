#include "DrawFunctions.h"
#include <math.h>
#include <vector>

namespace gb
{
	float GetRadian(const float& degree) // degree to radian
	{
		return degree / 180.0f * 3.141592f;
	}

	void DrawLine(const RGB& color0, const vec2& position0, const vec3& color1, const vec2& position1)
	{
		glBegin(GL_LINES);
		{
			glColor3fv(&color0[0]);
			glVertex2fv(&position0[0]);
			glColor3fv(&color1[0]);
			glVertex2fv(&position1[0]);
		}
		glEnd();
	}

	void BeginTransformation()
	{
		glPushMatrix();
	}

	void EndTransformation()
	{
		glPopMatrix();
	}

	void Translate(const float& pos_x, const float& pos_y)
	{
		glTranslatef(pos_x, pos_y, 0.0);
	}

	void Translate(const vec2& dx)
	{
		glTranslatef(dx.x, dx.y, 0.0);
	}

	void Rotate(const float& degree)
	{
		glRotatef(degree, 0.0, 0.0, 1.0);
	}

	void Scale(const float& scale_x, const float& scale_y)
	{
		glScalef(scale_x, scale_y, 1.0);
	}

	void DrawPoint(const RGB& color, const vec2& position, const float& size)
	{
		glColor3fv(color.data);
		glPointSize(size);
		glBegin(GL_POINTS);
		glVertex2fv(position.data);
		glEnd();
	}

	void DrawWiredTriangle(const RGB& color, const float& edge_length)
	{
		DrawWiredRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.0f), 90.0f, 3);
	}

	void DrawWiredTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2)
	{
		glColor3fv(color.data);
		glBegin(GL_LINE_LOOP);
		glVertex2fv(v0.data);
		glVertex2fv(v1.data);
		glVertex2fv(v2.data);
		glEnd();
	}

	void DrawFilledTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2)
	{
		glColor3fv(color.data);
		glBegin(GL_TRIANGLES);
		glVertex2fv(v0.data);
		glVertex2fv(v1.data);
		glVertex2fv(v2.data);
		glEnd();
	}

	void DrawWiredSquare(const RGB& color, const float& edge_length)
	{
		DrawWiredRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.0f), 45.0f, 4);
	}

	void DrawFilledSquare(const RGB& color, const float& edge_length)
	{
		DrawFilledRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.f), 45.0f, 4);
	}

	void DrawFilledBox(const RGB& color, const float& width, const float& height)
	{
		const vec2 left_bottom(-0.5f * width, -0.5f * height);

		glColor3fv(&color[0]);
		glBegin(GL_QUADS);
		{
			glVertex2f(left_bottom.x, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y + height);
			glVertex2f(left_bottom.x, left_bottom.y + height);
		}
		glEnd();
	}

	void DrawWiredBox(const RGB& color, const float& width, const float& height)
	{
		const vec2 left_bottom(-0.5f * width, -0.5f * height);

		glColor3fv(&color[0]);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(left_bottom.x, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y + height);
			glVertex2f(left_bottom.x, left_bottom.y + height);
		}
		glEnd();
	}

	void DrawFilledRegularConvexPolygon(const RGB& color, const float& radius, const float& theta_start, const int& num_segments)
	{
		const float d_theta = 3.141592f * 2.0f / static_cast<float>(num_segments);

		glColor3fv(&color[0]);

		glBegin(GL_TRIANGLE_FAN);
		{
			float theta = GetRadian(theta_start);
			for (int i = 0; i < num_segments; ++i)
			{
				glVertex2f(radius * cosf(theta), radius * sinf(theta));

				theta += d_theta;
			}
		}
		glEnd();
	}

	void DrawFilledCircle(const RGB& color, const float& radius)
	{
		DrawFilledRegularConvexPolygon(color, radius - 1e-4f, 0.0f, 30);
		DrawWiredRegularConvexPolygon(color, radius, 0.0f, 30); // draw smooth boundary
	}

	void DrawFilledTriangle(const RGB& color, const float& edge_length)
	{
		DrawFilledRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.0f), 90.0f, 3);
	}

	void DrawGrid(const RGB& color, const float& dx)
	{
		const float maxl = 2.0f;
		const float dy = dx;

		// vertical
		for (float x = 0.0f; x < maxl; x += dx)
			DrawLine(color, vec2(x, -maxl), color, vec2(x, +maxl));

		for (float x = -dx; x > -maxl; x -= dx)
			DrawLine(color, vec2(x, -maxl), color, vec2(x, +maxl));

		// horizontal
		for (float y = 0.0f; y < maxl; y += dy)
			DrawLine(color, vec2(-maxl, y), color, vec2(maxl, y));

		for (float y = -dy; y > -maxl; y -= dy)
			DrawLine(color, vec2(-maxl, y), color, vec2(maxl, y));

	}

	void SetLineWidth(const int& width)
	{
		glLineWidth(static_cast<float>(width));
	}

	void DrawWiredRegularConvexPolygon(const RGB& color, const float& radius, const float& start_theta, const int& num_segments)
	{
		const float d_theta = 3.141592f * 2.0f / (float)num_segments;

		glColor3fv(&color[0]);

		glBegin(GL_LINE_LOOP);
		{
			float theta = GetRadian(start_theta);
			for (int i = 0; i < num_segments; ++i)
			{
				glVertex2f(radius * cosf(theta), radius * sinf(theta));

				theta += d_theta;
			}
		}
		glEnd();
	}

	void DrawWiredCircle(const RGB& color, const float& radius)
	{
		DrawWiredRegularConvexPolygon(color, radius, 0.0f, 30);
	}

	void DrawWiredPentagon(const RGB& color, const float& radius)
	{
		DrawWiredRegularConvexPolygon(color, radius, 90.0f, 5);
	}

	void DrawFilledPentagon(const RGB& color, const float& radius)
	{
		DrawFilledRegularConvexPolygon(color, radius, 90.0f, 5);
		DrawWiredPentagon(color, radius);// draw smooth boundary
	}

	std::vector<vec2> MakeRegularConvexPolygon(const float& radius, const float& theta_start, const int& num_segments)
	{
		std::vector<vec2> vertices;
		vertices.resize(num_segments);

		const float d_theta = 3.141592f * 2.0f / static_cast<float>(num_segments);

		float theta = GetRadian(theta_start);
		for (int i = 0; i < num_segments; ++i)
		{
			vertices[i] = vec2{ radius * cos(theta), radius * sin(theta) };
			theta += d_theta;
		}

		return vertices;
	}

	void DrawFilledStar(const RGB& color, const float& outer_radius, const float& inner_radius)
	{
		const int num_segments = 5;

		//Note: not optimized
		const auto outer_vertices = MakeRegularConvexPolygon(outer_radius, 90.0f, num_segments);
		const auto inner_vertices = MakeRegularConvexPolygon(inner_radius, 90.0f - 360.0f * 0.5f / num_segments, num_segments);

		glColor3fv(&color[0]);

		glBegin(GL_TRIANGLES);

		for (int i = 0; i < num_segments; ++i)
		{
			glVertex2fv(outer_vertices[i].data);
			glVertex2fv(inner_vertices[i].data);
			glVertex2fv(inner_vertices[(i + 1) % 5].data);

			glVertex2f(0.0f, 0.0f);
			glVertex2fv(inner_vertices[i].data);
			glVertex2fv(inner_vertices[(i + 1) % 5].data);
		}

		glEnd();
	}
}

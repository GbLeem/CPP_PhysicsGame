#pragma once

#include <cassert>
#include <iostream>

namespace gb
{
	template<typename T>
	class Vector2
	{
	public:
		union
		{
			struct { T x, y; };
			struct { T v0, v1; };
			T data[2];
		};

	public:
		Vector2()
		{}

		Vector2(const T& x_input, const T& y_input)
			:x(x_input)
			,y(y_input)
		{}

		~Vector2()
		{}

		T DotProduct(const Vector2<T>& other) const
		{
			return x * other.x + y * other.y;
		}

		T GetMagnitude()
		{
			return sqrt(x * x + y * y);
		}

		void operator += (const Vector2<T>& other)
		{
			x += other.x;
			y += other.y;
		}

		void operator -= (const Vector2<T>& other)
		{
			x -= other.x;
			y -= other.y;
		}

		void operator *=(const T& other)
		{
			x *= other;
			y *= other;
		}

		void operator /=(const T& other)
		{
			const T fraction = T(1) / other;
			x *= fraction;
			y *= fraction;
		}

		Vector2<T> operator + (const Vector2<T>& other) const
		{
			return Vector2<T>(x + other.x, y + other.y);
		}

		Vector2<T> operator -(const Vector2<T>& other) const
		{
			return Vector2<T>(x - other.x, y - other.y);
		}

		Vector2<T> operator * (const T& other) const
		{
			return Vector2<T>(x * other, y * other);
		}

		Vector2<T> operator / (const T& other) const
		{
			const T fraction = T(1) / other;
			return Vector2<T>(x * fraction, y * fraction);
		}

		Vector2<T> operator - () const
		{
			return Vector2<T>(-x, -y);
		}

		float& operator [] (const int& ix)
		{
			assert(ix >= 0);
			assert(ix < 2);

			return data[ix];
		}

		const float& operator [] (const int& ix) const
		{
			assert(ix >= 0);
			assert(ix < 2);

			return data[ix];
		}

		friend std::ostream& operator << (std::ostream& out, const Vector2<T>& vec)
		{
			out << vec.x << " " << vec.y;
			return out;
		}
	};
}
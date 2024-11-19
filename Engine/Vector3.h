#pragma once

#include <cassert>

namespace gb
{
	template<typename T>
	class Vector3
	{
	public:
		union 
		{
			struct { T x, y, z; };
			struct { T v0, v1, v2; };
			struct { T r, g, b; };		
			T data[3];
			T rgb[3];
		};

	public:
		Vector3()
		{}

		Vector3(const T& _x, const T& _y, const T& _z)
			: x(_x), y(_y), z(_z)
		{}

		~Vector3()
		{}

		void operator += (const Vector3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		void operator -= (const Vector3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		void operator *= (const T& other)
		{
			x *= other;
			y *= other;
		}

		void operator /= (const T& other)
		{
			const T fraction = T(1) / other;
			x *= fraction;
			y *= fraction;
		}

		Vector3<T> operator + (const Vector3<T>& other) const
		{
			return Vector3<T>(x + other.x, y + other.y, z + other.z);
		}

		Vector3<T> operator - (const Vector3<T>& other) const
		{
			return Vector3<T>(x - other.x, y - other.y, z - other.z);
		}

		Vector3<T> operator * (const T& other) const
		{
			return Vector3<T>(x * other, y * other, z * other);
		}

		Vector3<T> operator / (const T& other) const
		{
			const T fraction = T(1) / other;
			return Vector3<T>(x * fraction, y * fraction, z * fraction);
		}
		T& operator [] (const int& ix)
		{
			assert(ix >= 0);
			assert(ix < 3);

			return data[ix];
		}

		const T& operator [] (const int& ix) const
		{
			assert(ix >= 0);
			assert(ix < 3);

			return data[ix];
		}
	};
}

#pragma once

template <class T>
class Vector2
{
public:
	T x, y;

	Vector2(T argX, T argY)
		: x(argX), y(argY)
	{}

	void Normalise()
	{
		const float dot = Dot();

		if(dot != 0)
			*this /= sqrt(dot);
	}

	float Dot() const
	{
		return (x * x) + (y * y);
	}

	// *= vec2
	inline void operator*=(const Vector2<T>& argVec2)
	{
		x *= argVec2.x;
		y *= argVec2.y;
	}

	// += vec2
	inline void operator+=(const Vector2<T>& argVec2)
	{
		x += argVec2.x;
		y += argVec2.y;
	}

	// -= vec2
	inline void operator-=(const Vector2<T>& argVec2)
	{
		x -= argVec2.x;
		y -= argVec2.y;
	}

	// = vec2
	inline void operator=(const Vector2& argVec2)
	{
		x = argVec2.x;
		y = argVec2.y;
	}

	// /= vec2
	inline void operator/=(const Vector2& argVec2)
	{
		x /= argVec2.x;
		y /= argVec2.y;
	}

	// /= int
	inline void operator/=(const int argInt)
	{
		x /= argInt;
		y /= argInt;
	}

	// *= int
	inline void operator*=(const int argInt)
	{
		x *= argInt;
		y *= argInt;
	}

	// /= float
	inline void operator/=(const float argFloat)
	{
		x /= argFloat;
		y /= argFloat;
	}

	// *= float
	inline void operator*=(const float argFloat)
	{
		x *= argFloat;
		y *= argFloat;
	}


	// ++ int
	inline void operator++(const int argInt)
	{
		x += argInt;
		y += argInt;
	}

	// -- int
	inline void operator--(const int argInt)
	{
		x -= argInt;
		y -= argInt;
	}
};

// + vec2
template <class T>
inline bool operator==(const Vector2<T>& argVec1, const Vector2<T>& argVec2)
{
	if (argVec1.x == argVec2.x && argVec1.y == argVec2.y)
		return true;
	else
		return false;
}

// + vec2
template <class T>
inline Vector2<T> operator+(Vector2<T> argVec1, const Vector2<T>& argVec2)
{
	argVec1 += argVec2;

	return argVec1;
}

// - vec2
template <class T>
inline Vector2<T> operator-(Vector2<T> argVec1, const Vector2<T>& argVec2)
{
	argVec1 -= argVec2;

	return argVec1;
}

// / Vec2
template <class T>
inline Vector2<T> operator/(Vector2<T> argVec1, const Vector2<T>& argVec2)
{
	argVec1 /= argVec2;

	return argVec1;
}

// * Vec2
template <class T>
inline Vector2<T> operator*(Vector2<T> argVec1, const Vector2<T>& argVec2)
{
	argVec1 *= argVec2;
	return argVec1;
}

// / Int
template <class T>
inline Vector2<T> operator/(Vector2<T> argVec1, const int argInt)
{
	argVec1 /= argInt;

	return argVec1;
}

// * int
template <class T>
inline Vector2<T> operator*(Vector2<T> argVec1, const int argInt)
{
	argVec1 *= argInt;

	return argVec1;
}

// * float
template <class T>
inline Vector2<T> operator*(Vector2<T> argVec1, const float argFloat)
{
	argVec1 *= argFloat;

	return argVec1;
}

// / float
template <class T>
inline Vector2<T> operator/(Vector2<T> argVec1, const float argFloat)
{
	argVec1 /= argFloat;

	return argVec1;
}
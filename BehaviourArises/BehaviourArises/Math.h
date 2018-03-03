#pragma once


template<typename T>
struct Vector2
{
	T x;
	T y;

	Vector2<T>(const T p_x, const T p_y) {
		x = p_x;
		y = p_y;
	}
	Vector2(void)
	{
	}
};


template <typename T>
float Length(Vector2<T> v)
{

	return sqrt((v.x * v.x) + (v.y * v.y));

}
template <typename T>
int Manhattan(Vector2<T> lhs, Vector2<T> rhs)
{

	return (abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y));

}
template <typename T>
Vector2<T> Normalize(Vector2<T> v)
{

	Vector2 <T > vec = v / Length(v);
	return vec;
}

template <typename T>
Vector2<float> ToFloat(Vector2<T> v)
{
	return Vector2<float>(static_cast<float>(v.x), static_cast<float>(v.y));
}

template<typename T>
Vector2<T> operator-(Vector2<T> lhs, Vector2<T> rhs)
{
	return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}
template<typename T>
Vector2<T> operator-(Vector2<T> lhs)
{
	return Vector2<T>(-lhs.x, -lhs.y);
}
template<typename T>
Vector2<T> operator+(Vector2<T> lhs, Vector2<T> rhs)
{
	return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template<typename T>
bool operator==(Vector2<T> lhs, Vector2<T> rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}


template<typename T>
Vector2<T> operator*(Vector2<T> lhs, float rhs)
{
	return Vector2<T>(lhs.x*rhs, lhs.y*rhs);
}

template<typename T>
Vector2<T> operator/(Vector2<T> lhs, float rhs)
{
	Vector2<T> vec = lhs*(1.f / rhs);

	return vec;
}

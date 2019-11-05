/*In Vector2D.h header file Vector2D class is defined with members declared
Vector2D objects are used in transform component for position and velocity of entities
multiple operators are overloaded in this class*/
#pragma once
#include <iostream>
using namespace std;
class Vector2D
{
private:
public:
	float x, y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vector);
	Vector2D& Subtract(const Vector2D& vector);
	Vector2D& Multiply(const Vector2D& vector);
	Vector2D& Divide(const Vector2D& vector);

	friend Vector2D& operator+(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1,Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, Vector2D& v2);

	Vector2D& operator+=(Vector2D& vector);
	Vector2D& operator-=(Vector2D& vector);
	Vector2D& operator*=(Vector2D& vector);
	Vector2D& operator/=(Vector2D& vector);

	Vector2D& operator*(const int& i);
	Vector2D& zero();

	friend ostream& operator<<(ostream& stream, const Vector2D& vector);

	
};
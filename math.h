#pragma once

#include <iostream>
using namespace std;
struct Vector2f
{

    float x, y;
	Vector2f():x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y):x(p_x), y(p_y)
	{}

	void print()
	{
		cout << x << ", " << y << endl;
	}
    Vector2f operator+(Vector2f other){
    return {x+other.x,y+other.y};
}

};

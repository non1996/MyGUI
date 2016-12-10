#pragma once

#include <iostream>

class MyVector2
{
private:
	float _x, _y;
public:	
	MyVector2()
	{
		_x = 0;
		_y = 0;
	}
	MyVector2(float x, float y)
	{
		_x = x;
		_y = y;
	}
	void SetX(float x) { _x = x; }
	void SetY(float y) { _y = y; }
	float X() const
	{
		return _x;
	}
	float Y() const
	{
		return _y;
	}

	bool Equal(MyVector2 & v1, MyVector2 & v2)
	{
		return (v1._x == v2._x) && (v1._y == v2._y);
	}
	void Add(MyVector2 & v1, MyVector2 & v2)
	{
		this->_x = v1._x + v2._x;
		this->_y = v1._y + v2._y;
	}
	void Sub(MyVector2 & v1, MyVector2 & v2)
	{
		this->_x = v1._x - v2._x;
		this->_y = v1._y - v2._y;
	}
};

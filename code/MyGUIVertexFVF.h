#pragma once

#include <d3dx9.h>

struct MyGUIVertex
{
public:
	float _x, _y, _z, _rhw;
	unsigned long _color;
	float _u, _v;

	MyGUIVertex(){}
	MyGUIVertex(float x, float y, float z, float rhw,
		unsigned long color, float u, float v)
		:_x(x), _y(y), _z(z), _rhw(rhw),
		_color(color), _u(u), _v(v)
	{

	}

	static const UINT D3DFVFGUI =	D3DFVF_XYZRHW |
									D3DFVF_DIFFUSE |
									D3DFVF_TEX1;
};


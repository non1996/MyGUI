#include "MyGUIFont.h"



MyGUIFont::MyGUIFont(IDirect3DDevice9 *device)
{
	_font = 0;
	_fontColor = D3DCOLOR_XRGB(255, 255, 255);
}


MyGUIFont::~MyGUIFont()
{
	if (_font)
		delete _font;
}

void MyGUIFont::ResetFont(UINT height, UINT width, UINT weight, const wchar_t *name, D3DCOLOR color)
{
	if (_font)
		_font->Release();
	_fontHeight = height;
	_fontWidth = width;
	_fontWeight = weight;
	_fontName = name;
	_fontColor = color;
	D3DXCreateFont(	_device,
					height,
					width,
					weight,
					1000,
					0,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					0,
					name,
					&_font);
}

void MyGUIFont::Draw(const wchar_t * text, LONG left, LONG top, LONG right, LONG bottom)
{
	if (_font)
	{
		RECT _r;
		_r.left = left;
		_r.top = top;
		_r.right = right;
		_r.bottom = bottom;

		_font->DrawTextW(
			0,
			text,
			-1,
			&_r,
			DT_TOP | DT_LEFT,
			_fontColor);
	}
}
#pragma once

#include <d3dx9.h>

class MyGUIFont
{
private:
	ID3DXFont *_font;
	IDirect3DDevice9 *_device;
	#pragma region FontInfo
	
	UINT _fontHeight;
	UINT _fontWidth;
	UINT _fontWeight;
	const wchar_t *_fontName;
	D3DCOLOR _fontColor;
	
	#pragma endregion
	
public:
	MyGUIFont(IDirect3DDevice9 *device);
	virtual ~MyGUIFont();
	
	void SetFont(ID3DXFont *font) { _font = font; }
	ID3DXFont *GetFont() const { return _font; }
	void SetColor(D3DCOLOR fontColor) { _fontColor = fontColor; }
	D3DCOLOR GetColor() const { return _fontColor; }

	void ResetFont(	UINT height,
					UINT width,
					UINT weight,
					const wchar_t *name,
					D3DCOLOR color);

	void Draw(	const wchar_t *text,
				LONG left,
				LONG top,
				LONG right,
				LONG bottom);

	void Release()
	{
		if (_font)
			_font->Release();
		if (_fontName)
			delete [] _fontName;
		_device = 0;
	}
};


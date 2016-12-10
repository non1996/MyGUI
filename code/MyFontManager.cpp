#include "MyFontManager.h"


MyFontManager *MyFontManager::_instance = 0;


MyFontManager * MyFontManager::Instance(IDirect3DDevice9* device)
{
	if (!_instance)
		_instance = new MyFontManager(device);
	return _instance;
}


MyFontManager::~MyFontManager()
{
}

ID3DXFont *MyFontManager::CreateMyFont( const wchar_t *fontName,
										UINT height,
										UINT width,
										UINT weight)
{
	ID3DXFont *font = 0;
	D3DXCreateFont(_device,
				   height,
				   width,
				   weight,
				   1000,
				   0,
				   DEFAULT_CHARSET,
				   OUT_DEFAULT_PRECIS,
				   DEFAULT_QUALITY,
				   0,
				   fontName,
				   &font);
	return font;
}

void MyFontManager::Release()
{
	if(_instance)
		delete _instance;
	_instance = 0;
}

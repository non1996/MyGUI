#pragma once

#include <d3dx9.h>
#include <list>

class MyFontManager							//һ��ʼ����������߿��أ� �������ã� Ĭ��ֵΪ25 12 500
{
private:
	static MyFontManager *_instance;
	IDirect3DDevice9 *_device;
	MyFontManager(IDirect3DDevice9 *device) { _device = device; }
public:
	static MyFontManager *Instance(IDirect3DDevice9* device);

	ID3DXFont *CreateMyFont(const wchar_t *fontName,
							UINT height,
							UINT width,
							UINT weight);


	static void Release();
	~MyFontManager();
};


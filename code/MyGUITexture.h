#pragma once
#include <d3dx9.h>
#include "MyGUIVertexBuffer.h"
#include "MyGUIVertexFVF.h"

class MyGUITexture
{
private:
	IDirect3DTexture9 *_texture;
//	IDirect3DVertexBuffer9 *_buffer;
	MyGUIVertexBuffer* _buffer;
	IDirect3DDevice9 *_device;
	
public:
	
	MyGUITexture(IDirect3DDevice9 *device);
	~MyGUITexture();

	bool LoadTexture(const wchar_t *path);
	
	void SetBuffer(MyGUIVertexBuffer *buffer) { _buffer = buffer; }
	IDirect3DTexture9 *GetTexture() { return _texture; }
	void Draw();
	void Release();
};


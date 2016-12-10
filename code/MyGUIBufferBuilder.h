#pragma once

//#include "MyGUIVertexFVF.h"
#include "MyGUIVertexBuffer.h"
#include <d3dx9.h>


class MyGUIBufferBuilder
{
private:
	IDirect3DDevice9* _device;
	static MyGUIBufferBuilder* _instance;

	MyGUIBufferBuilder(IDirect3DDevice9* device);
public:

	MyGUIVertexBuffer* BuildBuffer(		float x,
										float y,
										float width,
										float height);

	static MyGUIBufferBuilder* Instance(IDirect3DDevice9* device);
	static void Release() { delete _instance; _instance = 0; }

};


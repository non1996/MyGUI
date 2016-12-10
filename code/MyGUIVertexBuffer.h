#pragma once

#include "MyGUIVertexFVF.h"
#include <d3dx9.h>
class MyGUIVertexBuffer
{
private:
	IDirect3DVertexBuffer9* _buffer;
	IDirect3DDevice9* _device;
	MyGUIVertex* _vertexes;
public:
	MyGUIVertexBuffer(IDirect3DDevice9* _device);
	~MyGUIVertexBuffer();

	void SetBuffer(IDirect3DVertexBuffer9* buffer) { _buffer = buffer; }
	void SetVertexes(MyGUIVertex* vertex) { _vertexes = vertex; }
	IDirect3DVertexBuffer9* GetBuffer() { return _buffer; }

	void Resize(float x, float y, float height, float width)
	{
		if (_buffer)
		{
			_buffer->Lock(0, 0, (void**)&_vertexes, 0);

			_vertexes[0]._x = x;
			_vertexes[0]._y = y + height;
			_vertexes[1]._x = x;
			_vertexes[1]._y = y;
			_vertexes[2]._x = x + width;
			_vertexes[2]._y = y;

			_vertexes[3]._x = x;
			_vertexes[3]._y = y + height;
			_vertexes[4]._x = x + width;
			_vertexes[4]._y = y;
			_vertexes[5]._x = x + width;
			_vertexes[5]._y = y + height;

			_buffer->Unlock();
		}
	}
};


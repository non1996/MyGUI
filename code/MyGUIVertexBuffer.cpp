#include "MyGUIVertexBuffer.h"



MyGUIVertexBuffer::MyGUIVertexBuffer(IDirect3DDevice9* device)
{
	_device = device;
	_buffer = 0;
}


MyGUIVertexBuffer::~MyGUIVertexBuffer()
{
}

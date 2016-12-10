#include "MyGUIBufferBuilder.h"

MyGUIBufferBuilder* MyGUIBufferBuilder::_instance = 0;

MyGUIVertexBuffer* MyGUIBufferBuilder::BuildBuffer(float x, float y, float width, float height)
{
	IDirect3DVertexBuffer9* buffer;
	_device->CreateVertexBuffer(6 * sizeof(MyGUIVertex),
								D3DUSAGE_WRITEONLY,
								MyGUIVertex::D3DFVFGUI,
								D3DPOOL_MANAGED,
								&buffer,
								0);

	MyGUIVertex *v = new MyGUIVertex[6];
	buffer->Lock(0, 0, (void **)&v, 0);

		v[0] = MyGUIVertex(x, y + height, 0.0f, 1, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f);
		v[1] = MyGUIVertex(x, y, 0.0f, 1, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f);
		v[2] = MyGUIVertex(x + width, y, 0.0f, 1, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f);


		v[3] = MyGUIVertex(x, y + height, 0.0f, 1, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f);
		v[4] = MyGUIVertex(x + width, y, 0.0f, 1, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f);
		v[5] = MyGUIVertex(x + width, y + height, 0.0f, 1, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f);

	buffer->Unlock();

	MyGUIVertexBuffer *b = new MyGUIVertexBuffer(_device);
	b->SetBuffer(buffer);
	b->SetVertexes(v);
	return b;
}

MyGUIBufferBuilder * MyGUIBufferBuilder::Instance(IDirect3DDevice9* device)
{
	if (_instance == 0)
		_instance = new MyGUIBufferBuilder(device);
	return _instance;
}

MyGUIBufferBuilder::MyGUIBufferBuilder(IDirect3DDevice9* device)
{
	_device = device;
}


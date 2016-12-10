#include "MyGUITexture.h"

MyGUITexture::MyGUITexture(IDirect3DDevice9 * device)
{
	_device = device;
	_texture = 0;
	_buffer = 0;
}

MyGUITexture::~MyGUITexture()
{
	_texture = 0;
	_buffer = 0;
	_device = 0;
}

bool MyGUITexture::LoadTexture(const wchar_t * path)
{
	if (!path)
		return false;
	if(D3DXCreateTextureFromFile(_device, path, &_texture) != D3D_OK)
		return false;
	return true;
}

void MyGUITexture::Draw()
{
	if (_texture != 0 &&
		_buffer != 0 &&
		_device != 0)
	{
		_device->SetTexture(0, _texture);

		_device->SetStreamSource(0, _buffer->GetBuffer(), 0, sizeof(MyGUIVertex));
		_device->SetFVF(MyGUIVertex::D3DFVFGUI);
		_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		_device->SetTexture(0, 0);
	}
}

void MyGUITexture::Release()
{
	if (_texture)
		_texture->Release();
}

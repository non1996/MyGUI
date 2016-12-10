#pragma once

class MyGUIInputBox;
class MyGUIPushButton;
class MyGUISlider;
class MyGUITextLable;
class MyVector2;

#include <d3dx9.h>
#include "MyGUIBufferBuilder.h"
#include "MyFontManager.h"

class MyGUIWidgetFactoryBase
{
protected:
	IDirect3DDevice9* _device;
	MyGUIBufferBuilder* _bufferBuilder;
	MyFontManager* _fontManager;

	MyGUIWidgetFactoryBase(	IDirect3DDevice9* device,
							MyGUIBufferBuilder* b,
							MyFontManager* f)
	{
		_device = device;
		_bufferBuilder = b;
		_fontManager = f;
	}
	
public:
	
	virtual ~MyGUIWidgetFactoryBase();

	void SetBufBuilder(MyGUIBufferBuilder* b) { _bufferBuilder = b; }
	void SetFontManager(MyFontManager* f) { _fontManager = f; }

	virtual MyGUIInputBox* MakeInputBox(MyVector2&, MyVector2&, const wchar_t*) = 0;
	virtual MyGUIPushButton* MakePushButton(MyVector2&, MyVector2&, const wchar_t*) = 0;
	virtual MyGUISlider* MakeVerticalSlider(MyVector2&, MyVector2&, const wchar_t*) = 0;
	virtual MyGUISlider* MakeHorizontalSlider(MyVector2&, MyVector2&, const wchar_t*) = 0;
	virtual MyGUITextLable* MakeLable(MyVector2&, MyVector2&, const wchar_t*) = 0;

};


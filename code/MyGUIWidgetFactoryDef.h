#pragma once

#include "MyGUIWidgetFactoryBase.h"
#include "SafeCleaner.h"

class MyGUIWidgetFactoryDef :
	public MyGUIWidgetFactoryBase
{
private:
	static MyGUIWidgetFactoryDef* _instance;
protected:
	MyGUIWidgetFactoryDef(	IDirect3DDevice9* device, MyGUIBufferBuilder* b, MyFontManager* f)
		:MyGUIWidgetFactoryBase(device, b, f){}
public:
	virtual ~MyGUIWidgetFactoryDef();

	static MyGUIWidgetFactoryDef* Instance(IDirect3DDevice9* device);
	

	virtual MyGUIInputBox* MakeInputBox(MyVector2&, MyVector2&, const wchar_t* = 0);
	virtual MyGUIPushButton* MakePushButton(MyVector2&, MyVector2&, const wchar_t* = 0);
	virtual MyGUISlider* MakeVerticalSlider(MyVector2&, MyVector2&, const wchar_t* = 0);
	virtual MyGUISlider* MakeHorizontalSlider(MyVector2&, MyVector2&, const wchar_t* = 0);
	virtual MyGUITextLable* MakeLable(MyVector2&, MyVector2&, const wchar_t* = 0);

	void Clean();
	static void Release();

};


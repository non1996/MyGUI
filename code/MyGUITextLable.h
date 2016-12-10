#pragma once

#include "MyGUIWidgetBase.h"

class MyGUITextLable: public MyGUIWidgetBase
{
public:
	MyGUITextLable(IDirect3DDevice9*);
	virtual ~MyGUITextLable();
	
	virtual bool Init(	MyVector2 &pos,
						MyVector2 &size,
						const wchar_t* name,
						MyFontManager* f_manager,
						const wchar_t* normFontName,
						MyGUIBufferBuilder* b_builder,
						const wchar_t* normTexPath,
						MyGUIWidgetBase* owner,
						MyGUIWidgetManager* manager);
	
	virtual void Changed(){}
	virtual void HandleMouse(MyGUIInput::MyGUIMouseEvent & event){}
	virtual void Draw();
};


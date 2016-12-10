#pragma once

#include "MyGUIWidgetBase.h"
#include <list>

class MyGUIWidgetComposite :
	public MyGUIWidgetBase
{
protected:
	std::list<MyGUIWidgetBase*> _widgets;
public:
	MyGUIWidgetComposite(IDirect3DDevice9* device);
	virtual ~MyGUIWidgetComposite();

	virtual void Draw();
	virtual void AddSubWidget(MyGUIWidgetBase* subWidget);
	virtual void RemoveWidget(MyGUIWidgetBase* delWidget);

	virtual void HandleMouse(MyGUIInput::MyGUIMouseEvent&);
	virtual void HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent&);
};


#pragma once

#include "MyGUIWidgetBase.h"


//interface
class MyGUIWidgetManager
{
public:
	MyGUIWidgetManager() {}
	virtual ~MyGUIWidgetManager() {}

	virtual void Draw() = 0;
	virtual void CreateWidget() = 0;
	virtual void WidgetChanged(MyGUIWidgetBase*) = 0;

	virtual void Close() = 0;
	virtual void Open() = 0;
};


#include "MyGUIWidgetComposite.h"

MyGUIWidgetComposite::MyGUIWidgetComposite(IDirect3DDevice9 * device)
	:MyGUIWidgetBase(device)
{
//	_widgets = new std::list<MyGUIWidgetBase*>;
}

MyGUIWidgetComposite::~MyGUIWidgetComposite()
{
}

void MyGUIWidgetComposite::Draw()
{
//	if (!_widgets)
//		return;
	for (std::list<MyGUIWidgetBase*>::iterator iter = _widgets.begin();
		iter != _widgets.end();
		++iter)
		(*iter)->Draw();
}

void MyGUIWidgetComposite::AddSubWidget(MyGUIWidgetBase * subWidget)
{
//	if (!_widgets)
//		return;
	_widgets.push_back(subWidget);
}

void MyGUIWidgetComposite::RemoveWidget(MyGUIWidgetBase * delWidget)
{
//	if (!_widgets)
//		return;
	_widgets.remove(delWidget);
}

void MyGUIWidgetComposite::HandleMouse(MyGUIInput::MyGUIMouseEvent &event)
{
//	if (!_widgets)
//		return;
	for (std::list<MyGUIWidgetBase*>::iterator iter = _widgets.begin();
		iter != _widgets.end();
		++iter)
		(*iter)->HandleMouse(event);
}

void MyGUIWidgetComposite::HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent &event)
{
//	if (!_widgets)
//		return;
	for (std::list<MyGUIWidgetBase*>::iterator iter = _widgets.begin();
		iter != _widgets.end();
		++iter)
		(*iter)->HandleKeyboard(event);
}


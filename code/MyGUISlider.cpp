#include "MyGUISlider.h"

MyGUISlider::MyGUISlider(IDirect3DDevice9 * device)
	:MyGUIWidgetComposite(device)
{
	_up = 0;
	_down = 0;
	_block = 0;
}

MyGUISlider::~MyGUISlider()
{
}

bool MyGUISlider::Init(	MyVector2 & pos, 
						MyVector2 & size, 
						MyGUIBufferBuilder * b_builder, 
						const wchar_t * normTexPath, 
						const wchar_t * highLightTexPath, 
						const wchar_t * disableTexPath, 
						MyGUIWidgetBase * owner, 
						MyGUIWidgetManager * manager)
{
	MyGUIWidgetBase::Init(	pos, size, 0, 0, 0, 0, 0, b_builder,
							normTexPath, highLightTexPath, disableTexPath,
							owner, manager);
	if (_up && _down && _block)
	{
		AddSubWidget(_up);
		AddSubWidget(_down);
		AddSubWidget(_block);
	}
	return true;
}

void MyGUISlider::SubWidgetEvent(MyGUIWidgetBase* w)
{
	if (w == _up)
	{
		_block->Move((_block->GetMaxPos() - _block->GetMinPos()) / 20);
		return;
	}
	if (w == _down)
	{
		_block->Move(-(_block->GetMaxPos() - _block->GetMinPos()) / 20);
		return;
	}
	if (w == _block)
	{
		Changed();
		return;
	}
}

void MyGUISlider::Draw()
{
	DrawNormal();
	MyGUIWidgetComposite::Draw();
}

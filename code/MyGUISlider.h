#pragma once
#include "MyGUIWidgetComposite.h"

#include "MyGUIPushButton.h"
#include "MyGUISliderBlock.h"

class MyGUISlider :
	public MyGUIWidgetComposite
{
private:
	//滑动条包含的组件
	MyGUIPushButton* _up, *_down;
	MyGUISliderBlock* _block;

	
public:
	MyGUISlider(IDirect3DDevice9* device);
	virtual ~MyGUISlider();
	
	virtual bool Init(	MyVector2 &pos,
						MyVector2 &size,
						MyGUIBufferBuilder* b_builder,
						const wchar_t* normTexPath,
						const wchar_t* highLightTexPath,
						const wchar_t* disableTexPath,
						MyGUIWidgetBase* owner,
						MyGUIWidgetManager* manager);


	void SetStateNormal()
	{
		MyGUIWidgetBase::SetStateNormal();
		_up->SetStateNormal();
		_down->SetStateNormal();
		_block->SetStateNormal();
	}
	void SetStateDisable()
	{
		MyGUIWidgetBase::SetStateDisable();
		_up->SetStateDisable();
		_down->SetStateDisable();
		_block->SetStateDisable();
	}
	
	void AddUpButton(MyGUIPushButton* up) { _up = up; }
	void AddDownButton(MyGUIPushButton* down) { _down = down; }
	void AddSliderBlock(MyGUISliderBlock* block) { _block = block; }

	virtual void SubWidgetEvent(MyGUIWidgetBase* w);
	
//	virtual void HandleMouse(MyGUIInput::MyGUIMouseEvent & event);
//	virtual void HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent & event);
	virtual void Draw();
	
};


#include "MyGUISliderBlock.h"

bool MyGUISliderBlock::Init(	MyVector2 &pos,
								MyVector2 &size,
								float maxPos,
								float minPos,
								MyGUIBufferBuilder* b_builder,
								const wchar_t* normTexPath,
								const wchar_t* highLightTexPath,
								const wchar_t* disableTexPath,
								MyGUIWidgetBase* owner,
								MyGUIWidgetManager* manager)
{
	MyGUIWidgetBase::Init(	pos,
							size,
							0,
							0,
							0,
							0,
							0,
							b_builder,
							normTexPath,
							highLightTexPath,
							disableTexPath,
							owner,
							manager);
	SetMaxPos(maxPos);
	SetMinPos(minPos);

	return true;
}

void MyGUISliderBlock::SetMoveHorizontal()
{
	_moveType = Horizontal::Instance();
}

void MyGUISliderBlock::SetMoveVertical()
{
	_moveType = Vertical::Instance();
}

void MyGUISliderBlock::Move(float offset)
{
	_moveType->Move(this, offset);
}

bool MyGUISliderBlock::UpdateThis(MyGUIInput::MyGUIMouseEvent & event)
{
	return _moveType->UpdateThis(this, event);
}

void MyGUISliderBlock::HandleMouse(MyGUIInput::MyGUIMouseEvent & event)
{
	if (IsStateDisable())
		return;
	if (!UpdateThis(event))
	{
		SetStateNormal();
		return;
	}

	if (IsStateNormal())
	{
		if (event.IsMove()) SetStateMouseon();
		return;
	}
	if (IsStateMouseOn())
	{
		if (event.IsLeftDown() || event.IsRightDown())
		{
			SetStateMouseClick();
			StartMove();
		}
		return;
	}
	if (IsStateClick())
	{
		if (IsMoving())
		{
			_moveType->HandleMouse(this, event);
		}
		if (event.IsLeftUp() || event.IsRightUp())
		{
			SetStateNormal();
			EndMove();
		}	
		return;
	}
}

void MyGUISliderBlock::HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent & event)
{
	_moveType->HandleKeyboard(this, event);
}

MyGUISliderBlock::Horizontal* MyGUISliderBlock::Horizontal::_instance = 0;
MyGUISliderBlock::Vertical* MyGUISliderBlock::Vertical::_instance = 0;

MyGUISliderBlock::Horizontal * MyGUISliderBlock::Horizontal::Instance()
{
	if (!_instance)
		_instance = new Horizontal;
	return _instance;
}

void MyGUISliderBlock::Horizontal::Move(MyGUISliderBlock *block, float offset)
{
	MyVector2 tempPos = block->GetPosition();
	MyVector2 tempSize = block->GetSize();

	
	if (offset == 0)
		return;
	//滑块位置不能超过限定值
	if (offset > 0)//向右移动
	{
		if (tempPos.X() + tempSize.X() + offset < block->GetMaxPos())
			block->ReSetPosition(MyVector2(tempPos.X() + offset, tempPos.Y()));
		else
			block->ReSetPosition(MyVector2(block->GetMaxPos() - tempSize.X(), tempPos.Y()));
		return;
	}
	if (offset < 0)//向左移动
	{
		if (tempPos.X() + offset > block->GetMinPos())
			block->ReSetPosition(MyVector2(tempPos.X() + offset, tempPos.Y()));
		else
			block->ReSetPosition(MyVector2(block->GetMinPos(), tempPos.Y()));
		return;
	}
}

bool MyGUISliderBlock::Horizontal::UpdateThis(MyGUISliderBlock *block, MyGUIInput::MyGUIMouseEvent &e)
{
	return (e.GetX() < block->GetMaxPos() &&
			e.GetX() > block->GetMinPos() &&
			e.GetY() < block->GetPosition().Y() + block->GetSize().Y()&&
			e.GetY() > block->GetPosition().Y());
}

void MyGUISliderBlock::Horizontal::HandleMouse(MyGUISliderBlock *block, MyGUIInput::MyGUIMouseEvent &event)
{
	float offset = (float)event.GetX() - block->GetPosition().X() - block->GetSize().X() / 2;
	Move(block, offset);
}

void MyGUISliderBlock::Horizontal::HandleKeyboard(MyGUISliderBlock *block, MyGUIInput::MyGUIKeyboardEvent &event)
{
	if (event.IsLeft())
	{
		Move(block, -((block->GetMaxPos() - block->GetMinPos()) / 20));
		return;
	}
	if (event.IsRight())
	{
		Move(block, (block->GetMaxPos() - block->GetMinPos()) / 20);
		return;
	}
}

void MyGUISliderBlock::Horizontal::Release()
{
	if (_instance)
		delete _instance;
}

MyGUISliderBlock::Vertical * MyGUISliderBlock::Vertical::Instance()
{
	if (!_instance)
		_instance = new Vertical;
	return _instance;
}

void MyGUISliderBlock::Vertical::Move(MyGUISliderBlock *block, float offset)
{
	MyVector2 tempPos = block->GetPosition();
	MyVector2 tempSize = block->GetSize();


	if (offset == 0)
		return;
	//滑块位置不能超过限定值
	if (offset < 0)//向下移动
	{
		if (tempPos.Y() + tempSize.Y() - offset <= block->GetMaxPos())
			block->ReSetPosition(MyVector2(tempPos.X(), tempPos.Y() - offset));
		else
			block->ReSetPosition(MyVector2(tempPos.X(), block->GetMaxPos() - tempSize.Y()));
		return;
	}
	if (offset > 0)//向上移动
	{
		if (tempPos.Y() - offset >= block->GetMinPos())
			block->ReSetPosition(MyVector2(tempPos.X(), tempPos.Y() - offset));
		else
			block->ReSetPosition(MyVector2(tempPos.X(), block->GetMinPos()));
		return;
	}
}

bool MyGUISliderBlock::Vertical::UpdateThis(MyGUISliderBlock *block, MyGUIInput::MyGUIMouseEvent &e)
{
	return (	 e.GetY() < block->GetMaxPos()
			  && e.GetY() > block->GetMinPos()
			  && e.GetX() < block->GetPosition().X() + block->GetSize().X()
			  && e.GetX() > block->GetPosition().X());
}

void MyGUISliderBlock::Vertical::HandleMouse(MyGUISliderBlock *block, MyGUIInput::MyGUIMouseEvent &event)
{
	float offset =  block->GetPosition().Y() + block->GetSize().Y() / 2 - (float)event.GetY();
	Move(block, offset);
}

void MyGUISliderBlock::Vertical::HandleKeyboard(MyGUISliderBlock *block, MyGUIInput::MyGUIKeyboardEvent &event)
{
	if (event.IsUp())
	{
		Move(block, (block->GetMaxPos() - block->GetMinPos()) / 20);
		return;
	}
	if (event.IsDown())
	{
		Move(block, -(block->GetMaxPos() - block->GetMinPos()) / 20);
		return;
	}
}

void MyGUISliderBlock::Vertical::Release()
{
	if(_instance)
		delete _instance;
}

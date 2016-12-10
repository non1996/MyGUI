#include "MyGUIInputBox.h"
#include <iterator>


void MyGUIInputBox::CursorChange(MyGUIInput::MyGUIMouseEvent & event)
{
	if (!HasContent())
	{
		SetCursorPosition(0);
		return;
	}

	UINT pos =  (event.GetX() - GetPosition().X()) / _sizePerChar + 1;
	if (_content->size() - _startOffset < pos)
	{
		pos = _content->size() - _startOffset;
//		SetCursorPosition(_content->size() - _startOffset);
	}
	else if (_content->size() - _startOffset == pos)
	{
		IncreaseOffset();
		--pos;
	}
	SetCursorPosition(pos);
}

void MyGUIInputBox::DeleteFront()
{
	if (_cursorPosition != 0)
	{
		_content->erase(_content->begin() + _startOffset + (_cursorPosition - 1));

		if (_startOffset)
			DecreaseOffset();
		else
			DecreaseCursorPosition();
	}
}

void MyGUIInputBox::DeleteBack()
{
	if (_cursorPosition < _content->size())
	{
		_content->erase(_content->begin() + _startOffset + _cursorPosition);
	}		
}

void MyGUIInputBox::AddCharacter(wchar_t ch)
{
	if (_content->size() < MaxNum)
	{
		_content->insert(_content->begin() + _startOffset + _cursorPosition, ch);		
		//如果光标到最右端，偏移量增加
		if (_cursorPosition == _totalNumCanShow)
			IncreaseOffset();
		//如果光标没到最右端， 则每添加一个字符光标右移一次
		if(_cursorPosition < _totalNumCanShow)
			IncreaseCursorPosition();
	}
}

void MyGUIInputBox::DrawHighLight()
{
	MyGUIWidgetBase::DrawHighLight();
	DrawContent();

}

void MyGUIInputBox::DrawNormal()
{
	MyGUIWidgetBase::DrawNormal();
	DrawContent();
}

void MyGUIInputBox::DrawContent()
{
	MyGUIFont* f = GetNormalFont();

	if (!HasContent())
		return;
	
	UINT size = _content->size();
	ZeroMemory(_canDraw, (_totalNumCanShow + 1) * sizeof(wchar_t));
	if (size - _startOffset < _totalNumCanShow)
		_content->copy(_canDraw, size - _startOffset, _startOffset);
	else
		_content->copy(_canDraw, _totalNumCanShow, _startOffset);
	
	if (f)
		f->Draw(_canDraw,
				(LONG)GetPosition().X(),
				(LONG)GetPosition().Y(),
				(LONG)(GetPosition().X() + GetSize().X()),
				(LONG)(GetPosition().Y() + GetSize().Y()));
}

void MyGUIInputBox::DrawCursor()
{
	if (_cursor)
	{
		_cursor->Draw(	GetPosition().X() + _cursorPosition * _sizePerChar,
						GetPosition().Y(),
						GetSize().Y());
	}
}

MyGUIInputBox::MyGUIInputBox(IDirect3DDevice9 * device): MyGUIWidgetBase(device)
{
	_canDraw = 0;
	_content = 0;
	_cursor = new Cursor;
	_cursor->Init(device);

	_enableBlink = false;
}

bool MyGUIInputBox::Init(MyVector2 & pos, MyVector2 & size, MyFontManager * f_manager, const wchar_t * normFontName, MyGUIBufferBuilder * b_builder, const wchar_t * normTexPath, const wchar_t * highLightTexPath, const wchar_t * disableTexPath, MyGUIWidgetBase * owner, MyGUIWidgetManager * manager)
{
	MyGUIWidgetBase::Init(	pos,
							size,
							0,
							f_manager,
							normFontName,
							0,
							0,
							b_builder,
							normTexPath,
							highLightTexPath,
							disableTexPath,
							owner,
							manager);
	SetNormalFont(f_manager, normFontName);
	_content = new std::wstring;

	
	FinishInput();
	SetStartOffset(0);
	SetCursorPosition(0);
	SetSizePerChar(12);
	SetTotalNumCanShow();
	
	_canDraw = new wchar_t[_totalNumCanShow + 1];
	ZeroMemory(_canDraw, (_totalNumCanShow + 1) * sizeof(wchar_t));
	
	//_totalNumCanShow  

	return false;
}

void MyGUIInputBox::HandleMouse(MyGUIInput::MyGUIMouseEvent &event)
{
	
	if (IsStateDisable())
		return;

	if (!UpdateThis(event))
	{
		if (event.IsLeftUp() || event.IsRightUp())
		{
			SetHighLightTypeMouseOver();
			SetStateNormal();
			FinishInput();
		}
		else SetStateNormal();

		return;
	}

	if (IsInput())
	{
		if(event.IsLeftUp() || event.IsRightUp())
			CursorChange(event);
		return;
	}

	if (IsStateNormal())
	{
		if (event.IsMove()) SetStateMouseon();
	}
	if (IsStateMouseOn())
	{
		if (event.IsLeftDown() || event.IsRightDown()) SetStateMouseClick();
	}
	if (IsStateClick())
	{
		if (event.IsLeftUp() || event.IsRightUp())
		{
			SetHighLightTypeForce();
			CursorChange(event);
			StartInput();
		}
	}
}

void MyGUIInputBox::HandleKeyBoard(MyGUIInput::MyGUIKeyboardEvent &event)
{
	if (!IsInput())
		return;

	if (event.IsBackspace())
		DeleteFront();
	if (event.IsDel())
		DeleteBack();
	if (event.IsEnter())
	{
		FinishInput();
		SetHighLightTypeMouseOver();
		Changed();
	}
	if (event.IsLeft())
	{
		DecreaseCursorPosition();
		if(_cursorPosition == 0)
			DecreaseOffset();
	}
	if (event.IsRight())
	{
		if (_content->size() - _startOffset > _totalNumCanShow && _cursorPosition == _totalNumCanShow)
			IncreaseOffset();

		if(_cursorPosition < _content->size() - _startOffset &&_cursorPosition < _totalNumCanShow)
			IncreaseCursorPosition();
	}
	if (event.IsCharacter())
		AddCharacter(event.GetChar());
}

void MyGUIInputBox::Draw()
{
	if (IsHighlightForce())
	{
		DrawHighLight();
		DrawCursor();
	}
	else if (IsHighlightMouseOver())
	{
		if (IsStateDisable())
			DrawDisable();
		if (IsStateNormal() || IsStateClick())
			DrawNormal();
		if (IsStateMouseOn())
			DrawHighLight();
	}
}

/*
MyGUIInputBox::~MyGUIInputBox()
{
}
*/


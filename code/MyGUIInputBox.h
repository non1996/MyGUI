#pragma once

#include "MyGUIWidgetBase.h"
#include <string>

class MyGUIInputBox: public MyGUIWidgetBase
{
///------------------------------------
///	光标类
///------------------------------------
	class Cursor
	{
	public:
		LPD3DXLINE _cursor;
		D3DXVECTOR2* _cursorArr;

		Cursor() 
		{
			_cursor = 0;
			_cursorArr = 0;
		}
		void Init(IDirect3DDevice9* device)
		{
			D3DXCreateLine(device, &_cursor);
			_cursorArr = new D3DXVECTOR2[2];
		}
		void Draw(UINT x, UINT y, UINT height)
		{
			if (_cursor && _cursorArr)
			{
				_cursorArr[0].x = _cursorArr[1].x = x;
				_cursorArr[0].y = y;
				_cursorArr[1].y = y + height;

				_cursor->SetWidth(2.0f);
				_cursor->SetAntialias(TRUE);
				_cursor->Draw(_cursorArr, 2, D3DCOLOR_XRGB(100, 100, 100));
			}
		}
	};

private:
	std::wstring* _content;
	wchar_t* _canDraw;

	bool _isInput;
	UINT _startOffset, _cursorPosition, _totalNumCanShow, _sizePerChar;
	//绘制光标用
	Cursor* _cursor;
	bool _enableBlink;

	const static UINT MaxNum = 40;
protected:
	#pragma region InputAbout

	bool HasContent()
	{
		if (_content)
			return _content->size() != 0;
		return false;
	}
	//设置开始显示的字符的偏移量
	void IncreaseOffset()
	{
		if (_startOffset < _content->size())
			++_startOffset;
	}
	void DecreaseOffset()
	{
		if (_startOffset > 0)
			--_startOffset;
	}
	void SetStartOffset(UINT offset) { _startOffset = offset; }
	//设置闪烁的光标位置
	void IncreaseCursorPosition() { if (_cursorPosition < _totalNumCanShow) _cursorPosition++; }
	void DecreaseCursorPosition() { if (_cursorPosition > 0) _cursorPosition--; }
	void SetCursorPosition(UINT pos) { _cursorPosition = pos; }

	void CursorChange(MyGUIInput::MyGUIMouseEvent &event);
	//开始或结束输入，判断是否在输入
	bool IsInput() 
	{
		if (_isInput == true)
			return true;
		else
			return false;
//		return (_isInput == true); 
	}
	void StartInput() { _isInput = true; }
	void FinishInput() { _isInput = false; }
	//响应键盘
	void DeleteFront();
	void DeleteBack();
	void AddCharacter(wchar_t ch);

	#pragma endregion

	virtual void DrawHighLight();
	virtual void DrawNormal();
	virtual void DrawContent();
//	virtual void DrawDisable();
	

	virtual void DrawCursor();
public:
	MyGUIInputBox(IDirect3DDevice9 *device);

	virtual ~MyGUIInputBox(){}

	virtual bool Init(	MyVector2 &pos,
						MyVector2 &size,
						MyFontManager* f_manager,
						const wchar_t* normFontName,
						MyGUIBufferBuilder* b_builder,
						const wchar_t* normTexPath,
						const wchar_t* highLightTexPath,
						const wchar_t* disableTexPath,
						MyGUIWidgetBase* owner,
						MyGUIWidgetManager* manager);

	virtual void SetStateDisable()
	{
		MyGUIWidgetBase::SetStateDisable();
		CleanContent();
	}
	virtual void SetSizePerChar(UINT s)
	{
		_sizePerChar = s;
	}
	virtual void SetTotalNumCanShow()
	{
		_totalNumCanShow = (UINT)GetSize().X() / _sizePerChar;
	}
	
	void CleanContent() 
	{
		SetStartOffset(0);
		SetCursorPosition(0);
		_content->clear(); 
	}

	virtual void HandleMouse(MyGUIInput::MyGUIMouseEvent &);
	virtual void HandleKeyBoard(MyGUIInput::MyGUIKeyboardEvent &);
	virtual void Draw();

	virtual void Release()
	{
		MyGUIWidgetBase::Release();
		SafeCleaner::Delete(_content);
	}
};


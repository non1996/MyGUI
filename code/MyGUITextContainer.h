#pragma once
#include "MyGUIWidgetBase.h"
#include <vector>
#include <string>

class MyGUITextContainer :
	public MyGUIWidgetBase
{
private:
	std::vector<std::wstring> *_content;

	//-------------------------------------------------------
	// 显示的起始行， 显示的结束行， 总行数， 总共能显示的行数
	//-------------------------------------------------------
	UINT _startLine, _finishLine, _linesNum, _drawNum;

public:
	MyGUITextContainer(IDirect3DDevice9 *device)
		:MyGUIWidgetBase(device)
	{
		_content = 0;
		_startLine = 0;
		_finishLine = 0;
		_drawNum = 0;
		_linesNum = 0;
	}
	virtual ~MyGUITextContainer();

	virtual bool Init(	MyVector2 &pos,
						MyVector2 &size,
						MyFontManager* f_manager,
						const wchar_t* normFontName,
						MyGUIBufferBuilder* b_builder,
						const wchar_t* normTexPath,
						const wchar_t* highLightTexPath,
						const wchar_t* disableTexPath,
						const char* contentPath,
						MyGUIWidgetBase* owner,
						MyGUIWidgetManager* manager);
	
	void LoadText(const char* fileName);
	virtual void SetText(std::wstring &str);

	virtual void SetLineNum(UINT n) { _linesNum = n; }
	virtual void SetStartLine(UINT s) { _startLine = s; }

	virtual void SetView(float f);

	bool HasContent() { return _content != 0; }

	virtual void Draw();

	virtual void HandleMouse(MyGUIInput::MyGUIMouseEvent &event){}
	virtual void HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent &event){}
	virtual void Release() {}

};


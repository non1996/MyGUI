#include <fstream>
#include <streambuf>
#include "MyGUITextContainer.h"

MyGUITextContainer::~MyGUITextContainer()
{
}

bool MyGUITextContainer::Init(MyVector2 & pos, MyVector2 & size, MyFontManager * f_manager, const wchar_t * normFontName, MyGUIBufferBuilder * b_builder, const wchar_t * normTexPath, const wchar_t * highLightTexPath, const wchar_t * disableTexPath, const char * contentPath, MyGUIWidgetBase * owner, MyGUIWidgetManager * manager)
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
	
	_drawNum = (int)(GetSize().Y() / 25);

	SetNormalFont(f_manager, normFontName);
	LoadText(contentPath);
	return false;
}

//------------------------------------------------------------------------
//	从文件中读取一段文字作为文本框的内容， 参数为文件名
//------------------------------------------------------------------------
void MyGUITextContainer::LoadText(const char* fileName)
{
	std::ifstream fin(fileName);
	std::istreambuf_iterator<char> beg(fin), end;
	std::string s(beg, end);
	std::wstring ws;
	int len = (int)s.length();
	ws.resize(len, L'\0');
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)s.c_str(), len, (LPWSTR)ws.c_str(), len);

	SetText(ws);
	fin.close();
}

//------------------------------------------------------------------------
//	将读入的文本分行，每行字数不超过最大显示数量
//------------------------------------------------------------------------
void MyGUITextContainer::SetText(std::wstring & str)
{
	_content = new std::vector<std::wstring>;
	int begin = 0, count = 0, end = 0;
	int numPerLine = (int)(GetSize().X() / 12);
	for (; end < str.length(); ++end)
	{
		count++;
		if (str.at(end) == L'\n' || count == numPerLine || end == str.length() - 1)
		{
			count = 0;
			_content->push_back(str.substr(begin, end - begin + 1));
			begin = end + 1;
			_linesNum++;
		}
	}
//	if (count != 0) 
//	{
//		_content->push_back(str.substr(begin, end - begin));
//	}
	//------------------------
	//	设置初始的显示结束行
	//------------------------
	if (_drawNum < _linesNum) 
	{
		_finishLine = _drawNum - 1;
	}
	else
	{
		_finishLine = _linesNum - 1;
	}
}

//------------------------------------------------------------------------
//	传入一个浮点数，以此改变字符显示的起始和终止行数
//------------------------------------------------------------------------
void MyGUITextContainer::SetView(float f)
{
	if (f < 0 || f > 1)
		return;
	_startLine = _linesNum * f;
	if (_startLine + _drawNum <= _linesNum)
		_finishLine = _startLine + _drawNum - 1;
	else
		_finishLine = _linesNum - 1;
}

//------------------------------------------------------------------------
//	绘制贴图以及根据偏移行数显示文本内容
//------------------------------------------------------------------------
void MyGUITextContainer::Draw()
{
	MyGUIFont* f = GetNormalFont();

	//--------------------------------测试用
	f->Draw(
		//std::to_wstring(_content->size()).c_str(),
		//std::to_wstring(_finishLine).c_str(),
		std::to_wstring(_linesNum).c_str(),
		50,
		50,
		100,
		100
	);
	//--------------------------------------------------------------

	DrawNormal();

	if (f && _content)
	{
		int line = 0;
		for (int i = _startLine; i <= _finishLine; ++i)
		{
			f->Draw(	(*_content)[i].c_str(),
						(LONG)GetPosition().X(),
						(LONG)GetPosition().Y() + 13 * (line++),
						(LONG)(GetPosition().X() + GetSize().X()),
						(LONG)(GetPosition().Y() + GetSize().Y()));
		}
	}
}

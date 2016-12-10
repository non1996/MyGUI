#include "MyGUIWidgetFactoryDef.h"

#include "MyGUIInputBox.h"
#include "MyGUISlider.h"
#include "MyGUIPushButton.h"
#include "MyGUITextLable.h"

MyGUIWidgetFactoryDef::~MyGUIWidgetFactoryDef()
{
}


MyGUIWidgetFactoryDef* MyGUIWidgetFactoryDef::_instance = 0;

MyGUIWidgetFactoryDef* MyGUIWidgetFactoryDef::Instance(IDirect3DDevice9 * device)
{
	if (!_instance)
		_instance = new MyGUIWidgetFactoryDef(	device, 
												MyGUIBufferBuilder::Instance(device),
												MyFontManager::Instance(device)
												);
	return _instance;
}

MyGUIInputBox * MyGUIWidgetFactoryDef::MakeInputBox(MyVector2 &pos, MyVector2 &size, const wchar_t *name)
{
	MyGUIInputBox* ib = 0;
	ib = new MyGUIInputBox(_device);

	ib->Init(	pos,
				size,
				_fontManager,
				L"黑体",
				_bufferBuilder,
				L"GameMedia\\inputNormal.png",
				L"GameMedia\\inputHighLight.png",
				L"GameMedia\\inputDisable.png",
				0,
				0);

	return ib;
}

MyGUIPushButton * MyGUIWidgetFactoryDef::MakePushButton(MyVector2 &pos, MyVector2 &size, const wchar_t *name)
{
	MyGUIPushButton* pb = 0;
	pb = new MyGUIPushButton(_device);

	pb->Init(	pos,
				size,
				name,
				_fontManager,
				L"黑体",
				L"黑体",
				L"黑体",
				_bufferBuilder,
				L"GameMedia\\NormalTexture.bmp",
				L"GameMedia\\highLightTexture.bmp",
				L"GameMedia\\DisableTexture.bmp", 
				0,
				0);
	return pb;
}

MyGUISlider * MyGUIWidgetFactoryDef::MakeVerticalSlider(MyVector2 &pos, MyVector2 &size, const wchar_t *name)
{
	MyGUISlider* s = 0;
	MyGUISliderBlock* block = 0;
	MyGUIPushButton* up = 0, *down = 0;

	s = new MyGUISlider(_device);
	block = new MyGUISliderBlock(_device);
	up = new MyGUIPushButton(_device);
	down = new MyGUIPushButton(_device);

	up->Init(	pos,
				MyVector2(size.X(), size.X()),
				0,
				0,
				0,
				0,
				0,
				_bufferBuilder,
				L"GameMedia\\SliderUpNorm.bmp",
				L"GameMedia\\SliderUpHighLight.bmp",
				L"GameMedia\\SliderUpDisable.bmp",
				s,
				0);
	down->Init(	MyVector2(pos.X(), pos.Y() + size.Y() - size.X()),
				MyVector2(size.X(), size.X()),
				0,
				0,
				0,
				0,
				0,
				_bufferBuilder,
				L"GameMedia\\SliderDownNorm.bmp",
				L"GameMedia\\SliderDownHighLight.bmp",
				L"GameMedia\\SliderDownDisable.bmp",
				s,
				0);
	block->Init(MyVector2(pos.X(), pos.Y() + size.X()),
				MyVector2(size.X(), size.Y() / 10),
				pos.Y() + size.Y() - size.X(),
				pos.Y() + size.X(),
				_bufferBuilder,
				L"GameMedia\\BlockNorm.bmp",
				L"GameMedia\\BlockHighLight.bmp",
				L"GameMedia\\BlockDisable.bmp",
				s,
				0);
	block->SetMoveVertical();

	s->AddUpButton(up);
	s->AddDownButton(down);
	s->AddSliderBlock(block);
	s->Init(pos,
			size,
			_bufferBuilder,
			L"GameMedia\\VerSliderNorm.bmp",
			L"GameMedia\\VerSliderHighLight.bmp",
			L"GameMedia\\VerSliderDisable.bmp",
			0,
			0);

	return s;
}

MyGUISlider * MyGUIWidgetFactoryDef::MakeHorizontalSlider(MyVector2 &pos, MyVector2 &size, const wchar_t *name)
{
	MyGUISlider* s = 0;
	MyGUISliderBlock* block = 0;
	MyGUIPushButton* up = 0, *down = 0;

	s = new MyGUISlider(_device);
	up = new MyGUIPushButton(_device);
	down = new MyGUIPushButton(_device);
	block = new MyGUISliderBlock(_device);

	up->Init(	MyVector2(pos.X() + size.X() - size.Y(), pos.Y()),
				MyVector2(size.Y(), size.Y()),
				0,
				0,
				0,
				0,
				0,
				_bufferBuilder,
				L"GameMedia\\SliderRightNorm.bmp",
				L"GameMedia\\SliderRightHighLight.bmp",
				L"GameMedia\\SliderRightDisable.bmp",
				s,
				0);
	down->Init(	pos,
				MyVector2(size.Y(), size.Y()),
				0,
				0,
				0,
				0,
				0,
				_bufferBuilder,
				L"GameMedia\\SliderLeftNorm.bmp",
				L"GameMedia\\SliderLeftHighLight.bmp",
				L"GameMedia\\SliderLeftDisable.bmp",
				s,
				0);
	block->Init(MyVector2(pos.X() + size.Y(), pos.Y()),
				MyVector2(size.X() / 10, size.Y()),
				pos.Y() + size.Y() - pos.X(),
				pos.Y() + size.X(),
				_bufferBuilder,
				L"GameMedia\\BlockNorm.bmp",
				L"GameMedia\\BlockHighLight.bmp",
				L"GameMedia\\BlockDisable.bmp",
				s,
				0);
	block->SetMoveHorizontal();

	s->AddUpButton(up);
	s->AddDownButton(down);
	s->AddSliderBlock(block);
	s->Init(	pos,
				size,
				_bufferBuilder,
				L"GameMedia\\HorSliderNorm.bmp",
				L"GameMedia\\HorSliderHighLight.bmp",
				L"GameMedia\\HorSliderDisable.bmp",
				0,
				0);

	return s;
}


MyGUITextLable * MyGUIWidgetFactoryDef::MakeLable(MyVector2 &pos, MyVector2 &size, const wchar_t *name)
{
	MyGUITextLable* l = 0;

	l = new MyGUITextLable(_device);
	l->Init(pos,
			size,
			name,
			_fontManager,
			L"黑体",
			_bufferBuilder,
			L"",
			0,
			0);
	return l;
}

void MyGUIWidgetFactoryDef::Clean()
{
	SafeCleaner::Release(_bufferBuilder);
	SafeCleaner::Release(_fontManager);
	_device = 0;
}

void MyGUIWidgetFactoryDef::Release()
{
	SafeCleaner::Delete(_instance);
}
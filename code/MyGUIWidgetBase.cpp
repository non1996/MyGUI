#include "MyGUIWidgetManager.h"
#include "MyGUIWidgetBase.h"

void MyGUIWidgetBase::DrawHighLight()
{
	if (_highLightTexture)
		_highLightTexture->Draw();
	if (_highLightFont)
		_highLightFont->Draw(	_name,
								//L"move",
								(LONG)_position.X(),
								(LONG)_position.Y(),
								(LONG)(_position.X() + _size.X()),
								(LONG)(_position.Y() + _size.Y()));
}

void MyGUIWidgetBase::DrawDisable()
{
	if (_disableTexture)
		_disableTexture->Draw();
	if (_disableFont)
		_disableFont->Draw(		_name,
								//L"disable",
								(LONG)_position.X(),
								(LONG)_position.Y(),
								(LONG)(_position.X() + _size.X()),
								(LONG)(_position.Y() + _size.Y()));
}

void MyGUIWidgetBase::DrawNormal()
{
	if (_normTexture)
		_normTexture->Draw();
	if (_normFont)
		_normFont->Draw(		_name,
								//L"normal",
								(LONG)_position.X(),
								(LONG)_position.Y(),
								(LONG)(_position.X() + _size.X()),
								(LONG)(_position.Y() + _size.Y()));
}

MyGUIWidgetBase::MyGUIWidgetBase(IDirect3DDevice9 * device)
{
	_device = device;
	_normFont = 0;
	_highLightFont = 0;
	_disableFont = 0;

	_normTexture = 0;
	_highLightTexture = 0;
	_disableTexture = 0;

	_textAlignment = TextAlignment::LEFT;
	_highLightType = HighLightType::MOUSEOVER;

	_name = 0;
	_currentState = WidgetState::NORMAL;
	_previousState = WidgetState::NORMAL;

	_owner = 0;
	_manager = 0;
}

MyGUIWidgetBase::~MyGUIWidgetBase()
{
	_device = 0;
	_normFont = 0;
	_highLightFont = 0;
	_disableFont = 0;

	_normTexture = 0;
	_highLightTexture = 0;
	_disableTexture = 0;

	_name = 0;

	_owner = 0;
	_manager = 0;
}

bool MyGUIWidgetBase::Init( MyVector2 &pos,
							MyVector2 &size,
							const wchar_t* name,
							MyFontManager* f_manager,
							const wchar_t* normFontName,
							const wchar_t* highLightFontName,
							const wchar_t* disableFontName,
							MyGUIBufferBuilder* b_builder,
							const wchar_t* normTexPath,
							const wchar_t* highLightTexPath,
							const wchar_t* disableTexPath,
							MyGUIWidgetBase* owner,
							MyGUIWidgetManager* manager)
{
	SetPosition(pos);
	SetSize(size);
	SetName(name);
	
	#pragma region initFont

	if (name != 0)
	{
		SetNormalFont(f_manager, normFontName);
		SetHighLightFont(f_manager, highLightFontName);
		SetDisableFont(f_manager, disableFontName);
	}
	
	#pragma endregion
	
	#pragma region initTexture
	//加载贴图和创建顶点缓存
	bool hasTex = false;
//	MyGUIVertexBuffer* buffer = 0;
	_buffer = b_builder->BuildBuffer(_position.X(), _position.Y(), _size.X(), _size.Y());
	
	if (normTexPath)
	{
		SetNormalTexture(normTexPath, _buffer);
		hasTex = true;
	}
	if (highLightTexPath)
	{
		SetHighLightTexture(highLightTexPath, _buffer);
		hasTex = true;
	}	
	if (disableTexPath)
	{
		SetDisableTexture(disableTexPath, _buffer);
		hasTex = true;
	}
	
	#pragma endregion
	
	SetOwner(owner);
	SetControlManager(manager);

//	SetHighLightTypeMouseOver();
//	SetTextAligmentCenter();
//	SetStateNormal();

	return false;
}

void MyGUIWidgetBase::Changed()
{
	if(_manager)
		_manager->WidgetChanged(this);
	if (_owner)
		_owner->SubWidgetEvent(this);
}

bool MyGUIWidgetBase::UpdateThis(MyGUIInput::MyGUIMouseEvent &e)
{
	return (e.GetX() > _position.X() &&
			e.GetX() < _position.X() + _size.X() &&
			e.GetY() > _position.Y() &&
			e.GetY() < _position.Y() + _size.Y());
}

void MyGUIWidgetBase::HandleMouse(MyGUIInput::MyGUIMouseEvent &e)
{
	if (IsStateDisable())
		return;
	if (UpdateThis(e))
	{
		switch (_currentState)
		{
		case WidgetState::NORMAL:
			if (e.IsMove())
				SetStateMouseon();
			break;
		case WidgetState::MOUSEON:
			if (e.IsLeftDown() || e.IsRightDown())
				SetStateMouseClick();
			break;
		case WidgetState::MOUSECLICK:
			if (e.IsLeftUp() || e.IsRightUp())
			{
				Changed();
				SetStateNormal();
			}
			break;
		default:
			break;
			}
	}
	else SetStateNormal();
}

void MyGUIWidgetBase::HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent &)
{
}

void MyGUIWidgetBase::Draw()
{
	switch (_highLightType)
	{
	case HighLightType::FORCE:
		DrawHighLight();
		break;
	case HighLightType::NEVER:
		if (IsStateDisable())
			DrawDisable();
		else DrawNormal();
		break;
	case HighLightType::MOUSEOVER:
		if (IsStateDisable())
			DrawDisable();
		if (IsStateNormal() || IsStateClick())
			DrawNormal();
		if (IsStateMouseOn())
			DrawHighLight();
	default:
		break;
	}
}

void MyGUIWidgetBase::Release()
{
	SafeCleaner::Release<MyGUIFont*>(_normFont);
	SafeCleaner::Release<MyGUIFont*>(_highLightFont);
	SafeCleaner::Release<MyGUIFont*>(_disableFont);

}


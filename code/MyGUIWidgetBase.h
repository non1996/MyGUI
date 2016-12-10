#pragma once

#include <wchar.h>
#include <d3dx9.h>

#include "SafeCleaner.h"
#include "MyGUIInput.h"
#include "MyVector2.h"
#include "MyFontManager.h"
#include "MyGUIBufferBuilder.h"
#include "MyGUITexture.h"
#include "MyGUIFont.h"

class MyGUIWidgetManager;

class MyGUIWidgetBase				//绘制接口
{
private:

	//顶点类型

	//高亮类型
	enum HighLightType
	{
		NEVER,
		MOUSEOVER,
		ACTIVE,
		FORCE
	};
	//控件状态
	enum WidgetState
	{
		NORMAL,
		MOUSECLICK,
		MOUSEON,
		DISABLE
	};
	//文本对齐方式
	enum TextAlignment
	{
		LEFT,
		CENTER
	};

private:
	#pragma region style

	MyGUIFont *_normFont;
	MyGUIFont *_highLightFont;
	MyGUIFont *_disableFont;

	MyGUITexture *_normTexture;
	MyGUITexture *_highLightTexture;
	MyGUITexture *_disableTexture;
	MyGUIVertexBuffer* _buffer;

	TextAlignment _textAlignment;
	HighLightType _highLightType;
	#pragma endregion

	#pragma region Info
	
	wchar_t *_name;
	MyVector2 _position;
	MyVector2 _size;

	WidgetState _currentState, _previousState;

	IDirect3DDevice9 *_device;
	#pragma endregion

	#pragma region ConponentMode

	MyGUIWidgetBase *_owner;

	#pragma endregion

	#pragma region MediatorMode
	
	MyGUIWidgetManager *_manager;

	#pragma endregion

protected:
	virtual void DrawHighLight();
	virtual void DrawDisable();
	virtual void DrawNormal();


public:
	MyGUIWidgetBase(IDirect3DDevice9 *device);
	virtual ~MyGUIWidgetBase();

	virtual bool Init(	MyVector2 &pos,
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
						MyGUIWidgetManager* manager);

	#pragma region Set
	//字体设置
	virtual void SetHighLightFont(MyFontManager* fontManager, const wchar_t* name)
	{
		UINT len = wcslen(_name);
		if (name)
		{
			_highLightFont = new MyGUIFont(_device);
			_highLightFont->SetFont(fontManager->CreateMyFont(name, 20, 12, 500));
			_highLightFont->SetColor(D3DCOLOR_XRGB(255, 255, 255));
		}
	}
	virtual void SetNormalFont(MyFontManager* fontManager, const wchar_t* name)
	{
		UINT len = wcslen(_name);
		if (name)
		{
			_normFont = new MyGUIFont(_device);
			_normFont->SetFont(fontManager->CreateMyFont(name, 20, 12, 500));
			_normFont->SetColor(D3DCOLOR_XRGB(120, 120, 120));
		}
	}
	virtual void SetDisableFont(MyFontManager* fontManager, const wchar_t* name) 
	{
		UINT len = wcslen(_name);
		if (name)
		{
			_disableFont = new MyGUIFont(_device);
			_disableFont->SetFont(fontManager->CreateMyFont(name, 20, 12, 500));
			_disableFont->SetColor(D3DCOLOR_XRGB(0, 0, 0));
		}
	}
	//纹理设置
	virtual void SetHighLightTexture() { _highLightTexture->LoadTexture(L"GameMedia\\DisableTexture.png"); }
	virtual void SetNormalTexture() { _normTexture->LoadTexture(L"GameMedia\\NormalTexture.png"); }
	virtual void SetDisableTexture() { _disableTexture->LoadTexture(L"GameMedia\\NormalTexture.png"); }
	virtual void SetHighLightTexture(const wchar_t* path, MyGUIVertexBuffer* buffer)
	{
		_highLightTexture = new MyGUITexture(_device);
		_highLightTexture->LoadTexture(path); 
		_highLightTexture->SetBuffer(buffer);
	}
	virtual void SetNormalTexture(const wchar_t* path, MyGUIVertexBuffer* buffer)
	{
		_normTexture = new MyGUITexture(_device);
		_normTexture->LoadTexture(path); 
		_normTexture->SetBuffer(buffer);
	}
	virtual void SetDisableTexture(const wchar_t* path, MyGUIVertexBuffer* buffer)
	{
		_disableTexture = new MyGUITexture(_device);
		_disableTexture->LoadTexture(path);
		_disableTexture->SetBuffer(buffer);
	}

	virtual void SetTextAligmentLeft() { _textAlignment = TextAlignment::LEFT; }
	virtual void SetTextAligmentCenter() { _textAlignment = TextAlignment::CENTER; }
	
	virtual void SetHighLightTypeNever() { _highLightType = HighLightType::NEVER; }
	virtual void SetHighLightTypeMouseOver() { _highLightType = HighLightType::MOUSEOVER; }
	virtual void SetHighLightTypeActive() { _highLightType = HighLightType::ACTIVE; }
	virtual void SetHighLightTypeForce() { _highLightType = HighLightType::FORCE; }

	void SetStateNormal() 
	{
		_previousState = _currentState;
		_currentState = WidgetState::NORMAL;
	}
	void SetStateMouseClick()
	{
		_previousState = _currentState;
		_currentState = WidgetState::MOUSECLICK;
	}
	void SetStateMouseon()
	{
		_previousState = _currentState;
		_currentState = WidgetState::MOUSEON;
	}
	void SetStateDisable()
	{
		_previousState = _currentState;
		_currentState = WidgetState::DISABLE;
	}

	void SetName(const wchar_t *name) 
	{
		if (name == 0)
			return;
		_name = new wchar_t [wcslen(name)];
		wcscpy(_name, name);
	}

	void SetPosition(MyVector2 &pos){ _position = pos; }
	void SetSize(MyVector2 &size) { _size = size; }
	void SetPosition(const float x, const float y) 
	{
		_position.SetX(x);
		_position.SetY(y);
	}
	void SetSize(const float width, const float height)
	{
		_size.SetX(width);
		_size.SetY(height);
	}

	void ReSetSizeAndPosition(MyVector2 &size, MyVector2 &position) 
	{
		SetPosition(position);
		SetSize(size);
		_buffer->Resize(position.X(),
						position.Y(),
						size.Y(),
						size.X());
	}

	void SetOwner(MyGUIWidgetBase *owner) { _owner = owner; }
	void SetControlManager(MyGUIWidgetManager *manager) { _manager = manager; }
	#pragma endregion

	#pragma region Get
	
	MyVector2 & GetPosition() { return _position; }
	MyVector2 & GetSize() { return _size; }

	MyGUIFont* GetNormalFont() { return _normFont; }
	#pragma endregion

	#pragma region Judge

	bool IsHighlightActive() { return _highLightType == HighLightType::ACTIVE; }
	bool IsHighlightMouseOver() { return _highLightType == HighLightType::MOUSEOVER; }
	bool IsHighlightNever() { return _highLightType == HighLightType::NEVER; }
	bool IsHighlightForce() { return _highLightType == HighLightType::FORCE; }

	bool IsStateNormal() { return _currentState == WidgetState::NORMAL; }
	bool IsStateClick() { return _currentState == WidgetState::MOUSECLICK; }
	bool IsStateMouseOn() { return _currentState == WidgetState::MOUSEON; }
	bool IsStateDisable() { return _currentState == WidgetState::DISABLE; }

	bool IsPreStateNormal() { return _previousState == WidgetState::NORMAL; }
	bool IsPreStateClick() { return _previousState == WidgetState::MOUSECLICK; }
	bool IsPreStateMouseOn() { return _previousState == WidgetState::MOUSEON; }
	bool IsPreStateDisable() { return _previousState == WidgetState::DISABLE; }

	#pragma endregion
	
	#pragma region Component
	
	virtual void AddSubWidget(MyGUIWidgetBase *w){}
	virtual void RemoveWidget(MyGUIWidgetBase *w){}
	virtual void SubWidgetEvent(MyGUIWidgetBase* w) {}
//	virtual MyGUIWidgetBase *GetWidget(unsigned int){}

	#pragma endregion

	#pragma region Mediator
	virtual void Changed();
	#pragma endregion
	
	#pragma region Event
	virtual bool UpdateThis(MyGUIInput::MyGUIMouseEvent &);
	virtual void HandleMouse(MyGUIInput::MyGUIMouseEvent &);
	virtual void HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent &);
	#pragma endregion

	virtual void Draw();

	virtual void Release();
};

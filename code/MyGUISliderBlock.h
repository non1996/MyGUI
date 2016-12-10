#pragma once
#include "MyGUIWidgetBase.h"


class MyGUISliderBlock: public MyGUIWidgetBase
{
private:
	class BlockType
	{
	public:
		virtual void Move(MyGUISliderBlock*, float offset) = 0;
		virtual bool UpdateThis(MyGUISliderBlock*, MyGUIInput::MyGUIMouseEvent&) = 0;
		virtual void HandleMouse(MyGUISliderBlock*, MyGUIInput::MyGUIMouseEvent&) = 0;
		virtual void HandleKeyboard(MyGUISliderBlock*, MyGUIInput::MyGUIKeyboardEvent&) = 0;
	};
	class Horizontal		//水平移动
		: public BlockType
	{
	private:
		static Horizontal* _instance;
	public:
		static Horizontal* Instance();
		virtual void Move(MyGUISliderBlock*, float offset);
		virtual bool UpdateThis(MyGUISliderBlock*, MyGUIInput::MyGUIMouseEvent&);
		virtual void HandleMouse(MyGUISliderBlock*, MyGUIInput::MyGUIMouseEvent&);
		virtual void HandleKeyboard(MyGUISliderBlock*, MyGUIInput::MyGUIKeyboardEvent&);
		static void Release();
	};
	class Vertical			//纵向移动
		: public BlockType
	{
	private:
		static Vertical* _instance;
	public:
		static Vertical* Instance();
		virtual void Move(MyGUISliderBlock*, float offset);
		virtual bool UpdateThis(MyGUISliderBlock*, MyGUIInput::MyGUIMouseEvent&);
		virtual void HandleMouse(MyGUISliderBlock*, MyGUIInput::MyGUIMouseEvent&);
		virtual void HandleKeyboard(MyGUISliderBlock*, MyGUIInput::MyGUIKeyboardEvent&);
		static void Release();
	};

private:
	bool _isMove;
	
	BlockType* _moveType;
	float _maxPosition;
	float _minPosition;

public:
	MyGUISliderBlock(IDirect3DDevice9* device) :MyGUIWidgetBase(device) { _isMove = false; }
	virtual ~MyGUISliderBlock(){}

	virtual bool Init(	MyVector2 &pos,
						MyVector2 &size,
						float maxPos,
						float minPos,
						MyGUIBufferBuilder* b_builder,
						const wchar_t* normTexPath,
						const wchar_t* highLightTexPath,
						const wchar_t* disableTexPath,
						MyGUIWidgetBase* owner,
						MyGUIWidgetManager* manager);

	void SetMoveHorizontal();
	void SetMoveVertical();

	void StartMove() { _isMove = true; }
	void EndMove() { _isMove = false; }
	bool IsMoving() { return _isMove == true; }

	void SetMaxPos(const float mp) { _maxPosition = mp; }
	void SetMinPos(const float mp) { _minPosition = mp; }
	float GetMaxPos() { return _maxPosition; }
	float GetMinPos() { return _minPosition; }

	void Move(float offset);
	void ReSetPosition(MyVector2 & position) { ReSetSizeAndPosition(GetSize(), position); }
//	void ReSetHeight(float height) { ReSetSizeAndPosition(MyVector2(GetSize().X(), height), GetPosition()); }

	virtual bool UpdateThis(MyGUIInput::MyGUIMouseEvent & event);
	virtual void HandleMouse(MyGUIInput::MyGUIMouseEvent & event);
	virtual void HandleKeyboard(MyGUIInput::MyGUIKeyboardEvent & event);
};


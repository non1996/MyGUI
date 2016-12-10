#pragma once

namespace MyGUIInput
{
	class MyGUIMouseEvent
	{
	private:
		enum Event 
		{
			LEFTDOWN,
			LEFTUP,
			RIGHTDOWN,
			RIGHTUP,
			MOVE
		};

		UINT _mouseX, _mouseY;
		Event _eventType;
	public:
		MyGUIMouseEvent() {}
		virtual ~MyGUIMouseEvent(){}

		void SetEventLeftDown(){ _eventType = Event::LEFTDOWN; }
		void SetEventLeftUp() { _eventType = Event::LEFTUP; }
		void SetEventRightDown() { _eventType = Event::RIGHTDOWN; }
		void SetEventRightUp() { _eventType = Event::RIGHTUP; }
		void SetEventMove() { _eventType = Event::MOVE; }

		bool IsLeftDown() { return _eventType == Event::LEFTDOWN; }
		bool IsLeftUp() { return _eventType == Event::LEFTUP; }
		bool IsRightDown() { return _eventType == Event::RIGHTDOWN; }
		bool IsRightUp() { return _eventType == Event::RIGHTUP; }
		bool IsMove() { return _eventType == Event::MOVE; }

		UINT GetX() { return _mouseX; }
		UINT GetY() { return _mouseY; }

		void SetX(UINT x) { _mouseX = x; }
		void SetY(UINT y) { _mouseY = y; }
	};

	class MyGUIKeyboardEvent
	{
		
	private:
		wchar_t _ch;
		
	public:
		enum Event
		{
			ENTER,
			BACKSPACE,
			DEL,
			LEFT,
			UP,
			RIGHT,
			DOWN,
			CHARACTER
		};
		Event _eventType;

		MyGUIKeyboardEvent() { _ch = '\0'; }

		bool IsEnter() const { return _eventType == Event::ENTER; }
		bool IsBackspace() const { return _eventType == Event::BACKSPACE; }
		bool IsDel() const { return _eventType == Event::DEL; }
		bool IsLeft() const { return _eventType == Event::LEFT; }
		bool IsUp() const { return _eventType == Event::UP; }
		bool IsRight() const { return _eventType == Event::RIGHT; }
		bool IsDown() const { return _eventType == Event::DOWN; }
		bool IsCharacter() const { return _eventType == Event::CHARACTER; }

		wchar_t GetChar() const { return _ch; }
		void SetChar(wchar_t ch) { _ch = ch; }
	};
}
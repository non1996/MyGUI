#include "MyGUITextLable.h"



MyGUITextLable::MyGUITextLable(IDirect3DDevice9* device)
	:MyGUIWidgetBase(device)
{
}


MyGUITextLable::~MyGUITextLable()
{
}

bool MyGUITextLable::Init(	MyVector2 & pos,
							MyVector2 & size, 
							const wchar_t * name, 
							MyFontManager * f_manager, 
							const wchar_t * normFontName, 
							MyGUIBufferBuilder * b_builder, 
							const wchar_t * normTexPath, 
							MyGUIWidgetBase * owner, 
							MyGUIWidgetManager * manager)
{
	SetPosition(pos);
	SetSize(size);
	SetName(name);

	SetNormalFont(f_manager, normFontName);

	
	
	if (normTexPath)
		SetNormalTexture(normTexPath, b_builder->BuildBuffer(	GetPosition().X(),
																GetPosition().Y(),
																GetSize().X(),
																GetSize().Y()));


	SetOwner(owner);
	SetControlManager(manager);

	SetHighLightTypeNever();
	SetTextAligmentLeft();
	SetStateNormal();

	return false;
}

void MyGUITextLable::Draw()
{
	DrawNormal();
}


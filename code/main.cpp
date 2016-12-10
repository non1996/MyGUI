
//-----------------------------------������˵����----------------------------------------------
// ��Visual C++����Ϸ����ϵ������Դ����ʮ�� ǳīDirectX�̶̳�ʮ�� ������ϷGUI���棨һ��
// VS2010��
//	2013��11�� Create by ǳī
// ���������زĳ����� �̿�����
// �������ײ������ӣ�http://blog.csdn.net/zhmxy555/article/details/16384009
// �������������ǳī�Ĳ��ͣ�http://blog.csdn.net/zhmxy555
// ǳī������΢���� @ǳī_ë����
//	ʵ�������Ϸ���룺ǳī�������������ọ́�Windows��Ϸ���֮���㿪ʼ�����ҳ�棺 
//					http://blog.csdn.net/poem_qianmo/article/details/12895487
//------------------------------------------------------------------------------------------------


//-----------------------------------���궨�岿�֡�--------------------------------------------
// ����������һЩ������
//------------------------------------------------------------------------------------------------
#define WINDOW_WIDTH	1366						//Ϊ���ڿ�ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڿ��
#define WINDOW_HEIGHT	768							//Ϊ���ڸ߶ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڸ߶�
#define WINDOW_TITLE	 _T("������������Ϩ�����Ϸ�������롿 ǳīDirectX�̶̳�ʮ�� ������ϷGUI���棨һ����������ʾ������ byǳī") //Ϊ���ڱ��ⶨ��ĺ�



//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//	����������������������ͷ�ļ�
//------------------------------------------------------------------------------------------------                                                                                      
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h> 
#include "D3DUtil.h"
#include "D3DGUIClass.h"

//-----------------------------------
//	���ò���
//-----------------------------------
#include "MyGUIInput.h"
#include "MyGUIBufferBuilder.h"
#include "MyFontManager.h"
#include "MyGUIFont.h"
#include "MyGUITexture.h"
#include "MyGUIWidgetBase.h"
#include "MyGUIInputBox.h"
//#include "MyGUISliderBlock.h"
#include "MyGUISlider.h"
#include "MyGUITextContainer.h"
#include "MyGUIWidgetFactoryDef.h"
//-----------------------------------�����ļ��������֡�---------------------------------------
//	���������������������Ŀ��ļ�
//------------------------------------------------------------------------------------------------  
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dinput8.lib")     // ʹ��DirectInput��������Ŀ��ļ���ע��������8
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "winmm.lib") 



// �ذ�Ķ���ṹ
struct CUSTOMVERTEX
{
	FLOAT _x, _y, _z;
	FLOAT _u, _v ;
	CUSTOMVERTEX(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
		: _x(x), _y(y), _z(z), _u(u), _v(v) {}
};
#define D3DFVF_CUSTOMVERTEX  (D3DFVF_XYZ | D3DFVF_TEX1)


//-----------------------------------��ȫ�ֱ����������֡�-------------------------------------
//	������ȫ�ֱ���������
//------------------------------------------------------------------------------------------------
LPDIRECT3DDEVICE9						g_pd3dDevice = NULL;				//Direct3D�豸����
LPD3DXFONT								g_pTextFPS =NULL;    //����COM�ӿ�
LPD3DXFONT								g_pTextAdaperName = NULL;  // �Կ���Ϣ��2D�ı�
LPD3DXFONT								g_pTextHelper = NULL;  // ������Ϣ��2D�ı�
LPD3DXFONT								g_pTextInfor= NULL;  // ������Ϣ��2D�ı�
float									g_FPS= 0.0f;       //һ�������͵ı���������֡����
wchar_t									g_strFPS[50] ={0};    //����֡���ʵ��ַ�����
wchar_t									g_strAdapterName[60] ={0};   //�����Կ����Ƶ��ַ�����

D3DGUIClass								*g_gui = NULL;  //����GUI�����
bool									g_LMBDown = false;      // GUI�е����״̬��Ϣ���������Ƿ��µı�ʶ
int										g_MouseX = 0, g_MouseY = 0;      //�洢����������������
int g_FontID = -1;						//  GUI����������ID


//----������
MyFontManager* f_manager = 0; 
MyGUIBufferBuilder* b_builder = 0; 
MyGUIPushButton* button = 0;
MyGUIPushButton* up = 0;
MyGUIFont* f_fo = 0;
MyGUIWidgetFactoryDef* factory = 0;

MyGUIInput::MyGUIMouseEvent m_mouse;
MyGUIInput::MyGUIKeyboardEvent m_key;

MyGUIInputBox* inputBox = 0;
MyGUISliderBlock* sliderBlock = 0;
MyGUISlider* v_slider = 0;
MyGUISlider* h_slider = 0;
MyGUITextContainer* text = 0;


LPD3DXLINE g_pLine = 0;
D3DXVECTOR2* g_pLineArr = 0;

wchar_t mouseInfo[30];

int delta = 1;
//-----------------------------------��ȫ�ֺ����������֡�-------------------------------------
//	������ȫ�ֺ�����������ֹ��δ�����ı�ʶ��ϵ�д���
//------------------------------------------------------------------------------------------------
LRESULT CALLBACK		WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
HRESULT						Direct3D_Init(HWND hwnd,HINSTANCE hInstance);
HRESULT						Objects_Init();
void								Direct3D_Render( HWND hwnd,FLOAT fTimeDelta);
void								Direct3D_Update( HWND hwnd,FLOAT fTimeDelta);
void								Direct3D_CleanUp( );
float								Get_FPS();
void								HelpText_Render(HWND hwnd);
void								GUICallback(int id, int state);
void DrawMesh();
//-----------------------------------��WinMain( )������--------------------------------------
//	������WindowsӦ�ó������ں��������ǵĳ�������￪ʼ
//------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
{

	//��ʼ���һ�������Ĵ�����
	WNDCLASSEX wndClass={0} ;				//��WINDCLASSEX������һ�������࣬����wndClassʵ������WINDCLASSEX������֮�󴰿ڵĸ����ʼ��    
	wndClass.cbSize = sizeof( WNDCLASSEX ) ;	//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;				//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance = hInstance;				//ָ���������ڹ��̵ĳ����ʵ�������
	wndClass.hIcon=(HICON)::LoadImage(NULL,_T("GameMedia\\icon.ico"),IMAGE_ICON,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE); //��ȫ�ֵ�::LoadImage�����ӱ��ؼ����Զ���icoͼ��
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );    //ָ��������Ĺ������
	wndClass.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);  //ΪhbrBackground��Աָ��һ����ɫ��ˢ���
	wndClass.lpszMenuName = NULL;						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndClass.lpszClassName = _T("ForTheDreamOfGameDevelop");		//��һ���Կ���ֹ���ַ�����ָ������������֡�

	if( !RegisterClassEx( &wndClass ) )				//����괰�ں���Ҫ�Դ��������ע�ᣬ�������ܴ��������͵Ĵ���
		return -1;		

	HWND hwnd = CreateWindow( _T("ForTheDreamOfGameDevelop"),WINDOW_TITLE,			//ϲ���ּ��Ĵ������ں���CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL );


	//Direct3D��Դ�ĳ�ʼ��������ʧ����messagebox������ʾ
	if (!(S_OK==Direct3D_Init (hwnd,hInstance)))
	{
		MessageBox(hwnd, _T("Direct3D��ʼ��ʧ��~��"), _T("ǳī����Ϣ����"), 0); //ʹ��MessageBox����������һ����Ϣ���� 
	}
//	PlaySound(L"GameMedia\\Heart - �̿�����.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);   //ѭ�����ű�������

	MoveWindow(hwnd,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,true);   //����������ʾʱ��λ�ã��������Ͻ�λ����Ļ���꣨200��10����
	ShowWindow( hwnd, nShowCmd );    //����Win32����ShowWindow����ʾ����
	UpdateWindow(hwnd);  //�Դ��ڽ��и��£��������������·���Ҫװ��һ��


	//��Ϣѭ������
	MSG msg = { 0 };  //��ʼ��msg
	while( msg.message != WM_QUIT )			//ʹ��whileѭ��
	{
		static FLOAT fLastTime  = (float)::timeGetTime();
		static FLOAT fCurrTime  = (float)::timeGetTime();
		static FLOAT fTimeDelta = 0.0f;
		fCurrTime  = (float)::timeGetTime();
		fTimeDelta = (fCurrTime - fLastTime) / 1000.0f;
		fLastTime  = fCurrTime;

		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			TranslateMessage( &msg );		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage( &msg );		//�ú����ַ�һ����Ϣ�����ڳ���
		}
		else
		{
			Direct3D_Update(hwnd,fTimeDelta);         //���ø��º��������л���ĸ���
			Direct3D_Render(hwnd,fTimeDelta);			//������Ⱦ���������л������Ⱦ			
		}
	}

	UnregisterClass(_T("ForTheDreamOfGameDevelop"), wndClass.hInstance);
	return 0;  
}


//-----------------------------------��WndProc( )������--------------------------------------
//	���������ڹ��̺���WndProc,�Դ�����Ϣ���д���
//------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )   //���ڹ��̺���WndProc
{
	bool hasMouse = false;
	switch( message )				//switch��俪ʼ
	{
	case WM_SIZE:					//���ر�����
	{
		LONG_PTR Style = ::GetWindowLongPtr(hwnd, GWL_STYLE);
		Style = Style &~WS_CAPTION &~WS_SYSMENU &~WS_SIZEBOX;
		::SetWindowLongPtr(hwnd, GWL_STYLE, Style);
		break;
	}
	case WM_PAINT:					 // �ͻ����ػ���Ϣ
		Direct3D_Render(hwnd,0.0f);          //����Direct3D_Render���������л���Ļ���
		ValidateRect(hwnd, NULL);   // ���¿ͻ�������ʾ
		break;									//������switch���

	case WM_KEYDOWN:                // ���̰�����Ϣ
		if (wParam == VK_ESCAPE)    // ESC��
			DestroyWindow(hwnd);    // ���ٴ���, ������һ��WM_DESTROY��Ϣ
		break;
	case WM_DESTROY:				//����������Ϣ
		Direct3D_CleanUp();     //����Direct3D_CleanUp����������COM�ӿڶ���
		PostQuitMessage( 0 );		//��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;						//������switch���

	case WM_KEYUP:
		if(wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == VK_UP)
		{
			m_key._eventType = MyGUIInput::MyGUIKeyboardEvent::Event::CHARACTER;
			m_key.SetChar('A');
			inputBox->HandleKeyBoard(m_key);
		}
		if (wParam == VK_DOWN)
		{
			m_key._eventType = MyGUIInput::MyGUIKeyboardEvent::Event::CHARACTER;
			m_key.SetChar('B');
			inputBox->HandleKeyBoard(m_key);
		}
		if (wParam == VK_LEFT)
		{
			m_key._eventType = MyGUIInput::MyGUIKeyboardEvent::Event::LEFT;
			inputBox->HandleKeyBoard(m_key);
		}
		if (wParam == VK_RIGHT)
		{
			m_key._eventType = MyGUIInput::MyGUIKeyboardEvent::Event::RIGHT;
			inputBox->HandleKeyBoard(m_key);
		}
		if (wParam == VK_BACK)
		{
			m_key._eventType = MyGUIInput::MyGUIKeyboardEvent::Event::BACKSPACE;
			inputBox->HandleKeyBoard(m_key);
		}
		if (wParam == VK_DELETE)
		{
			m_key._eventType = MyGUIInput::MyGUIKeyboardEvent::Event::DEL;
			inputBox->HandleKeyBoard(m_key);
		}
		break;

	case WM_LBUTTONDOWN:
		g_LMBDown = true;

		m_mouse.SetX(LOWORD(lParam));
		m_mouse.SetY(HIWORD(lParam));
		m_mouse.SetEventLeftDown();
		button->HandleMouse(m_mouse);
		inputBox->HandleMouse(m_mouse);
		sliderBlock->HandleMouse(m_mouse);
		v_slider->HandleMouse(m_mouse);
		h_slider->HandleMouse(m_mouse);
		break;

	case WM_LBUTTONUP:
		g_LMBDown = false;
		
		m_mouse.SetX(LOWORD(lParam));
		m_mouse.SetY(HIWORD(lParam));
		m_mouse.SetEventLeftUp();
		button->HandleMouse(m_mouse);
		inputBox->HandleMouse(m_mouse);
		sliderBlock->HandleMouse(m_mouse);
		v_slider->HandleMouse(m_mouse);
		h_slider->HandleMouse(m_mouse);
		break;

	case WM_MOUSEMOVE:
		g_MouseX = LOWORD (lParam);
		g_MouseY = HIWORD (lParam);
		
		m_mouse.SetX(LOWORD(lParam));
		m_mouse.SetY(HIWORD(lParam));
		m_mouse.SetEventMove();
		button->HandleMouse(m_mouse);
		inputBox->HandleMouse(m_mouse);
		sliderBlock->HandleMouse(m_mouse);
		v_slider->HandleMouse(m_mouse);
		h_slider->HandleMouse(m_mouse);
		break;

	default:						//������case�����������ϣ���ִ�и�default���
		return DefWindowProc( hwnd, message, wParam, lParam );		//����ȱʡ�Ĵ��ڹ�����ΪӦ�ó���û�д���Ĵ�����Ϣ�ṩȱʡ�Ĵ���
	}

	return 0;					//�����˳�
}


//-----------------------------------��Direct3D_Init( )������----------------------------------
//	������Direct3D��ʼ������������Direct3D�ĳ�ʼ��
//------------------------------------------------------------------------------------------------
HRESULT Direct3D_Init(HWND hwnd,HINSTANCE hInstance)
{

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮һ�����ӿڡ�������Direct3D�ӿڶ���, �Ա��ø�Direct3D���󴴽�Direct3D�豸����
	//--------------------------------------------------------------------------------------
	LPDIRECT3D9  pD3D = NULL; //Direct3D�ӿڶ���Ĵ���
	if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ) //��ʼ��Direct3D�ӿڶ��󣬲�����DirectX�汾Э��
		return E_FAIL;

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮��,ȡ��Ϣ������ȡӲ���豸��Ϣ
	//--------------------------------------------------------------------------------------
	D3DCAPS9 caps; int vp = 0;
	if( FAILED( pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps ) ) )
	{
		return E_FAIL;
	}
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //֧��Ӳ���������㣬���ǾͲ���Ӳ���������㣬���׵�
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //��֧��Ӳ���������㣬����ֻ�ò��������������

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮���������ݡ������D3DPRESENT_PARAMETERS�ṹ��
	//--------------------------------------------------------------------------------------
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth            = WINDOW_WIDTH;
	d3dpp.BackBufferHeight           = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 2;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = hwnd;
	d3dpp.Windowed                   = true;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮�ģ����豸��������Direct3D�豸�ӿ�
	//--------------------------------------------------------------------------------------
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
		hwnd, vp, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;


	//��ȡ�Կ���Ϣ��g_strAdapterName�У������Կ�����֮ǰ���ϡ���ǰ�Կ��ͺţ����ַ���
	wchar_t TempName[60]=L"��ǰ�Կ��ͺţ�";   //����һ����ʱ�ַ������ҷ����˰�"��ǰ�Կ��ͺţ�"�ַ����������ǵ�Ŀ���ַ�����
	D3DADAPTER_IDENTIFIER9 Adapter;  //����һ��D3DADAPTER_IDENTIFIER9�ṹ�壬���ڴ洢�Կ���Ϣ
	pD3D->GetAdapterIdentifier(0,0,&Adapter);//����GetAdapterIdentifier����ȡ�Կ���Ϣ
	int len = MultiByteToWideChar(CP_ACP,0, Adapter.Description, -1, NULL, 0);//�Կ����������Ѿ���Adapter.Description���ˣ�������Ϊchar���ͣ�����Ҫ����תΪwchar_t����
	MultiByteToWideChar(CP_ACP, 0, Adapter.Description, -1, g_strAdapterName, len);//�ⲽ������ɺ�g_strAdapterName�о�Ϊ��ǰ���ǵ��Կ���������wchar_t���ַ�����
	wcscat_s(TempName,g_strAdapterName);//�ѵ�ǰ���ǵ��Կ����ӵ�����ǰ�Կ��ͺţ����ַ������棬�������TempName��
	wcscpy_s(g_strAdapterName,TempName);//��TempName�еĽ��������ȫ�ֱ���g_strAdapterName�У��󹦸��~

	if(!(S_OK==Objects_Init())) return E_FAIL;

	SAFE_RELEASE(pD3D) //LPDIRECT3D9�ӿڶ����ʹ����ɣ����ǽ����ͷŵ�

		return S_OK;
}


//-----------------------------------��Object_Init( )������--------------------------------------
//	��������Ⱦ��Դ��ʼ���������ڴ˺����н���Ҫ����Ⱦ���������Դ�ĳ�ʼ��
//--------------------------------------------------------------------------------------------------
HRESULT Objects_Init()
{
	//��������
	D3DXCreateFont(g_pd3dDevice, 36, 0, 0, 1000, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Calibri"), &g_pTextFPS);
	D3DXCreateFont(g_pd3dDevice, 20, 0, 1000, 0, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"��������", &g_pTextAdaperName); 
	D3DXCreateFont(g_pd3dDevice, 23, 0, 1000, 0, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"΢���ź�", &g_pTextHelper); 
	D3DXCreateFont(g_pd3dDevice, 26, 0, 1000, 0, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"����", &g_pTextInfor); 
//	g_pTextFPS = f_manager->CreateCalibri(g_pd3dDevice);
//	g_pTextAdaperName = f_manager->CreateHuaWen(g_pd3dDevice);
//	g_pTextHelper = f_manager->CreateYAHei(g_pd3dDevice);
//	g_pTextInfor = f_manager->CreateHeiTi(g_pd3dDevice);

	//���������������
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);


//-----------------------------------��GUIϵͳ��ش��롿-------------------------------
	// ����GUIϵͳ
	g_gui = new D3DGUIClass(g_pd3dDevice, WINDOW_WIDTH, WINDOW_HEIGHT);
	if(!g_gui) return false;

	// ��ӱ���ͼƬ
	if(!g_gui->AddBackground(L"GameMedia\\Assassins creed.jpg")) return false;

	// �������
	if(!g_gui->CreateTextFont(L"΢���ź�", 28, &g_FontID)) return false;


	// ��Ӿ�̬�ı���GUI��
	if(!g_gui->AddStaticText(STATIC_ID_1, L"Version ǳī1.0��",
		1170, 735, D3DCOLOR_XRGB(55,155,255), g_FontID)) return false;

	if(!g_gui->AddStaticText(STATIC_ID_2, L"ǳīDirectX�̵̳����� ֮ ������ϷGUI����",
		500, 10, D3DCOLOR_XRGB(255,255,255), g_FontID)) return false;


	// ���4����ť���ֱ��ǿ�ʼ��Ϸ��������ȣ�ѡ����˳���Ϸ��ÿ����ť��Ӧ3��ͼ
	if(!g_gui->AddButton(BUTTON_ID_1, 650, 340, L"GameMedia\\startUp.png",
		L"GameMedia\\StartOver.png", L"GameMedia\\startDown.png")) return false;

	if(!g_gui->AddButton(BUTTON_ID_2, 650, 385, L"GameMedia\\loadUp.png",
		L"GameMedia\\loadOver.png", L"GameMedia\\loadDown.png")) return false;

	if(!g_gui->AddButton(BUTTON_ID_3, 650, 430, L"GameMedia\\optionsUp.png",
		L"GameMedia\\optionsOver.png", L"GameMedia\\optionsDown.png")) return false;

	if(!g_gui->AddButton(BUTTON_ID_4, 650, 475, L"GameMedia\\quitUp.png",
		L"GameMedia\\quitOver.png", L"GameMedia\\quitDown.png")) return false;

	//-----------------------------------------------------------------
	//	����
	//-----------------------------------------------------------------
	D3DXCreateLine(g_pd3dDevice, &g_pLine);
	g_pLineArr = new D3DXVECTOR2[2];

	f_fo = new MyGUIFont(g_pd3dDevice);
	f_fo->SetFont(g_pTextFPS);
	f_fo->SetColor(D3DCOLOR_XRGB(0, 0, 0));

	f_manager = MyFontManager::Instance(g_pd3dDevice);
	b_builder = MyGUIBufferBuilder::Instance(g_pd3dDevice);
	factory = MyGUIWidgetFactoryDef::Instance(g_pd3dDevice);

	v_slider = factory->MakeVerticalSlider(MyVector2(100, 100),MyVector2(25, 300));
	h_slider = factory->MakeHorizontalSlider(MyVector2(100, 600), MyVector2(300, 25));
	button = factory->MakePushButton(MyVector2(50, 50), MyVector2(50, 25), L"+1S");
	inputBox = factory->MakeInputBox(MyVector2(200, 200), MyVector2(200, 30));

	sliderBlock = new MyGUISliderBlock(g_pd3dDevice);
	sliderBlock->Init(	MyVector2(300, 300),
						MyVector2(25, 40),
						500,
						100,
						b_builder,
						L"GameMedia\\NormalTexture.bmp",
						L"GameMedia\\highLightTexture.bmp",
						L"GameMedia\\DisableTexture.bmp",
						0,
						0);
	sliderBlock->SetMoveVertical();

	text = new MyGUITextContainer(g_pd3dDevice);
	text->Init(			MyVector2(600, 100),
						MyVector2(600, 600),
						f_manager,
						L"����",
						b_builder,
						L"GameMedia\\NormalTexture.bmp",
						L"GameMedia\\NormalTexture.bmp",
						L"GameMedia\\NormalTexture.bmp",
						"content.txt",
						0,
						0
				);
	return S_OK;
}


void GUICallback(int id, int state)
{
	switch(id)
	{
	case BUTTON_ID_1: 
		//����ʼ��Ϸ����ť����ش���ʵ��
		break;
	case BUTTON_ID_2:
		//��������Ϸ����ť����ش���ʵ��
		break;
	case BUTTON_ID_3:
		//��ѡ���ť����ش���ʵ��
		break;
	case BUTTON_ID_4:
		//���������˳���ť�����˳�����
		if(state == UGP_BUTTON_DOWN) PostQuitMessage(0);
		break;
	}
}


//-----------------------------------��Direct3D_Update( )������--------------------------------
//	���������Ǽ�ʱ��Ⱦ���뵫����Ҫ��ʱ���õģ��簴���������ĸ��ģ�����������
//--------------------------------------------------------------------------------------------------
void	Direct3D_Update( HWND hwnd,FLOAT fTimeDelta)
{
	//GUI��ʵ����ʱ����Ҫ������д����
}



//-----------------------------------��Direct3D_Render( )������-------------------------------
//	������ʹ��Direct3D������Ⱦ
//--------------------------------------------------------------------------------------------------
void Direct3D_Render(HWND hwnd,FLOAT fTimeDelta)
{
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮һ������������
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, D3DCOLOR_XRGB(100, 255, 255), 1.0f, 0);

	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮��������ʼ����
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->BeginScene();                     // ��ʼ����

	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮��������ʽ����
	//--------------------------------------------------------------------------------------


	// �������ȾGUIϵͳ
	ProcessGUI(g_gui, g_LMBDown, g_MouseX, g_MouseY, GUICallback);
	

	//-----------------------------������������Ϣ��-----------------------------
	HelpText_Render(hwnd);
	button->Draw();
	inputBox->Draw();
	sliderBlock->Draw();
	text->Draw();
	v_slider->Draw();
	h_slider->Draw();
//	up->Draw();
	DrawMesh();
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮�ġ�����������
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->EndScene();                       // ��������
	//--------------------------------------------------------------------------------------
	// ��Direct3D��Ⱦ�岽��֮�塿����ʾ��ת
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);  // ��ת����ʾ

}


//-----------------------------------��HelpText_Render( )������-------------------------------
//	��������װ�˰�����Ϣ�ĺ���
//--------------------------------------------------------------------------------------------------
void HelpText_Render(HWND hwnd)
{
	//����һ�����Σ����ڻ�ȡ�����ھ���
	RECT formatRect;
	GetClientRect(hwnd, &formatRect);

	//�ڴ������ϽǴ�����ʾÿ��֡��
	formatRect.top = 5;
	int charCount = swprintf_s(g_strFPS, 20, _T("FPS:%0.3f"), Get_FPS() );
	g_pTextFPS->DrawText(NULL, g_strFPS, charCount , &formatRect, DT_TOP | DT_RIGHT, D3DCOLOR_RGBA(0,239,136,255));

	wchar_t g_strTest[20];
	int testCount = swprintf_s(g_strTest, 20, L"fuck you");
//**************************����
//	static int i = 0;
//	if ((i++) >= 255)
//		i = 0;

	static wchar_t info[30];
	ZeroMemory(info, sizeof(info));
	static float xx = 0, yy = 0;
	xx = (inputBox->GetSize()).X();
	yy = (inputBox->GetSize()).Y();
	wsprintf(info, L"%d, %d", (int)xx, (int)yy);

	f_fo->SetColor(D3DCOLOR_XRGB(0, 0, 0));
	f_fo->Draw(info, 100, 300, 300, 500);

	ZeroMemory(mouseInfo, sizeof(mouseInfo));
	wsprintf(mouseInfo, L"%d, %d", (int)g_MouseX, (int)g_MouseY);
	f_fo->Draw(mouseInfo, 400, 400, 700, 500);
//**************************
	//��ʾ�Կ�������
	g_pTextAdaperName->DrawText(NULL,g_strAdapterName, -1, &formatRect, 
		DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
}


//-----------------------------------��Get_FPS( )������------------------------------------------
//	���������ڼ���ÿ��֡���ʵ�һ������
//--------------------------------------------------------------------------------------------------
float Get_FPS()
{

	//�����ĸ���̬����
	static float  fps = 0; //������Ҫ�����FPSֵ
	static int    frameCount = 0;//֡��
	static float  currentTime =0.0f;//��ǰʱ��
	static float  lastTime = 0.0f;//����ʱ��

	frameCount++;//ÿ����һ��Get_FPS()������֡������1
	currentTime = timeGetTime()*0.001f;//��ȡϵͳʱ�䣬����timeGetTime�������ص����Ժ���Ϊ��λ��ϵͳʱ�䣬������Ҫ����0.001���õ���λΪ���ʱ��

	//�����ǰʱ���ȥ����ʱ�������1���ӣ��ͽ���һ��FPS�ļ���ͳ���ʱ��ĸ��£�����֡��ֵ����
	if(currentTime - lastTime > 1.0f) //��ʱ�������1����
	{
		fps = (float)frameCount /(currentTime - lastTime);//������1���ӵ�FPSֵ
		lastTime = currentTime; //����ǰʱ��currentTime��������ʱ��lastTime����Ϊ��һ��Ļ�׼ʱ��
		frameCount    = 0;//������֡��frameCountֵ����
	}

	return fps;
}



//-----------------------------------��Direct3D_CleanUp( )������--------------------------------
//	��������Direct3D����Դ���������ͷ�COM�ӿڶ���
//---------------------------------------------------------------------------------------------------
void Direct3D_CleanUp()
{
	//�ͷ�COM�ӿڶ���
	SAFE_RELEASE(g_pd3dDevice);
	SAFE_RELEASE(g_pTextFPS)
	SAFE_RELEASE(g_pd3dDevice)
	SAFE_DELETE(g_gui)
}



void DrawMesh()
{
	g_pLine->SetWidth(1.0f);
	g_pLine->SetAntialias(TRUE);
	for (UINT i = 20; i < WINDOW_WIDTH; i += 20)
	{
		g_pLineArr[0].x = g_pLineArr[1].x = i;
		g_pLineArr[0].y = 0;
		g_pLineArr[1].y = WINDOW_HEIGHT;

		g_pLine->Draw(g_pLineArr, 2, D3DCOLOR_XRGB(255, 0, 0));
	}
	for (UINT i = 20; i < WINDOW_HEIGHT; i += 20)
	{
		g_pLineArr[0].x = 0;
		g_pLineArr[1].x = WINDOW_WIDTH;
		g_pLineArr[0].y = g_pLineArr[1].y = i;

		g_pLine->Draw(g_pLineArr, 2, D3DCOLOR_XRGB(255, 0, 0));
	}
}
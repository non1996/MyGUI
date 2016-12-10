
//-----------------------------------【程序说明】----------------------------------------------
// 【Visual C++】游戏开发系列配套源码五十六 浅墨DirectX教程二十三 打造游戏GUI界面（一）
// VS2010版
//	2013年11月 Create by 浅墨
// 背景音乐素材出处： 刺客信条
// 程序配套博文链接：http://blog.csdn.net/zhmxy555/article/details/16384009
// 更多内容请访问浅墨的博客：http://blog.csdn.net/zhmxy555
// 浅墨的新浪微博： @浅墨_毛星云
//	实现你的游戏梦想：浅墨的著作《逐梦旅程：Windows游戏编程之从零开始》简介页面： 
//					http://blog.csdn.net/poem_qianmo/article/details/12895487
//------------------------------------------------------------------------------------------------


//-----------------------------------【宏定义部分】--------------------------------------------
// 描述：定义一些辅助宏
//------------------------------------------------------------------------------------------------
#define WINDOW_WIDTH	1366						//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define WINDOW_HEIGHT	768							//为窗口高度定义的宏，以方便在此处修改窗口高度
#define WINDOW_TITLE	 _T("【致我们永不熄灭的游戏开发梦想】 浅墨DirectX教程二十三 打造游戏GUI界面（一）博文配套示例程序 by浅墨") //为窗口标题定义的宏



//-----------------------------------【头文件包含部分】---------------------------------------
//	描述：包含程序所依赖的头文件
//------------------------------------------------------------------------------------------------                                                                                      
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h> 
#include "D3DUtil.h"
#include "D3DGUIClass.h"

//-----------------------------------
//	自用测试
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
//-----------------------------------【库文件包含部分】---------------------------------------
//	描述：包含程序所依赖的库文件
//------------------------------------------------------------------------------------------------  
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "dinput8.lib")     // 使用DirectInput必须包含的库文件，注意这里有8
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "winmm.lib") 



// 地板的顶点结构
struct CUSTOMVERTEX
{
	FLOAT _x, _y, _z;
	FLOAT _u, _v ;
	CUSTOMVERTEX(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
		: _x(x), _y(y), _z(z), _u(u), _v(v) {}
};
#define D3DFVF_CUSTOMVERTEX  (D3DFVF_XYZ | D3DFVF_TEX1)


//-----------------------------------【全局变量声明部分】-------------------------------------
//	描述：全局变量的声明
//------------------------------------------------------------------------------------------------
LPDIRECT3DDEVICE9						g_pd3dDevice = NULL;				//Direct3D设备对象
LPD3DXFONT								g_pTextFPS =NULL;    //字体COM接口
LPD3DXFONT								g_pTextAdaperName = NULL;  // 显卡信息的2D文本
LPD3DXFONT								g_pTextHelper = NULL;  // 帮助信息的2D文本
LPD3DXFONT								g_pTextInfor= NULL;  // 绘制信息的2D文本
float									g_FPS= 0.0f;       //一个浮点型的变量，代表帧速率
wchar_t									g_strFPS[50] ={0};    //包含帧速率的字符数组
wchar_t									g_strAdapterName[60] ={0};   //包含显卡名称的字符数组

D3DGUIClass								*g_gui = NULL;  //创建GUI类对象
bool									g_LMBDown = false;      // GUI中的鼠标状态信息，鼠标左键是否按下的标识
int										g_MouseX = 0, g_MouseY = 0;      //存储鼠标坐标的两个变量
int g_FontID = -1;						//  GUI中字体对象的ID


//----测试用
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
//-----------------------------------【全局函数声明部分】-------------------------------------
//	描述：全局函数声明，防止“未声明的标识”系列错误
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
//-----------------------------------【WinMain( )函数】--------------------------------------
//	描述：Windows应用程序的入口函数，我们的程序从这里开始
//------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
{

	//开始设计一个完整的窗口类
	WNDCLASSEX wndClass={0} ;				//用WINDCLASSEX定义了一个窗口类，即用wndClass实例化了WINDCLASSEX，用于之后窗口的各项初始化    
	wndClass.cbSize = sizeof( WNDCLASSEX ) ;	//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;				//设置指向窗口过程函数的指针
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance = hInstance;				//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon=(HICON)::LoadImage(NULL,_T("GameMedia\\icon.ico"),IMAGE_ICON,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE); //从全局的::LoadImage函数从本地加载自定义ico图标
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );    //指定窗口类的光标句柄。
	wndClass.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);  //为hbrBackground成员指定一个灰色画刷句柄
	wndClass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = _T("ForTheDreamOfGameDevelop");		//用一个以空终止的字符串，指定窗口类的名字。

	if( !RegisterClassEx( &wndClass ) )				//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;		

	HWND hwnd = CreateWindow( _T("ForTheDreamOfGameDevelop"),WINDOW_TITLE,			//喜闻乐见的创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL );


	//Direct3D资源的初始化，调用失败用messagebox予以显示
	if (!(S_OK==Direct3D_Init (hwnd,hInstance)))
	{
		MessageBox(hwnd, _T("Direct3D初始化失败~！"), _T("浅墨的消息窗口"), 0); //使用MessageBox函数，创建一个消息窗口 
	}
//	PlaySound(L"GameMedia\\Heart - 刺客信条.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);   //循环播放背景音乐

	MoveWindow(hwnd,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,true);   //调整窗口显示时的位置，窗口左上角位于屏幕坐标（200，10）处
	ShowWindow( hwnd, nShowCmd );    //调用Win32函数ShowWindow来显示窗口
	UpdateWindow(hwnd);  //对窗口进行更新，就像我们买了新房子要装修一样


	//消息循环过程
	MSG msg = { 0 };  //初始化msg
	while( msg.message != WM_QUIT )			//使用while循环
	{
		static FLOAT fLastTime  = (float)::timeGetTime();
		static FLOAT fCurrTime  = (float)::timeGetTime();
		static FLOAT fTimeDelta = 0.0f;
		fCurrTime  = (float)::timeGetTime();
		fTimeDelta = (fCurrTime - fLastTime) / 1000.0f;
		fLastTime  = fCurrTime;

		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage( &msg );		//将虚拟键消息转换为字符消息
			DispatchMessage( &msg );		//该函数分发一个消息给窗口程序。
		}
		else
		{
			Direct3D_Update(hwnd,fTimeDelta);         //调用更新函数，进行画面的更新
			Direct3D_Render(hwnd,fTimeDelta);			//调用渲染函数，进行画面的渲染			
		}
	}

	UnregisterClass(_T("ForTheDreamOfGameDevelop"), wndClass.hInstance);
	return 0;  
}


//-----------------------------------【WndProc( )函数】--------------------------------------
//	描述：窗口过程函数WndProc,对窗口消息进行处理
//------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )   //窗口过程函数WndProc
{
	bool hasMouse = false;
	switch( message )				//switch语句开始
	{
	case WM_SIZE:					//隐藏标题栏
	{
		LONG_PTR Style = ::GetWindowLongPtr(hwnd, GWL_STYLE);
		Style = Style &~WS_CAPTION &~WS_SYSMENU &~WS_SIZEBOX;
		::SetWindowLongPtr(hwnd, GWL_STYLE, Style);
		break;
	}
	case WM_PAINT:					 // 客户区重绘消息
		Direct3D_Render(hwnd,0.0f);          //调用Direct3D_Render函数，进行画面的绘制
		ValidateRect(hwnd, NULL);   // 更新客户区的显示
		break;									//跳出该switch语句

	case WM_KEYDOWN:                // 键盘按下消息
		if (wParam == VK_ESCAPE)    // ESC键
			DestroyWindow(hwnd);    // 销毁窗口, 并发送一条WM_DESTROY消息
		break;
	case WM_DESTROY:				//窗口销毁消息
		Direct3D_CleanUp();     //调用Direct3D_CleanUp函数，清理COM接口对象
		PostQuitMessage( 0 );		//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;						//跳出该switch语句

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

	default:						//若上述case条件都不符合，则执行该default语句
		return DefWindowProc( hwnd, message, wParam, lParam );		//调用缺省的窗口过程来为应用程序没有处理的窗口消息提供缺省的处理。
	}

	return 0;					//正常退出
}


//-----------------------------------【Direct3D_Init( )函数】----------------------------------
//	描述：Direct3D初始化函数，进行Direct3D的初始化
//------------------------------------------------------------------------------------------------
HRESULT Direct3D_Init(HWND hwnd,HINSTANCE hInstance)
{

	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之一，创接口】：创建Direct3D接口对象, 以便用该Direct3D对象创建Direct3D设备对象
	//--------------------------------------------------------------------------------------
	LPDIRECT3D9  pD3D = NULL; //Direct3D接口对象的创建
	if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ) //初始化Direct3D接口对象，并进行DirectX版本协商
		return E_FAIL;

	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之二,取信息】：获取硬件设备信息
	//--------------------------------------------------------------------------------------
	D3DCAPS9 caps; int vp = 0;
	if( FAILED( pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps ) ) )
	{
		return E_FAIL;
	}
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //支持硬件顶点运算，我们就采用硬件顶点运算，妥妥的
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //不支持硬件顶点运算，无奈只好采用软件顶点运算

	//--------------------------------------------------------------------------------------
	// 【Direct3D初始化四步曲之三，填内容】：填充D3DPRESENT_PARAMETERS结构体
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
	// 【Direct3D初始化四步曲之四，创设备】：创建Direct3D设备接口
	//--------------------------------------------------------------------------------------
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
		hwnd, vp, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;


	//获取显卡信息到g_strAdapterName中，并在显卡名称之前加上“当前显卡型号：”字符串
	wchar_t TempName[60]=L"当前显卡型号：";   //定义一个临时字符串，且方便了把"当前显卡型号："字符串引入我们的目的字符串中
	D3DADAPTER_IDENTIFIER9 Adapter;  //定义一个D3DADAPTER_IDENTIFIER9结构体，用于存储显卡信息
	pD3D->GetAdapterIdentifier(0,0,&Adapter);//调用GetAdapterIdentifier，获取显卡信息
	int len = MultiByteToWideChar(CP_ACP,0, Adapter.Description, -1, NULL, 0);//显卡名称现在已经在Adapter.Description中了，但是其为char类型，我们要将其转为wchar_t类型
	MultiByteToWideChar(CP_ACP, 0, Adapter.Description, -1, g_strAdapterName, len);//这步操作完成后，g_strAdapterName中就为当前我们的显卡类型名的wchar_t型字符串了
	wcscat_s(TempName,g_strAdapterName);//把当前我们的显卡名加到“当前显卡型号：”字符串后面，结果存在TempName中
	wcscpy_s(g_strAdapterName,TempName);//把TempName中的结果拷贝到全局变量g_strAdapterName中，大功告成~

	if(!(S_OK==Objects_Init())) return E_FAIL;

	SAFE_RELEASE(pD3D) //LPDIRECT3D9接口对象的使命完成，我们将其释放掉

		return S_OK;
}


//-----------------------------------【Object_Init( )函数】--------------------------------------
//	描述：渲染资源初始化函数，在此函数中进行要被渲染的物体的资源的初始化
//--------------------------------------------------------------------------------------------------
HRESULT Objects_Init()
{
	//创建字体
	D3DXCreateFont(g_pd3dDevice, 36, 0, 0, 1000, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Calibri"), &g_pTextFPS);
	D3DXCreateFont(g_pd3dDevice, 20, 0, 1000, 0, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"华文中宋", &g_pTextAdaperName); 
	D3DXCreateFont(g_pd3dDevice, 23, 0, 1000, 0, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"微软雅黑", &g_pTextHelper); 
	D3DXCreateFont(g_pd3dDevice, 26, 0, 1000, 0, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"黑体", &g_pTextInfor); 
//	g_pTextFPS = f_manager->CreateCalibri(g_pd3dDevice);
//	g_pTextAdaperName = f_manager->CreateHuaWen(g_pd3dDevice);
//	g_pTextHelper = f_manager->CreateYAHei(g_pd3dDevice);
//	g_pTextInfor = f_manager->CreateHeiTi(g_pd3dDevice);

	//设置纹理采样参数
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);


//-----------------------------------【GUI系统相关代码】-------------------------------
	// 创建GUI系统
	g_gui = new D3DGUIClass(g_pd3dDevice, WINDOW_WIDTH, WINDOW_HEIGHT);
	if(!g_gui) return false;

	// 添加背景图片
	if(!g_gui->AddBackground(L"GameMedia\\Assassins creed.jpg")) return false;

	// 添加字体
	if(!g_gui->CreateTextFont(L"微软雅黑", 28, &g_FontID)) return false;


	// 添加静态文本到GUI中
	if(!g_gui->AddStaticText(STATIC_ID_1, L"Version 浅墨1.0版",
		1170, 735, D3DCOLOR_XRGB(55,155,255), g_FontID)) return false;

	if(!g_gui->AddStaticText(STATIC_ID_2, L"浅墨DirectX教程第三季 之 打造游戏GUI界面",
		500, 10, D3DCOLOR_XRGB(255,255,255), g_FontID)) return false;


	// 添加4个按钮，分别是开始游戏，载入进度，选项和退出游戏，每个按钮对应3幅图
	if(!g_gui->AddButton(BUTTON_ID_1, 650, 340, L"GameMedia\\startUp.png",
		L"GameMedia\\StartOver.png", L"GameMedia\\startDown.png")) return false;

	if(!g_gui->AddButton(BUTTON_ID_2, 650, 385, L"GameMedia\\loadUp.png",
		L"GameMedia\\loadOver.png", L"GameMedia\\loadDown.png")) return false;

	if(!g_gui->AddButton(BUTTON_ID_3, 650, 430, L"GameMedia\\optionsUp.png",
		L"GameMedia\\optionsOver.png", L"GameMedia\\optionsDown.png")) return false;

	if(!g_gui->AddButton(BUTTON_ID_4, 650, 475, L"GameMedia\\quitUp.png",
		L"GameMedia\\quitOver.png", L"GameMedia\\quitDown.png")) return false;

	//-----------------------------------------------------------------
	//	测试
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
						L"黑体",
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
		//“开始游戏”按钮的相关代码实现
		break;
	case BUTTON_ID_2:
		//“载入游戏”按钮的相关代码实现
		break;
	case BUTTON_ID_3:
		//“选项”按钮的相关代码实现
		break;
	case BUTTON_ID_4:
		//如果点击了退出按钮，就退出程序
		if(state == UGP_BUTTON_DOWN) PostQuitMessage(0);
		break;
	}
}


//-----------------------------------【Direct3D_Update( )函数】--------------------------------
//	描述：不是即时渲染代码但是需要即时调用的，如按键后的坐标的更改，都放在这里
//--------------------------------------------------------------------------------------------------
void	Direct3D_Update( HWND hwnd,FLOAT fTimeDelta)
{
	//GUI的实现暂时不需要在这里写代码
}



//-----------------------------------【Direct3D_Render( )函数】-------------------------------
//	描述：使用Direct3D进行渲染
//--------------------------------------------------------------------------------------------------
void Direct3D_Render(HWND hwnd,FLOAT fTimeDelta)
{
	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之一】：清屏操作
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, D3DCOLOR_XRGB(100, 255, 255), 1.0f, 0);

	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之二】：开始绘制
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->BeginScene();                     // 开始绘制

	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之三】：正式绘制
	//--------------------------------------------------------------------------------------


	// 处理和渲染GUI系统
	ProcessGUI(g_gui, g_LMBDown, g_MouseX, g_MouseY, GUICallback);
	

	//-----------------------------【绘制文字信息】-----------------------------
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
	// 【Direct3D渲染五步曲之四】：结束绘制
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->EndScene();                       // 结束绘制
	//--------------------------------------------------------------------------------------
	// 【Direct3D渲染五步曲之五】：显示翻转
	//--------------------------------------------------------------------------------------
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);  // 翻转与显示

}


//-----------------------------------【HelpText_Render( )函数】-------------------------------
//	描述：封装了帮助信息的函数
//--------------------------------------------------------------------------------------------------
void HelpText_Render(HWND hwnd)
{
	//定义一个矩形，用于获取主窗口矩形
	RECT formatRect;
	GetClientRect(hwnd, &formatRect);

	//在窗口右上角处，显示每秒帧数
	formatRect.top = 5;
	int charCount = swprintf_s(g_strFPS, 20, _T("FPS:%0.3f"), Get_FPS() );
	g_pTextFPS->DrawText(NULL, g_strFPS, charCount , &formatRect, DT_TOP | DT_RIGHT, D3DCOLOR_RGBA(0,239,136,255));

	wchar_t g_strTest[20];
	int testCount = swprintf_s(g_strTest, 20, L"fuck you");
//**************************测试
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
	//显示显卡类型名
	g_pTextAdaperName->DrawText(NULL,g_strAdapterName, -1, &formatRect, 
		DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
}


//-----------------------------------【Get_FPS( )函数】------------------------------------------
//	描述：用于计算每秒帧速率的一个函数
//--------------------------------------------------------------------------------------------------
float Get_FPS()
{

	//定义四个静态变量
	static float  fps = 0; //我们需要计算的FPS值
	static int    frameCount = 0;//帧数
	static float  currentTime =0.0f;//当前时间
	static float  lastTime = 0.0f;//持续时间

	frameCount++;//每调用一次Get_FPS()函数，帧数自增1
	currentTime = timeGetTime()*0.001f;//获取系统时间，其中timeGetTime函数返回的是以毫秒为单位的系统时间，所以需要乘以0.001，得到单位为秒的时间

	//如果当前时间减去持续时间大于了1秒钟，就进行一次FPS的计算和持续时间的更新，并将帧数值清零
	if(currentTime - lastTime > 1.0f) //将时间控制在1秒钟
	{
		fps = (float)frameCount /(currentTime - lastTime);//计算这1秒钟的FPS值
		lastTime = currentTime; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
		frameCount    = 0;//将本次帧数frameCount值清零
	}

	return fps;
}



//-----------------------------------【Direct3D_CleanUp( )函数】--------------------------------
//	描述：对Direct3D的资源进行清理，释放COM接口对象
//---------------------------------------------------------------------------------------------------
void Direct3D_CleanUp()
{
	//释放COM接口对象
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
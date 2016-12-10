//====================================================
// Name: D3DGUIClass.h
//	Des: һ����ϷGUI����ϵͳ���ͷ�ļ�
// 2013�� 11��17��  Create by ǳī 
//====================================================

#pragma once


// ��֧�ֵĿؼ����ͺ�
#define UGP_GUI_STATICTEXT		1
#define UGP_GUI_BUTTON			2
#define UGP_GUI_Background		3

// ��갴��״̬��
#define UGP_BUTTON_UP			1
#define UGP_BUTTON_OVER		2
#define UGP_BUTTON_DOWN		3

// ����һЩGUI���õ��Ŀؼ�ID
#define STATIC_ID_1  1
#define STATIC_ID_2  2
#define BUTTON_ID_1  3
#define BUTTON_ID_2  4
#define BUTTON_ID_3  5
#define BUTTON_ID_4  6



// FVF�������͵Ľṹ��
struct GUIVERTEX
{
	float x, y, z, rhw;
	unsigned long color;
	float tu, tv;
};
#define D3DFVF_GUI (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//�ؼ����Խṹ��
struct GUICONTROL
{
	//�������ͣ�ID����ɫ
	int m_type;  //�ؼ�����
	int m_id;  //�ؼ�ID
	unsigned long m_color; //�ؼ���ɫ
	int m_listID;   //��������ֵĻ�����������ͱ�ʾ��ʹ�õ����壬����ͱ�ʾ���㻺��
	float m_xPos, m_yPos;   //�ؼ�����ʼλ��
	float m_width, m_height;   // �ؼ��Ŀ�Ⱥ͸߶�
	wchar_t *m_text;   // ��������
	LPDIRECT3DTEXTURE9 m_Background;   // �ؼ����������ͼ��
	LPDIRECT3DTEXTURE9 m_upTex, m_downTex, m_overTex;   // ��Ű�ť���𣬰��º���꾭��ʱ��3������ͼ
};



class D3DGUIClass
{

private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;  //D3D�豸����	
	LPD3DXFONT *m_pFonts;  //D3D�������
	GUICONTROL *m_pControls;  //�ؼ�����
	LPDIRECT3DVERTEXBUFFER9 *m_pVertexBuffer;   //���㻺�����ָ��
	GUICONTROL m_Background;  //����ͼ����
	LPDIRECT3DVERTEXBUFFER9 m_BackgroundBuffer;   //����ͼ����������

	bool m_bIsBackgroundUsed;  //һ����ʶ�����ڱ�ʶ�Ƿ��Ѿ����˱���
	int m_nTotalFontNum;		//������Ŀ������
	int m_nTotalControlNum;	//�ؼ���Ŀ������
	int m_nTotalBufferNum;	//��������Ŀ������

	int m_nWindowWidth;	//���ڿ��
	int m_nWindowHeight;	//���ڸ߶�



public:
	D3DGUIClass(LPDIRECT3DDEVICE9 device, int w, int h);
	~D3DGUIClass() { ClearUp(); }

	LPDIRECT3DDEVICE9 GetD3dDevice() { return m_pd3dDevice; }  //����D3D�豸����ĺ���
	GUICONTROL *GetBackground() { return &m_Background; } //���ر����ĺ���
	LPDIRECT3DVERTEXBUFFER9 GetBackgroundBuffer() { return m_BackgroundBuffer; }  //���ر�������������ĺ���


	int GetTotalFontNum() { return m_nTotalFontNum; }  //��������������Ŀ�ĺ���
	int GetTotalControlNum() { return m_nTotalControlNum; }  //�������пؼ���Ŀ�ĺ���
	int GetTotalBufferNum() { return m_nTotalBufferNum; } //�����ܵĻ�������Ŀ�ĺ���
	int GetWindowWidth() { return m_nWindowWidth; }  //���ش��ڿ�ȵĺ���
	int GetWindowHeight() { return m_nWindowHeight; }  //���ش��ڸ߶ȵĺ���
	bool IsBackgroundUsed() { return m_bIsBackgroundUsed; }     //���ر����Ƿ���ʹ�õ�boolֵ�ĺ���
	void SetWindowSize(int w, int h) { m_nWindowWidth = w; m_nWindowHeight = h; }  //���ô��ڿ�Ⱥ͸߶ȵĺ���

	LPD3DXFONT GetFont(int id)  //��������ID����
	{
		if(id < 0 || id >= m_nTotalFontNum) return NULL;
		return m_pFonts[id];
	}

	GUICONTROL *GetGUIControl(int id)  //����GUI�ؼ�ID����
	{
		if(id < 0 || id >= m_nTotalControlNum) return NULL;
		return &m_pControls[id];
	}

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(int id) //���ض��㻺��ID����
	{
		if(id < 0 || id >= m_nTotalBufferNum) return NULL;
		return m_pVertexBuffer[id];
	}


	bool CreateTextFont(wchar_t *fontName, int size, int *fontID);  //���崴������
	bool AddBackground(wchar_t *fileName);  //GUI������Ӻ���
	bool AddStaticText(int id, wchar_t *text, float x, float y, unsigned long color, int fontID); //��Ӿ�̬�ı�����
	bool AddButton(int id, float x, float y, wchar_t *up, wchar_t *over, wchar_t *down); //��Ӱ�ť����
	void ClearUp( ); //��Դ������


};

void ProcessGUI(D3DGUIClass *gui, bool LMBDown, int mouseX, int mouseY,
	void(*funcPtr)(int id, int state));  //�ص�����


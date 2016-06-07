//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : CurrentPriceDlg.cpp
//! Function      : ���簡 ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// CurrentPriceDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "CurrentPriceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString m_strRealSet = "�ֽĽü�;�ֽ�ü��;�ֽ�ȣ���ܷ�;�ֽĽð���ȣ��";

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPT10001[] = 
{
	{"�����",			"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	/////////////////////////////////////
	// ���簡 �׸���
	{"���簡",			"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"����ȣ",		"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,	"",	""}, 
	{"���ϴ��",		"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"�����",			"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	{"�ŷ���",			"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŷ����",		"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 1��
	{"250�ְ�",			"-1",	0,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"250�ְ������",	"-1",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	{"250�ְ���",		"-1",	0,	3,	DT_DATE,		FALSE,	DT_CENTER,	"",	""}, 
	{"�׸鰡",			"-1",	0,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	" ��"}, 
	{"�ð��Ѿ�",		"-1",	0,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	" ��"}, 
	{"EPS",				"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 2��
	{"250����",			"-1",	1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"250�����������",	"-1",	1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	{"250��������",		"-1",	1,	3,	DT_DATE,		FALSE,	DT_CENTER,	"",	""}, 
	{"�ں���",			"-1",	1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	" ��"}, 
	{"��밡",			"-1",	1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"PER",				"-1",	1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 3��
	{"���μ�����",		"-1",	2,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"%"}, 
	{"�����ֽ�",		"-1",	2,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	" õ"}, 
	{"�ſ����",		"-1",	2,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"%"}, 
	{"����",			"-1",	2,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"��"}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 4��
	{"�����ְ�",		"-1",	3,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"BPS",				"-1",	3,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	""}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 5��
	{"��������",		"-1",	4,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"PBR",				"-1",	4,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	""}, 
};

// �ǽð� �ֹ�ü��(���簡 ǥ�ÿ�)
const stGRID lstOPT10001_B[] = 
{
	{"�����",			"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	/////////////////////////////////////
	// ���簡 �׸���
	{"���簡",			"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"����ȣ",		"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,	"",	""}, 
	{"���ϴ��",		"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"�����",			"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	{"�ŷ���",			"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŷ����",		"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
};

const stGRID lstOPT10003[] = 
{
	{"�ð�",			"20",	-1,	0,	DT_TIME,		FALSE,	DT_CENTER,	"",	""}, 
	{"���簡",			"10",	-1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"sign",			"25",	-1,	2,	DT_SIGN,		TRUE,	DT_CENTER,	"",	""}, 
	{"���ϴ��",		"11",	-1,	3,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�����ŷ���",		"13",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�����ŷ����",	"14",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
};

const stGRID lstOPT10004[] = 
{
	/////////////////////////////////////
	// �Ѹŵ�/�ż� �ܷ�
	{"�Ѹŵ��ܷ�",		"61",	0,	0,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""},
	{"�Ѹż��ܷ�",		"63",	0,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	/////////////////////////////////////
	// �ŵ�ȣ��
	{"�ŵ�10�����ܷ�",	"70",	1,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�10����ȣ��",	"50",	1,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�9�����ܷ�",	"69",	2,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�9����ȣ��",	"49",	2,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�8�����ܷ�",	"68",	3,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�8����ȣ��",	"48",	3,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�7�����ܷ�",	"67",	4,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�7����ȣ��",	"47",	4,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�6�����ܷ�",	"66",	5,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�6����ȣ��",	"46",	5,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�5�����ܷ�",	"65",	6,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�5����ȣ��",	"45",	6,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�4�����ܷ�",	"64",	7,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�4����ȣ��",	"44",	7,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�3�����ܷ�",	"63",	8,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�3����ȣ��",	"43",	8,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�2�����ܷ�",	"62",	9,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ�2����ȣ��",	"42",	9,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŵ��ֿ켱�ܷ�",	"61",	10,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ŵ��ֿ켱ȣ��",	"41",	10,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	/////////////////////////////////////
	// �ż�ȣ��
	{"�ż��ֿ켱ȣ��",	"51",	11,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ŵ��ֿ켱�ܷ�",	"71",	11,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�2����ȣ��",	"52",	12,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�2�����ܷ�",	"72",	12,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�3����ȣ��",	"53",	13,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�3�����ܷ�",	"73",	13,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�4����ȣ��",	"54",	14,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�4�����ܷ�",	"74",	14,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�5����ȣ��",	"55",	15,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�5�����ܷ�",	"75",	15,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�6����ȣ��",	"56",	16,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�6�����ܷ�",	"76",	16,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�7����ȣ��",	"57",	17,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�7�����ܷ�",	"77",	17,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�8����ȣ��",	"58",	18,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�8�����ܷ�",	"78",	18,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�9����ȣ��",	"59",	19,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�9�����ܷ�",	"79",	19,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	{"�ż�10����ȣ��",	"60",	20,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	""},
	{"�ż�10�����ܷ�",	"80",	20,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	/////////////////////////////////////
	// ���ܷ�
	{"�Ѹŵ��ܷ�",		"121",	21,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""},
	{"�Ѹż��ܷ�",		"125",	21,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
	/////////////////////////////////////
	// ȣ���ܷ����ؽð�
	{"ȣ���ܷ����ؽð�","21",	21,	1,	DT_TIME,		FALSE,	DT_CENTER,	"",	""}, 
	/////////////////////////////////////
	// �ð��� �ŵ�/�ż� �ܷ�
	{"�ð��ܸŵ��ܷ�",	"131",	22,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""},
	{"�ð��ܸż��ܷ�",	"132",	22,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	""}, 
};

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPT10080[] = 
{
	{"���簡",			"20",	-1,	0,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	""}, 
	{"�ŷ���",			"10",	-1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"ü��ð�",			"25",	-1,	2,	DT_TIME,		TRUE,	DT_CENTER,	"",	""}, 
	{"�ð�",				"11",	-1,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"��",				"13",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"����",				"14",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�����ְ�����",		"14",	-1,	6,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"��������",			"14",	-1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"���������",		"14",	-1,	8,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�Ҿ�������",		"14",	-1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"��������",			"14",	-1,	10,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�����ְ��̺�Ʈ",	"14",	-1,	11,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"��������",			"14",	-1,	12,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
};

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPT10081[] = 
{
	{"���簡",			"20",	-1,	0,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	""}, 
	{"�ŷ���",			"10",	-1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"�ŷ����",			"25",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_CENTER,	"",	""}, 
	{"����",				"11",	-1,	3,	DT_DATE,		TRUE,	DT_RIGHT,	"",	""}, 
	{"�ð�",				"13",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"��",				"14",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"����",				"14",	-1,	6,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�����ְ�����",		"14",	-1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"��������",			"14",	-1,	8,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"���������",		"14",	-1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�Ҿ�������",		"14",	-1,	10,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"��������",			"14",	-1,	11,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"�����ְ��̺�Ʈ",	"14",	-1,	12,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"��������",			"14",	-1,	13,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
};
// CCurrentPriceDlg ��ȭ ����
//*******************************************************************/
//! Function Name : CCurrentPriceDlg::CCurrentPriceDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CCurrentPriceDlg::IDD, pParent)
//! Function      : ���� �ʱ� ó��
//! Param         : HANDLE hBitmap, int bits
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
CCurrentPriceDlg::CCurrentPriceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCurrentPriceDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "7777";
	m_strJongCode = "";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//*******************************************************************/
// Function Name : DoDataExchange
// Function      : DDX/DDV�� ���� �� �Լ� ȣ��
// Param         : CDataExchange*	pDX
// Return        : void
// Create        : , 2014/06/02
// Comment       : DDX - ��Ʈ�Ѱ� ����������̿� ������ ��ȯ�ϴ� ����
//				 : DDV - ��������� ���� �� ���� ��ȿ�� üũ
//				 : UapdateData()�Լ��� ���� ȣ�� �� �� ����
//*******************************************************************/
void CCurrentPriceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurrentPriceDlg)
	DDX_Control(pDX, IDC_GRD_CURPRC,	m_grdCurPrc);
	DDX_Control(pDX, IDC_GRD_JONGINFO,	m_grdJongInfo);
	DDX_Control(pDX, IDC_GRD_HOGA,		m_grdHoga);
	DDX_Control(pDX, IDC_GRD_TICK,		m_grdTick);
	//}}AFX_DATA_MAP
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(CCurrentPriceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEARCH,	OnBtnSearch)
END_MESSAGE_MAP()

//*******************************************************************/
//! Function Name : OnInitDialog
//! Function      : ���� �ʱ� ó��
//! Param         : void
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : CCurrentPriceDlg �޽��� ó����
//******************************************************************/
BOOL CCurrentPriceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetLimitText(6);	// �����ڵ� �ִ���� ����

	// �׸��� ����
	InitCurPrcGrid();				// ���簡 �׸��� �ʱ� ó��
	InitJongInfoGrid();				// �������� �׸��� �ʱ� ó��
	InitHogaGrid();					// ȣ�� �׸��� �ʱ� ó��
	InitTickGrid();					// ƽ �׸��� �ʱ� ó��

	// ������ �����ڵ� ���
	char szItem[7];
	int nSize = sizeof(szItem);
	memset(szItem, 0, nSize);
	CString strFileName = theApp.m_sAppPath + "/data/jongcodedata.ini";
	::GetPrivateProfileString("CURRENTPRICEDLG", "LAST_JONG_CODE", "039490", szItem, nSize, strFileName);
	m_strJongCode = szItem;		m_strJongCode.Trim();
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetWindowText(m_strJongCode);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//*******************************************************************/
//! Function Name : OnPaint
//! Function      : �׸��� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//!               : �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//!               : �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
//******************************************************************/
void CCurrentPriceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//*******************************************************************/
//! Function Name : OnClose
//! Function      : �ı���
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::OnClose()
{
	// ȭ�� ���� �� �θ������쿡�� �뺸(ȭ�� ���� ����)
	if (m_pParent)
	{
		int nLen = m_strScrNo.GetLength();
		char *cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);

		nLen = m_strScrNo2.GetLength();
		char *cScrNo2 = new char[nLen + 1];
		memset(cScrNo2, 0x00, nLen + 1);
		memcpy(cScrNo2, m_strScrNo2, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo2);

		nLen = m_strScrNo3.GetLength();
		char *cScrNo3 = new char[nLen + 1];
		memset(cScrNo3, 0x00, nLen + 1);
		memcpy(cScrNo3, m_strScrNo3, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo3);
	}

	CDialogEx::OnClose();
}

//*******************************************************************/
//! Function Name : OnQueryDragIcon
//! Function      : �巡�� ������ ó��
//! Param         : void
//! Return        : HCURSOR
//! Create        : , 2014/06/02
//! Comment       : ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ��� 
//!               : �� �Լ��� ȣ���մϴ�.
//******************************************************************/
HCURSOR CCurrentPriceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name : OnBtnSearch
//! Function      : ��ȸ ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::OnBtnSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// �����ڵ� �Է� ����
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(m_strJongCode);
	if (m_strJongCode.GetLength() != 6)
	{
		AfxMessageBox("�����ڵ� 6�ڸ� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	m_grdTick.SetRowCount(1);		// ��/�� ���� ����
	SendSearch();					// ��ȸ ó��
}

//*******************************************************************/
//! Function Name : InitCurPrcGrid
//! Function      : ���簡 �׸��� �ʱ� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::InitCurPrcGrid()
{
	m_grdCurPrc.SetEditable(false);					//cell�� ����Ʈ ���ϰ� ��.
	m_grdCurPrc.EnableScrollBars(SB_BOTH, FALSE);

	// ��/�� ���� ����
	m_grdCurPrc.SetRowCount(1);
	m_grdCurPrc.SetColumnCount(6);

	// ���� ���� ����
	int i, nWidth[] = {80, 20, 80, 60, 80, 80};
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		m_grdCurPrc.SetColumnWidth(i, nWidth[i]);
		m_grdCurPrc.SetItemFormat(0, i, DT_RIGHT);
	}
	m_grdCurPrc.SetItemFormat(0, 1, DT_CENTER);

	// ���� ���� ����
	m_grdCurPrc.SetRowHeight(0, 20);

	m_grdCurPrc.Invalidate();
}

//*******************************************************************/
//! Function Name : InitJongInfoGrid
//! Function      : �������� �׸��� �ʱ� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::InitJongInfoGrid()
{
	m_grdJongInfo.SetEditable(false);				//cell�� ����Ʈ ���ϰ� ��.
	m_grdJongInfo.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(220, 224, 233);

	// ��/�� ���� ����
	m_grdJongInfo.SetRowCount(5);
	m_grdJongInfo.SetColumnCount(10);

	// ���� ���� ����
	UINT nFormat;
	int i, nWidth[] = {67, 67, 60, 80, 45, 80, 55, 80, 45, 60};
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		m_grdJongInfo.SetColumnWidth(i, nWidth[i]);
		switch (i)
		{
			case 0:
				nFormat = DT_LEFT;
				break;
			case 1:	case 2:	case 7:	case 9:
				nFormat = DT_RIGHT;
				break;
			default:
				nFormat = DT_CENTER;
				break;
		}
		m_grdJongInfo.SetItemFormat(0, i, nFormat);
		m_grdJongInfo.SetItemFormat(1, i, nFormat);
		m_grdJongInfo.SetItemFormat(2, i, nFormat);
		m_grdJongInfo.SetItemFormat(3, i, nFormat);
		m_grdJongInfo.SetItemFormat(4, i, nFormat);
	}

	// ���� ���� ����
	for (i = 0; i < 5; i++)
	{
		m_grdJongInfo.SetRowHeight(i, 24);
		m_grdJongInfo.SetItemBkColour(i, 0, clr);	// ������ ���� ���� ����
		m_grdJongInfo.SetItemBkColour(i, 4, clr);	// ������ ���� ���� ����
		m_grdJongInfo.SetItemBkColour(i, 6, clr);	// ������ ���� ���� ����
		m_grdJongInfo.SetItemBkColour(i, 8, clr);	// ������ ���� ���� ����
	}

	m_grdJongInfo.SetItemText(0, 0, "250���ְ�");
	m_grdJongInfo.SetItemText(1, 0, "250������");
	m_grdJongInfo.SetItemText(2, 0, "�ܱ��κ���");
	m_grdJongInfo.SetItemText(3, 0, "�����ְ�");
	m_grdJongInfo.SetItemText(4, 0, "��������");

	m_grdJongInfo.SetItemText(0, 4, "�׸鰡");
	m_grdJongInfo.SetItemText(1, 4, "�ں���");
	m_grdJongInfo.SetItemText(2, 4, "�ֽļ�");
	m_grdJongInfo.SetItemText(3, 4, "");
	m_grdJongInfo.SetItemText(4, 4, "");

	m_grdJongInfo.SetItemText(0, 6, "�ð��Ѿ�");
	m_grdJongInfo.SetItemText(1, 6, "��밡");
	m_grdJongInfo.SetItemText(2, 6, "�ſ����");
	m_grdJongInfo.SetItemText(3, 6, "");
	m_grdJongInfo.SetItemText(4, 6, "");

	m_grdJongInfo.SetItemText(0, 8, "EPS");
	m_grdJongInfo.SetItemText(1, 8, "BPS");
	m_grdJongInfo.SetItemText(2, 8, "����");
	m_grdJongInfo.SetItemText(3, 8, "PER");
	m_grdJongInfo.SetItemText(4, 8, "PBR");
	
	m_grdJongInfo.Invalidate();
}

//*******************************************************************/
//! Function Name : InitHogaGrid
//! Function      : ȣ�� �׸��� �ʱ� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::InitHogaGrid()
{
	m_grdHoga.SetEditable(false);				//cell�� ����Ʈ ���ϰ� ��.
	m_grdHoga.EnableScrollBars(SB_BOTH, FALSE);

	// ��/�� ���� ����
	m_grdHoga.SetRowCount(23);
	m_grdHoga.SetColumnCount(3);

	// ���� ���� ����
	int i;
	for (i = 0; i < 3; i++)
	{
		m_grdHoga.SetColumnWidth(i, 80);
	}

	// ���� ���� ����
	for (i = 0; i < 21; i++)
	{
		m_grdHoga.SetRowHeight(i, 20);
		m_grdHoga.SetItemFormat(i, 0, DT_RIGHT);
		m_grdHoga.SetItemFormat(i, 1, DT_RIGHT);
		m_grdHoga.SetItemFormat(i, 2, DT_RIGHT);
	}

	m_grdHoga.SetRowHeight(21, 22);
	m_grdHoga.SetItemFormat(21, 0, DT_RIGHT);
	m_grdHoga.SetItemFormat(21, 1, DT_CENTER);
	m_grdHoga.SetItemFormat(21, 2, DT_RIGHT);
	m_grdHoga.SetRowHeight(22, 22);
	m_grdHoga.SetItemFormat(22, 0, DT_RIGHT);
	m_grdHoga.SetItemFormat(22, 1, DT_CENTER);
	m_grdHoga.SetItemFormat(22, 2, DT_RIGHT);
	m_grdHoga.SetItemText(22, 1, "�ð���");

	// ȣ�� �׸��� ���� ����
	m_grdHoga.SetItemBkColour(0, 0, RGB(233, 243, 253));		// ������ ���� ���� ����
	COLORREF clrHoga[] = 
	{
		RGB(253,232,227),
		RGB(205,230,235), RGB(209,234,238), RGB(216,235,241), RGB(222,237,242), RGB(226,241,244), 
		RGB(233,244,246), RGB(238,246,249), RGB(243,248,251), RGB(248,252,251), RGB(249,255,253), 
		RGB(251,255,250), RGB(255,250,247), RGB(255,241,241), RGB(252,239,231), RGB(252,233,226), 
		RGB(253,226,219), RGB(251,221,211), RGB(250,216,204), RGB(250,210,198), RGB(252,204,192), 
	};
	for (i = 0; i < 21; i++)
	{
		m_grdHoga.SetItemBkColour(i, 1, clrHoga[i]);			// ������ ���� ���� ����
	}

	COLORREF clr = RGB(238, 238, 238);
	for (i = 21; i < 23; i++)
	{
		m_grdHoga.SetItemBkColour(i, 0, clr);			// ������ ���� ���� ����
		m_grdHoga.SetItemBkColour(i, 1, clr);			// ������ ���� ���� ����
		m_grdHoga.SetItemBkColour(i, 2, clr);			// ������ ���� ���� ����
	}

	m_grdHoga.Invalidate();
}

//*******************************************************************/
//! Function Name : InitTickGrid
//! Function      : ƽ �׸��� �ʱ� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::InitTickGrid()
{
	m_grdTick.SetEditable(false);				//cell�� ����Ʈ ���ϰ� ��.
	m_grdTick.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(215, 227, 241);

	// ���� ��/�� ����
	m_grdTick.SetFixedRowCount(1);

	// ��/�� ���� ����
	m_grdTick.SetRowCount(1);
	m_grdTick.SetColumnCount(6);

	// ���� ���� ����
	int i, nWidth[] = {72, 80, 20, 60, 80, 80};
	CString strHeader[] = {"�ð�", "ü�ᰡ", "", "���ϴ��", "�ŷ���", "�ŷ����"};
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		m_grdTick.SetColumnWidth(i, nWidth[i]);
		m_grdTick.SetItemFormat(0, i, DT_CENTER);
		m_grdTick.SetItemText(0, i, strHeader[i]);
		m_grdTick.SetItemBkColour(0, i, clr);	// ������ ���� ���� ����
	}

	// ���� ���� ����
	m_grdTick.SetRowHeight(0, 24);

	m_grdTick.Invalidate();
}

//*******************************************************************/
//! Function Name : SendSearch
//! Function      : ��ȸ ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::SendSearch()
{
	CString strFileName = theApp.m_sAppPath + "/data/jongcodedata.ini";
	::WritePrivateProfileString("CURRENTPRICEDLG", "LAST_JONG_CODE", m_strJongCode, strFileName);

	CString strRQName = _T("���簡/��������");
	CString strTRCode = TR_OPT10001;
	theApp.m_khOpenApi.SetInputValue("�����ڵ�", m_strJongCode);
	long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	CString		strErr;
	if (!theApp.IsError(lRet))
	{
		strErr.Format(_T("�ֽı⺻������û ���� [%s][%d]"), strTRCode, lRet);
		OutputDebugString(strErr);
	}
	
	strRQName = _T("ü��ƽ");
	strTRCode = TR_OPT10003;
	theApp.m_khOpenApi.SetInputValue("�����ڵ�", m_strJongCode);
	lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	if (!theApp.IsError(lRet))
	{
		strErr.Format(_T("ü��������û ���� [%s][%d]"), strTRCode, lRet);
		OutputDebugString(strErr);
	}

	strRQName = _T("ȣ��");
	strTRCode = TR_OPT10004;
	theApp.m_khOpenApi.SetInputValue("�����ڵ�", m_strJongCode);
	lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	if (!theApp.IsError(lRet))
	{
		strErr.Format(_T("�ֽ�ȣ����û ���� [%s][%d]"), strTRCode, lRet);
		OutputDebugString(strErr);
	}
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("���簡/��������"))		// �ֽı⺻���� ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10001) / sizeof(*lstOPT10001);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("�ֽı⺻����");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10001[j].strKey);	strData.Trim();
				arrData.Add(strData);
			}
			SetDataJongInfoGrid(arrData);
		}
	}
	else if (strRQName == _T("ü��ƽ"))			// ü������ ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10003) / sizeof(*lstOPT10003);		// ��üũ�� / ����ũ�� = ���Ұ���

		m_grdTick.SetRowCount(1);
		strRQName = _T("ü������");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10003[j].strKey);	strData.Trim();
				if (j == nFieldCnt - 1)
				{	// �鸸����
					strData.Format("%ld", long(atof(strData) / 1000000));
				}
				arrData.Add(strData);
			}
			SetDataTickGrid(-1, i + 1, arrData);
		}
	}
	else if (strRQName == _T("ȣ��"))			// �ֽ�ȣ�� ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10004) / sizeof(*lstOPT10004);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("�ֽ�ȣ��");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10004[j].strKey);	strData.Trim();
				arrData.Add(strData);
			}
			SetDataHogaGrid(arrData);
		}
	}
	else if (strRQName == _T("�ֽĺк���Ʈ"))		// �ֽı⺻���� ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10080) / sizeof(*lstOPT10080);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("�ֽı⺻����");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10001[j].strKey);	strData.Trim();
			}
		}
	}
	else if (strRQName == _T("�ֽ��Ϻ���Ʈ"))		// �ֽı⺻���� ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10081) / sizeof(*lstOPT10081);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("�ֽı⺻����");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10001[j].strKey);	strData.Trim();
			}
		}
	}

}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : �ǽð� ó��
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (m_strJongCode.Compare(sJongmokCode) || m_strRealSet.Find(sRealType) < 0)
	{
		return;
	}

	CString strData;
	CStringArray arrData;
	if (!strcmp(sRealType, "�ֽĽü�"))		// �ֽĽü�
	{
		int i, nFieldCnt = sizeof(lstOPT10001) / sizeof(*lstOPT10001);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10001[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10001[i].strRealKey));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataJongInfoGrid(arrData, sRealType);
	}
	else if (!strcmp(sRealType, "�ֽ�ü��"))	// �ֽ�ü��
	{
		CStringArray arrData;
		int i, nFieldCnt = sizeof(lstOPT10003) / sizeof(*lstOPT10003);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10003[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10003[i].strRealKey));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataTickGrid(1, 1, arrData);
		m_grdTick.SetFocusCell(1, 0);
		m_grdTick.SetSelectedRange(1, 0, 1, 5);

		arrData.RemoveAll();
		nFieldCnt = sizeof(lstOPT10001_B) / sizeof(*lstOPT10001_B);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10001_B[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10001_B[i].strRealKey));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataJongInfoGrid(arrData, sRealType);
	}
	else if(!strcmp(sRealType, "�ֽ�ȣ���ܷ�") ||	// �ֽ�ȣ���ܷ�
			!strcmp(sRealType, "�ֽĽð���ȣ��"))	// �ֽĽð���ȣ��
	{
		CStringArray arrData;
		int i, nFieldCnt = sizeof(lstOPT10004) / sizeof(*lstOPT10004);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10004[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10004[i].strRealKey));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataHogaGrid(arrData, sRealType);
	}
	arrData.RemoveAll();
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : ü���ܰ� �ǽð� ó��
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{

}

//*******************************************************************/
//! Function Name : SetDataJongInfoGrid
//! Function      : ���簡, �������� �׸��� ����Ÿ ����(�ֽı⺻���� ����)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::SetDataJongInfoGrid(CStringArray &arrData, CString strRealType/* = ""*/)
{
	CString strData, strTempData, strTemp;
	int i, nCnt = arrData.GetSize();
	for (i = 0; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		if (i == 0 && strRealType == "")			// �����
		{
			((CStatic*)GetDlgItem(IDC_STC_JONGNAME))->SetWindowText(strData);
		}
		else if (i < 7)		// ���簡 �׸���
		{
			/////////////////////////////////////////////
			// ���� �� ������ ���� ó������������
			if (strRealType != "" && (i == 1 || i == 3 || i == 4))
			{
				strTempData = strData;
				strTempData.Replace("+", "");	strTempData.Replace("-", "");	strTempData.Replace(".", "");

				strTemp = m_grdCurPrc.GetItemText(lstOPT10001[i].nRow, lstOPT10001[i].nCol);
				strTemp.Replace("%", "");	strTemp.Replace("+", "");	strTemp.Replace("-", "");
				strTemp.Replace(",", "");	strTemp.Replace(".", "");
				if (strTempData != strTemp)
				{
					m_grdCurPrc.SetFocusCell(lstOPT10001[i].nRow, lstOPT10001[i].nCol);
					m_grdCurPrc.SetSelectedRange(lstOPT10001[i].nRow, lstOPT10001[i].nCol, lstOPT10001[i].nRow, lstOPT10001[i].nCol);
					m_grdCurPrc.Invalidate();
				}
			}
			// ���� �� ������ ���� ó������������
			/////////////////////////////////////////////
			if (lstOPT10001[i].bTextColor)
			{
				strTemp = arrData.GetAt(2);
				if (strTemp == "1" || strTemp == "2")	// ��ȣ�� ���� ���󺯰�
				{
					strTemp = "1";
				}
				else if (strTemp == "4" || strTemp == "5")	// ��ȣ�� ���� ���󺯰�
				{
					strTemp = "-1";
				}
				else
				{
					strTemp = "0";
				}
				theApp.SetDataFgColour(&m_grdCurPrc, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strTemp);
			}
			if (lstOPT10001[i].nDataType == DT_SIGN)
			{
				theApp.SetSignData(&m_grdCurPrc, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strData);
			}
			else
			{
				if (strData.IsEmpty())
				{
					continue;
				}
				m_grdCurPrc.SetItemText(lstOPT10001[i].nRow, lstOPT10001[i].nCol, theApp.ConvDataFormat(lstOPT10001[i].nDataType, strData, lstOPT10001[i].strBeforeData, lstOPT10001[i].strAfterData));
			}
		}
		else				// �ֽı⺻���� �׸��� 1��
		{
			if (strRealType != "")
			{
				break;
			}
			if (lstOPT10001[i].bTextColor)
			{
				theApp.SetDataFgColour(&m_grdJongInfo, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strData);
			}
			if (lstOPT10001[i].nDataType == DT_SIGN)
			{
				theApp.SetSignData(&m_grdJongInfo, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strData);
			}
			else
			{
				m_grdJongInfo.SetItemText(lstOPT10001[i].nRow, lstOPT10001[i].nCol, theApp.ConvDataFormat(lstOPT10001[i].nDataType, strData, lstOPT10001[i].strBeforeData, lstOPT10001[i].strAfterData));
			}
		}
	}
	m_grdCurPrc.Invalidate();
	m_grdJongInfo.Invalidate();
}

//*******************************************************************/
//! Function Name : SetDataTickGrid
//! Function      : ƽ �׸��� ����Ÿ ����(ü������ ����)
//! Param         : int nInsertRow, int nRow, CStringArray &arrData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::SetDataTickGrid(int nInsertRow, int nRow, CStringArray &arrData)
{
	if (nInsertRow >= m_grdTick.GetRowCount())
	{
		nInsertRow = -1;
	}
	// �� �߰�
	m_grdTick.InsertRow("", nInsertRow);
	m_grdTick.SetRowHeight(1, 20);		// ���� ���� ����

	CString strData, strTemp;
	int i, nCnt = arrData.GetSize();
	for (i = 0; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		m_grdTick.SetItemFormat(nRow, lstOPT10003[i].nCol, lstOPT10003[i].nAlign);
		if (lstOPT10003[i].bTextColor)
		{
			strTemp = arrData.GetAt(2);
			if (strTemp == "1" || strTemp == "2")	// ��ȣ�� ���� ���󺯰�
			{
				strTemp = "1";
			}
			else if (strTemp == "4" || strTemp == "5")	// ��ȣ�� ���� ���󺯰�
			{
				strTemp = "-1";
			}
			else
			{
				strTemp = "0";
			}
			theApp.SetDataFgColour(&m_grdTick, nRow, lstOPT10003[i].nCol, strTemp);
		}
		if (lstOPT10003[i].nDataType == DT_SIGN)
		{
			theApp.SetSignData(&m_grdTick, nRow, lstOPT10003[i].nCol, strData);
		}
		else
		{
			m_grdTick.SetItemText(nRow, lstOPT10003[i].nCol, theApp.ConvDataFormat(lstOPT10003[i].nDataType, strData, lstOPT10003[i].strBeforeData, lstOPT10003[i].strAfterData));
		}
	}
	m_grdTick.Invalidate();
}

//*******************************************************************/
//! Function Name : SetDataHogaGrid
//! Function      : ȣ�� �׸��� ����Ÿ ����(�ֽ�ȣ�� ����)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CCurrentPriceDlg::SetDataHogaGrid(CStringArray &arrData, CString strRealType/* = ""*/)
{
	CString strData, strTemp;
	int i, nCnt = arrData.GetSize();

	int nStart = 0, nEnd = nCnt;
	if (strRealType == "D")			// �ֽ�ȣ���ܷ�
	{
		nEnd = nCnt - 2;
	}
	else if (strRealType == "E")	// �ֽĽð���ȣ��
	{
		nStart = nCnt - 3;
	}

	for (i = nStart; i < nEnd; i++)
	{
		strData = arrData.GetAt(i);
		if (lstOPT10004[i].bTextColor)
		{
			theApp.SetDataFgColour(&m_grdHoga, lstOPT10004[i].nRow, lstOPT10004[i].nCol, strData);
		}
		if (lstOPT10004[i].nDataType == DT_SIGN)
		{
			theApp.SetSignData(&m_grdHoga, lstOPT10004[i].nRow, lstOPT10004[i].nCol, strData);
		}
		else
		{
			m_grdHoga.SetItemText(lstOPT10004[i].nRow, lstOPT10004[i].nCol, theApp.ConvDataFormat(lstOPT10004[i].nDataType, strData, lstOPT10004[i].strBeforeData, lstOPT10003[i].strAfterData));
		}
	}
	m_grdHoga.Invalidate();
}

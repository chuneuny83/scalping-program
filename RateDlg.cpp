//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2015 (��)�ѱ��Ҹ���ġ                /
//******************************************************************/
//! File Name			: RateDlg.cpp
//! Function			: ���ͷ����
//! System Name	: Ű�� ����API �׽�Ʈ
//! Create				: , 2015/05/07
//! Update				: 
//! Comment			: 
//******************************************************************/
// RateDlg.cpp : ���� ����

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "RateDlg.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  COMMISSION	0.00015
#define  COMMISSION1	0.0015
#define  COMMISSION2	0.003

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstFID[] = 
{
	{"�ſ뱸��",	"917",		-1,	0,		DT_NONE,					FALSE,	DT_CENTER,	"",	""},
	{"�����ڵ�",	"9001",	-1,	1,		DT_NONE,					FALSE,	DT_CENTER,	"",	""},
	{"�����",		"302",		-1,	2,		DT_NONE,					FALSE,	DT_CENTER,	"",	""},
	{"���簡",		"10",		-1,	3,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		"",	""},
	{"��������",	"930",		-1,	4,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		"",	""},
	{"�򰡱ݾ�",	"-1",		-1,	5,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		"",	""},
	{"�򰡼���",	"-1",		-1,	6,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		"",	""},
	{"���ͷ�",		"-1",		-1,	7,		DT_NONE,					FALSE,	DT_RIGHT,		"",	"%"},
	{"���Աݾ�",	"932",		-1,	8,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		"",	""},
	{"���簡",		"10",		-1,	9,		DT_NONE,					FALSE,	DT_RIGHT,		"",	""},	//(�������� ����)
	{"��������",	"930",		-1,	10,	DT_NONE,					FALSE,	DT_RIGHT,		"",	""},	//(�������� ����)
	{"���Աݾ�",	"932",		-1,	11,	DT_NONE,					FALSE,	DT_RIGHT,		"",	""},	//(�������� ����)
	{"�򰡱ݾ�",	"-1",		-1,	12,	DT_NONE,					FALSE,	DT_RIGHT,		"",	""},	//(�������� ����)
};

// CRateDlg ��ȭ ����
//*******************************************************************************************************/
//! Function Name	: CRateDlg::CRateDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CRateDlg::IDD, pParent)
//! Function			: ���� �ʱ� ó��
//! Param				: HANDLE hBitmap, int bits
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//*******************************************************************************************************/
CRateDlg::CRateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRateDlg::IDD, pParent)
{
	m_pParent				= pParent;
	m_strScrNo			= "9999";

	m_TotalEval			= 0;
	m_TotalPurchase	= 0;
	m_TotalProfit			= 0;
	m_TotalRate			= 0;
	m_Eval					= 0;
	m_Profit					= 0;
	m_Rate					= 0;
	m_Purchase			= 0;
	m_Comm				= 0;
	m_BuyComm			= 0;
	m_SellComm			= 0;
	m_Tax					= 0;
	m_Price					= 0;
	m_Qty					= 0;
	m_nCount				= 0;
	m_nNextRow			= 0;

	m_bNextFlag			= FALSE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//*******************************************************************/
// Function Name	: DoDataExchange
// Function			: DDX/DDV�� ���� �� �Լ� ȣ��
// Param				: CDataExchange*	pDX
// Return				: void
// Create				: , 2015/05/07
// Comment			: DDX - ��Ʈ�Ѱ� ����������̿� ������ ��ȯ�ϴ� ����
//							: DDV - ��������� ���� �� ���� ��ȿ�� üũ
//							: UapdateData()�Լ��� ���� ȣ�� �� �� ����
//*******************************************************************/
void CRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRateDlg)
		DDX_Control(pDX, IDC_EDT_ACC,			m_EdtAcc);
		DDX_Control(pDX, IDC_GRD_RATE,			m_grdRate);
		DDX_Control(pDX, IDC_EDT_EVAL,			m_EdtTotalEval);
		DDX_Control(pDX, IDC_EDT_PURCHASE,	m_EdtTotalPurchase);
		DDX_Control(pDX, IDC_EDT_PROFIT,		m_EdtTotalProfit);
		DDX_Control(pDX, IDC_EDT_RATE,			m_EdtTotalRate);
		
	//}}AFX_DATA_MAP
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(CRateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
END_MESSAGE_MAP()

//*******************************************************************/
//! Function Name	: OnInitDialog
//! Function			: ���� �ʱ� ó��
//! Param				: void
//! Return				: BOOL
//! Create				: , 2015/05/07
//! Comment			: CRateDlg �޽��� ó����
//******************************************************************/
BOOL CRateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	InitRealAddGrid();					// �׸��� �ʱ� ó��

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//************************************************************************************************/
//! Function Name	: OnPaint
//! Function			: �׸��� ó��
//! Param				: void
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//!						: �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//!						: �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
//***********************************************************************************************/
void CRateDlg::OnPaint()
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
//! Function Name	: OnClose
//! Function			: �ı���
//! Param				: void
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CRateDlg::OnClose()
{
	// ȭ�� ���� �� �θ������쿡�� �뺸(ȭ�� ���� ����)
	if (m_pParent)
	{
		int nLen = m_strScrNo.GetLength();
		char *cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);
	}

	CDialogEx::OnClose();
}

//*******************************************************************************/
//! Function Name	: OnQueryDragIcon
//! Function			: �巡�� ������ ó��
//! Param				: void
//! Return				: HCURSOR
//! Create				: , 2015/05/07
//! Comment			: ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ��� 
//!						: �� �Լ��� ȣ���մϴ�.
//*******************************************************************************/
HCURSOR CRateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name	: InitRealAddGrid
//! Function			: ȣ�� �׸��� �ʱ� ó��
//! Param				: void
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CRateDlg::InitRealAddGrid()
{
	m_grdRate.SetEditable(false);				//cell�� ����Ʈ ���ϰ� ��.
	m_grdRate.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(215, 227, 241);

	// ���� ��/�� ����
	m_grdRate.SetFixedRowCount(1);

	// ��/�� ���� ����
	m_grdRate.SetRowCount(1);
	int nCount = sizeof(lstFID) / sizeof(*lstFID);		// ��üũ�� / ����ũ�� = ���Ұ���
	m_grdRate.SetColumnCount(nCount);

	// ���� ���� ����
	int i, nWidth[] = {70, 79, 80, 80, 80, 80, 80, 60, 90, 0, 0, 0, 0};
	CString strHeader[] = {"�ſ뱸��", "�ڵ�", "�����", "���簡", "��������", "�򰡱ݾ�", "�򰡼���", "���ͷ�", "���Աݾ�", "���簡(����)", "��������(����)", "���Աݾ�(����)", "�򰡱ݾ�(����)"};

	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		m_grdRate.SetColumnWidth(i, nWidth[i]);
		m_grdRate.SetItemFormat(0, i, DT_CENTER);
		m_grdRate.SetItemText(0, i, strHeader[i]);
		m_grdRate.SetItemBkColour(0, i, clr);	// ������ ���� ���� ����
	}

	// ���� ���� ����
	m_grdRate.SetRowHeight(0, 24);

	m_grdRate.Invalidate();
}

//*******************************************************************/
//! Function Name	: OnReceiveTrDataKhopenapictrl
//! Function			: ��ȸ ���� ó��
//! Param				: LPCTSTR sScrNo
//!						: LPCTSTR sRQName
//!						: LPCTSTR sTrcode
//!						: LPCTSTR sRecordName
//!						: LPCTSTR sPrevNext
//!						: long nDataLength
//!						: LPCTSTR sErrorCode
//!						: LPCTSTR sMessage
//!						: LPCTSTR sSplmMsg
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CRateDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strPrevNext(sPrevNext);
	CString strRQName(sRQName);
	if (strRQName == _T("���¼��ͷ�"))			// ���¼��ͷ�
	{
		m_bNextFlag = FALSE;
		CString strData;
		int nFieldCnt = sizeof(lstFID) / sizeof(*lstFID);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("���¼��ͷ�");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);	//������ �Ǽ�
		m_nCount += (nCnt+1);	//������ �Ǽ��� �׸��� ��� �߰�
		m_grdRate.SetRowCount(m_nCount);

		for (i = 0; i < nCnt; i++)
		{
			CString strCode;

			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstFID[j].strKey);
				strData.Trim();

				if (j == 0) //�ſ뱸��
				{
					if (strData == _T("00"))
					{
						strData = _T("����");
					} 
					else if (strData == _T("03"))
					{
						strData = _T("����");
					}
					else if (strData == _T("99"))
					{
						strData = _T("������");
					}
				}
				else if (j == 1)	//�����
				{
					strCode = strData;
				}

				if (strData != "")
				{
					m_grdRate.SetItemFormat(i + 1 + m_nNextRow, lstFID[j].nCol, lstFID[j].nAlign);
					m_grdRate.SetItemText(i + 1 + m_nNextRow, j, theApp.ConvDataFormat(lstFID[j].nDataType, strData, lstFID[j].strBeforeData, lstFID[j].strAfterData));
				}
			}

			int nRow(0);
			nRow = i + 1 + m_nNextRow;

			//���� ���ͷ� ���
			SetRate(nRow, strCode);

			CString strIndex;
			strIndex.Format(_T("%d"), nRow);

			//������ Ű������ �ؼ� �ο찪�� �����Ѵ�.
			m_mapJongCode.SetAt(strCode, strIndex);
		}

		//�� ���ͷ� ���
		SetTotalRate();

		if (strPrevNext == "2")	//������ȸ
		{
			m_bNextFlag = TRUE;	//������ȸ����
			m_nCount = m_nCount - 1;	//�׸��� ���Row��/�� ����.
			m_nNextRow = m_nCount;	//������ȸ�� ������ Row���� ����.
			
			CString strAccNo;
			m_EdtAcc.GetWindowText(strAccNo);	//�Է��� ���¹�ȣ.

			//������ȸ�� �Ѵ�.
			theApp.m_khOpenApi.SetInputValue("���¹�ȣ", strAccNo);
			theApp.m_khOpenApi.CommRqData("���¼��ͷ�", "OPT10085", 2, m_strScrNo);
		}

		//������ȸ�� �ƴҶ��� �ǽð� ����� �Ѵ�.
		if (!m_bNextFlag)
		{
			CString strRQName = _T("��������"), strCodeList, strCode;
			long  nCodeCount(0);

			for (int nRow = 1; nRow < m_nCount; nRow++)
			{
				nCodeCount++;
				strCode = m_grdRate.GetItemText(nRow, 1);
				strCode.Trim();
				strCodeList += strCode + ";";
			}

			long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, 0, strRQName, m_strScrNo);
			if (!lRet)
			{
				return;
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveMsgKhopenapictrl
//! Function			: ��ȸ ���� ó��
//! Param				: LPCTSTR sScrNo
//!						: LPCTSTR sRQName
//!						: LPCTSTR sTrCode
//!						: LPCTSTR sMsg
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CRateDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
}

//*******************************************************************/
//! Function Name	: OnReceiveRealDataKhopenapictrl
//! Function			: �ǽð� ó��
//! Param				: LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CRateDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	CString strIndex, strData;
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
	{
		return;
	}

	CString strCode;

	int i, nFieldCnt = sizeof(lstFID) / sizeof(*lstFID);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nFieldCnt; i++)
	{
		if (atoi(lstFID[i].strRealKey) < 0)
		{
			continue;
		}

		//�ǽð� �����͸� �׸� �°� �����´�.
		strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstFID[i].strRealKey));	strData.Trim();

		//�׸� �´� �����Ͱ� �������� �׸��忡 ǥ���Ѵ�.
		if (strData != "")
		{
			m_grdRate.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
		}
	}

	//���� ���ͷ� ���
	strCode = sJongmokCode;
	SetRate(_ttoi(strIndex), strCode);

	//�� ���ͷ� ���
	SetTotalRate();

	m_grdRate.Invalidate();
}

//*******************************************************************/
//! Function Name	: OnReceiveChejanData
//! Function			: ü���ܰ� �ǽð� ó��
//! Param				: LPCTSTR sGubun
//!						: LONG nItemCnt
//!						: LPCTSTR sFidList
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CRateDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	CString strGuBun(sGubun), strAccNo, strAcc;

	strAccNo	= theApp.m_khOpenApi.GetChejanData(9201);	// ü��� ������ ���¹�ȣ
	m_EdtAcc.GetWindowText(strAcc);									// ���� ���¹�ȣ

	//���� ���ͷ� ��ȸ�� ���¹�ȣ�� �ִ� ü��� ���� ���� �� �ְ� ó��.
	if (strAccNo == strAcc)
	{
		if (strGuBun == "4")
		{
			OnBtnSearch(); //���������� ����ȸ�Ѵ�.
		}
	}
}

//*******************************************************************/
//! Function Name	: OnBtnSearch
//! Function			: ��ȸ��ư
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CRateDlg::OnBtnSearch()
{
	m_grdRate.SetRowCount(1);		// ��/�� ���� ����
	m_nCount = 0;
	m_nNextRow = 0;

	CString strAccNo;
	m_EdtAcc.GetWindowText(strAccNo);	//�Է��� ���¹�ȣ.

	//���ͷ���� ��ȸ
	theApp.m_khOpenApi.SetInputValue("���¹�ȣ", strAccNo);
	long lRet = theApp.m_khOpenApi.CommRqData("���¼��ͷ�", "OPT10085", 0, m_strScrNo);

	if (!theApp.IsError(lRet))
	{
	}
}

//*******************************************************************/
//! Function Name	: SetRate
//! Function			: ���� ���ͷ� ���
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CRateDlg::SetRate(int nRow, CString strCode)
{
	//�ֽ� ���� ���� ���ͷ� ����̶� �ֽĿ� ������ ���ͷ��� �ٸ��� ������ �˷��帳�ϴ�.

	//���簡
	CString strData, strTmp;
	strData = m_grdRate.GetItemText(nRow, 9);
	strTmp = strData.Left(1);
	if (strTmp == "-" || strTmp == "+")
	{
		strData = strData.Mid(1);
	}
	double nPrice = _ttof(strData);

	//����
	double nQty = _ttof(m_grdRate.GetItemText(nRow, 10));

	//���Աݾ�
	double nPurchase = _ttof(m_grdRate.GetItemText(nRow, 11));

	int nCount(0);
	nCount = m_grdRate.GetRowCount();

	//�ż������ ������ = ���Աݾ� * ��ü������(0.015%) (10���̸� ����)
	m_BuyComm = nPurchase * COMMISSION;
	m_BuyComm = floor(m_BuyComm / 10) * 10;	//(10���̸� ����)

	//�ŵ������ ������ = ���簡 * ���� * ��ü������(0.015%) (10���̸� ����)
	m_SellComm = nPrice * nQty * COMMISSION;
	m_SellComm = floor(m_SellComm / 10) * 10;	//(10���̸� ����)

	//������
	long lMarketType = theApp.m_khOpenApi.GetMarketType(strCode);
	if (lMarketType == 0) //�ŷ���
	{
		//������(�ŷ���) = ���簡 * ���� * 0.15%(���̸� ����) * 2
		m_Tax = nPrice * nQty * COMMISSION1;
		m_Tax = floor(m_Tax) * 2;
	} 
	else if (lMarketType == 10)//�ڽ���
	{
		//������(�ڽ���) = ���簡 * ���� * 0.3%(���̸� ����)
		m_Tax = floor(nPrice * nQty * COMMISSION2);
	}

	CString strTemp;

	//���� �򰡱ݾ� = (���簡 * ����) - �ż������ ������ - �ŵ������ ������ - ������ �����
	m_Eval = (nPrice * nQty) - m_BuyComm - m_SellComm - m_Tax;
	strTemp.Format(_T("%0.lf"), m_Eval);
	m_grdRate.SetItemText(nRow, 5,  theApp.ConvDataFormat(lstFID[5].nDataType, strTemp, lstFID[5].strBeforeData, lstFID[5].strAfterData));
	m_grdRate.SetItemText(nRow, 12,  theApp.ConvDataFormat(lstFID[12].nDataType, strTemp, lstFID[12].strBeforeData, lstFID[12].strAfterData));

	//���� �򰡼��� = �򰡱ݾ� - ���Աݾ�
	m_Profit = m_Eval - nPurchase;
	strTemp.Format(_T("%0.lf"), m_Profit);
	m_grdRate.SetItemText(nRow, 6,  theApp.ConvDataFormat(lstFID[6].nDataType, strTemp, lstFID[6].strBeforeData, lstFID[6].strAfterData));

	//���� ���ͷ� = �򰡼��� / ���Աݾ� * 100
	if (nPurchase == 0)
	{
		m_Rate = 0;
	}
	else
	{
		m_Rate = m_Profit / nPurchase * 100;
	}
	strTemp.Format(_T("%0.2lf"), m_Rate);
	m_grdRate.SetItemText(nRow, 7,  theApp.ConvDataFormat(lstFID[7].nDataType, strTemp, lstFID[7].strBeforeData, lstFID[7].strAfterData));
}

//*******************************************************************/
//! Function Name	: SetRate
//! Function			: ���� ���ͷ� ���
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CRateDlg::SetTotalRate()
{
	int nCnt = m_grdRate.GetRowCount();	//�׸��� Row ���� ���ϱ�
	double dTotalEval(0), dTotalPurchase(0), dTotalProfit, dTotalRate(0);
	CString strTotalEval, strTotalPurchase, strTotalProfit, strTotalRate;

	for (int i = 1; i < nCnt; i++)
	{
		dTotalEval += _ttof(m_grdRate.GetItemText(i, 12));			// �� �򰡱ݾ�
		dTotalPurchase += _ttof(m_grdRate.GetItemText(i, 11));	// �� ���Աݾ�
	}
	
	strTotalEval.Format(_T("%0.lf"), dTotalEval);
	strTotalEval = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalEval);
	m_EdtTotalEval.SetWindowText(strTotalEval);

	strTotalPurchase.Format(_T("%0.lf"), dTotalPurchase);
	strTotalPurchase = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalPurchase);
	m_EdtTotalPurchase.SetWindowText(strTotalPurchase);


	// �� �򰡼���
	dTotalProfit = dTotalEval - dTotalPurchase;
	strTotalProfit.Format(_T("%0.lf"), dTotalProfit);
	strTotalProfit = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalProfit);
	m_EdtTotalProfit.SetWindowText(strTotalProfit);

	// �� ���ͷ�
	dTotalRate = dTotalProfit / dTotalPurchase * 100;
	strTotalRate.Format(_T("%0.2lf"), dTotalRate);
	strTotalRate = theApp.ConvDataFormat(DT_NONE, strTotalRate, "", "%");
	m_EdtTotalRate.SetWindowText(strTotalRate);
}
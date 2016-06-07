//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : KhOpenApiTestDlg.cpp
//! Function      : Ű�� ����API �׽�Ʈ ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// KhOpenApiTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "KhOpenApiTestDlg.h"
#include "afxdialogex.h"

#include "CurrentPriceDlg.h"
#include "OrderDlg.h"
#include "KwanSimDlg.h"
#include "RealAddDlg.h"
#include "RateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKhOpenApiTestDlg ��ȭ ����
//*******************************************************************/
//! Function Name : CKhOpenApiTestDlg::CKhOpenApiTestDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CKhOpenApiTestDlg::IDD, pParent)
//! Function      : ���� �ʱ� ó��
//! Param         : HANDLE hBitmap, int bits
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
CKhOpenApiTestDlg::CKhOpenApiTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKhOpenApiTestDlg::IDD, pParent)
{
	m_nRet = 0;
	m_nScrN0 = 0;
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
void CKhOpenApiTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKhOpenApiTestDlg)
	DDX_Control(pDX, IDC_KHOPENAPICTRL1, theApp.m_khOpenApi);
	//}}AFX_DATA_MAP
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(CKhOpenApiTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_SCRENN_CLOSE,			OnScreenClose)
//	ON_BN_CLICKED(IDC_BTN_CURRENTPRICE,	OnBtnCurrentPrice)
	ON_BN_CLICKED(IDC_BTN_ORDER,		OnBtnOrder)
//	ON_BN_CLICKED(IDC_BTN_KWANSIM,		OnBtnKwanSim)
	ON_BN_CLICKED(IDC_BTN_CURRENTPRICE2, OnBnClickedBtnCurrentprice2)
	ON_BN_CLICKED(IDC_BTN_CON, OnBnClickedBtnReal)
	ON_BN_CLICKED(IDC_BTN_AUTO_ORDER_START, &CKhOpenApiTestDlg::OnBnClickedButton1)	// Emily added
//	ON_BN_CLICKED(IDC_BUTTON1, &CKhOpenApiTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

//*******************************************************************/
// BEGIN_EVENTSINK_MAP
//*******************************************************************/
BEGIN_EVENTSINK_MAP(CKhOpenApiTestDlg, CDialogEx)
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 1, OnReceiveTrDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 2, OnReceiveRealDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 3, OnReceiveMsgKhopenapictrl,		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR )
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 4, OnReceiveChejanData,				VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 5, OnEventConnect,					VTS_I4)
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 7, OnReceiveRealCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 8, OnReceiveTrCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	ON_EVENT(CKhOpenApiTestDlg, IDC_KHOPENAPICTRL1, 9, OnReceiveConditionVer,			VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

//*******************************************************************/
//! Function Name : OnInitDialog
//! Function      : ���� �ʱ� ó��
//! Param         : void
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : CKhOpenApiTestDlg �޽��� ó����
//******************************************************************/
BOOL CKhOpenApiTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString		strTitle;
	GetWindowText(strTitle);
	strTitle += SAMPLE_VERSION;
	SetWindowText(strTitle);
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// OpenApi ���� ó��(�α��� â ����)
	theApp.m_khOpenApi.CommConnect();

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
void CKhOpenApiTestDlg::OnPaint()
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
//! Function Name : OnDestroy
//! Function      : �ı���
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnDestroy()
{
	CString strKey;
	CWnd *pWnd = NULL;
	POSITION pos = m_mapScreen.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreen.GetNextAssoc(pos, strKey, (void *&)pWnd);
		if (pWnd)
		{
			delete pWnd;
			pWnd = NULL;
		}
	}
	m_mapScreen.RemoveAll();
	m_mapScreenNum.RemoveAll();

	// ��� ���� ó��
	theApp.m_khOpenApi.CommTerminate();
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
HCURSOR CKhOpenApiTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name : OnScreenClose
//! Function      : ȭ���� ���� �� ó��
//! Param         : WPARAM wParam, LPARAM lParam
//! Return        : LRESULT
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
LRESULT CKhOpenApiTestDlg::OnScreenClose(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case 0:
			{
				char *cScrNo = (char*)lParam;
				CString strKey, strScrType;
				strKey.Format("%s", cScrNo);
				delete cScrNo;

				if (m_mapScreenNum.Lookup(strKey, strScrType))
				{
					m_mapScreenNum.RemoveKey(strKey);
				}

				CWnd *pWnd = NULL;
				if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
				{
					delete pWnd;
					pWnd = NULL;
				}
				m_mapScreen.RemoveKey(strKey);

				if (theApp.m_khOpenApi.GetSafeHwnd())
				{
					theApp.m_khOpenApi.DisconnectRealData(strKey);
				}
			}
			break;
	}

	return 0L;
}

//*******************************************************************/
//! Function Name : OnBtnCurrentPrice
//! Function      : ���簡 ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnBtnCurrentPrice()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!GetNextScreenNum(0))
	{
		return;
	}

	CCurrentPriceDlg *pCurrentPriceDlg = new CCurrentPriceDlg(this);
	pCurrentPriceDlg->m_strScrNo.Format("%04d", m_nScrN0);
	pCurrentPriceDlg->Create(IDD_CURRENTPRICE_DLG);

	m_mapScreen.SetAt(pCurrentPriceDlg->m_strScrNo, pCurrentPriceDlg);

	// 2���̻��� ���񽺸� ��ȸ �� m_mapScreen�� ȭ���� ����ϱ� ���� 
	// ������ ������ ���� �ͼ� ó���� �Ұ��� �Ͽ� ���⼭ ��ȸ ó�� ��.
	pCurrentPriceDlg->SendSearch();		// ��ȸ ó��
}

//*******************************************************************/
//! Function Name : OnBtnOrder
//! Function      : �ֹ� ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnBtnOrder()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!GetNextScreenNum(1))
	{
		return;
	}

	COrderDlg *pOrderDlg = new COrderDlg(this);
	pOrderDlg->m_strScrNo.Format("%04d", m_nScrN0);
	pOrderDlg->Create(IDD_ORDER_DLG);

	m_mapScreen.SetAt(pOrderDlg->m_strScrNo, pOrderDlg);
}

//*******************************************************************/
//! Function Name : OnBtnKwanSim
//! Function      : ���� ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnBtnKwanSim()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!GetNextScreenNum(2))
	{
		return;
	}

	CKwanSimDlg *pKwanSimDlg = new CKwanSimDlg(this);
	pKwanSimDlg->m_strScrNo.Format("%04d", m_nScrN0);
	pKwanSimDlg->Create(IDD_KWANSIM_DLG);

	m_mapScreen.SetAt(pKwanSimDlg->m_strScrNo, pKwanSimDlg);

	// 2���̻��� ���񽺸� ��ȸ �� m_mapScreen�� ȭ���� ����ϱ� ���� 
	// ������ ������ ���� �ͼ� ó���� �Ұ��� �Ͽ� ���⼭ ��ȸ ó�� ��.
	pKwanSimDlg->SetKwanSimJong();		// ���� �׸��忡 ���� ���� ó��
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (atoi(strScrType))
		{
			case 0:		// ���簡
				{
					((CCurrentPriceDlg *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
				}
				break;
			case 1:		// �ֹ�
				{
					((COrderDlg *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
				}
				break;
			case 2:		// ��������
				{
					((CKwanSimDlg *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
				}
				break;
			case 3:		// ���ǰ˻�
				{
					((CRealAddDlg *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
				}
				break;
			case 4:		// ���ͷ�
				{
					((CRateDlg *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
				}
				break;
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
void CKhOpenApiTestDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CString strRQ = sRQName;
	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		CString strData;
		strData.Format(_T("[%s] [%s] ����"), sRQName, sTrCode);

		CString strRQName = strRQ.Mid(4);
		switch (atoi(strScrType))
		{
			case 0:		// ���簡
				{
					((CCurrentPriceDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
					pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
				}
				break;
			case 1:		// �ֹ�
				{
					((COrderDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
				}
				break;
			case 2:		// ��������
				{
					((CKwanSimDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
					pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
				}
				break;
			case 3:		// ���ǰ˻�
				{
					((CRealAddDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
					pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
				}
				break;
			case 4:	// ���ͷ�
				{
					((CRateDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
				}
				break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : �ǽð� ó��
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (atoi(strScrType))
			{
				case 0:		// ���簡
					{
						((CCurrentPriceDlg *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					}
					break;
				case 1:		// �ֹ�
					{
						((COrderDlg *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					}
					break;
				case 2:		// ��������
					{
						((CKwanSimDlg *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					}
					break;
				case 3:		// ���ǰ˻�
					{
						((CRealAddDlg *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					}
					break;
				case 4:	// ���ͷ�
					{
						((CRateDlg *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					}
					break;
			}
		}
	}

	// �� ���� ó��
	if (!strcmp(sRealType, "����۽ð�"))
	{
		int i;
		CString strData[3], strMsg;
		// 0: ������, 1:�ð�, 2:����� �����ܿ��ð�
		for (i = 0; i < 3; i++)
		{
			strData[i] = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, i);	strData[i].Trim();
// 			strData.Format("%d", i);
// 			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, strData, 0,  _T(""));	strData.Trim();
		}
		strMsg.Format("������ : %s\r\n�ð� : %s\r\n�����ܿ��ð� : %s", strData[0], strData[1], strData[2]);

		if (atoi(strData[2]) == 10)
		{
			ReplyMessage(S_OK);		// SendMessage Ǯ��
			MessageBox(strMsg, "�� ����", MB_ICONINFORMATION | MB_OK);
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : ü���ܰ� �ǽð� ó��
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (atoi(strScrType))
			{
				case 0:		// ���簡
					{
						((CCurrentPriceDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
					}
					break;
				case 1:		// �ֹ�
					{
						((COrderDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
					}
					break;
				case 2:		// ��������
					{
						((CKwanSimDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
					}
					break;
				case 4:		// ���ͷ�
					{
						((CRateDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
					}
					break;
			}
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveRealCondition
//! Function      : ���ǰ˻� �ǽð� ���� ����/����
//! Param         : LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (atoi(strScrType))
			{
			case 3:		// ���ǰ˻�
				{
					((CRealAddDlg *)pWnd)->OnReceiveRealCondition(strCode, strType, strConditionName, strConditionIndex);
				}
				break;
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveTrCondition
//! Function			: ���ǰ˻� ������ȸ ����
//! Param				: LPCTSTR sScrNo					- ȭ���ȣ
//!						: LPCTSTR strCodeList			- ���񸮽�Ʈ
//!						: LPCTSTR strConditionName	- ���Ǹ�
//!						: int nIndex								- ���Ǹ��ε���
//!						: int nNext								- ������ȸ����(2: ������ȸ, 0:������ȸ����)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (atoi(strScrType))
		{
		case 3:	//���ǰ˻�
			{
				((CRealAddDlg *)pWnd)->OnReceiveTrCondition(sScrNo, strCodeList, strConditionName, nIndex, nNext);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveConditionVer
//! Function			: ����� ���ǽ� ����
//! Param				: BOOL bRet							- ����(TRUE), ����(FALSE)
//!						: LPCTSTR sMsg					- �޼���(reserved)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	if(lRet != 1)
	{// ����� ���ǰ˻��� ������û�� ������ �߻��� ���...
		CString		strErr; strErr.Format(_T("%s [%d]"), sMsg, lRet);
		AfxMessageBox(strErr);
		return;
	}

	int nScrNo = GetNextScreenNum(3);
	CString strScrNo;
	strScrNo.Format("%04d", nScrNo);

	CString strScrType, strKey = strScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (atoi(strScrType))
		{
		case 3:	//���ǰ˻�
			{
				((CRealAddDlg *)pWnd)->OnReceiveConditionVer(lRet, sMsg);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnEventConnect
//! Function      : ���� �뺸 ó��
//! Param         : LONG nItemCnt
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKhOpenApiTestDlg::OnEventConnect(LONG nItemCnt)
{
	if (nItemCnt == 0)
	{
		// ���� ����ó��
	}
	else
	{
		// ���� ������ ó��
		EndDialog(IDCANCEL);
	}
}

//*******************************************************************/
//! Function Name : GetNextScreenNum
//! Function      : ���� ȭ�� ��ȣ ���
//! Param         : int nScreenType
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CKhOpenApiTestDlg::GetNextScreenNum(int nScreenType)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	static int nRepeat = 0;
	m_nScrN0++;
	if (m_nScrN0 > 9999)
	{
		nRepeat++;
		m_nScrN0 = 1;
	}

	if (nRepeat > 1)
	{
		nRepeat = 0;
		AfxMessageBox("�� �̻� ȭ���� ���� �����ϴ�.�ٸ� ȭ���� �ݰ� ���� �� �ּ���~!");
		return FALSE;
	}

	CString strKey, strTemp;
	strKey.Format("%04d", m_nScrN0);
	if (m_mapScreenNum.Lookup(strKey, strTemp))
	{
		return GetNextScreenNum(nScreenType);
	}

	nRepeat = 0;
	strTemp.Format("%d", nScreenType);
	m_mapScreenNum.SetAt(strKey, strTemp);
	return TRUE;
}


void CKhOpenApiTestDlg::OnBnClickedBtnCurrentprice2()
{
	CString strTemp = "";
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE2))->GetWindowText(strTemp);
	if (strTemp.GetLength() != 6)
		return;

	CString strRe = theApp.m_khOpenApi.GetMasterStockState(strTemp);
	AfxMessageBox(strRe);
}

void CKhOpenApiTestDlg::OnBnClickedBtnReal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!GetNextScreenNum(3))
	{
		return;
	}

	// ȭ�� ���½� ������ ����� ���ǽ��� �޾ƿ´�.
	// �� �Լ��� ȣ������ ������ ���� ���Ǹ���Ʈ�� �ҷ��ü��� ������ ���� �˻��� �� ���
	// ������ �� �Լ��� ó���� �ҷ��;� �Ѵ�.
	// ���ǰ˻��� �����Ϸ��� �ѹ��� �� ȣ���ؾ��Ѵ�.
	m_nRet = theApp.m_khOpenApi.GetConditionLoad();

	if (m_nRet > 0)
	{
		CRealAddDlg *pRealAddDlg = new CRealAddDlg(this);
		pRealAddDlg->m_strScrNo.Format("%04d", m_nScrN0);
		pRealAddDlg->Create(IDD_CON_SET);

		m_mapScreen.SetAt(pRealAddDlg->m_strScrNo, pRealAddDlg);
	}
}

void CKhOpenApiTestDlg::OnBnClickedButton1()
{
	if (!GetNextScreenNum(4))
	{
		return;
	}

	CRateDlg *pRateDlg = new CRateDlg(this);
	pRateDlg->m_strScrNo.Format(_T("%04d"), m_nScrN0);
	pRateDlg->Create(IDD_RATE);

	m_mapScreen.SetAt(pRateDlg->m_strScrNo, pRateDlg);
}
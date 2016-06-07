//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : OrderDlg.cpp
//! Function      : �ֹ� ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// OrderDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "OrderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COrderDlg ��ȭ ����
//*******************************************************************/
//! Function Name : COrderDlg::COrderDlg(CWnd* pParent /*=NULL*/) : CDialogEx(COrderDlg::IDD, pParent)
//! Function      : ���� �ʱ� ó��
//! Param         : HANDLE hBitmap, int bits
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
COrderDlg::COrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COrderDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "8888";
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
void COrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrderDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST1, m_listCtl);
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(COrderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ORDER,	OnBtnOrder)
	ON_BN_CLICKED(IDC_ORDERTYPE_DEFAULT, &COrderDlg::OnBnClickedOrdertypeDefault)
	ON_BN_CLICKED(IDC_ORDERTYPE_MARGIN, &COrderDlg::OnBnClickedOrdertypeMargin)
	ON_CBN_SELCHANGE(IDC_COM_SBTP, &COrderDlg::OnSelchangeComSbtp)
	ON_CBN_SELCHANGE(IDC_COM_LOAN_TP, &COrderDlg::OnSelchangeComLoanTP)
	ON_BN_CLICKED(IDC_BTN_QRY_LOAN_DATE, &COrderDlg::OnBnClickedQryLoanDate)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &COrderDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()

//*******************************************************************/
//! Function Name : OnInitDialog
//! Function      : ���� �ʱ� ó��
//! Param         : void
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : COrderDlg �޽��� ó����
//******************************************************************/
BOOL COrderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetLimitText(10);		// ���¹�ȣ �ִ���� ����
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetLimitText(6);	// �����ڵ� �ִ���� ����

	// �ֹ��Է� �޺� �ε��� �ʱ�ȭ
	((CComboBox*)GetDlgItem(IDC_COM_TRTP))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COM_SBTP))->SetCurSel(0);

	// �ŷ����� ������ ����
	// 0:������, 3:���尡, 5:���Ǻ�������, 6:������������, 7:�ֿ켱������, 
	// 10:������IOC, 13:���尡IOC, 16:������IOC, 20:������FOK, 23:���尡FOK, 
	// 26:������FOK, 61:�尳�����ð���, 62:�ð��ܴ��ϰ��Ÿ�, 81:�ð�������
	int nTrTpCode[] = {0, 3, 5, 6, 7, 10, 13, 16, 20, 23, 26, 61, 62, 81};
	int i, nCnt = sizeof(nTrTpCode) / sizeof(*nTrTpCode);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		((CComboBox*)GetDlgItem(IDC_COM_TRTP))->SetItemData(i, nTrTpCode[i]);
	}

	/// �ſ��ֹ�
	GetDlgItem(IDC_EDT_ACCNO)->SetWindowText(_T(""));
	/// �����ֹ��� �⺻������...
	((CButton*)GetDlgItem(IDC_ORDERTYPE_DEFAULT))->SetCheck(TRUE);
	OnBnClickedOrdertypeDefault();
	
	/// �űԸż��� �⺻������...
	SetCreditType(0);

	InitFIDName();
	return TRUE;
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
void COrderDlg::OnPaint()
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
void COrderDlg::OnClose()
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

//*******************************************************************/
//! Function Name : OnQueryDragIcon
//! Function      : �巡�� ������ ó��
//! Param         : void
//! Return        : HCURSOR
//! Create        : , 2014/06/02
//! Comment       : ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ��� 
//!               : �� �Լ��� ȣ���մϴ�.
//******************************************************************/
HCURSOR COrderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name : OnBtnOrder
//! Function      : �ֹ� ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnBtnOrder()
{
	// ���¹�ȣ �Է� ����
	CString strAccNo;
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->GetWindowText(strAccNo);
	if (strAccNo.GetLength() != 10)
	{
		AfxMessageBox("���¹�ȣ 10�ڸ� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetFocus();
		return;
	}

	// �����ڵ� �Է� ����
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(m_strJongCode);
	if (m_strJongCode.GetLength() != 6)
	{
		AfxMessageBox("�����ڵ� 6�ڸ� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	// �ֹ����� �Է� ����
	CString strQty;
	((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->GetWindowText(strQty);
	int lQty = atol(strQty);
	if (lQty < 1)
	{
		AfxMessageBox("�ֹ������� 0���� ū ���� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->SetFocus();
		return;
	}

	// �ŷ����� ���
	// 0:������, 3:���尡, 5:���Ǻ�������, 6:������������, 7:�ֿ켱������, 
	// 10:������IOC, 13:���尡IOC, 16:������IOC, 20:������FOK, 23:���尡FOK, 
	// 26:������FOK, 61:�尳�����ð���, 62:�ð��ܴ��ϰ��Ÿ�, 81:���Ľð�������
	CString strHogaGb;
	int		nIndex = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetCurSel();
	DWORD	dwData = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetItemData(nIndex);
	strHogaGb.Format(_T("%02d"), dwData);

	// �ֹ����� �Է� ����
	CString strPrice;
	((CEdit*)GetDlgItem(IDC_EDT_PRICE))->GetWindowText(strPrice);
	long lPrice = atoi(strPrice);
	if (dwData != 3 && dwData != 13 && dwData != 23 && lPrice < 1)
	{
		AfxMessageBox("�ֹ������� 0���� ū ���� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_PRICE))->SetFocus();
		return;
	}

	// �Ÿű��� ���(1:�űԸż�, 2:�űԸŵ� 3:�ż����, 4:�ŵ����, 5:�ż�����, 6:�ŵ�����)
	long lOrderType = ((CComboBox*)GetDlgItem(IDC_COM_SBTP))->GetCurSel() + 1;

	// ���ֹ���ȣ �Է� ����
	CString strOrgNo;
	((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->GetWindowText(strOrgNo);
	if (lOrderType > 2 && strOrgNo.GetLength() < 1)
	{
		AfxMessageBox("���ֹ���ȣ�� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetFocus();
		return;
	}

	/// ����(����)�ֹ����� �ſ��ֹ����� üũ...
	int	nCheckedOrder = GetCheckedRadioButton(IDC_ORDERTYPE_DEFAULT, IDC_ORDERTYPE_MARGIN);

	CString strRQName = _T("�ֽ��ֹ�");
	int i;
	long lRet;
//	for (i = 0; i < 10; i++)
	{
		// �ֹ����� ������ �� �ֹ����� ���� �� ������ ��� ������ ó��.
		lRet = OP_ERR_ORD_OVERFLOW;
	//	while (lRet == OP_ERR_ORD_OVERFLOW)
		{
			if(nCheckedOrder == IDC_ORDERTYPE_DEFAULT)
			{/// ����(����)�ֹ��̸�...
				lRet = theApp.m_khOpenApi.SendOrder(strRQName, m_strScrNo, strAccNo, lOrderType, m_strJongCode, lQty, lPrice, strHogaGb, strOrgNo);
			}
			else if(nCheckedOrder == IDC_ORDERTYPE_MARGIN)
			{/// �ſ��ֹ��̸�...
				/// �ſ뱸�� �� ����(�ż�, �ŵ�)�� �ſ뱸�а��� ������ ����...
				/// �ſ�ż� : �ڱ����� (03)
				/// �ſ�ŵ� : �ڱ����� (33), �ڱ�������(99)
				CString		strCreditType(GetLoanType());

				/// ������ 
				/// �ſ�ŵ� �ڱ�����(33)�϶��� ��Ȯ�� ������ �ʿ�
				CString		strLoandDate(GetLoanDate());
				lRet = theApp.m_khOpenApi.SendOrderCredit(strRQName, m_strScrNo, strAccNo, lOrderType, m_strJongCode, lQty, lPrice, strHogaGb, strCreditType, strLoandDate, strOrgNo);
			}

			if (lRet == OP_ERR_ORD_OVERFLOW)
			{
				Sleep(300);
			}
		}
	}
	if (!theApp.IsError(lRet))
	{
		return;
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
void COrderDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("�ֽ��ֹ�"))		// �ֽı⺻���� ����
	{
		// �ֹ� ��ȣ
		CString strData = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("�ֹ���ȣ"));	strData.Trim();
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetWindowText(strData);
	}
	else if(strRQName == _T("��������ȸ"))
	{/// 
		CString		strTRCode(sTrcode);
		int		nCnt = theApp.m_khOpenApi.GetRepeatCnt(strTRCode, _T(""));
		
		if(nCnt < 1)
		{
			m_listCtl.AddString(_T("������ ��ȸ �ݺ������� ����."));
			return;
		}

		CString		strSymbol, strSymbolName, strLoanDate, strText;
		for(int nIdx = 0; nIdx < nCnt; nIdx++)
		{
			strSymbol		= theApp.m_khOpenApi.CommGetData(strTRCode, _T(""), _T(""), nIdx, _T("�����ȣ"));
			strSymbolName	= theApp.m_khOpenApi.CommGetData(strTRCode, _T(""), _T(""), nIdx, _T("�����"));
			strLoanDate		= theApp.m_khOpenApi.CommGetData(strTRCode, _T(""), _T(""), nIdx, _T("������"));

			strSymbol.Trim();
			if(!strSymbol.IsEmpty())
			{
				strSymbol = strSymbol.Mid(1, 6);
			}
			strSymbolName.Trim();
			strLoanDate.Trim();
			strText.Format(_T("������[%s]    �����ȣ[%s]    �����[%s] \n"), strLoanDate, strSymbol, strSymbolName);
			m_listCtl.AddString(strText);
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
void COrderDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	((CStatic*)GetDlgItem(IDC_STC_MSGBAR))->SetWindowText(sMsg);
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : �ǽð� ó��
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

void COrderDlg::InitFIDName()
{
	m_mapFIDName.SetAt(_T("9201")	, _T("���¹�ȣ"));
	m_mapFIDName.SetAt(_T("9203")	, _T("�ֹ���ȣ"));
	m_mapFIDName.SetAt(_T("9001")	, _T("�����ڵ�"));
	m_mapFIDName.SetAt(_T("913")	, _T("�ֹ�����"));
	m_mapFIDName.SetAt(_T("302")	, _T("�����"));
	m_mapFIDName.SetAt(_T("900")	, _T("�ֹ�����"));
	m_mapFIDName.SetAt(_T("901")	, _T("�ֹ�����"));
	m_mapFIDName.SetAt(_T("902")	, _T("��ü�����"));
	m_mapFIDName.SetAt(_T("903")	, _T("ü�ᴩ��ݾ�"));
	m_mapFIDName.SetAt(_T("904")	, _T("���ֹ���ȣ"));
	m_mapFIDName.SetAt(_T("905")	, _T("�ֹ�����"));
	m_mapFIDName.SetAt(_T("906")	, _T("�Ÿű���"));
	m_mapFIDName.SetAt(_T("907")	, _T("�ŵ�������"));
	m_mapFIDName.SetAt(_T("908")	, _T("�ֹ�/ü��ð�"));
	m_mapFIDName.SetAt(_T("909")	, _T("ü���ȣ"));
	m_mapFIDName.SetAt(_T("910")	, _T("ü�ᰡ"));
	m_mapFIDName.SetAt(_T("911")	, _T("ü�ᷮ"));
	m_mapFIDName.SetAt(_T("10")		, _T("���簡"));
	m_mapFIDName.SetAt(_T("27")		, _T("(�ֿ켱)�ŵ�ȣ��"));
	m_mapFIDName.SetAt(_T("28")		, _T("(�ֿ켱)�ż�ȣ��"));
	m_mapFIDName.SetAt(_T("914")	, _T("����ü�ᰡ"));
	m_mapFIDName.SetAt(_T("915")	, _T("����ü�ᷮ"));
	m_mapFIDName.SetAt(_T("919")	, _T("�źλ���"));
	m_mapFIDName.SetAt(_T("920")	, _T("ȭ���ȣ"));

	m_mapFIDName.SetAt(_T("917")	, _T("�ſ뱸��"));
	m_mapFIDName.SetAt(_T("916")	, _T("������"));
	m_mapFIDName.SetAt(_T("930")	, _T("��������"));
	m_mapFIDName.SetAt(_T("931")	, _T("���Դܰ�"));
	m_mapFIDName.SetAt(_T("932")	, _T("�Ѹ��԰�"));
	m_mapFIDName.SetAt(_T("933")	, _T("�ֹ����ɼ���"));
	m_mapFIDName.SetAt(_T("945")	, _T("���ϼ��ż�����"));
	m_mapFIDName.SetAt(_T("946")	, _T("�ŵ�/�ż�����"));
	m_mapFIDName.SetAt(_T("950")	, _T("�����Ѹŵ�����"));
	m_mapFIDName.SetAt(_T("951")	, _T("������"));
	m_mapFIDName.SetAt(_T("307")	, _T("���ذ�"));
	m_mapFIDName.SetAt(_T("8019")	, _T("������"));
	m_mapFIDName.SetAt(_T("957")	, _T("�ſ�ݾ�"));
	m_mapFIDName.SetAt(_T("958")	, _T("�ſ�����"));
	m_mapFIDName.SetAt(_T("918")	, _T("������"));
	m_mapFIDName.SetAt(_T("990")	, _T("���Ͻ�������(����"));
	m_mapFIDName.SetAt(_T("991")	, _T("���Ͻ������ͷ�(����"));
	m_mapFIDName.SetAt(_T("992")	, _T("���Ͻ�������(�ſ�"));
	m_mapFIDName.SetAt(_T("993")	, _T("���Ͻ������ͷ�(�ſ�"));

	m_mapFIDName.SetAt(_T("397")	, _T("�Ļ���ǰ�ŷ�����"));
	m_mapFIDName.SetAt(_T("305")	, _T("���Ѱ�"));
	m_mapFIDName.SetAt(_T("306")	, _T("���Ѱ�"));
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : ü���ܰ� �ǽð� ó��
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	CString strGubun(sGubun), strFidList(sFidList), strText;
	CString	strAccNo, strOrdNo, strOrdPrice, strOrdCnt;

	int			nIndex(0);
	LONG		lFid;
	CString		strFID, strOneData, strFIDName;
	while(AfxExtractSubString(strFID, strFidList, nIndex++, _T(';')))
	{
		if(m_mapFIDName.Lookup(strFID, strFIDName) == FALSE)
			strFIDName = strFID;

		if(strFIDName.IsEmpty())	strFIDName = strFID;

		strOneData = theApp.m_khOpenApi.GetChejanData(atoi(strFID)).Trim();
		
		strText.Format(_T("����[%s] FID[%4s:%s] = [%s]"),strGubun, strFID, strFIDName, strOneData);
		m_listCtl.AddString(strText);
		strFIDName.Empty();
	}
}

///////////////////////////////////////////////////////////
///////////////////// �ſ��ֹ����� ó��. /////////////////////
///////////////////////////////////////////////////////////
void COrderDlg::OnBnClickedOrdertypeDefault()
{/// ����(����)�ֹ� ����......
	/// �ſ��ֹ����� ��Ʈ���� ��Ȱ�� ��Ų��...
	EnableCreditOrderControl(FALSE);
	((CComboBox*)(GetDlgItem(IDC_COM_CREDIT_TP)))->SetCurSel(0);	
}

void COrderDlg::OnBnClickedOrdertypeMargin()
{/// �ſ��ֹ� ����....
	/// �ſ��ֹ����� ��Ʈ���� Ȱ�� ��Ų��...
	EnableCreditOrderControl(TRUE);
	((CComboBox*)(GetDlgItem(IDC_COM_CREDIT_TP)))->SetCurSel(0);

	OnSelchangeComSbtp();
}

void COrderDlg::EnableCreditOrderControl(BOOL bEnable)
{/// �ſ��ֹ� ���� ��Ʈ�� Ȱ��/��Ȱ��
	GetDlgItem(IDC_STATIC_CREDIT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COM_CREDIT_TP)->EnableWindow(bEnable);		/// �ſ뱸��
	GetDlgItem(IDC_STATIC_LOAN_DATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_LOAN_DATE)->EnableWindow(bEnable);			/// ������
	GetDlgItem(IDC_STATIC_LOAN)->EnableWindow(bEnable);			/// ���ڱ���
	GetDlgItem(IDC_COM_LOAN_TP)->EnableWindow(bEnable);			/// �����޺�
	GetDlgItem(IDC_BTN_QRY_LOAN_DATE)->EnableWindow(bEnable);	/// ������
}

void COrderDlg::OnSelchangeComSbtp()
{/// �Ÿ����� �����...

	int	nChecked = GetCheckedRadioButton(IDC_ORDERTYPE_DEFAULT, IDC_ORDERTYPE_MARGIN);
	if(nChecked == IDC_ORDERTYPE_DEFAULT)
	{/// ����(����)�ֹ��� ���...
		EnableCreditOrderControl(FALSE);
		return;
	}

	/// �ſ��ֹ��϶���....	
	EnableCreditOrderControl(TRUE);

	int	nCurSel = ((CComboBox*)(GetDlgItem(IDC_COM_SBTP)))->GetCurSel();
	SetCreditType(nCurSel);
}

void COrderDlg::SetCreditType(int nIndex)
{/// �Ÿ������� ���� �ſ뱸�а��� �����Ѵ�.

	/// �ſ�ż� : �ڱ����ڸż� (03)
	/// �ſ�ŵ� : �ڱ����ڻ�ȯ (33), �ڱ������ջ�(99)
	CComboBox	*pCreditGb	= ((CComboBox*)(GetDlgItem(IDC_COM_CREDIT_TP)));
	CComboBox	*pLoanGb	= ((CComboBox*)(GetDlgItem(IDC_COM_LOAN_TP)));
	
	ASSERT(pCreditGb	!= NULL);
	ASSERT(pLoanGb		!= NULL);

	if(pCreditGb	== NULL)	return;
	if(pLoanGb		== NULL)	return;

	pCreditGb->ResetContent();
	pLoanGb->ResetContent();

	BOOL	bEnable = FALSE;
	if(nIndex == 0)
	{/// �űԸż� �ֹ�
		pCreditGb->AddString(_T("�ڱ����ڸż�   (03)"));
		pLoanGb->AddString(_T("����            (03)"));
		/// �ſ�ż� �ֹ��� �������� ��Ȱ��...
		/// �ſ�ż� �ֹ��� ������ ��ȸ�� ��Ȱ��
		bEnable = FALSE;
	}
	else if(nIndex == 1)
	{/// �űԸŵ� �ֹ�
		pCreditGb->AddString(_T("�ڱ����ڻ�ȯ   (33)"));
		pLoanGb->AddString(_T("����            (33)"));
		pLoanGb->AddString(_T("������           (99)"));
		
		/// �ſ�ŵ� �ֹ��� �������� Ȱ��...
		/// �ſ�ŵ� �ֹ��� ������ ��ȸ�� Ȱ��
		bEnable = TRUE;
	}
	else
	{
		EnableCreditOrderControl(FALSE);
		return;
	}

	GetDlgItem(IDC_LOAN_DATE)->EnableWindow(bEnable);
	//GetDlgItem(IDC_BTN_QRY_LOAN_DATE)->EnableWindow(bEnable);
	pCreditGb->SetCurSel(0);
	pLoanGb->SetCurSel(0);
}

void COrderDlg::OnSelchangeComLoanTP()
{/// �ſ�ŵ� �ֹ� "����(33)"�϶��� �������� Ȱ��ȭ...
	CComboBox	*pLoanGb = ((CComboBox*)(GetDlgItem(IDC_COM_LOAN_TP)));
	
	BOOL	bEnable = TRUE;
	/// "����"�϶��� ...
	if(pLoanGb->GetCurSel() == 1)
	{/// ������(99)�̸� ��Ȱ����Ų��.
		bEnable = FALSE;
	}
	else
	{/// ����(33)�϶��� Ȱ��ȭ
		bEnable	= TRUE;
	}

	GetDlgItem(IDC_LOAN_DATE)->EnableWindow(bEnable);
	//GetDlgItem(IDC_BTN_QRY_LOAN_DATE)->EnableWindow(bEnable);
}

CString	COrderDlg::GetLoanType()
{/// �ſ뱸�а��� ��´�....
	CString		strLoanType (_T("03"));
	/// �ſ��ֹ� ����(�ż�, �ŵ�)�� �ſ뱸�а��� ������ ����...
	/// �ſ�ż� : �ڱ����� (03)
	/// �ſ�ŵ� : �ڱ����� (33), �ڱ�������(99)

	/// �ż��ֹ�����, �ŵ��ֹ����� ��´�....
	int	nOrderType = ((CComboBox*)(GetDlgItem(IDC_COM_SBTP)))->GetCurSel();
	if(nOrderType == 1)	
	{/// �ŵ��ֹ��̸�
		/// ��������, ���������� ã�´�...
		int nIdx = ((CComboBox*)GetDlgItem(IDC_COM_LOAN_TP))->GetCurSel();

		if(		nIdx == 0)	strLoanType = _T("33");	/// ����
		else if(nIdx == 1)	strLoanType = _T("99");	/// ������
	}
	else if(nOrderType == 0)
	{/// �ż��ֹ��̸�...
		strLoanType = _T("03");
	}

	return	strLoanType;
}

CString	COrderDlg::GetLoanDate()
{/// �������� ��´�...
	/// ������ ������ YYYYMMDD, �� 20150101 �̷��� �Է��ؾ� �Ѵ�.
	/// �ſ�ŵ��� ����(33)�϶� ���� �������� �Է�.
	/// �ſ�ŵ��� ������(99)���� �����ϸ� ���忡�� ó��
	int	nOrderType = ((CComboBox*)(GetDlgItem(IDC_COM_SBTP)))->GetCurSel();
	if(nOrderType == 0)
	{/// �ſ�ż� �ű��ֹ��϶� �������� ��������ó��.
		return _T("");
	}
	else if(nOrderType == 1)
	{/// �ſ�ŵ� ������(99) �ϰ��ŵ��� "99991231"�� ������������...
		CString		strCreditType(GetLoanType());
		if(strCreditType == _T("99"))	return	_T("99991231");
	}

	CString		strLoanDate;
	GetDlgItem(IDC_LOAN_DATE)->GetWindowText(strLoanDate);
	strLoanDate.Remove(_T('-'));
	return	strLoanDate;
}

void COrderDlg::OnBnClickedQryLoanDate()
{/// ������ ��ȸ...
	/// ������ ��ȸ�� �ſ�ŵ� ��Ȳ(���� 33)�϶��� ó��.
	int nIdx = ((CComboBox*)GetDlgItem(IDC_COM_LOAN_TP))->GetCurSel();
	if(	nIdx != 0)	return;

	/// TR : OPW00005 ü���ܰ��û
	/// ���¹�ȣ : �ſ���¹�ȣ
	/// ��й�ȣ : ����
	/// ��й�ȣ�Է¸�ü���� : 00

	CString strAccNo;
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->GetWindowText(strAccNo);
	if (strAccNo.GetLength() != 10)
	{
		AfxMessageBox("���¹�ȣ 10�ڸ� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetFocus();
		return;
	}
	theApp.m_khOpenApi.SetInputValue("���¹�ȣ"			, strAccNo);
	theApp.m_khOpenApi.SetInputValue("��й�ȣ"			, _T(""));
	theApp.m_khOpenApi.SetInputValue("��й�ȣ�Է¸�ü����"	, _T("00"));

	LONG lRet = theApp.m_khOpenApi.CommRqData(_T("��������ȸ"), _T("OPW00005"), 0, m_strScrNo);

	if (!theApp.IsError(lRet))
	{
		return;
	}
}

void COrderDlg::OnBnClickedBtnClear()
{/// �ֹ���� ����
	m_listCtl.ResetContent();
}

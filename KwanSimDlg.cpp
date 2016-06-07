//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : KwanSimDlg.cpp
//! Function      : ���� ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// KwanSimDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "KwanSimDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString m_strRealSet = "�ֽĽü�;�ֽ�ü��";

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPTKWFID[] = 
{
	{"�����ڵ�",		"-1",	-1,	0,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	{"�����",			"-1",	-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	{"���簡",			"0",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"���ϴ���ȣ",	"10",	-1,	3,	DT_SIGN,		TRUE,	DT_CENTER,	"",	""}, 
	{"���ϴ��",		"1",	-1,	4,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"�����",			"2",	-1,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	{"�ŷ���",			"5",	-1,	6,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"���ϰŷ������",	"13",	-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
};

// �ǽð� �ֹ�ü��(���簡 ǥ�ÿ�)
const stGRID lstOPTKWFID_B[] = 
{
	{"�����ڵ�",		"-1",	-1,	0,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	{"�����",			"-1",	-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	"",	""}, 
	{"���簡",			"1",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"���ϴ���ȣ",	"12",	-1,	3,	DT_SIGN,		TRUE,	DT_CENTER,	"",	""}, 
	{"���ϴ��",		"2",	-1,	4,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	""}, 
	{"�����",			"3",	-1,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
	{"�ŷ���",			"7",	-1,	6,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	""}, 
	{"���ϰŷ������",	"15",	-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%"}, 
};

// CKwanSimDlg ��ȭ ����
//*******************************************************************/
//! Function Name : CKwanSimDlg::CKwanSimDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CKwanSimDlg::IDD, pParent)
//! Function      : ���� �ʱ� ó��
//! Param         : HANDLE hBitmap, int bits
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
CKwanSimDlg::CKwanSimDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKwanSimDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "9999";
	m_cellSelect.row = 0;
	m_cellSelect.col = 0;
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
void CKwanSimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKwanSimDlg)
	DDX_Control(pDX, IDC_GRD_KWANSIM,		m_grdKwanSim);
	//}}AFX_DATA_MAP
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(CKwanSimDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_JONGADD,			OnBtnJongAdd)
	ON_BN_CLICKED(IDC_BTN_JONGDELETE,		OnBtnJongDelete)
	ON_BN_CLICKED(IDC_BTN_JONGALLDELETE,	OnBtnJongAllDelete)
	ON_BN_CLICKED(IDC_BTN_SEARCH,			OnBtnSearch)
END_MESSAGE_MAP()

//*******************************************************************/
//! Function Name : OnInitDialog
//! Function      : ���� �ʱ� ó��
//! Param         : void
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : CKwanSimDlg �޽��� ó����
//******************************************************************/
BOOL CKwanSimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetLimitText(6);	// �����ڵ� �ִ���� ����

	InitKwanSimGrid();					// ���� �׸��� �ʱ� ó��

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
void CKwanSimDlg::OnPaint()
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
void CKwanSimDlg::OnClose()
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
HCURSOR CKwanSimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name : OnBtnJongAdd
//! Function      : �����߰� ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::OnBtnJongAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// �����ڵ� �Է� ����
	CString strCode, strIndex;
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(strCode);
	if (strCode.GetLength() != 6)
	{
		AfxMessageBox("�����ڵ� 6�ڸ� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	if (m_mapJongCode.Lookup(strCode, strIndex))
	{
		AfxMessageBox("�̹� ��� �� �����Դϴ�.");
		CCellID cureentCell(atoi(strIndex), 0);
		m_grdKwanSim.SetFocusCell(cureentCell);
		m_grdKwanSim.SetSelectedRange(cureentCell.row, 0, cureentCell.row, 7);
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
	int nCnt = ::GetPrivateProfileInt("JONG_CODE", "COUNT", 0,strFileName) + 1;

	// �����ڵ� ���� �߰�
	strIndex.Format("%d", nCnt);
	::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);

	// �����ڵ� �߰�
	::WritePrivateProfileString("JONG_CODE", strIndex, strCode, strFileName);
	m_mapJongCode.SetAt(strCode, strIndex);

	// �� �߰�
	m_grdKwanSim.InsertRow("", -1);
	m_grdKwanSim.SetRowHeight(1, 20);		// ���� ���� ����
	m_grdKwanSim.SetItemFormat(lstOPTKWFID[nCnt].nRow, lstOPTKWFID[nCnt].nCol, lstOPTKWFID[nCnt].nAlign);
	m_grdKwanSim.SetItemText(nCnt, 0, strCode);

	// ���� ��ȸ ��û
	SendJongSearch(1, strCode, 5);
}

//*******************************************************************/
//! Function Name : OnBtnJongDelete
//! Function      : ������� ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::OnBtnJongDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nCnt = m_grdKwanSim.GetRowCount();
	if (nCnt > 2)
	{
		m_cellSelect = m_grdKwanSim.GetFocusCell();
		if (m_cellSelect.row < 1 || m_cellSelect.row > nCnt - 1)
		{
			return;
		}
		CString strTemp;
		strTemp.Format("�������� [%s %s] �� ���� �ϰڽ��ϱ�?", 
			m_grdKwanSim.GetItemText(m_cellSelect.row, 0), 
			m_grdKwanSim.GetItemText(m_cellSelect.row, 1));
		if (MessageBox(strTemp, "�������� ����", MB_ICONQUESTION | MB_YESNO) == IDNO)
		{
			return;
		}

		nCnt--;
		m_grdKwanSim.DeleteRow(m_cellSelect.row);
		m_mapJongCode.RemoveAll();

		CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
		// �����ڵ� ���� �߰�
		CString strIndex, strCode;
		strIndex.Format("%d", nCnt - 1);
		::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);

		// ���� �缳��
		int i;
		for (i = 1; i < nCnt; i++)
		{
			strIndex.Format("%d", i);
			strCode = m_grdKwanSim.GetItemText(i, 0);

			// �����ڵ� �߰�
			::WritePrivateProfileString("JONG_CODE", strIndex, strCode, strFileName);
			m_mapJongCode.SetAt(strCode, strIndex);
		}

		SendJongSearch();		// ���� ��ȸ ��û
	}
	else
	{
		OnBtnJongAllDelete();
	}
}

//*******************************************************************/
//! Function Name : OnBtnJongAllDelete
//! Function      : ��ü���� ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::OnBtnJongAllDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (MessageBox("���������� ��ü���� �ϰڽ��ϱ�?", "�������� ��ü����", MB_ICONQUESTION | MB_YESNO) == IDNO)
	{
		return;
	}
	// ���ϻ���
	CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
	::DeleteFile(strFileName);
	m_mapJongCode.RemoveAll();		// �����ڵ� �ʱ�ȭ
	m_grdKwanSim.SetRowCount(1);	// �׸��� �ʱ�ȭ

	m_grdKwanSim.Invalidate();
}

//*******************************************************************/
//! Function Name : OnBtnSearch
//! Function      : ��ȸ ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::OnBtnSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cellSelect.row = 0;
	m_cellSelect.col = 0;
	m_grdKwanSim.SetRowCount(1);
	SetKwanSimJong();					// ���� �׸��忡 ���� ���� ó��
}

//*******************************************************************/
//! Function Name : InitKwanSimGrid
//! Function      : ȣ�� �׸��� �ʱ� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::InitKwanSimGrid()
{
	m_grdKwanSim.SetEditable(false);				//cell�� ����Ʈ ���ϰ� ��.
	m_grdKwanSim.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(215, 227, 241);

	// ���� ��/�� ����
	m_grdKwanSim.SetFixedRowCount(1);

	// ��/�� ���� ����
	m_grdKwanSim.SetRowCount(1);
	m_grdKwanSim.SetColumnCount(8);

	// ���� ���� ����
	int i, nWidth[] = {50, 80, 80, 20, 60, 60, 80, 80};
	CString strHeader[] = {"�ڵ�", "�����", "���簡", "", "���ϴ��", "�����", "�ŷ���", "�ŷ������"};
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		m_grdKwanSim.SetColumnWidth(i, nWidth[i]);
		m_grdKwanSim.SetItemFormat(0, i, DT_CENTER);
		m_grdKwanSim.SetItemText(0, i, strHeader[i]);
		m_grdKwanSim.SetItemBkColour(0, i, clr);	// ������ ���� ���� ����
	}

	// ���� ���� ����
	m_grdKwanSim.SetRowHeight(0, 24);

	m_grdKwanSim.Invalidate();
}

//*******************************************************************/
//! Function Name : SetKwanSimJong
//! Function      : ���� �׸��忡 ���� ���� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::SetKwanSimJong()
{
	CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
	int i, nCnt = ::GetPrivateProfileInt("JONG_CODE", "COUNT", 0, strFileName) + 1;

	char szItem[12];
	int nSize = sizeof(szItem);
	CString strCode, strIndex, strCodeList = "";
	m_grdKwanSim.SetRowCount(nCnt);
	m_mapJongCode.RemoveAll();
	for (i = 1; i < nCnt; i++)
	{
		strIndex.Format("%d", i);
		memset(szItem, 0, nSize);
		::GetPrivateProfileString("JONG_CODE", strIndex, "", szItem, nSize, strFileName);
		strCode = szItem;		strCode.Trim();

		// �����ڵ� �߰�
		m_mapJongCode.SetAt(strCode, strIndex);

		m_grdKwanSim.SetRowHeight(i, 20);		// ���� ���� ����
		m_grdKwanSim.SetItemText(i, 0, strCode);

		strCodeList += strCode + ";";
	}

	if (!strCodeList.IsEmpty())
	{
		// ���� ��ȸ ��û
		SendJongSearch(nCnt - 1, strCodeList);
	}

	m_grdKwanSim.Invalidate();
}

//*******************************************************************/
//! Function Name : SendJongSearch
//! Function      : ���� ��ȸ ��û
//! Param         : int nCodeCount/* = 0*/, CString strCodeList/* = ""*/ : ���� - "000660;005930;", int nAddType/*= 0*/ ���� ������ȸ���� �߰��� ������ ��ȸ�Ҷ� ����(0:�⺻, 5:�߰�)
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::SendJongSearch(int nCodeCount/* = 0*/, CString strCodeList/* = ""*/, int nAddType/*= 0*/)
{
	if (nCodeCount < 1 || strCodeList.GetLength() < 1)
	{
		int i, nCnt = m_grdKwanSim.GetRowCount();
		if (nCnt < 2)
		{
			return;
		}
		nCodeCount = 0;
		for (i = 1; i < nCnt; i++)
		{
			nCodeCount++;
			strCodeList += m_grdKwanSim.GetItemText(i, 0) + ";";
		}
	}

	if (nCodeCount > 0 && strCodeList.GetLength() > 0)
	{
		CString strRQName = _T("��������");
		long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, nAddType, strRQName, m_strScrNo);
		if (!theApp.IsError(lRet))
		{
			return;
		}
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
void CKwanSimDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("��������"))			// ������������ ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPTKWFID) / sizeof(*lstOPTKWFID);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("������������");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPTKWFID[j].strKey);	strData.Trim();
//				strData = theApp.m_khOpenApi.CommGetData(sTrcode, _T(""), strRQName, i, lstOPTKWFID[j].strKey);	strData.Trim();
				m_grdKwanSim.SetItemFormat(i + 1, lstOPTKWFID[j].nCol, lstOPTKWFID[j].nAlign);
				arrData.Add(strData);
			}
			SetDataKwanSimGrid(arrData);
		}
		if (m_cellSelect.row > 0)
		{
			if (m_cellSelect.row >= m_grdKwanSim.GetRowCount())
			{
				m_cellSelect.row = m_grdKwanSim.GetRowCount() - 1;
			}
			m_grdKwanSim.SetFocusCell(m_cellSelect);
			m_grdKwanSim.SetSelectedRange(m_cellSelect.row, m_cellSelect.col, m_cellSelect.row, m_cellSelect.col);
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
void CKwanSimDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
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
void CKwanSimDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	CString strIndex;
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex) || m_strRealSet.Find(sRealType) < 0)
	{
		return;
	}

	CString strData;
	CStringArray arrData;
	if (!strcmp(sRealType, "�ֽĽü�"))		// �ֽĽü�
	{
		arrData.Add(sJongmokCode);
		int i, nFieldCnt = sizeof(lstOPTKWFID) / sizeof(*lstOPTKWFID);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 1; i < nFieldCnt; i++)
		{
			if (atoi(lstOPTKWFID[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPTKWFID[i].strRealKey));	strData.Trim();
//			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, lstOPTKWFID[i].strRealKey, 0,  _T(""));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataKwanSimGrid(arrData, sRealType);
	}
	else if (!strcmp(sRealType, "�ֽ�ü��"))	// �ֽ�ü��
	{
		arrData.Add(sJongmokCode);
		int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 1; i < nFieldCnt; i++)
		{
			if (atoi(lstOPTKWFID[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
//			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, lstOPTKWFID_B[i].strRealKey, 0,  _T(""));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataKwanSimGrid(arrData, sRealType);
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
void CKwanSimDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
// 	CString strGubun, strFidList, strFid, strData, strText;
// 	int nIndex(0);
// 	strGubun	= sGubun;
// 	strFidList	= sFidList;
// 
// 	m_listCtrl.AddString("ü������");
// 	while ( AfxExtractSubString( strFid, strFidList, nIndex++, _T(';')) )
// 	{
// 		strData = m_openApi.CommGetData(strGubun, _T("-1"), strFid, 0, _T(""));
// 
// 		strText.Format(_T("[%s] : %s"), strFid, strData);
// 		m_listCtrl.AddString(strText);
// 	}
}

//*******************************************************************/
//! Function Name : SetDataKwanSimGrid
//! Function      : ���� �׸��� ����Ÿ ����(������������ ����)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CKwanSimDlg::SetDataKwanSimGrid(CStringArray &arrData, CString strRealType/* = ""*/)
{
	// �����ڵ忡 �´� �� ã��
	CString strData, strTemp;
	strData = arrData.GetAt(0);
	if (!m_mapJongCode.Lookup(strData, strTemp))
	{
		return;
	}

	// �����
	int i, nRow = atol(strTemp), nCnt = arrData.GetSize();
	if (strRealType == "")
	{
		CString strName = arrData.GetAt(1);
		((CStatic*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(strTemp);	// �����ڵ� �Է¶�
		if (strTemp == strData)
		{
			((CStatic*)GetDlgItem(IDC_STC_JONGNAME))->SetWindowText(strName);
		}
		m_grdKwanSim.SetItemText(nRow, lstOPTKWFID[1].nCol, theApp.ConvDataFormat(lstOPTKWFID[1].nDataType, strName, lstOPTKWFID[1].strBeforeData, lstOPTKWFID[1].strAfterData));
	}

	// ����Ÿ ����
	CString strTempData;
	for (i = 2; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		/////////////////////////////////////////////
		// ���� �� ������ ���� ó������������
		if (strRealType != "" && (i == 2 || i == 4 || i == 5))
		{
			strTempData = strData;
			strTempData.Replace("+", "");	strTempData.Replace("-", "");	strTempData.Replace(".", "");

			strTemp = m_grdKwanSim.GetItemText(nRow, lstOPTKWFID[i].nCol);
			strTemp.Replace("%", "");	strTemp.Replace("+", "");	strTemp.Replace("-", "");
			strTemp.Replace(",", "");	strTemp.Replace(".", "");
			if (strTempData != strTemp)
			{
				m_cellSelect.col = lstOPTKWFID[i].nCol;
				m_grdKwanSim.SetFocusCell(m_cellSelect);
				m_grdKwanSim.SetSelectedRange(nRow, m_cellSelect.col, nRow, m_cellSelect.col);
				m_grdKwanSim.Invalidate();
			}
		}
		// ���� �� ������ ���� ó������������
		/////////////////////////////////////////////
		if (lstOPTKWFID[i].bTextColor)
		{
			strTemp = arrData.GetAt(3);
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
			theApp.SetDataFgColour(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strTemp);
		}
		if (lstOPTKWFID[i].nDataType == DT_SIGN)
		{
			theApp.SetSignData(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strData);
		}
		else
		{
			if (strData.IsEmpty())
			{
				continue;
			}
			m_grdKwanSim.SetItemText(nRow, lstOPTKWFID[i].nCol, theApp.ConvDataFormat(lstOPTKWFID[i].nDataType, strData, lstOPTKWFID[i].strBeforeData, lstOPTKWFID[i].strAfterData));
		}
	}
	m_grdKwanSim.Invalidate();
}
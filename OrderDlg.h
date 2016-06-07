//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : OrderDlg.h
//! Function      : �ֹ� ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// OrderDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

// COrderDlg ��ȭ ����
class COrderDlg : public CDialogEx
{
// �����Դϴ�.
public:
	COrderDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ORDER_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
	CWnd*		m_pParent;
	CString		m_strScrNo;
	CString		m_strJongCode;

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);

// �����Դϴ�.
protected:
	CMapStringToString	m_mapFIDName;
	void	InitFIDName();
	HICON m_hIcon;
	void	SetCreditType(int nIndex);
	void	SetCreditType(CString	strGubun);
	void	EnableCreditOrderControl(BOOL bEnable);
	CString	GetLoanType();/// �ſ뱸�а��� ���´�...
	CString GetLoanDate();/// ������...
	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOrder();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listCtl;
	afx_msg void OnBnClickedOrdertypeDefault();
	afx_msg void OnBnClickedOrdertypeMargin();
	afx_msg void OnSelchangeComSbtp();
	afx_msg void OnSelchangeComLoanTP();
	afx_msg void OnBnClickedQryLoanDate();
	afx_msg void OnBnClickedBtnClear();
};

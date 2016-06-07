//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2015 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : RateDlg.h
//! Function      : ���ͷ����
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2015/05/07
//! Update        : 
//! Comment       : 
//******************************************************************/
// RateDlg.h : ��� ����
//

#pragma once

// CRateDlg ��ȭ ����
class CRateDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRateDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RATE };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
	CWnd*							m_pParent;
	CString							m_strScrNo;
	CMapStringToString		m_mapJongCode;		// ������ ����
	long								m_nCount;					// �׸��� Row ����.
	long								m_nNextRow;				// ������ȸ�� ���� row ��ġ

	CGridCtrl						m_grdRate;				// ���� ���ͷ� �׸���
	CEdit								m_EdtAcc;					// ���¹�ȣ
	CEdit								m_EdtTotalEval;			// �� �򰡱ݾ�
	CEdit								m_EdtTotalPurchase;	// �� ���Աݾ�
	CEdit								m_EdtTotalProfit;			// �� ����
	CEdit								m_EdtTotalRate;			// �� ���ͷ�

	double							m_TotalEval;				// �� �򰡱ݾ�
	double							m_TotalPurchase;		// �� ���Աݾ�
	double							m_TotalProfit;				// �� ����
	double							m_TotalRate;				// �� ���ͷ�

	double							m_Eval;						// �򰡱ݾ�(����, �ſ�/����)
	double							m_Profit;					// �򰡼���(����, �ſ�/����)
	double							m_Rate;						// ���ͷ�

	double							m_Purchase;				// ���Աݾ�
	double							m_Comm;					// ��ü������
	double							m_BuyComm;			// �ż������ ������(���)
	double							m_SellComm;			// �ŵ������ ������(���)
	double							m_Tax;						// ������(���)
	double							m_Price;					// ���簡
	double							m_Qty;						// ����

	BOOL							m_bNextFlag;				// ������ȸ ���� �÷���.

	void InitRealAddGrid();						// ���� �׸��� �ʱ� ó��
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);
	void SetRate(int nRow, CString strCode);
	void SetTotalRate();

	// �׸��� ����Ÿ ����(�ֽı⺻���� ����)
	void SetDataRealAddGrid(CStringArray &arrData, CString strRealType = "");

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSearch();
	DECLARE_MESSAGE_MAP()
};

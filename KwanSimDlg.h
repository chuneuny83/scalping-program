//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : KwanSimDlg.h
//! Function      : ���� ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// KwanSimDlg.h : ��� ����
//

#pragma once

// CKwanSimDlg ��ȭ ����
class CKwanSimDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CKwanSimDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_KWANSIM_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
	CWnd*					m_pParent;
	CString					m_strScrNo;
	CMapStringToString		m_mapJongCode;		// ��������

	CCellID					m_cellSelect;		// ���� �׸��� ���� ��
	CGridCtrl				m_grdKwanSim;		// ���� �׸���
	void InitKwanSimGrid();						// ���� �׸��� �ʱ� ó��
	void SetKwanSimJong();						// ���� �׸��忡 ���� ���� ó��
	// ���� ��ȸ ��û
	void SendJongSearch(int nCodeCount = 0, CString strCodeList = "", int nAddType = 0);

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);

	// �׸��� ����Ÿ ����(�ֽı⺻���� ����)
	void SetDataKwanSimGrid(CStringArray &arrData, CString strRealType = "");

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnJongAdd();
	afx_msg void OnBtnJongDelete();
	afx_msg void OnBtnJongAllDelete();
	afx_msg void OnBtnSearch();
	DECLARE_MESSAGE_MAP()
};

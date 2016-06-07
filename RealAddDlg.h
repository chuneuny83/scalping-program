//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2015 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : RealAddDlg.h
//! Function      : ������ ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2015/04/01
//! Update        : 
//! Comment       : 
//******************************************************************/
// RealAddDlg.h : ��� ����
//

#pragma once

// CRealAddDlg ��ȭ ����
class CRealAddDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRealAddDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CON_SET };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
	CWnd*					m_pParent;
	CString					m_strScrNo;
	CString					m_strConditionName;			//���� ���Ǹ�
	int							m_nConditionIndex;			//���� ���Ǹ� �ε���
	CString					m_strPreConditionName;		//���� ���Ǹ�
	int							m_nPreConditionIndex;		//���� ���Ǹ� �ε���
	CMapStringToString		m_mapJongCode;		// ������ ����
	CMapStringToString		m_mapNameList;			// ���ǰ˻�����Ʈ

	CCellID					m_cellSelect;		// ���� �׸��� ���� ��
	CGridCtrl				m_grdRealAdd;		// ���� �׸���
	CComboBox			m_cmbCon;		// ���ǰ˻��� �޺�
	CListBox m_listCtl_Insert;
	CListBox m_listCtl_Delete;
	CListBox m_listCtl_AutoOrderState;
	void InitRealAddGrid();						// ���� �׸��� �ʱ� ó��
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);
	void OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex);				//���ǰ˻� �ǽð� ����,�����Ǵ� ������ �޴´�
	void OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext);	   //���ǰ˻� ���񸮽�Ʈ�� �޴´�.
	void OnReceiveConditionVer(long bRet, LPCTSTR sMsg);

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
	afx_msg void OnBtnClose();
	afx_msg void OnBnClickedBtnAllcancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCondi();
	afx_msg void OnCbnSelchangeCmbCon();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOrderStart();		// Emily added
	afx_msg void OnBnClickedOrderCancel();		// Emily added
};

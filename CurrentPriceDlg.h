//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : CurrentPriceDlg.h
//! Function      : ���簡 ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// CurrentPriceDlg.h : ��� ����
//

#pragma once

#include "KhOpenApiTestDlg.h"

// CCurrentPriceDlg ��ȭ ����
class CCurrentPriceDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCurrentPriceDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CURRENTPRICE_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
	CWnd*		m_pParent;
	CString		m_strScrNo;
	CString		m_strScrNo2;
	CString		m_strScrNo3;
	CString		m_strJongCode;

	CGridCtrl	m_grdCurPrc;		// ���簡 �׸���
	CGridCtrl	m_grdJongInfo;		// �������� �׸���
	CGridCtrl	m_grdHoga;			// ȣ�� �׸���
	CGridCtrl	m_grdTick;			// ƽ �׸���
	void InitCurPrcGrid();			// ���簡 �׸��� �ʱ� ó��
	void InitJongInfoGrid();		// �������� �׸��� �ʱ� ó��
	void InitHogaGrid();			// ȣ�� �׸��� �ʱ� ó��
	void InitTickGrid();			// ƽ �׸��� �ʱ� ó��

	void SendSearch();				// ��ȸ ó��

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);

	// ���簡, �������� �׸��� ����Ÿ ����(�ֽı⺻���� ����)
	void SetDataJongInfoGrid(CStringArray &arrData, CString strRealType = "");
	// ƽ �׸��� ����Ÿ ����(ü������ ����)
	void SetDataTickGrid(int nInsertRow, int nRow, CStringArray &arrData);
	// ȣ�� �׸��� ����Ÿ ����(�ֽ�ȣ�� ����)
	void SetDataHogaGrid(CStringArray &arrData, CString strRealType = "");

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

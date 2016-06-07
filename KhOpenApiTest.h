//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : KhOpenApiTest.h
//! Function      : Ű�� ����API �׽�Ʈ
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// KhOpenApiTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "KHOpenAPICtrl.h"
#include "GridCtrl\GridCtrl.h"

#define OP_ERR_SISE_OVERFLOW	-200			//"�ü���ȸ ������"
#define OP_ERR_RQ_STRUCT_FAIL	-201			//"REQUEST_INPUT_st Failed"
#define OP_ERR_RQ_STRING_FAIL	-202			//"��û ���� �ۼ� ����"
#define OP_ERR_NO_DATA			-203			//"�����Ͱ� �������� �ʽ��ϴ�."
#define OP_ERR_OVER_MAX_DATA	-204			//"�ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�."


#define OP_ERR_ORD_WRONG_INPUT	-300			//"�Է°� ����"
#define OP_ERR_ORD_WRONG_ACCNO	-301			//"���º�й�ȣ�� �Է��Ͻʽÿ�."
#define OP_ERR_OTHER_ACC_USE	-302			//"Ÿ�ΰ��´� ����� �� �����ϴ�."
#define OP_ERR_MIS_2BILL_EXC	-303			//"�ֹ������� 20����� �ʰ��մϴ�."
#define OP_ERR_MIS_5BILL_EXC	-304			//"�ֹ������� 50����� �ʰ��մϴ�."
#define OP_ERR_MIS_1PER_EXC		-305			//"�ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�."
#define OP_ERR_MIS_3PER_EXC		-306			//"�ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�."
#define OP_ERR_SEND_FAIL		-307			//"�ֹ����۽���"
#define OP_ERR_ORD_OVERFLOW		-308			//"�ֹ����� ������"

#define UM_SCRENN_CLOSE		1000

#define TR_OPT10001		"OPT10001"
#define TR_OPT10003		"OPT10003"
#define TR_OPT10004		"OPT10004"
#define TR_OPT10080		"OPT10080"
#define TR_OPT10081		"OPT10081"

#define DT_NONE			0		// �⺻���� ����
#define DT_DATE			1		// ���� ����
#define DT_TIME			2		// �ð� ����
#define DT_NUMBER		3		// ���� ���� ����
#define DT_ZERO_NUMBER	4		// ���� ����(0ǥ��) ����
#define DT_SIGN			5		// ����ȣ ����

#define		SAMPLE_VERSION				_T(" ver 2.5")

typedef struct
{
   CString	strKey;				// ��ȸ Ű
   CString	strRealKey;			// ���� Ű
   int		nRow;				// �׸��� ��
   int		nCol;				// �׸��� ��
   int		nDataType;			// ����Ÿ Ÿ��(0:�⺻����, 1:����, 2:�ð�, 3:���� ����, 4:���� ����(0ǥ��), 5:����ȣ)
   BOOL		bTextColor;			// ���ڿ� �� ����(���, �϶���)
   UINT		nAlign;				// ���ڿ� ����(DT_LEFT, DT_CENTER, DT_RIGHT)
   CString	strBeforeData;		// ���ڿ� �� ���� �ֱ�
   CString	strAfterData;		// ���ڿ� �� ���� �ֱ�
} stGRID;

// CKhOpenApiTestApp:
// �� Ŭ������ ������ ���ؼ��� KhOpenApiTest.cpp�� �����Ͻʽÿ�.
//
class CKhOpenApiTestApp : public CWinApp
{
public:
	CKhOpenApiTestApp();

public:
	//CKhopenapictrl1 m_khOpenApi;
	CKHOpenAPI	m_khOpenApi;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

public:
	CString	m_sAppPath;		// ���� ���� �н�

	CString ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData = "", LPCTSTR szAfterData = "");
	void SetSignData(CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData);
	void SetDataFgColour(CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData);		// �׸��� �� ���ڻ� ����
	BOOL IsError(long lErrCode);		// ���� ����

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CKhOpenApiTestApp theApp;
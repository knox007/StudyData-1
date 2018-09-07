// PRTracerDlg.h : ��� ����
//

#pragma once

#include "FrameBufferDlg.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "ZRayTracer.h"

// CPRTracerDlg ��ȭ ����
class CPRTracerDlg : public CDialog
{
// ����
public:
	CPRTracerDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_PRTRACER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON				m_hIcon;
	LPRGBA				m_lpFrameBuffer;
	int					m_cxFrameBuffer;
	int					m_cyFrameBuffer;
	CFrameBufferDlg*	m_pDlgFrameBuffer;
	ZRayTracer*			m_pRayTracer;

	void	AllocFrameBuffer();
	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenxml();
	afx_msg void OnBnClickedBtnRender();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnRefresh();
	CButton m_btnViewFrameBuffer;
	CStatic m_textFilename;
	CProgressCtrl m_progressRender;
	CEdit m_editWidth;
	CEdit m_editHeight;
	CButton m_btnAutoRefresh;
	afx_msg void OnBnClickedCheckAutorefresh();
	afx_msg void OnTimer(UINT nIDEvent);
	CButton m_btnRender;
};

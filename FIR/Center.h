#pragma once


// Center �Ի���

class Center : public CDialogEx
{
	DECLARE_DYNAMIC(Center)

public:
	Center(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Center();

// �Ի�������
	enum { IDD = IDD_CENTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����
	CString editor1;
	// ����
	CString editor2;
	afx_msg void OnBnClickedOk();
};

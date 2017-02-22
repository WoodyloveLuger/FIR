#pragma once


// Center 对话框

class Center : public CDialogEx
{
	DECLARE_DYNAMIC(Center)

public:
	Center(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Center();

// 对话框数据
	enum { IDD = IDD_CENTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 黑子
	CString editor1;
	// 白子
	CString editor2;
	afx_msg void OnBnClickedOk();
};

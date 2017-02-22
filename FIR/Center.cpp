// Center.cpp : 实现文件
//

#include "stdafx.h"
#include "FIR.h"
#include "Center.h"
#include "afxdialogex.h"
#include <string>
#include "FIRView.h"

using namespace std;
// Center 对话框

IMPLEMENT_DYNAMIC(Center, CDialogEx)
player gamelayer[100];
Center::Center(CWnd* pParent /*=NULL*/)
	: CDialogEx(Center::IDD, pParent)
	, editor1(_T(""))
	, editor2(_T(""))
{

}

Center::~Center()
{
}

void Center::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, editor1);
	DDX_Text(pDX, IDC_EDIT2, editor2);
}


BEGIN_MESSAGE_MAP(Center, CDialogEx)
	ON_BN_CLICKED(IDOK, &Center::OnBnClickedOk)
END_MESSAGE_MAP()


// Center 消息处理程序


void Center::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString cst1;
	CString cst2;
	GetDlgItem(IDC_EDIT1)->GetWindowText(cst1);
	GetDlgItem(IDC_EDIT2)->GetWindowText(cst2);
	gamelayer[0].name=cst1;
	gamelayer[1].name = cst2;

	CDialogEx::OnOK();
}

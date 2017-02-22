
// FIRView.h : CFIRView 类的接口
//

#pragma once
#include "Managers.h"
class CFIRDoc;
class CFIRView : public CView
{
protected: // 仅从序列化创建
	CFIRView();
	DECLARE_DYNCREATE(CFIRView)

// 特性
public:
 
	CFIRDoc* GetDocument() const;
 
// 操作
public:

	CDC Chessboard;   //定义棋盘的CDC
	CDC Begin; //定义开始按钮CDC
	CDC End; //定义结束按钮CDC
	CDC Black; //定义黑色按钮
	CDC White; //定义白色按钮
	CDC Mask;//定义Mask
	CBitmap m_Chessboard;//定义棋盘的bitmap
	CBitmap m_Begin; //定义开始的bitmap	
	CBitmap m_End; //定义结束的bitmap
	CBitmap m_Black; //定义黑色棋子的bitmap
	CBitmap m_White;//定义白色棋子的bitmap
	CBitmap m_Mask;//定义Mask的bitmap

	Managers manager;
	CImageList imgList;
public:
	void PrintPart(int x,int y,int type,CDC* pDC);//用来画棋子
	void PrintAll(CDC* pDC); //用于全体重画
	void PrintState(CDC* pDC); //打印当前状态

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CFIRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
class player
{
public:
	player(){};
	 ~player(){};
	CString name; //存储玩家输入姓名
	int num; //存储玩家的净胜场数
};

//定义为全局变量，由于可能有多个用户，所以定义100个对象
extern player gamelayer[100];

#ifndef _DEBUG  // FIRView.cpp 中的调试版本
inline CFIRDoc* CFIRView::GetDocument() const
   { return reinterpret_cast<CFIRDoc*>(m_pDocument); }
#endif


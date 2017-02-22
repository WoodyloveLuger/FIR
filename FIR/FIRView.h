
// FIRView.h : CFIRView ��Ľӿ�
//

#pragma once
#include "Managers.h"
class CFIRDoc;
class CFIRView : public CView
{
protected: // �������л�����
	CFIRView();
	DECLARE_DYNCREATE(CFIRView)

// ����
public:
 
	CFIRDoc* GetDocument() const;
 
// ����
public:

	CDC Chessboard;   //�������̵�CDC
	CDC Begin; //���忪ʼ��ťCDC
	CDC End; //���������ťCDC
	CDC Black; //�����ɫ��ť
	CDC White; //�����ɫ��ť
	CDC Mask;//����Mask
	CBitmap m_Chessboard;//�������̵�bitmap
	CBitmap m_Begin; //���忪ʼ��bitmap	
	CBitmap m_End; //���������bitmap
	CBitmap m_Black; //�����ɫ���ӵ�bitmap
	CBitmap m_White;//�����ɫ���ӵ�bitmap
	CBitmap m_Mask;//����Mask��bitmap

	Managers manager;
	CImageList imgList;
public:
	void PrintPart(int x,int y,int type,CDC* pDC);//����������
	void PrintAll(CDC* pDC); //����ȫ���ػ�
	void PrintState(CDC* pDC); //��ӡ��ǰ״̬

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CFIRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	CString name; //�洢�����������
	int num; //�洢��ҵľ�ʤ����
};

//����Ϊȫ�ֱ��������ڿ����ж���û������Զ���100������
extern player gamelayer[100];

#ifndef _DEBUG  // FIRView.cpp �еĵ��԰汾
inline CFIRDoc* CFIRView::GetDocument() const
   { return reinterpret_cast<CFIRDoc*>(m_pDocument); }
#endif


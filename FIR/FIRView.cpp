
// FIRView.cpp : CFIRView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FIR.h"
#endif

#include "FIRDoc.h"
#include "FIRView.h"
#include "Center.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFIRView

IMPLEMENT_DYNCREATE(CFIRView, CView)

BEGIN_MESSAGE_MAP(CFIRView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CFIRView ����/����

CFIRView::CFIRView()
{
	// TODO:  �ڴ˴���ӹ������
	CBitmap White; //��ʼ�����ͼƬ
	CBitmap Black;
	Black.LoadBitmap(IDB_BLACK);
	White.LoadBitmap(IDB_WHITE);
	imgList.Create(24, 24, ILC_COLOR24 | ILC_MASK, 0, 2);
	imgList.Add(&White, 0xff00ff); //ʹ������ȥ��λͼ����Ҫ͸���Ĳ���
	imgList.Add(&Black, 0xff00ff);

}

CFIRView::~CFIRView()
{
}

BOOL CFIRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFIRView ����

void CFIRView::OnDraw(CDC* /*pDC*/pDC)
{
	CFIRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	static int  i = 0;
	if (i==0)
	{
		m_Chessboard.LoadBitmap(IDB_BACK);    //��������λͼ
		Chessboard.CreateCompatibleDC(pDC); //����һ�����ʵ�pdc��pdc���Կ�����CDC��ָ��
		Chessboard.SelectObject(m_Chessboard); //��Chessboardѡ�иոյ�bitmap

		m_Begin.LoadBitmap(IDB_START);    //������ʼλͼ
		Begin.CreateCompatibleDC(pDC); //����һ�����ʵ�pdc��pdc���Կ�����CDC��ָ��
		Begin.SelectObject(m_Begin); //��Beginѡ�иոյ�bitmap

		m_End.LoadBitmap(IDB_END);    //��������λͼ
		End.CreateCompatibleDC(pDC); //����һ�����ʵ�pdc��pdc���Կ�����CDC��ָ��
		End.SelectObject(m_End); //��Endѡ�иոյ�bitmap

		m_Black.LoadBitmap(IDB_BLACK);    //������ɫ����λͼ
		Black.CreateCompatibleDC(pDC); //����һ�����ʵ�pdc��pdc���Կ�����CDC��ָ��
		Black.SelectObject(m_Black); //��Blackѡ�иոյ�bitmap

		m_White.LoadBitmap(IDB_WHITE);    //��������λͼ
		White.CreateCompatibleDC(pDC); //����һ�����ʵ�pdc��pdc���Կ�����CDC��ָ��
		White.SelectObject(m_White); //��BEGINѡ�иոյ�bitmap

		m_Mask.LoadBitmap(IDB_MASK);    //��������λͼ
		Mask.CreateCompatibleDC(pDC); //����һ�����ʵ�pdc��pdc���Կ�����CDC��ָ��
		Mask.SelectObject(m_Mask); //��BEGINѡ�иոյ�bitmap
		i = 1;
	}
	pDC->BitBlt(0, 0, 546, 609, &Chessboard, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 50, 320, 120, &Begin, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 150, 320, 120, &End, 0, 0, SRCCOPY);
}


// CFIRView ��ӡ

BOOL CFIRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFIRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFIRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CFIRView ���

#ifdef _DEBUG
void CFIRView::AssertValid() const
{
	CView::AssertValid();
}

void CFIRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFIRDoc* CFIRView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFIRDoc)));
	return (CFIRDoc*)m_pDocument;
}
#endif //_DEBUG


// CFIRView ��Ϣ�������


void CFIRView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x1 = point.x;
	int y1 = point.y;
	int mx = (point.x - 27) / 35.0+0.5;
	int my = (point.y - 92) / 35.0+0.5;//26,93Ϊ���̸������Ͻ����꣬35Ϊһ�������δ�С
	//�жϹ��λ�������ڲ�
	if (mx>=0&&mx<15&&my>=0&&my<15)
	{
		CDC* pDC = GetDC();
		if (manager.DoMsg(mx, my, 1))
		{
			chess temp = manager.GetLastChe();
			if (temp.type == 0)  //����Ϊ0����������
			{
				PrintPart(mx, my, 0, pDC);   //PrintPart����������
			}
			else
				PrintPart(mx, my, 1, pDC); //���򻭰�����
			if (manager.Game_State>2)
			{
				//GamePlayer();  //�˺������������������������˵��
			}
			PrintState(pDC); //��ӡ��ǰ��Ϸ״̬

		}
		ReleaseDC(pDC);
		
	}
	else if (x1>564&&x1<848&&y1>80&&y1<130)
	{
		//��Ϸ��ʼ�������ǰ������Ϸ�У������Ի���ȷ���Ƿ�Ҫ���¿�ʼ������kȡ���û���������
		int k=0;
		if (manager.Game_State == 1 || manager.Game_State==2)
		{
			k = MessageBox(_T("������Ϸ��û�н������Ƿ����¿�ʼ��"), _T("������"), MB_OKCANCEL);
		}
		if (k!=IDCANCEL)
		{
			Center enter; //����Enter�Ի���Ķ���
			//enter.editor1.Format("%s", gamelayer[0].name);
			//enter.editor2.Format("%s", gamelayer[1].name);
			enter.editor1=gamelayer[0].name;
			enter.editor2 = gamelayer[1].name;
			
			enter.DoModal();

			manager.GameStart();
			CDC* pDC = GetDC();
			PrintAll(pDC);
			pDC->DeleteDC();
		}
	}
	else if (x1>564&&x1<848&&y1>198&&y1<254)
	{
		//����k��ȡ���û��������
		int k=0;
		if (manager.Game_State == 1 || manager.Game_State == 2)
		{
			k = MessageBox(_T("������Ϸ��û�н������Ƿ������Ϸ��"), _T("������"), MB_OKCANCEL);
		}
		if (k != IDOK)
		{
			return;
		}
		exit(0);
	}
	CView::OnLButtonDown(nFlags, point);
}


void CFIRView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x = point.x;
	int y = point.y;
	CString st;
	st.Format((_T("%d,%d  ")), x, y);//δ���Textout���峤�ȵ�����
	CDC* pDC = this->GetDC();
	pDC->TextOut(20,20, st);
	ReleaseDC(pDC);
	SetCursor(LoadCursor(NULL, IDC_CROSS));
	CView::OnMouseMove(nFlags, point);
}

void CFIRView::PrintPart(int x, int y, int type,CDC* pDC)
{
	if (type ==0) //0������,1������
	{
		//�ھ��廭��ʱ����Ҫ�������Ͻ����Ӧ�����껹ԭΪ��Ļ�ϵ�ʵ������
// 		pDC->BitBlt(x * 35 + 27 - 12, y * 35 + 93 - 12, 26, 26, &Mask, 0, 0, MERGEPAINT);
// 		pDC->BitBlt(x * 35 + 27 - 12, y * 35 + 93 - 12, 26, 26, &Black, 0, 0, SRCAND);
		imgList.Draw(GetDC(), true, CPoint(x * 35 + 27 - 12, y * 35 + 93 - 12), ILD_TRANSPARENT);
	}
	else if (type==1)
	{
// 		pDC->BitBlt(x * 35 + 27-12, y * 35 +93-12, 26, 26, &Mask, 0, 0, MERGEPAINT);
// 		pDC->BitBlt(x * 35 + 27-12, y * 35 + 93-12 , 26, 26, &White, 0, 0, SRCAND);
		imgList.Draw(GetDC(), false, CPoint(x * 35 + 27 - 12, y * 35 + 93 - 12), ILD_TRANSPARENT);
	}
}

void CFIRView::PrintAll(CDC* pDC)
{
	int x, y;
	//�����̡���ʼ��ť��
	pDC->BitBlt(0, 0, 546, 609, &Chessboard, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 50, 320, 120, &Begin, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 150, 320, 120, &End, 0, 0, SRCCOPY);
	//��ӡ��ǰ��Ϸ״̬
	PrintState(pDC);
	//����֮ǰͨ��DoMsg����manager.map������������
	for (x = 0; x <= 14;x++)
	{
		for (y = 0; y <= 14;y++)
		{
			if (manager.map[x][y]>=0)
			{
				PrintPart(x,y,manager.map[x][y],pDC);
			}
		}
	}
}

void CFIRView::PrintState(CDC* pDC)
{
	CString st; //����CString�Ķ���st
	//����Ϸ��ǰ״̬Game_State�����жϣ�������Ӧ��Ӧ
	if (manager.Game_State==1) //��Ϸ״̬Ϊ1����ʾ��ǰ�ֵ���ɫ����
	{
		st.Format(_T("��������      "));
		PrintPart(8, -1, 0, pDC);  //����һ�����ӱ�ʾ��ǰ�ֵ���������
	}
	else if (manager.Game_State == 2)//��Ϸ״̬Ϊ2����ʾ��ǰ�ֵ���ɫ����
	{
		st.Format(_T("��������      "));
		PrintPart(8, -1, 1, pDC);  //����һ�����ӱ�ʾ��ǰ�ֵ���������
	}
	//��Ϸ״̬Ϊ3��ʾ��ɫʤ����״̬4��ʾ��ɫʤ��������gameplayer[manager.Game_State-3].name��ʾʤ���������
	else if (manager.Game_State == 3)//��Ϸ״̬Ϊ3����ʾ����ʤ��
	{
		CString cstr;
		cstr = "ʤ��        ";
		st = gamelayer[manager.Game_State - 3].name + cstr;
		PrintPart(8, -1, 0, pDC);
	}
	else if (manager.Game_State == 4)//��Ϸ״̬Ϊ4����ʾ����ʤ��
	{
		CString cstr;
		cstr = "ʤ��        ";
		st = gamelayer[manager.Game_State - 3].name + cstr;
		PrintPart(8, -1, 1, pDC);
	}
	else
		st.Format(_T("��Ϸ��û�п�ʼ"));//��st���г�ʼ��

	//��ӡ��ǰ��Ϸ״̬
	pDC->TextOut(280, 10, st);
	pDC->TextOut(130, 25,_T("����"));
	pDC->TextOut(190, 25,gamelayer[0].name);
	pDC->TextOut(440, 25, _T("����"));
	pDC->TextOut(480, 25, gamelayer[1].name);
}
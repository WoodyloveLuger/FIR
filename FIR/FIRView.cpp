
// FIRView.cpp : CFIRView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CFIRView 构造/析构

CFIRView::CFIRView()
{
	// TODO:  在此处添加构造代码
	CBitmap White; //初始化相关图片
	CBitmap Black;
	Black.LoadBitmap(IDB_BLACK);
	White.LoadBitmap(IDB_WHITE);
	imgList.Create(24, 24, ILC_COLOR24 | ILC_MASK, 0, 2);
	imgList.Add(&White, 0xff00ff); //使用掩码去除位图中需要透明的部分
	imgList.Add(&Black, 0xff00ff);

}

CFIRView::~CFIRView()
{
}

BOOL CFIRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFIRView 绘制

void CFIRView::OnDraw(CDC* /*pDC*/pDC)
{
	CFIRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	static int  i = 0;
	if (i==0)
	{
		m_Chessboard.LoadBitmap(IDB_BACK);    //关联背景位图
		Chessboard.CreateCompatibleDC(pDC); //创建一个合适的pdc，pdc可以看做是CDC的指针
		Chessboard.SelectObject(m_Chessboard); //用Chessboard选中刚刚的bitmap

		m_Begin.LoadBitmap(IDB_START);    //关联开始位图
		Begin.CreateCompatibleDC(pDC); //创建一个合适的pdc，pdc可以看做是CDC的指针
		Begin.SelectObject(m_Begin); //用Begin选中刚刚的bitmap

		m_End.LoadBitmap(IDB_END);    //关联结束位图
		End.CreateCompatibleDC(pDC); //创建一个合适的pdc，pdc可以看做是CDC的指针
		End.SelectObject(m_End); //用End选中刚刚的bitmap

		m_Black.LoadBitmap(IDB_BLACK);    //关联黑色棋子位图
		Black.CreateCompatibleDC(pDC); //创建一个合适的pdc，pdc可以看做是CDC的指针
		Black.SelectObject(m_Black); //用Black选中刚刚的bitmap

		m_White.LoadBitmap(IDB_WHITE);    //关联结束位图
		White.CreateCompatibleDC(pDC); //创建一个合适的pdc，pdc可以看做是CDC的指针
		White.SelectObject(m_White); //用BEGIN选中刚刚的bitmap

		m_Mask.LoadBitmap(IDB_MASK);    //关联结束位图
		Mask.CreateCompatibleDC(pDC); //创建一个合适的pdc，pdc可以看做是CDC的指针
		Mask.SelectObject(m_Mask); //用BEGIN选中刚刚的bitmap
		i = 1;
	}
	pDC->BitBlt(0, 0, 546, 609, &Chessboard, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 50, 320, 120, &Begin, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 150, 320, 120, &End, 0, 0, SRCCOPY);
}


// CFIRView 打印

BOOL CFIRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFIRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CFIRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CFIRView 诊断

#ifdef _DEBUG
void CFIRView::AssertValid() const
{
	CView::AssertValid();
}

void CFIRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFIRDoc* CFIRView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFIRDoc)));
	return (CFIRDoc*)m_pDocument;
}
#endif //_DEBUG


// CFIRView 消息处理程序


void CFIRView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int x1 = point.x;
	int y1 = point.y;
	int mx = (point.x - 27) / 35.0+0.5;
	int my = (point.y - 92) / 35.0+0.5;//26,93为棋盘格网左上角坐标，35为一个正方形大小
	//判断光标位于棋盘内部
	if (mx>=0&&mx<15&&my>=0&&my<15)
	{
		CDC* pDC = GetDC();
		if (manager.DoMsg(mx, my, 1))
		{
			chess temp = manager.GetLastChe();
			if (temp.type == 0)  //种类为0，画黑棋子
			{
				PrintPart(mx, my, 0, pDC);   //PrintPart用来画棋子
			}
			else
				PrintPart(mx, my, 1, pDC); //否则画白棋子
			if (manager.Game_State>2)
			{
				//GamePlayer();  //此函数用来排列玩家姓名，后面说明
			}
			PrintState(pDC); //打印当前游戏状态

		}
		ReleaseDC(pDC);
		
	}
	else if (x1>564&&x1<848&&y1>80&&y1<130)
	{
		//游戏开始，如果当前仍在游戏中，弹出对话框确定是否要重新开始，并由k取得用户点击的情况
		int k=0;
		if (manager.Game_State == 1 || manager.Game_State==2)
		{
			k = MessageBox(_T("您的游戏还没有结束，是否重新开始？"), _T("五子棋"), MB_OKCANCEL);
		}
		if (k!=IDCANCEL)
		{
			Center enter; //定义Enter对话框的对象
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
		//定义k来取得用户单机情况
		int k=0;
		if (manager.Game_State == 1 || manager.Game_State == 2)
		{
			k = MessageBox(_T("您的游戏还没有结束，是否结束游戏？"), _T("五子棋"), MB_OKCANCEL);
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int x = point.x;
	int y = point.y;
	CString st;
	st.Format((_T("%d,%d  ")), x, y);//未解决Textout字体长度的问题
	CDC* pDC = this->GetDC();
	pDC->TextOut(20,20, st);
	ReleaseDC(pDC);
	SetCursor(LoadCursor(NULL, IDC_CROSS));
	CView::OnMouseMove(nFlags, point);
}

void CFIRView::PrintPart(int x, int y, int type,CDC* pDC)
{
	if (type ==0) //0画黑子,1画白子
	{
		//在具体画的时候，需要把棋盘上交点对应的坐标还原为屏幕上的实际坐标
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
	//画棋盘、开始按钮等
	pDC->BitBlt(0, 0, 546, 609, &Chessboard, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 50, 320, 120, &Begin, 0, 0, SRCCOPY);
	pDC->BitBlt(550, 150, 320, 120, &End, 0, 0, SRCCOPY);
	//打印当前游戏状态
	PrintState(pDC);
	//画出之前通过DoMsg存在manager.map里面的棋子情况
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
	CString st; //定义CString的对象st
	//对游戏当前状态Game_State进行判断，做出对应响应
	if (manager.Game_State==1) //游戏状态为1，表示当前轮到黑色走棋
	{
		st.Format(_T("黑棋走棋      "));
		PrintPart(8, -1, 0, pDC);  //画上一个黑子表示当前轮到黑子走棋
	}
	else if (manager.Game_State == 2)//游戏状态为2，表示当前轮到白色走棋
	{
		st.Format(_T("白棋走棋      "));
		PrintPart(8, -1, 1, pDC);  //画上一个黑子表示当前轮到黑子走棋
	}
	//游戏状态为3表示黑色胜利，状态4表示白色胜利，其中gameplayer[manager.Game_State-3].name表示胜利玩家名字
	else if (manager.Game_State == 3)//游戏状态为3，表示黑棋胜利
	{
		CString cstr;
		cstr = "胜利        ";
		st = gamelayer[manager.Game_State - 3].name + cstr;
		PrintPart(8, -1, 0, pDC);
	}
	else if (manager.Game_State == 4)//游戏状态为4，表示白棋胜利
	{
		CString cstr;
		cstr = "胜利        ";
		st = gamelayer[manager.Game_State - 3].name + cstr;
		PrintPart(8, -1, 1, pDC);
	}
	else
		st.Format(_T("游戏还没有开始"));//对st进行初始化

	//打印当前游戏状态
	pDC->TextOut(280, 10, st);
	pDC->TextOut(130, 25,_T("黑子"));
	pDC->TextOut(190, 25,gamelayer[0].name);
	pDC->TextOut(440, 25, _T("白子"));
	pDC->TextOut(480, 25, gamelayer[1].name);
}

// GemotaryTransView.cpp: CGemotaryTransView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GemotaryTrans.h"
#endif

#include "GemotaryTransDoc.h"
#include "GemotaryTransView.h"
#include "Transform.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGemotaryTransView

IMPLEMENT_DYNCREATE(CGemotaryTransView, CView)

BEGIN_MESSAGE_MAP(CGemotaryTransView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGemotaryTransView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CGemotaryTransView::OnMDraw)
	ON_COMMAND(ID_32772, &CGemotaryTransView::OnProJect)
	ON_COMMAND(ID_32773, &CGemotaryTransView::DrawRoll)
END_MESSAGE_MAP()

// CGemotaryTransView 构造/析构

CGemotaryTransView::CGemotaryTransView() noexcept
{
	// TODO: 在此处添加构造代码

}

CGemotaryTransView::~CGemotaryTransView()
{
}

BOOL CGemotaryTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGemotaryTransView 绘图

void CGemotaryTransView::OnDraw(CDC* pDC)
{
	CGemotaryTransDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);//设置映射模式
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区:x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//客户区中心为坐标系原点
	//绘制坐标轴
	CPen NewPen, * pOldPen;
	NewPen.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(-rect.right / 2, 0);//绘制x轴
	pDC->LineTo(rect.right / 2, 0);
	pDC->MoveTo(rect.right / 2 - 10, 5);//绘制右箭头　
	pDC->LineTo(rect.right / 2, 0);
	pDC->LineTo(rect.right / 2 - 10, -5);
	pDC->LineTo(rect.right / 2, 0);
	pDC->TextOut(rect.right / 2 - 20, 30, CString("x"));
	pDC->MoveTo(0, -rect.bottom / 2);//绘制y轴
	pDC->LineTo(0, rect.bottom / 2);
	pDC->MoveTo(-5, rect.bottom / 2 - 10);//绘制上箭头
	pDC->LineTo(0, rect.bottom / 2);
	pDC->LineTo(5, rect.bottom / 2 - 10);
	pDC->LineTo(0, rect.bottom / 2);
	pDC->TextOut(-30, rect.bottom / 2 - 20, CString("y"));
	pDC->TextOut(-20, -10, CString("O"));
}


// CGemotaryTransView 打印


void CGemotaryTransView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGemotaryTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGemotaryTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGemotaryTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGemotaryTransView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGemotaryTransView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGemotaryTransView 诊断

#ifdef _DEBUG
void CGemotaryTransView::AssertValid() const
{
	CView::AssertValid();
}

void CGemotaryTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGemotaryTransDoc* CGemotaryTransView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGemotaryTransDoc)));
	return (CGemotaryTransDoc*)m_pDocument;
}
#endif //_DEBUG


// CGemotaryTransView 消息处理程序


void CGemotaryTransView::OnMDraw()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();
	CTransform trans;
	/*设置坐标映射模式*/
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);

	trans.num = 4;
	CP2* PArray = new CP2[trans.num];
	PArray[0].x = 50; PArray[0].y = 50;
	PArray[1].x = 100; PArray[1].y = 50;
	PArray[2].x = 100; PArray[2].y = 100;
	PArray[3].x = 50; PArray[3].y = 100;

	trans.POld = PArray;
	pDC->MoveTo(PArray[0].x, PArray[0].y);
	for (int i = 1; i < 4; i++)
	{
		pDC->LineTo(PArray[i].x, PArray[i].y);
	}
	pDC->LineTo(PArray[0].x, PArray[0].y);

	for (int c = 0; c <= 36; c++) {
		//trans.Translate(-75,-75);
		trans.Rotate(10);
		if (c % 2 == 0)
			trans.Scale(2, 2);
		else
			trans.Scale(0.5, 0.5);
		//trans.Translate(75,75);
		Sleep(200);
		RedrawWindow();//����

		pDC->MoveTo(PArray[0].x, PArray[0].y);
		for (int i = 1; i < 4; i++)
		{
			pDC->LineTo(PArray[i].x, PArray[i].y);
		}
		pDC->LineTo(PArray[0].x, PArray[0].y);

	}

	
	ReleaseDC(pDC);
	delete[]PArray;
}


void CGemotaryTransView::OnProJect()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();

	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);

	int i;
	double k[9];
	double Theta, Phi, R;//旋转角度，半径
	const double PI = 3.141592653589;
	const double dt = PI / 12;
	Theta = PI / 6;
	Phi = PI * 3 / 4;
	R = 1000;
	int vex_s_x[12] = { 200,200,200,200,  0,  0,  0,  0,200,200,200,200 };
	int vex_s_y[12] = { 0  ,200,200,  0,  0,200,200,  0,  0,200,200,0 };
	int vex_s_z[12] = { 0,  0,200,200,  0,  0,200,200,  0,  0,200,200 };
	//起点坐标
	int vex_e_x[12] = { 200,200,200,200,  0,  0,  0,  0,  0,  0,  0, 0 };
	int vex_e_y[12] = { 200,200,  0,  0,200,200,  0,  0,  0,200,200,0 };
	int vex_e_z[12] = { 0,200,200,  0,  0,200,200,  0,  0,  0,200,200 };
	//终点坐标
	int newvex_s_x, newvex_s_y, newvex_s_z, newvex_e_x, newvex_e_y, newvex_e_z;
	double t ;
	for (t = 0; t < 2 * PI; t = t + dt) {

		//k[1] = sin(Theta);
		Theta += dt;
		k[1] = sin(Theta);
		k[2] = sin(Phi);
		k[3] = cos(Theta);
		k[4] = cos(Phi);
		k[5] = k[2] * k[3];
		k[6] = k[2] * k[1];
		k[7] = k[4] * k[3];
		k[8] = k[4] * k[1];
		
		Sleep(200);
		RedrawWindow();

		for (i = 0; i < 12; i++)
		{
			newvex_s_x = k[3] * vex_s_x[i] - k[1] * vex_s_z[i]; 
			newvex_s_y = -k[8] * vex_s_x[i] + k[2] * vex_s_y[i] - k[7] * vex_s_z[i];
			newvex_s_z = -k[6] * vex_s_x[i] - k[4] * vex_s_y[i] - k[5] * vex_s_z[i] + R;

			newvex_e_x = k[3] * vex_e_x[i] - k[1] * vex_e_z[i]; 
			newvex_e_y = -k[8] * vex_e_x[i] + k[2] * vex_e_y[i] - k[7] * vex_e_z[i];
			newvex_e_z = -k[6] * vex_e_x[i] - k[4] * vex_e_y[i] - k[5] * vex_e_z[i] + R;


			pDC->MoveTo(newvex_s_x, newvex_s_y);
			pDC->LineTo(newvex_e_x, newvex_e_y);
		}
		

	}
	
}

/// <summary>
/// 绘制球体
/// </summary>
void CGemotaryTransView::DrawRoll()
{
	// TODO: 在此添加命令处理程序代码

	CDC* pDC = GetDC();

	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);

	double alpha, beta, R;
	R = 200;
	const int N = 60;
	const double PI = 3.141592653589793;
	const double da = PI / N;
	const double db = 2 * PI / N;

	const double angle = PI / 4;
	double k[9];
	double Theta, Phi;//旋转角度，半径
	const double dt = PI / 12;
	Theta = PI / 6;
	Phi = PI / 4;

	CTransform trans;
	trans.num = 4;
	trans.POld3 = new CP3[trans.num];

	


	for (int t = 0; t < 50; t++) {

		Theta += dt;
		k[1] = sin(Theta);
		k[2] = sin(Phi);
		k[3] = cos(Theta);
		k[4] = cos(Phi);
		k[5] = k[2] * k[3];
		k[6] = k[2] * k[1];
		k[7] = k[4] * k[3];
		k[8] = k[4] * k[1];

		/*初始化变换矩阵*/
		trans.T4[0][0] = k[3]; trans.T4[0][1] = -k[8]; trans.T4[0][2] = -k[6]; trans.T4[0][3] = 0;
		trans.T4[1][0] = 0; trans.T4[1][1] = k[2]; trans.T4[1][2] = -k[4]; trans.T4[1][3] = 0;
		trans.T4[2][0] = -k[1]; trans.T4[2][1] = -k[7]; trans.T4[2][2] = -k[5]; trans.T4[2][3] = 0;
		trans.T4[3][0] = 0; trans.T4[3][1] = 0; trans.T4[3][2] = R; trans.T4[3][3] = 1;

		CDC MemDC;//内存DC
		CBitmap NewBitmap, * pOldBitmap;//内存中承载图像的临时位图
		MemDC.CreateCompatibleDC(pDC);//建立与屏幕pDC兼容的MemDC 
		NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容位图 
		pOldBitmap = MemDC.SelectObject(&NewBitmap); //将兼容位图选入MemDC 
		MemDC.FillSolidRect(&rect, pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
		MemDC.SetMapMode(MM_ANISOTROPIC);//MemDC自定义坐标系
		MemDC.SetWindowExt(rect.Width(), rect.Height());
		MemDC.SetViewportExt(rect.Width(), -rect.Height());
		MemDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
		CDC* ppDC = &MemDC;

		for (alpha = 0; alpha < PI; alpha += da)
		{
			for (beta = 0; beta < 2 * PI; beta += db)
			{
				double a1 = alpha;
				double a2 = alpha + da;
				double b1 = beta;
				double b2 = beta + db;

				double x0 = R * sin(a1) * cos(b1);
				double y0 = R * sin(a1) * sin(b1);
				double z0 = R * cos(a1);
				/*x0++;
				y0 = (y0)*cos(angle) - (z0)*sin(angle);*/
				trans.POld3[0].x = x0;
				trans.POld3[0].y = y0;
				trans.POld3[0].z = z0;

				double x1 = R * sin(a2) * cos(b1);
				double y1 = R * sin(a2) * sin(b1);
				double z1 = R * cos(a2);
				/*x1++;
				y1 = (y1)*cos(angle) - (z1)*sin(angle);*/
				trans.POld3[1].x = x1;
				trans.POld3[1].y = y1;
				trans.POld3[1].z = z1;

				double x2 = R * sin(a2) * cos(b2);
				double y2 = R * sin(a2) * sin(b2);
				double z2 = R * cos(a2);
				/*x2++;
				y2 = (y2)*cos(angle) - (z2)*sin(angle);*/
				trans.POld3[2].x = x2;
				trans.POld3[2].y = y2;
				trans.POld3[2].z = z2;

				double x3 = R * sin(a1) * cos(b2);
				double y3 = R * sin(a1) * sin(b2);
				double z3 = R * cos(a1);
				/*x3++;
				y3 = (y3)*cos(angle) - (z3)*sin(angle);*/
				trans.POld3[3].x = x3;
				trans.POld3[3].y = y3;
				trans.POld3[3].z = z3;

				trans.MultiMatrix4();//矩阵变换

				/*双缓冲绘图，防止闪屏*/
				
				

				ppDC->MoveTo(trans.POld3[0].x, trans.POld3[0].y);
				for (int j = 0; j < trans.num; j++) {
					ppDC->LineTo(trans.POld3[j].x, trans.POld3[j].y);
				}
				ppDC->LineTo(trans.POld3[0].x, trans.POld3[0].y);

			}			
		}
		pDC->BitBlt(-rect.Width() / 2, -rect.Height() / 2, rect.Width(), rect.Height(), &MemDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存位图拷贝到屏幕
		MemDC.SelectObject(pOldBitmap);//恢复位图
		NewBitmap.DeleteObject();//删除位图
		Sleep(100);

	}
	ReleaseDC(pDC);//释放DC	
}

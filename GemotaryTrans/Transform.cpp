#include "pch.h"
#include "Transform.h"
// TransForm.cpp: implementation of the CTransForm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GemotaryTrans.h"
#include "Transform.h"
#include "P2.h"
#include "math.h"
#define PI 3.14159
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}

void CTransform::SetMat(CP2* p, int n)
{
	POld = p;
	num = n;
}

void CTransform::Identity()//单位矩阵
{
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0;
}

void CTransform::Translate(double tx, double ty)//平移变换矩阵
{
	Identity();
	T[2][0] = tx;
	T[2][1] = ty;
	MultiMatrix();
}

void CTransform::Scale(double sx, double sy)//比例变换矩阵
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	MultiMatrix();
}

void CTransform::Scale(double sx, double sy, CP2 p)//相对于任意点的整体比例变换矩阵
{
	Translate(-p.x, -p.y);
	Scale(sx, sy);
	Translate(p.x, p.y);
}

void CTransform::Rotate(double beta)//旋转变换矩阵
{
	Identity();
	double rad = beta * PI / 180;
	T[0][0] = cos(rad); T[0][1] = sin(rad);
	T[1][0] = -sin(rad); T[1][1] = cos(rad);
	MultiMatrix();
}

void CTransform::Rotate(double beta, CP2 p)//相对于任意点的旋转变换矩阵
{
	Translate(-p.x, -p.y);
	Rotate(beta);
	Translate(p.x, p.y);
}

void CTransform::ReflectOrg()//原点反射变换矩阵
{
	Identity();
	T[0][0] = -1;
	T[1][1] = -1;
	MultiMatrix();
}

void CTransform::ReflectX()//X轴反射变换矩阵
{
	Identity();
	T[0][0] = 1;
	T[1][1] = -1;
	MultiMatrix();
}

void CTransform::ReflectY()//Y轴反射变换矩阵
{
	Identity();
	T[0][0] = -1;
	T[1][1] = 1;
	MultiMatrix();
}

void CTransform::Shear(double b, double c)//错切变换矩阵
{
	Identity();
	T[0][1] = b;
	T[1][0] = c;
	MultiMatrix();
}

void CTransform::MultiMatrix()//矩阵相乘
{
	CP2* PNew = new CP2[num];
	for (int i = 0; i < num; i++)
	{
		PNew[i] = POld[i];
	}
	for (int j = 0; j < num; j++)
	{
		POld[j].x = PNew[j].x * T[0][0] + PNew[j].y * T[1][0] + PNew[j].w * T[2][0];
		POld[j].y = PNew[j].x * T[0][1] + PNew[j].y * T[1][1] + PNew[j].w * T[2][1];
		POld[j].w = PNew[j].x * T[0][2] + PNew[j].y * T[1][2] + PNew[j].w * T[2][2];
	}
	delete[]PNew;
}
/// <summary>
/// 四阶矩阵相乘
/// </summary>
void CTransform::MultiMatrix4()
{
	CP3* PNew = new CP3[num];
	for (int i = 0; i < num; i++)
	{
		PNew[i] = POld3[i];
	}
	for (int j = 0; j < num; j++)
	{
		POld3[j].x = PNew[j].x * T4[0][0] + PNew[j].y * T4[1][0] + PNew[j].z * T4[2][0] + PNew[j].w * T4[3][0];
		POld3[j].y = PNew[j].x * T4[0][1] + PNew[j].y * T4[1][1] + PNew[j].z * T4[2][1] + PNew[j].w * T4[3][1];
		POld3[j].z = PNew[j].x * T4[0][2] + PNew[j].y * T4[1][2] + PNew[j].z * T4[2][2] + PNew[j].w * T4[3][2];
		POld3[j].w = PNew[j].x * T4[0][3] + PNew[j].y * T4[1][3] + PNew[j].z * T4[2][3] + PNew[j].w * T4[3][3];
	}
	delete[]PNew;
}


void CTransform::MultiMatrix14()
{
	double U4New[4]{};
	for (int i = 0; i < num; i++) {
		U4New[i] = U4[0] * T4[0][i] + U4[1] * T4[1][i] + U4[2] * T4[2][i] + U4[3] * T4[3][i];
	}
	for (int i = 0; i < num; i++)
		U4[i] = U4New[i];

}

double CTransform::MultiMartix141()
{
	double res = 0;
	for (int i = 0; i < num; i++) {
		res += U4[i] * V4[i];
	}
	return res;
}

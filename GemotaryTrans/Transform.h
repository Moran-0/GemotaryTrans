// Transform.h: interface for the CTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_)
#define AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P2.h"
#include "P3.h"

class CTransform//二维几何变换  
{
public:
	CTransform();
	virtual ~CTransform();
	void SetMat(CP2*, int);
	void Identity();
	void Translate(double, double);//平移变换矩阵
	void Scale(double, double);//比例变换矩阵
	void Scale(double, double, CP2);//相对于任意点的比例变换矩阵
	void Rotate(double);//旋转变换矩阵
	void Rotate(double, CP2);//相对于任意点的旋转变换矩阵
	void ReflectOrg();//原点反射变换矩阵
	void ReflectX();//X轴反射变换矩阵
	void ReflectY();//Y轴反射变换矩阵
	void Shear(double, double);//错切变换矩阵
	void MultiMatrix();//矩阵相乘
	void MultiMatrix4();//4阶矩阵相乘
	void MultiMatrix14();
	double MultiMartix141();
public:
	double T[3][3];
	double T4[4][4];
	double *U4;
	double *V4;
	CP2* POld;
	CP3* POld3;//3维坐标点数组指针
	int num;
};

#endif // !defined(AFX_TRANSFORM_H__C4FA86B2_0AF5_409A_94EB_B02A1EE13E05__INCLUDED_)


// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_)
#define AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P2.h"
#include "RGB.h"

class CLine
{
public:
	CLine();
	virtual ~CLine();
	void MoveTo(CDC*, CP2);//ÒÆ¶¯µ½Ö¸¶¨Î»ÖÃ
	void MoveTo(CDC*, double, double);
	void LineTo(CDC*, CP2);//»æÖÆÖ±Ïß£¬²»º¬ÖÕµã
	void LineTo(CDC*, double, double);
public:
	CP2 P0;//Æðµã
	CP2 P1;//ÖÕµã
};

#endif // !defined(AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_)


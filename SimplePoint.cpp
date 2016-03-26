#include "stdafx.h"
#include "SimplePoint.h"
#include "SimpleVector.h"
#include <math.h>

CSimplePoint::CSimplePoint()
{
	x = 0;
	y = 0;
}

CSimplePoint::CSimplePoint(double _x, double _y)
{
	x = _x;
	y = _y;
}

CSimplePoint::CSimplePoint(const CSimplePoint& p)
{
	x = p.x;
	y = p.y;
}

CSimplePoint::CSimplePoint(const SimplePoint& p)
{
	x = p.x;
	y = p.y;
}

CSimplePoint::~CSimplePoint()
{
}

void CSimplePoint::SetPoint(double _x, double _y)
{
	x = _x;
	y = _y;
}

void CSimplePoint::SetPoint(const CSimplePoint& p)
{
	x = p.x;
	y = p.y;
}

CSimplePoint& CSimplePoint::operator=(const CSimplePoint& p)
{
	return Copy(p);
}

CSimplePoint& CSimplePoint::operator+=(const CSimpleVector& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

CSimplePoint& CSimplePoint::operator-=(const CSimpleVector& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

bool CSimplePoint::IsInCircle(const CSimplePoint& c, double r) const
{
	double v = ((double)x-c.x)*(x-c.x)+((double)y-c.y)*(y-c.y)-(double)r*r;
	return v <= 0;
}

bool CSimplePoint::IsEqual(const CSimplePoint& p) const
{
	if (x != p.x)
		return false;
	if (y != p.y)
		return false;
	return true;
}

bool CSimplePoint::IsNear(const CSimplePoint& p, double r) const
{
	if (fabs(x-p.x) > r)
		return false;
	if (fabs(y-p.y) > r)
		return false;
	return true;
}

bool CSimplePoint::IsCircleNear(const CSimplePoint& p, double r) const
{
	return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)-r*r < 0;
}

bool CSimplePoint::operator==(const CSimplePoint& p) const
{
	return IsEqual(p);
}

bool CSimplePoint::operator!=(const CSimplePoint &p) const
{
	return !IsEqual(p);
}

CSimplePoint& CSimplePoint::Copy(const CSimplePoint &p)
{
	x = p.x;
	y = p.y;
	return *this;
}

CSimplePoint operator*(double c, const CSimplePoint& q)
{
	CSimplePoint p;
	p.x = c*q.x;
	p.y = c*q.y;
	return p;
}

CSimplePoint operator*(const CSimplePoint& q, double c)
{
	CSimplePoint p;
	p.x = c*q.x;
	p.y = c*q.y;
	return p;
}

CSimplePoint operator/(const CSimplePoint& q, double c)
{
	CSimplePoint p;
	p.x = q.x/c;
	p.y = q.y/c;
	return p;
}

double IsLeft(const CSimplePoint& p0, const CSimplePoint& p1, const CSimplePoint& p2)
{
	return ((double)p1.x-p0.x)*(p2.y-p0.y)-((double)p2.x-p0.x)*(p1.y-p0.y);
}

double Distance(const CSimplePoint& p1, const CSimplePoint& p2)
{
	double d;
	d = ((double)p1.x-p2.x)*(p1.x-p2.x)+((double)p1.y-p2.y)*(p1.y-p2.y);
	if (d)
		return sqrt(d);
	return 0;
}

int XYOrder(const CSimplePoint& p1, const CSimplePoint& p2) 
{
	if (p1.x > p2.x)
		return 1; 
	if (p1.x < p2.x)
		return -1;
	if (p1.y > p2.y)
		return 1; 
	if (p1.y < p2.y)
		return -1;
	return 0;
}

int YXOrder(const CSimplePoint& p1, const CSimplePoint& p2) 
{
	if (p1.y > p2.y)
		return 1; 
	if (p1.y < p2.y)
		return -1;
	if (p1.x > p2.x)
		return 1; 
	if (p1.x < p2.x)
		return -1;
	return 0;
}

CSimpleVector operator-(const CSimplePoint& q, const CSimplePoint& p)
{
	CSimpleVector v;
	v.x = q.x-p.x;
	v.y = q.y-p.y;
	return v;
}

CSimplePoint operator+(const CSimplePoint& q, const CSimpleVector& v)
{
	CSimplePoint p;
	p.x = q.x+v.x;
	p.y = q.y+v.y;
	return p;
}

CSimplePoint operator-(const CSimplePoint& q, const CSimpleVector& v)
{
	CSimplePoint p;
	p.x = q.x-v.x;
	p.y = q.y-v.y;
	return p;
}

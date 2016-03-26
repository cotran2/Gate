#include "stdafx.h"
#include "SimpleVector.h"

#include <Math.h>

CSimpleVector::CSimpleVector() : CSimplePoint()
{
}

CSimpleVector::CSimpleVector(double _x, double _y) : CSimplePoint(_x, _y)
{
}

CSimpleVector::~CSimpleVector()
{
}

CSimpleVector CSimpleVector::operator-()
{
	CSimpleVector v;
	v.x = -x;
	v.y = -y;
	return v;
}

CSimpleVector CSimpleVector::operator~()
{
	CSimpleVector v;
	v.x = -y;
	v.y = x;
	return v;
}

double CSimpleVector::operator*(const CSimpleVector& w)
{
	return ((double)x*w.x+(double)y*w.y);
}

double CSimpleVector::operator|(const CSimpleVector& w)
{
	return ((double)x*w.y-(double)y*w.x);
}

CSimpleVector& CSimpleVector::operator*=(double c)
{
	x *= c;
	y *= c;
	return *this;
}

CSimpleVector& CSimpleVector::operator/=(double c)
{
	x /= c;
	y /= c;
	return *this;
}

CSimpleVector& CSimpleVector::operator+=(const CSimpleVector& w)
{
	x += w.x;
	y += w.y;
	return *this;
}

CSimpleVector& CSimpleVector::operator-=(const CSimpleVector& w)
{
	x -= w.x;
	y -= w.y;
	return *this;
}

CSimpleVector& CSimpleVector::operator =(const CSimpleVector &w)
{
	return Copy(w);
}

void CSimpleVector::Normalize()
{
	double ln = sqrt((double)x*x+(double)y*y);
	if (ln == 0)
		return;
	x /= ln;
	y /= ln;
}

double CSimpleVector::Length2()
{
	return ((double)x*x+(double)y*y);
}

double CSimpleVector::Length()
{
	return sqrt((double)x*x+(double)y*y);
}

CSimpleVector& CSimpleVector::Copy(const CSimpleVector &w)
{
	x = w.x;
	y = w.y;
	return *this;
}

double Length2(const CSimpleVector& v)
{
	return ((double)v.x*v.x+(double)v.y*v.y);
}

double Length(const CSimpleVector& v)
{
	return sqrt((double)v.x*v.x+(double)v.y*v.y);
}

double Alpha(CSimpleVector& v, CSimpleVector& w)
{
	double L = Length(v)*Length(w);
	double V = v*w;
	return acos(V/L);
}

CSimpleVector operator*(const CSimpleVector& w, double c)
{
	CSimpleVector v;
	v.x = c*w.x;
	v.y = c*w.y;
	return v;
}

CSimpleVector operator/(const CSimpleVector& w, double c)
{
	CSimpleVector v;
	v.x = w.x/c;
	v.y = w.y/c;
	return v;
}

CSimpleVector operator+(const CSimpleVector& v, const CSimpleVector& w)
{
	CSimpleVector u;
	u.x = v.x+w.x;
	u.y = v.y+w.y;
	return u;
}

CSimpleVector operator-(const CSimpleVector& v, const CSimpleVector& w)
{
	CSimpleVector u;
	u.x = v.x-w.x;
	u.y = v.y-w.y;
	return u;
}

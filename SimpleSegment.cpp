#include "StdAfx.h"
#include "SimpleSegment.h"
#include "SimpleVector.h"
#include <float.h>
#include <math.h>

CSimpleSegment::CSimpleSegment()
{
}

CSimpleSegment::CSimpleSegment(const CSimpleSegment &ls)
{
	p1 = ls.p1;
	p2 = ls.p2;
}

CSimpleSegment::CSimpleSegment(const CSimplePoint& c1, const CSimplePoint& c2)
{
	p1 = c1;
	p2 = c2;
}

CSimpleSegment::CSimpleSegment(double x1, double y1, double x2, double y2)
{
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
}

CSimpleSegment::~CSimpleSegment()
{
}

void CSimpleSegment::SetPoints(double x1, double y1, double x2, double y2)
{
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
}

void CSimpleSegment::SetPoints(const CSimplePoint& c1, const CSimplePoint& c2)
{
	p1 = c1;
	p2 = c2;
}

void CSimpleSegment::SetPoints(const CSimpleSegment &ls)
{
	p1 = ls.p1;
	p2 = ls.p2;
}

double CSimpleSegment::Length() const
{
	return Distance(p1, p2);
}

void CSimpleSegment::Invert()
{
	CSimplePoint tt;
	tt = p1;
	p1 = p2;
	p2 = tt;
}

double CSimpleSegment::Angle() const
{
	return atan2((double)p2.y-p1.y, p2.x-p1.x);
}

double CSimpleSegment::Theta() const
{
	double dx, dy, adx, ady;
	double Angle;
	dx  = p2.x-p1.x;
	adx = fabs(dx);
	dy  = p2.y-p1.y;
	ady = fabs(dy);
	if ((!dx) && (!dy))
		Angle = 0.0;
	else
		Angle = dy/(adx+ady);

	if (dx < 0.0)
		Angle = 2.0-Angle;
	else
		if (dy < 0.0)
			Angle = 4.0+Angle;
	return 90*Angle;
}

double CSimpleSegment::Heading() const
{
	return atan2(p2.x-p1.x, p2.y-p1.y);
}

double CSimpleSegment::ToAngle(double heading) const
{
	double dx, dy;

	dx = sin(heading);
	dy = cos(heading);
	return atan2(dy, dx);
}

double CSimpleSegment::ToHeading(double angle) const
{
	double dx, dy;

	dx = cos(angle);
	dy = sin(angle);
	return atan2(dx, dy);
}

bool CSimpleSegment::IsVertival() const
{
	return p1.x == p2.x;
}

bool CSimpleSegment::IsHorizontal() const
{
	return p1.y == p2.y;
}

double CSimpleSegment::IsLeft(const CSimplePoint& p) const
{
	return ((double)p2.x-p1.x)*(p.y-p1.y)-(p.x-p1.x)*(p2.y-p1.y);
}

bool CSimpleSegment::IsInSegment(const CSimplePoint& p) const
{
	if (p1.x != p2.x)
	{
		if (p1.x <= p.x && p.x <= p2.x)
			return true;
		if (p1.x >= p.x && p.x >= p2.x)
			return true;
	}
	else
	{
		if (p1.y <= p.y && p.y <= p2.y)
			return true;
		if (p1.y >= p.y && p.y >= p2.y)
			return true;
	}
	return false;
}

bool CSimpleSegment::GetClip(double left, double top, double right, double bottom)
{
	double u1 = 0.0, u2 = 1.0, dx = p2.x-p1.x, dy;
	if (ClipTest(-dx, p1.x-left, &u1, &u2))
		if (ClipTest(dx, right-p1.x, &u1, &u2))
		{
			dy = p2.y-p1.y;
			if (ClipTest(-dy, p1.y-top, &u1, &u2))
				if (ClipTest(dy, bottom-p1.y, &u1, &u2))
				{
					if (u2 < 1.0)
					{
						p2.x = p1.x+u2*dx;
						p2.y = p1.y+u2*dy;
					}
					if (u1 > 0.0)
					{
						p1.x += u1*dx;
						p1.y += u1*dy;
					}
					return true;
				}
		}
	return false;
}

bool CSimpleSegment::GetCircleClip(const CSimplePoint& c, double r)
{
	if (!IsCircleClip(c, r))
		return false;
	double dx, dy, dr, dr2, D, D2, r2;
	double SQRT, x1, x2, y1, y2, t1, t2, t;
	int sgn;
	CSimplePoint I1, I2;
	x1 = p1.x-c.x;
	x2 = p2.x-c.x;
	y1 = p1.y-c.y;
	y2 = p2.y-c.y;
	dx = x2-x1;
	dy = y2-y1;
	dr = sqrt(dx*dx+dy*dy);
	dr2 = dr*dr;
	D = x1*y2-x2*y1;
	D2 = D*D;
	r2 = r*r;
	sgn = (dy < 0) ? -1 : 1;
	SQRT = sqrt(r2*dr2-D2);
	I1.x = c.x+(D*dy+sgn*dx*SQRT)/dr2;
	I1.y = c.y+(-D*dx+fabs(dy)*SQRT)/dr2;
	I2.x = c.x+(D*dy-sgn*dx*SQRT)/dr2;
	I2.y = c.y+(-D*dx-fabs(dy)*SQRT)/dr2;
	CSimpleSegment S(x1, y1, x2, y2);
	CSimpleVector u = p2-p1;
	CSimpleVector v = I1-p1;
	CSimpleVector w = I2-p1;
	if (v.x != 0)
	{
		t1 = v.x/u.x;
		t2 = w.x/u.x;
	}
	else
	{
		t1 = v.y/u.y;
		t2 = w.y/u.y;
	}
	if (t1 > t2)
	{
		t = t1;
		t1 = t2;
		t2 = t;
	}
	if (t2 < 1)
	{
		p2.x = p1.x+t2*u.x;
		p2.y = p1.y+t2*u.y;
	}
	if (t1 > 0)
	{
		p1.x = p1.x+t1*u.x;
		p1.y = p1.y+t1*u.y;
	}
	return true;
}

//  Temp
bool CSimpleSegment::GetCircleClip(const CSimplePoint& c, double r, double rMet, bool &bRet1, bool &bRet2)
{
	bRet1 = false;
	bRet2 = false;
	if (!IsCircleClip(c, rMet))
		return false;
	double dx, dy, dr, dr2, D, D2, r2;
	double SQRT, x1, x2, y1, y2, t1, t2, t;
	int sgn;
	CSimplePoint I1, I2;
	x1 = p1.x-c.x;
	x2 = p2.x-c.x;
	y1 = p1.y-c.y;
	y2 = p2.y-c.y;
	dx = x2-x1;
	dy = y2-y1;
	dr = sqrt(dx*dx+dy*dy);
	dr2 = dr*dr;
	D = x1*y2-x2*y1;
	D2 = D*D;
	r2 = r*r;
	sgn = (dy < 0) ? -1 : 1;
	SQRT = sqrt(r2*dr2-D2);
	I1.x = c.x+(D*dy+sgn*dx*SQRT)/dr2;
	I1.y = c.y+(-D*dx+fabs(dy)*SQRT)/dr2;
	I2.x = c.x+(D*dy-sgn*dx*SQRT)/dr2;
	I2.y = c.y+(-D*dx-fabs(dy)*SQRT)/dr2;
	CSimpleSegment S(x1, y1, x2, y2);
	CSimpleVector u = p2-p1;
	CSimpleVector v = I1-p1;
	CSimpleVector w = I2-p1;
	if (v.x != 0)
	{
		t1 = v.x/u.x;
		t2 = w.x/u.x;
	}
	else
	{
		t1 = v.y/u.y;
		t2 = w.y/u.y;
	}
	if (t1 > t2)
	{
		t = t1;
		t1 = t2;
		t2 = t;
	}
	if (t2 < 1)
	{
		p2.x = p1.x+t2*u.x;
		p2.y = p1.y+t2*u.y;
		bRet2 = true;
	}
	if (t1 > 0)
	{
		p1.x = p1.x+t1*u.x;
		p1.y = p1.y+t1*u.y;
		bRet1 = true;
	}
	return true;
}

//
bool CSimpleSegment::IsClip(double left, double top, double right, double bottom) 
{
	double u1 = 0.0, u2 = 1.0, dx = p2.x-p1.x, dy;
	if (ClipTest(-dx, p1.x-left, &u1, &u2))
		if (ClipTest(dx, right-p1.x, &u1, &u2))
		{
			dy = p2.y-p1.y;
			if (ClipTest(-dy, p1.y-top, &u1, &u2))
				if (ClipTest(dy, bottom-p1.y, &u1, &u2))
					return true;
		}
	return false;
}

bool CSimpleSegment::IsCircleClip(const CSimplePoint& c, double r)
{
	CSimplePoint closest = ClosestPoint(c);
	double d = Distance(closest, c);
	return d <= r;
}

bool CSimpleSegment::IsCircleClip(double xc, double yc, double r)
{
	CSimplePoint c;

	c.x = xc;
	c.y = yc;
	CSimplePoint closest = ClosestPoint(c);
	double d = Distance(closest, c);
	return d <= r;
}

CSimplePoint CSimpleSegment::ProjectPoint(const CSimplePoint& p) const
{
	if (p == p1 || p == p2)
		return p;
	CSimplePoint retP;
	double r = ProjectFactor(p);
	retP.x = p1.x+r*(p2.x-p1.x);
	retP.y = p1.y+r*(p2.y-p1.y);
	return retP;
}

CSimplePoint CSimpleSegment::ClosestPoint(const CSimplePoint &p) const
{
	double factor = ProjectFactor(p);
	if (factor > 0 && factor < 1)
		return ProjectPoint(p);
	double dist0 = Distance(p1, p);
	double dist1 = Distance(p2, p);
	if (dist0 < dist1)
		return p1;
	return p2;
}

bool CSimpleSegment::IsEqualsTopo(const CSimpleSegment& s) const
{
	return (p1 == s.p1 && p2 == s.p2) || (p1 == s.p2 && p2 == s.p1);
}

bool CSimpleSegment::IsEqualsAbs(const CSimpleSegment& s) const
{
	return p1 == s.p1 && p2 == s.p2;
}

bool CSimpleSegment::operator ==(const CSimpleSegment& s) 
{
	return IsEqualsAbs(s);
}

double DistanceFromPoint(const CSimpleSegment& s, const CSimplePoint& p)
{
	double dx, dy, Dist;

	dx = s.p2.x-s.p1.x;
	dy = s.p2.y-s.p1.y;
	Dist = (dy*(p.x-s.p1.x)-dx*(p.y-s.p1.y))/sqrt(dx*dx+dy*dy);
	return fabs(Dist);
}

void CSimpleSegment::ParallelSegments(double h, CSimpleSegment& SL, CSimpleSegment& SR)
{
	CSimplePoint SLP, SRP, ELP, ERP;
	double d = Distance(p1, p2);
	double f = h/d;
	OrthoPoints(SLP, SRP, ELP, ERP);
	SL.p1.x = p1.x+f*(SLP.x-p1.x);
	SL.p1.y = p1.y+f*(SLP.y-p1.y);
	SL.p2.x = p2.x+f*(ELP.x-p2.x);
	SL.p2.y = p2.y+f*(ELP.y-p2.y);
	SR.p1.x = p1.x+f*(SRP.x-p1.x);
	SR.p1.y = p1.y+f*(SRP.y-p1.y);
	SR.p2.x = p2.x+f*(ERP.x-p2.x);
	SR.p2.y = p2.y+f*(ERP.y-p2.y);
}

CSimpleSegment CSimpleSegment::ParaFromLeft(double h)
{
	CSimplePoint SLP, SRP, ELP, ERP;
	double d = Distance(p1, p2);
	double f = h/d;
	CSimpleSegment s;
	OrthoPoints(SLP, SRP, ELP, ERP);
	s.p1.x = p1.x+f*(SLP.x-p1.x);
	s.p1.y = p1.y+f*(SLP.y-p1.y);
	s.p2.x = p2.x+f*(ELP.x-p2.x);
	s.p2.y = p2.y+f*(ELP.y-p2.y);
	return s;
}

CSimpleSegment CSimpleSegment::ParaFromRight(double h)
{
	CSimplePoint SLP, SRP, ELP, ERP;
	double d = Distance(p1, p2);
	double f = h/d;
	CSimpleSegment s;
	OrthoPoints(SLP, SRP, ELP, ERP);
	s.p1.x = p1.x+f*(SRP.x-p1.x);
	s.p1.y = p1.y+f*(SRP.y-p1.y);
	s.p2.x = p2.x+f*(ERP.x-p2.x);
	s.p2.y = p2.y+f*(ERP.y-p2.y);
	return s;
}

CSimplePoint CSimpleSegment::GetPointAt(double dbDist)
{
	double t, dx, dy, dbLength;
	CSimplePoint P;

	dbLength = Distance(p1, p2);

	if (dbDist <= 0)
		return p1;
	if (dbDist >= dbLength)
		return p2;

	t = dbDist/dbLength;
	dx = p2.x-p1.x;
	dy = p2.y-p1.y;
	P.x = p1.x+dx*t;
	P.y = p1.y+dy*t;

	return P;
}

CSimpleSegment& CSimpleSegment::Copy(const CSimpleSegment& ls)
{
	p1 = ls.p1;
	p2 = ls.p2;
	return *this;
}

bool CSimpleSegment::ClipTest(double p, double q, double *u1, double *u2) 
{
	double r;
	bool retVal = true;
	if (p < 0.0)
	{
		r = q/p;
		if (r > *u2)
			retVal = false;
		else
			if (r > *u1)
				*u1 = r;
	}
	else
	{
		if (p > 0.0)
		{
			r = q/p;
			if (r < *u1)
				retVal = false;
			else
				if (r < *u2)
					*u2 = r;
		}
		else
			if (q < 0.0)
				retVal = false;
	}
	return retVal;
}

double CSimpleSegment::ProjectFactor(const CSimplePoint& p) const
{
	if (p == p1)
		return 0.0;
	if (p == p2)
		return 1.0;
	double dx = p2.x-p1.x;
	double dy = p2.y-p1.y;
	double len2 = dx*dx+dy*dy;
	double r = ((p.x-p1.x)*dx+(p.y-p1.y)*dy)/len2;
	return r;
}

void CSimpleSegment::OrthoPoints(CSimplePoint& SLP, CSimplePoint& SRP, CSimplePoint& ELP, CSimplePoint& ERP)
{
	double dx, dy;
	dx = p2.x-p1.x;
	dy = p2.y-p1.y;
	SRP.x = p1.x+dy;
	SRP.y = p1.y-dx;
	SLP.x = p1.x-dy;
	SLP.y = p1.y+dx;
	ERP.x = p2.x+dy;
	ERP.y = p2.y-dx;
	ELP.x = p2.x-dy;
	ELP.y = p2.y+dx;
}

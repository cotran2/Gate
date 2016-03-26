// SimpleSegment.h: interface for the CSimpleSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __SIMPLESEGMENT__H__
#define __SIMPLESEGMENT__H__

#include "SimplePoint.h"

class CSimpleSegment  
{
public:
	CSimpleSegment();
	CSimpleSegment(const CSimpleSegment &ls);
	CSimpleSegment(const CSimplePoint& c1, const CSimplePoint& c2);
	CSimpleSegment(double x1, double y1, double x2, double y2);
	virtual ~CSimpleSegment();
	void SetPoints(double x1, double y1, double x2, double y2);
	void SetPoints(const CSimplePoint& c1, const CSimplePoint& c2);
	void SetPoints(const CSimpleSegment &ls);
	double Length() const;
	void Invert();
	double Angle() const;
	double Theta() const;
	double Heading() const;
	double ToAngle(double heading) const;
	double ToHeading(double angle) const;
	bool IsVertival() const;
	bool IsHorizontal() const;
	double IsLeft(const CSimplePoint& p) const;
	bool IsInSegment(const CSimplePoint& p) const;
	bool GetClip(double left, double top, double right, double bottom);
	bool GetCircleClip(const CSimplePoint& c, double r);
	//  Temp
	bool GetCircleClip(const CSimplePoint& c, double r, double rMet, bool &bRet1, bool &bRet2);
	//  
	bool IsClip(double left, double top, double right, double bottom);
	bool IsCircleClip(const CSimplePoint& c, double r);
	bool IsCircleClip(double xc, double yc, double r);
	double ProjectFactor(const CSimplePoint& p) const;
	CSimplePoint ProjectPoint(const CSimplePoint& p) const;
	CSimplePoint ClosestPoint(const CSimplePoint &p) const;
	bool IsEqualsTopo(const CSimpleSegment& s) const;
	bool IsEqualsAbs(const CSimpleSegment& s) const;
	bool operator ==(const CSimpleSegment& s);
	void ParallelSegments(double h, CSimpleSegment& SL, CSimpleSegment& SR);
	CSimpleSegment ParaFromLeft(double h);
	CSimpleSegment ParaFromRight(double h);

	CSimplePoint GetPointAt(double dbDist);

private:
	CSimpleSegment& Copy(const CSimpleSegment& ls);
	bool ClipTest(double p, double q, double *u1, double *u2);
	void OrthoPoints(CSimplePoint& SLP, CSimplePoint& SRP, CSimplePoint& ELP, CSimplePoint& ERP);

public:
	CSimplePoint p1;
	CSimplePoint p2;
};

#endif // !defined(_SEGMENT2D_H_)

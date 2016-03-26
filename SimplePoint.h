// SimplePoint.h: interface for the CSimplePoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __SIMPLEPOINT__H__
#define __SIMPLEPOINT__H__

struct SimplePoint
{
	double x;
	double y;
};

class CSimplePoint : public SimplePoint
{
friend class CSimpleVector;
public:
	// constructors
	CSimplePoint();
	CSimplePoint(double _x, double _y);
	CSimplePoint(const CSimplePoint& p);
	CSimplePoint(const SimplePoint& p);
	// destructors
	virtual ~CSimplePoint();

public:
	void SetPoint(double _x, double _y);
	void SetPoint(const CSimplePoint& p);
	CSimplePoint& operator=(const CSimplePoint& p);
	CSimplePoint& operator+=(const CSimpleVector& v);
	CSimplePoint& operator-=(const CSimpleVector& v);
	bool IsInCircle(const CSimplePoint& c, double r) const;
	bool IsEqual(const CSimplePoint& p) const;
	bool IsNear(const CSimplePoint& p, double r) const;
	bool IsCircleNear(const CSimplePoint& p, double r) const;
	bool operator==(const CSimplePoint& p) const;
	bool operator!=(const CSimplePoint &p) const;
	friend CSimplePoint operator*(double c, const CSimplePoint& q);
	friend CSimplePoint operator*(const CSimplePoint& q, double c);
	friend CSimplePoint operator/(const CSimplePoint& q, double c);
	friend double IsLeft(const CSimplePoint& p0, const CSimplePoint& p1, const CSimplePoint& p2);
	friend double Distance(const CSimplePoint& p1, const CSimplePoint& p2);
	friend int XYOrder(const CSimplePoint& p1, const CSimplePoint& p2);
	friend int YXOrder(const CSimplePoint& p1, const CSimplePoint& p2);
	friend CSimpleVector operator-(const CSimplePoint& q, const CSimplePoint& p);
	friend CSimplePoint operator+(const CSimplePoint& q, const CSimpleVector& v);
	friend CSimplePoint operator-(const CSimplePoint& q, const CSimpleVector& v);
private:
	CSimplePoint& Copy(const CSimplePoint &p);
};

#endif // !defined __SIMPLEPOINT__H__

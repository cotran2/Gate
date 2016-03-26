// SimpleVector.h: interface for the CSimpleVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __SIMPLEVECTOR__H__
#define __SIMPLEVECTOR__H__

#include "SimplePoint.h"

class CSimpleVector : public CSimplePoint
{
public:
	// constructor
	CSimpleVector();
	CSimpleVector(double _x, double _y);
	// destructor
	~CSimpleVector();

public:
	CSimpleVector operator-();
	CSimpleVector operator~();
	double operator*(const CSimpleVector& w);
	double operator|(const CSimpleVector& w);
	CSimpleVector& operator*=(double c);
	CSimpleVector& operator/=(double c);
	CSimpleVector& operator+=(const CSimpleVector& w);
	CSimpleVector& operator-=(const CSimpleVector& w);
	CSimpleVector& operator =(const CSimpleVector& w);
	void Normalize();
	double Length2();
	double Length();
	// friend functions
	friend double Length2(const CSimpleVector& v);
	friend double Length(const CSimpleVector& v);
	friend double Alpha(const CSimpleVector& v, const CSimpleVector& w);
	// friend operators
	friend CSimpleVector operator*(const CSimpleVector& w, double c);
	friend CSimpleVector operator/(const CSimpleVector& w, double c);
	friend CSimpleVector operator+(const CSimpleVector& v, const CSimpleVector& w);
	friend CSimpleVector operator-(const CSimpleVector& v, const CSimpleVector& w);
private:
	CSimpleVector& Copy(const CSimpleVector &w);
};

#endif // !defined __SIMPLEVECTOR__H__

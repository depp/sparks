#ifndef _H_VECTORS_
#define _H_VECTORS_

#include <fp.h>

const float kTolerance = 0.01;

inline int withinTolerance (const float a, const float b);
inline int withinTolerance (const float a, const float b)
{
	return (((a+kTolerance)>b)&&((a-kTolerance)<b));
}

class t_Vector2f;
class t_Matrix2f;

/***************************************************

VECTORS

A vector is like a number, but in more dimensions.  
However, vectors don't have a place.  In other words, 
a you can't represent a place on the screen with a
vector.  That's what points are for.

A distinction between vectors and points is (no pun
intended) pointless, so we only define vectors.  

**************************************************/

class t_Vector2f {
	private:
		float	v[2];
	public:
		t_Vector2f();
		t_Vector2f(t_Vector2f& a);
		t_Vector2f(float a, float b);
		
		t_Vector2f& set(float a, float b);
		
		// Addition, Subtraction, Negation, Scalar Product (x2), Dot Product
		friend t_Vector2f operator+		(const t_Vector2f& a,
										 const t_Vector2f& b);
		
		friend t_Vector2f operator-		(const t_Vector2f& a,
										 const t_Vector2f& b);
		
		friend t_Vector2f operator-		(const t_Vector2f& a);
		
		friend t_Vector2f operator*		(const float a,
										 const t_Vector2f& b);
		
		friend t_Vector2f operator*		(const t_Vector2f& a,
										 const float b);
		
		friend float operator*			(const t_Vector2f& a,
										 const t_Vector2f& b);
		
		friend t_Vector2f operator/		(const t_Vector2f& a,
										 const float& b);
		
		// Equality, Inequality
		friend int operator==			(const t_Vector2f& a,
										 const t_Vector2f& b);
		
		friend int operator!=			(const t_Vector2f& a,
										 const t_Vector2f& b);
		
		// Assignment
		t_Vector2f& operator=			(const t_Vector2f& a);
		t_Vector2f& operator*=			(const float a);
		t_Vector2f& operator/=			(const float a);
		t_Vector2f& operator+=			(const t_Vector2f& a);
		t_Vector2f& operator-=			(const t_Vector2f& a);
		
		// Subscripting
		float& operator[]				(int a);
		
		// Other functions
		friend t_Vector2f normalize		(const t_Vector2f& a);
		friend float magnitude			(const t_Vector2f& a);
		
		friend t_Vector2f rotateCCW_90	(const t_Vector2f& a);
		friend t_Vector2f rotateCW_90	(const t_Vector2f& a);
		
		// Matrix Functions
		friend t_Vector2f operator*		(const t_Vector2f& a,
										 const t_Matrix2f& b);
		
		friend t_Vector2f operator*		(const t_Matrix2f& a,
										 const t_Vector2f& b);
};


/***************************************************

MATRIX

A matrix is a tool for rotating, shearing, and
scaling vectors.

**************************************************/

class t_Matrix2f {
	private:
		float	v[2][2];
	public:
		t_Matrix2f();
		t_Matrix2f(float a);
		t_Matrix2f(float a, float b, float c, float d);
		
		t_Matrix2f& set(float a, float b, float c, float d);
		t_Matrix2f& setRotate(float theta);
				
		// Addition, Subtraction, Negation, Scalar Product (x2), Dot Product
		friend t_Matrix2f operator+		(const t_Matrix2f& a,
										 const t_Matrix2f& b);
		
		friend t_Matrix2f operator-		(const t_Matrix2f& a,
										 const t_Matrix2f& b);
		
		friend t_Matrix2f operator-		(const t_Matrix2f& a);
		
		friend t_Matrix2f operator*		(const float a,
										 const t_Matrix2f& b);
		
		friend t_Matrix2f operator*		(const t_Matrix2f& a,
										 const float b);
		
		friend t_Matrix2f operator*		(const t_Matrix2f& a,
										 const t_Matrix2f& b);
		
		friend t_Vector2f operator*		(const t_Vector2f& a,
										 const t_Matrix2f& b);
		
		friend t_Vector2f operator*		(const t_Matrix2f& a,
										 const t_Vector2f& b);
		
		friend t_Matrix2f operator/		(const t_Matrix2f& a,
										 const float& b);
		
		// Equality, Inequality
		friend int operator==			(const t_Matrix2f& a,
										 const t_Matrix2f& b);
		
		friend int operator!=			(const t_Matrix2f& a,
										 const t_Matrix2f& b);
		
		// Assignment
		t_Matrix2f& operator=			(const t_Matrix2f& a);
		t_Matrix2f& operator*=			(const float a);
		t_Matrix2f& operator*=			(const t_Matrix2f& a);
		t_Matrix2f& operator/=			(const float a);
		t_Matrix2f& operator+=			(const t_Matrix2f& a);
		t_Matrix2f& operator-=			(const t_Matrix2f& a);
		
		// Subscripting
		float* operator[]				(int a);
		
		// Other functions
		friend float determinant		(const t_Matrix2f& a);
};

#endif

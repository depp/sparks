#include "Vectors.h"

/***************************************************

VECTORS

**************************************************/

// Initialization
t_Vector2f::t_Vector2f() {
	v[0] = v[1] = 0.0;
}

t_Vector2f::t_Vector2f(t_Vector2f &a) {
	v[0] = a.v[0];
	v[1] = a.v[1];
}

t_Vector2f::t_Vector2f(float a, float b) {
	v[0] = a;
	v[1] = b;
}

t_Vector2f &t_Vector2f::set(float a, float b) {
	v[0] = a;
	v[1] = b;
	return *this;
}

// Arithmetic
t_Vector2f operator+(const t_Vector2f &a, const t_Vector2f &b) {
	t_Vector2f c;
	c.v[0] = a.v[0] + b.v[0];
	c.v[1] = a.v[1] + b.v[1];
	return c;
}

t_Vector2f operator-(const t_Vector2f &a, const t_Vector2f &b) {
	t_Vector2f c;
	c.v[0] = a.v[0] - b.v[0];
	c.v[1] = a.v[1] - b.v[1];
	return c;
}

t_Vector2f operator-(const t_Vector2f &a) {
	t_Vector2f c;
	c.v[0] = -a.v[0];
	c.v[1] = -a.v[1];
	return c;
}

t_Vector2f operator*(const float a, const t_Vector2f &b) {
	t_Vector2f c;
	c.v[0] = a * b.v[0];
	c.v[1] = a * b.v[1];
	return c;
}

t_Vector2f operator*(const t_Vector2f &a, const float b) {
	t_Vector2f c;
	c.v[0] = a.v[0] * b;
	c.v[1] = a.v[1] * b;
	return c;
}

float operator*(const t_Vector2f &a, const t_Vector2f &b) {
	float c;
	c = a.v[0] * b.v[0] + a.v[1] * b.v[1];
	return c;
}

t_Vector2f operator/(const t_Vector2f &a, const float &b) {
	t_Vector2f c;
	if (b == 0)
		return c;
	c.v[0] = a.v[0] / b;
	c.v[1] = a.v[1] / b;
	return c;
}

// Comparison
int operator==(const t_Vector2f &a, const t_Vector2f &b) {
	return (withinTolerance(a.v[0], b.v[0]) && withinTolerance(a.v[1], b.v[1]));
}

int operator!=(const t_Vector2f &a, const t_Vector2f &b) {
	return !(withinTolerance(a.v[0], b.v[0]) &&
	         withinTolerance(a.v[1], b.v[1]));
}

// Assignmen
t_Vector2f &t_Vector2f::operator=(const t_Vector2f &a) {
	v[0] = a.v[0];
	v[1] = a.v[1];
	return *this;
}

t_Vector2f &t_Vector2f::operator*=(const float a) {
	v[0] *= a;
	v[1] *= a;
	return *this;
}

t_Vector2f &t_Vector2f::operator/=(const float a) {
	if (a != 0) {
		v[0] /= a;
		v[1] /= a;
	} else {
		v[0] = 0.0;
		v[1] = 0.0;
	}
	return *this;
}

t_Vector2f &t_Vector2f::operator+=(const t_Vector2f &a) {
	v[0] += a.v[0];
	v[1] += a.v[1];
	return *this;
}

t_Vector2f &t_Vector2f::operator-=(const t_Vector2f &a) {
	v[0] -= a.v[0];
	v[1] -= a.v[1];
	return *this;
}

// Subscripting
float &t_Vector2f::operator[](int a) {
	return v[a];
}

// Other Functions
t_Vector2f normalize(const t_Vector2f &a) {
	return a / magnitude(a);
}

t_Vector2f rotateCCW_90(const t_Vector2f &a) {
	t_Vector2f b;
	b.v[0] = -a.v[1];
	b.v[1] = a.v[0];
	return b;
}

t_Vector2f rotateCW_90(const t_Vector2f &a) {
	t_Vector2f b;
	b.v[0] = a.v[1];
	b.v[1] = -a.v[0];
	return b;
}

float magnitude(const t_Vector2f &a) {
	return sqrt(a.v[0] * a.v[0] + a.v[1] * a.v[1]);
}

/***************************************************

MATRICES

**************************************************/

// Initialization
// Identity Matrix
t_Matrix2f::t_Matrix2f() {
	v[0][0] = 1;
	v[1][0] = 0;
	v[0][1] = 0;
	v[1][1] = 1;
}

// Identity Matrix times a
t_Matrix2f::t_Matrix2f(float a) {
	v[0][0] = a;
	v[1][0] = 0;
	v[0][1] = 0;
	v[1][1] = a;
}

// The matrix becomes
// a b
// c d
t_Matrix2f::t_Matrix2f(float a, float b, float c, float d) {
	v[0][0] = a;
	v[1][0] = c;
	v[0][1] = b;
	v[1][1] = d;
}

t_Matrix2f &t_Matrix2f::set(float a, float b, float c, float d) {
	v[0][0] = a;
	v[1][0] = c;
	v[0][1] = b;
	v[1][1] = d;
	return *this;
}

t_Matrix2f &t_Matrix2f::setRotate(float theta) {
	float c, s;
	c = cos(theta);
	s = sin(theta);
	v[0][0] = c;
	v[0][1] = s;
	v[1][0] = -s;
	v[1][1] = c;
	return *this;
}

// Arithmetic
t_Matrix2f operator+(const t_Matrix2f &a, const t_Matrix2f &b) {
	t_Matrix2f c;
	c.v[0][0] = a.v[0][0] + b.v[0][0];
	c.v[1][0] = a.v[1][0] + b.v[1][0];
	c.v[0][1] = a.v[0][1] + b.v[0][1];
	c.v[1][1] = a.v[1][1] + b.v[1][1];
	return c;
}

t_Matrix2f operator-(const t_Matrix2f &a, const t_Matrix2f &b) {
	t_Matrix2f c;
	c.v[0][0] = a.v[0][0] - b.v[0][0];
	c.v[1][0] = a.v[1][0] - b.v[1][0];
	c.v[0][1] = a.v[0][1] - b.v[0][1];
	c.v[1][1] = a.v[1][1] - b.v[1][1];
	return c;
}

t_Matrix2f operator-(const t_Matrix2f &a) {
	t_Matrix2f b;
	b.v[0][0] = -a.v[0][0];
	b.v[1][0] = -a.v[1][0];
	b.v[0][1] = -a.v[0][1];
	b.v[1][1] = -a.v[1][1];
	return b;
}

t_Matrix2f operator*(const float a, const t_Matrix2f &b) {
	t_Matrix2f c;
	c.v[0][0] = a * b.v[0][0];
	c.v[1][0] = a * b.v[1][0];
	c.v[0][1] = a * b.v[0][1];
	c.v[1][1] = a * b.v[1][1];
	return c;
}

t_Matrix2f operator*(const t_Matrix2f &a, const float b) {
	t_Matrix2f c;
	c.v[0][0] = a.v[0][0] * b;
	c.v[1][0] = a.v[1][0] * b;
	c.v[0][1] = a.v[0][1] * b;
	c.v[1][1] = a.v[1][1] * b;
	return c;
}

t_Matrix2f operator*(const t_Matrix2f &a, const t_Matrix2f &b) {
	t_Matrix2f c;
	c.v[0][0] = a.v[0][0] * b.v[0][0] + a.v[0][1] * b.v[1][0];
	c.v[0][1] = a.v[0][0] * b.v[0][1] + a.v[0][1] * b.v[1][1];
	c.v[1][0] = a.v[1][0] * b.v[0][0] + a.v[1][1] * b.v[1][0];
	c.v[1][1] = a.v[1][0] * b.v[0][1] + a.v[1][1] * b.v[1][1];
	return c;
}

t_Vector2f operator*(const t_Vector2f &a, const t_Matrix2f &b) {
	t_Vector2f c;
	c.v[0] = a.v[0] * b.v[0][0] + a.v[1] * b.v[1][0];
	c.v[1] = a.v[0] * b.v[0][1] + a.v[1] * b.v[1][1];
	return c;
}

t_Vector2f operator*(const t_Matrix2f &a, const t_Vector2f &b) {
	t_Vector2f c;
	c.v[0] = a.v[0][0] * b.v[0] + a.v[0][1] * b.v[1];
	c.v[1] = a.v[1][0] * b.v[0] + a.v[1][1] * b.v[1];
	return c;
}

t_Matrix2f operator/(const t_Matrix2f &a, const float &b) {
	t_Matrix2f c;
	if (b == 0)
		return c;
	c.v[0][0] = a.v[0][0] / b;
	c.v[1][0] = a.v[1][0] / b;
	c.v[0][1] = a.v[0][1] / b;
	c.v[1][1] = a.v[1][1] / b;
	return c;
}

// Equality, Inequality
int operator==(const t_Matrix2f &a, const t_Matrix2f &b) {
	return (withinTolerance(a.v[0][0], b.v[0][0]) &&
	        withinTolerance(a.v[1][0], b.v[1][0]) &&
	        withinTolerance(a.v[0][1], b.v[0][1]) &&
	        withinTolerance(a.v[1][1], b.v[1][1]));
}

int operator!=(const t_Matrix2f &a, const t_Matrix2f &b) {
	return !(withinTolerance(a.v[0][0], b.v[0][0]) &&
	         withinTolerance(a.v[1][0], b.v[1][0]) &&
	         withinTolerance(a.v[0][1], b.v[0][1]) &&
	         withinTolerance(a.v[1][1], b.v[1][1]));
}

// Assignmen
t_Matrix2f &t_Matrix2f::operator=(const t_Matrix2f &a) {
	v[0][0] = a.v[0][0];
	v[1][0] = a.v[1][0];
	v[0][1] = a.v[0][1];
	v[1][1] = a.v[1][1];
	return *this;
}

t_Matrix2f &t_Matrix2f::operator*=(const float a) {
	v[0][0] *= a;
	v[1][0] *= a;
	v[0][1] *= a;
	v[1][1] *= a;
	return *this;
}

t_Matrix2f &t_Matrix2f::operator*=(const t_Matrix2f &a) {
	t_Matrix2f temp;
	temp = (*this) * a;
	*this = temp;
	return *this;
}

t_Matrix2f &t_Matrix2f::operator/=(const float a) {
	v[0][0] /= a;
	v[1][0] /= a;
	v[0][1] /= a;
	v[1][1] /= a;
	return *this;
}

t_Matrix2f &t_Matrix2f::operator+=(const t_Matrix2f &a) {
	v[0][0] += a.v[0][0];
	v[1][0] += a.v[1][0];
	v[0][1] += a.v[0][1];
	v[1][1] += a.v[1][1];
	return *this;
}

t_Matrix2f &t_Matrix2f::operator-=(const t_Matrix2f &a) {
	v[0][0] -= a.v[0][0];
	v[1][0] -= a.v[1][0];
	v[0][1] -= a.v[0][1];
	v[1][1] -= a.v[1][1];
	return *this;
}

// Subscripting
// This will return the ath row
float *t_Matrix2f::operator[](int a) {
	return v[a];
}

// Other functions
float determinant(const t_Matrix2f &a) {
	return a.v[0][0] * a.v[1][1] - a.v[1][0] * a.v[0][1];
}

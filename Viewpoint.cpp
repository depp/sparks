/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Viewpoint.h"
#include "Entity.h"
#include "Header.h"
#include "Params.h"
#include "Vectors.h"

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

t_Viewpoint gViewpoint;

/****************************************************/
/*                    Main Code                     */
/****************************************************/

void Initialize_Viewpoint(void) {
	gViewpoint.translate1.set(0.0, 0.0);
	gViewpoint.scale = ((float)kGameXSize) / (kVirtualXMax - kVirtualXMin);
	gViewpoint.translate2.h = kGameXSize / 2;
	gViewpoint.translate2.v = kGameYSize / 2;
	gViewpoint.e = NULL;
}

void Update_Viewpoint(void) {
	if (gViewpoint.e != NULL)
		gViewpoint.translate1 = gViewpoint.e->loc;
}

void Terminate_Viewpoint(void) {}

void t_Entity::follow(void) {
	gViewpoint.e = this;
	gViewpoint.translate1 = loc;
}

Point Viewpoint_Transform(t_Vector2f &v) {
	Point transformedPoint;
	t_Vector2f vPrime;

	transformedPoint = gViewpoint.translate2;

	vPrime = (v - gViewpoint.translate1) * gViewpoint.scale;
	transformedPoint.h += round(vPrime[0]);
	transformedPoint.v -= round(vPrime[1]);

	return transformedPoint;
}

void MoveTo(t_Vector2f &v) {
	Point transformedPoint;
	t_Vector2f vPrime;

	transformedPoint = gViewpoint.translate2;

	vPrime = (v - gViewpoint.translate1) * gViewpoint.scale;
	transformedPoint.h += round(vPrime[0]);
	transformedPoint.v -= round(vPrime[1]);

	MoveTo(transformedPoint.h, transformedPoint.v);
}

int Viewpoint_Transform(float f) {
	return round(f * gViewpoint.scale);
}

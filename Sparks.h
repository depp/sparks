#ifndef _H_SPARKS_
#define _H_SPARKS_

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Vectors.h"

/****************************************************/
/*                    Constants                     */
/****************************************************/

enum {
	kSparks_Hot,
	kSparks_Plasma,
	kSparks_Hot_Big
};

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void Draw_Sparks					(void);
void Update_Sparks					(void);
void Init_Sparks					(void);
void Terminate_Sparks				(void);
void Sparks_Create					(long type, long count, t_Vector2f& pos, t_Vector2f& vel, float randVel);

#endif

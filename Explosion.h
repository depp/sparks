#ifndef _H_EXPLOSION_
#define _H_EXPLOSION_

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Entity.h"
#include "Vectors.h"

/****************************************************/
/*                     Constants                    */
/****************************************************/

enum {
	kExplosion_Small,
	kExplosion_Medium,
	kExplosion_Big,
	kExplosion_Huge,
};

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void Explosion_Create(int type, t_Vector2f loc, t_Vector2f vel);
void Explosion_Think(t_Entity *e);
void Explosion_Draw(t_Entity *e);

#endif

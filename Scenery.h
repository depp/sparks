#ifndef _H_SCENERY_
#define _H_SCENERY_

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Entity.h"
#include "Vectors.h"

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

t_Entity *E_Scenery_Create(t_Vector2f loc);
void E_Scenery_Draw(t_Entity *e);

#endif

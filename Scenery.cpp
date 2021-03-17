/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Header.h"
#include "PaletteTable.h"
#include "Vectors.h"
#include "Entity.h"
#include "Scenery.h"

/****************************************************/
/*                    Main Code                     */
/****************************************************/

t_Entity * E_Scenery_Create ( t_Vector2f& loc )
{
	t_Entity	* e;
	
	e = Entity_Create();
	
	e->loc = loc;
	e->dir = t_Vector2f();
	e->vel = t_Vector2f();
	
	e->radius = 4.0;
	e->moveType = kMoveType_Static;
	
	e->fThink = NULL;
	e->nextThink = -1;
	e->fDraw = E_Scenery_Draw;
	
	e->touchFlags = kTF_MissileClip | kTF_PlayerClip;
	
	e->layer = kLayer_Scenery;
	
	return e;
}

void E_Scenery_Draw (t_Entity * e)
{
	PmForeColor(32);
	Draw_Circle(e->loc, e->radius);
	PenSize(3,3);
	PmForeColor(kPltt_Green);
	Draw_CircleOutline(e->loc, e->radius);
	PenSize(1,1);
}

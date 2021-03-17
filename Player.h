#ifndef _H_PLAYER_
#define _H_PLAYER_

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Vectors.h"
#include "Entity.h"

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void		E_Init_Player			(void);
t_Entity *	E_Player_Create			(t_Vector2f& loc, t_Vector2f& dir);
void		E_Player_Draw			(t_Entity * e);
void		E_Player_Think			(t_Entity * e);
void		E_Player_Collide		(t_Entity * e, t_Entity * other);

void		E_PlayerShot_Draw		(t_Entity * e);
void		E_PlayerShot_Think		(t_Entity * e);
void		E_PlayerShot_Think2		(t_Entity * e);
void		E_PlayerShot_Collide	(t_Entity * e, t_Entity * other);

#endif

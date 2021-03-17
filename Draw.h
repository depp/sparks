#ifndef _H_DRAW_
#define	_H_DRAW_

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Vectors.h"

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void		Draw_Circle				(t_Vector2f center, float r);
void		Draw_CircleOutline		(t_Vector2f center, float r);
void		Draw_CircleOutline		(t_Vector2f center, int r);
void		Draw_Circle				(t_Vector2f center, int r);
void		Draw_Line				(t_Vector2f start, t_Vector2f end);
void		Draw_String_Centered	(t_Vector2f loc, Str255 s);

int			Clip_Rect				(t_Vector2f corner1, t_Vector2f corner2);
int			Clip_Circle				(t_Vector2f center, float r);

void		Draw_Triangle			(t_Vector2f a, t_Vector2f b, t_Vector2f c, UInt8 color);
void		Draw_Triangle_Shaded	(t_Vector2f * points, UInt8 * colors, UInt8 * gradTable);

#endif

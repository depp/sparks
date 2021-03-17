#ifndef _H_VIEWPOINT_
#define _H_VIEWPOINT_

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Vectors.h"
#include "Entity.h"

/****************************************************/
/*                  Variable Types                  */
/****************************************************/

typedef struct {
	t_Vector2f	translate1;
	float		scale;
	Point		translate2;
	t_Entity	* e;
} t_Viewpoint;

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

extern	t_Viewpoint		gViewpoint;

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void		Initialize_Viewpoint	(void);
void		Update_Viewpoint		(void);
void		Terminate_Viewpoint		(void);
Point		Viewpoint_Transform		(t_Vector2f& v);
int			Viewpoint_Transform		(float f);
void		MoveTo					(t_Vector2f& v);

#endif

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Header.h"
#include "Entity.h"
#include "Params.h"

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

t_Entity		*gEntities;

/****************************************************/
/*                    Main Code                     */
/****************************************************/

void Init_Entities (void)
{
	int	i;
	
	gEntities = (t_Entity*)NewPtr(kNum_Entities*sizeof(t_Entity));
	
	if (gEntities == NULL)
		GracefulExit();
	
	for (i=0;i<kNum_Entities;i++)
		gEntities[i].destroy();
}

void Terminate_Entities (void)
{
	DisposePtr((Ptr)gEntities);
}

t_Entity * Entity_Create (void)
{
	int			i;
	t_Entity	*r;
	
	for (i=0;i<kNum_Entities;i++)
	{
		if (!gEntities[i].used)
		{
			r = gEntities + i;
			r->destroy();
			r->used = true;
			return r;
		}
	}
	GracefulExit();
	return NULL;
}

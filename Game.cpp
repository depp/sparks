/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Game.h"
#include "Entity.h"
#include "Graphics.h"
#include "Header.h"
#include "Input.h"
#include "Params.h"
#include "Sparks.h"
#include "Stars.h"
#include "Vectors.h"
#include "Viewpoint.h"

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

long gCurrentTime;
extern t_Entity *gEntities;

/****************************************************/
/*                    Main Code                     */
/****************************************************/

void Start_Game(void) {
	gCurrentTime = TickCount();
}

void Game_RunFrame(void) {
	int i, j, k;

	Update_Input();
	ClearBuffer();

	while (gCurrentTime < TickCount()) {
		gCurrentTime++;

		for (i = 0; i < kNum_Entities; i++)
			if (gEntities[i].isUsed())
				gEntities[i].think();

		for (i = 0; i < kNum_Entities; i++)
			if (gEntities[i].isUsed())
				gEntities[i].move();

		for (i = 0; i < (kNum_Entities - 1); i++) {
			for (j = (i + 1); j < kNum_Entities; j++) {
				if (magnitude(gEntities[i].loc - gEntities[j].loc) <=
				    (gEntities[i].radius + gEntities[j].radius)) {
					gEntities[i].collide(gEntities + j);
					gEntities[j].collide(gEntities + i);
				}
			}
		}

		Update_Sparks();
	}

	Update_Viewpoint();

	Draw_Stars();

	for (k = 0; k < kLayer_Num; k++)
		for (i = 0; i < kNum_Entities; i++)
			if ((gEntities[i].isUsed()) && (gEntities[i].layer == k))
				gEntities[i].draw();

	Draw_Sparks();

	CopyToScreen();
}

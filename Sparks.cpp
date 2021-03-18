/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Sparks.h"
#include "Draw.h"
#include "Game.h"
#include "Header.h"
#include "Vectors.h"
#include "Viewpoint.h"

/****************************************************/
/*                    Constants                     */
/****************************************************/

const float kSparkClipRadius = 5.0;

enum {
	kMax_SparkGroups = 50,
};

/****************************************************/
/*                  Variable Types                  */
/****************************************************/

typedef struct {
	t_Vector2f loc;
	t_Vector2f vel;
} t_Spark;

typedef struct {
	int exists;
	t_Spark *sparks;
	int sparkType;
	int startTime;
	int count;
} t_SparkGroup;

typedef struct {
	UInt8 *colors;
	long duration;
	short numColors;
	short period;
	long size;
} t_SparkType;

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

UInt8 gPltt_HotSparks[18] = {0,   100, 101, 102, 103, 104, 105, 29, 209,
                             208, 22,  21,  20,  19,  18,  17,  16, 1};
UInt8 gPltt_PlasmaSparks[11] = {43, 214, 215, 50, 49, 48, 47, 46, 45, 44, 1};

t_SparkType gSparkTypes[3] = {
	{gPltt_HotSparks, 36, 18, 2, 1},
	{gPltt_PlasmaSparks, 22, 11, 2, 1},
	{gPltt_HotSparks, 36, 18, 2, 2},
};

t_SparkGroup *gSparks;

void Init_Sparks(void) {
	int i;

	gSparks = (t_SparkGroup *)NewPtr(sizeof(t_SparkGroup) * kMax_SparkGroups);

	if (gSparks == NULL)
		GracefulExit();

	for (i = 0; i < kMax_SparkGroups; i++) {
		gSparks[i].exists = false;
	}
}

void Terminate_Sparks(void) {
	DisposePtr((Ptr)gSparks);
}

void Sparks_Create(long type, long count, t_Vector2f &pos, t_Vector2f &vel,
                   float randVel) {
	int i;
	t_SparkGroup *s;
	t_Spark *c;
	float rSquared = randVel * randVel;

	if (Clip_Circle(pos, kSparkClipRadius))
		return;

	s = NULL;
	for (i = 0; i < kMax_SparkGroups; i++) {
		if (!gSparks[i].exists) {
			s = gSparks + i;
			break;
		}
	}

	if (s == NULL)
		return;

	s->exists = true;
	s->sparkType = type;
	s->startTime = gCurrentTime;
	s->sparks = (t_Spark *)NewPtr(sizeof(t_Spark) * count);
	if (s->sparks == NULL)
		GracefulExit();
	s->count = count;

	c = s->sparks;

	for (i = 0; i < count; i++) {
		c->loc = pos;
		do {
			c->vel.set((((float)((Random()))) * randVel) / ((float)0x7FFF),
			           (((float)((Random()))) * randVel) / ((float)0x7FFF));
		} while ((c->vel[0] * c->vel[0] + c->vel[1] * c->vel[1]) > rSquared);
		c->vel += vel;

		c++;
	}
}

/*
    Ptr				baseAddress;
    long			bytesPerRow;
    Point			loc;
*/

void Update_Sparks(void) {
	int i, j;
	t_SparkGroup *curSG;
	t_Spark *curSP;

	curSG = gSparks;

	for (i = 0; i < kMax_SparkGroups; i++) {
		if (curSG->exists) {
			if ((gCurrentTime - curSG->startTime) >=
			    gSparkTypes[curSG->sparkType].duration) {
				DisposePtr((Ptr)curSG->sparks);
				curSG->exists = false;
			} else {
				curSP = curSG->sparks;

				for (j = 0; j < curSG->count; j++) {
					curSP->loc += curSP->vel;
					curSP++;
				}
			}
		}

		curSG++;
	}
}

void Draw_Sparks(void) {
	int i, j;
	t_SparkGroup *curSG;
	t_Spark *curSP;
	t_SparkType *curST;
	Ptr baseAddress;
	Ptr curAddr;
	long bytesPerRow;
	Point loc;
	UInt8 pixelData;
	int r, c;

	baseAddress = (**gPixMap).baseAddr;
	bytesPerRow = (**gPixMap).rowBytes & 0x7FFF;
	curSG = gSparks;

	for (i = 0; i < kMax_SparkGroups; i++) {
		if (curSG->exists) {
			curST = gSparkTypes + curSG->sparkType;
			curSP = curSG->sparks;
			pixelData = curST->colors[((gCurrentTime - curSG->startTime) /
			                           (curST->period)) %
			                          (curST->numColors)];

			if (curST->size == 1) {
				for (j = 0; j < curSG->count; j++) {
					loc = Viewpoint_Transform(curSP->loc);
					if ((loc.h > gBufferRect.left) &&
					    (loc.h < gBufferRect.right) &&
					    (loc.v > gBufferRect.top) &&
					    (loc.v < gBufferRect.bottom))
						*(baseAddress + bytesPerRow * loc.v + loc.h) =
							pixelData;
					curSP++;
				}
			} else {
				for (j = 0; j < curSG->count; j++) {
					loc = Viewpoint_Transform(curSP->loc);
					if ((loc.h > gBufferRect.left) &&
					    ((loc.h + curST->size) < gBufferRect.right) &&
					    (loc.v > gBufferRect.top) &&
					    ((loc.v + curST->size) < gBufferRect.bottom)) {
						curAddr = baseAddress + bytesPerRow * loc.v + loc.h;
						for (r = 0; r < curST->size; r++) {
							for (c = 0; c < curST->size; c++) {
								*(curAddr + c) = pixelData;
							}

							curAddr += bytesPerRow;
						}
					}
					curSP++;
				}
			}
		}

		curSG++;
	}
}

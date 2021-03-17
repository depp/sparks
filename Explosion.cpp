/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Header.h"
#include "PaletteTable.h"
#include "Sparks.h"
#include "Explosion.h"

/****************************************************/
/*                      Macros                      */
/****************************************************/

#define	SignedFloatRand		(((float)((Random()&0x7FFF)-0x4000))/16384.0)
#define	UnsignedFloatRand	(((float)(Random()&0x7FFF))/32767.0)

/****************************************************/
/*                  Variable Types                  */
/****************************************************/

typedef struct {
	int		spark_Count;
	float	spark_Speed;
	int		spark_Type;
	int		circle_Count;
	float	circle_Scatter;
	float	circle_Speed;
	float	circle_SpeedRand;
	float	circle_MaxSize;
	int		circle_Delay;
	int		circle_Thickness;
} t_ExplosionType;

t_ExplosionType gExplosionTypes[4] =
{
	{	10,		0.1,	kSparks_Hot,		0,		0,		0,		0,		0,		0,		0	},
//	{	15,		0.1,	kSparks_Hot,		1,		0,		0.03,	0,		1.0,	0,		1	},
	{	25,		0.2,	kSparks_Hot,		3,		1.0,	0.05,	0.08,	2.0,	7,		2	},
	{	30,		0.5,	kSparks_Hot_Big,	7,		2.0,	0.1,	0.2,	4.0,	15,		3	},
	{	60,		0.6,	kSparks_Hot_Big,	13,		4.0,	0.15,	0.25,	8.0,	20,		5	}
};

/****************************************************/
/*                    Main Code                     */
/****************************************************/

void Explosion_Create (int type, t_Vector2f loc, t_Vector2f vel)
{
	int				i;
	t_Entity		*explosion;
	t_ExplosionType	*theType;
	
	theType = &(gExplosionTypes[type]);
	
	Sparks_Create(theType->spark_Type,theType->spark_Count,loc,vel,theType->spark_Speed);
	
	for (i=0;i<(theType->circle_Count);i++) {
		explosion = Entity_Create();
		
		explosion->loc = loc;
		explosion->loc += t_Vector2f( SignedFloatRand, SignedFloatRand ) * theType->circle_Scatter;
		explosion->vel = vel;
		
		explosion->radius = 0;
		explosion->expansion = theType->circle_Speed + UnsignedFloatRand * theType->circle_SpeedRand;
		explosion->explosionType = type;
		explosion->touchFlags = 0;
		explosion->moveType = kMoveType_Linear;
		
		explosion->fThink = Explosion_Think;
		explosion->nextThink = gCurrentTime+((Random()&0x7FFF) % (theType->circle_Delay+1))+1;
		explosion->fDraw = Explosion_Draw;
		
		explosion->layer = kLayer_Fx;
	}
}

void Explosion_Think (t_Entity * e)
{
	e->radius += e->expansion;
	e->nextThink += 1;
	
	if (e->radius >= gExplosionTypes[e->explosionType].circle_MaxSize)
		e->destroy();
}

void Explosion_Draw (t_Entity * e)
{
	int	c;
	
	if (e->nextThink != (gCurrentTime + 1))
		return;
	
	c = floor(e->radius * 15.0 / gExplosionTypes[e->explosionType].circle_MaxSize);
	PenSize	(gExplosionTypes[e->explosionType].circle_Thickness,
			 gExplosionTypes[e->explosionType].circle_Thickness);
	PmForeColor(gPltt_Full_Red[c]);
	
	Draw_CircleOutline(e->loc,e->radius);
	
	PenSize(1,1);
}

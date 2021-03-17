#ifndef _H_ENTITY_
#define _H_ENTITY_

/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Vectors.h"
#include "Game.h"
#include "Draw.h"

/****************************************************/
/*                    Constants                     */
/****************************************************/

enum {
	kMoveType_Static,
	kMoveType_Linear
};

enum {
	kTF_PlayerClipBit,
	kTF_MissileClipBit
};
enum {
	kTF_PlayerClip	= 1 << kTF_PlayerClipBit,
	kTF_MissileClip	= 1 << kTF_MissileClipBit
};

enum {
	kLayer_Scenery,
	kLayer_Player,
	kLayer_Fx,
	kLayer_Num
};

/****************************************************/
/*                     Classes                      */
/****************************************************/

class t_Entity;

class t_Entity {
	private:
		int								used;
	public:
		t_Vector2f						loc;
		t_Vector2f						dir;
		t_Vector2f						vel;
		float							radius;
		
		int								touchFlags;
		
		int								moveType;
		int								nextThink;
		
		float							health;
		float							expansion;
		int								explosionType;
		char							*type;
		t_Entity						*owner;
		
		long							layer;
		
		void (*fThink)					(t_Entity * e);
		void (*fDraw)					(t_Entity * e);
		void (*fCollide)				(t_Entity * e, t_Entity * other);
		
		void think						(void)
			{ if ((fThink != NULL) && (nextThink == gCurrentTime)) fThink(this); }
		void draw						(void)
			{ if ((fDraw != NULL) && (!Clip_Circle(loc,radius))) fDraw(this); }
		void destroy					(void)
		{
			used = false;
			nextThink = -1;
			fThink = NULL;
			fDraw = NULL;
			fCollide = NULL;
			touchFlags = 0;
		}
		int isUsed						(void)
			{ return used; }
		void move						(void)
		{
			if (moveType == kMoveType_Linear)
				loc += vel;
		}
		void collide					(t_Entity * other)
			{ if ((fCollide != NULL) && (((touchFlags) & (other->touchFlags)) != 0)) fCollide(this,other); }
		
		void follow						(void);
		
		friend t_Entity * Entity_Create	(void);
};

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void		Init_Entities			(void);
void		Terminate_Entities		(void);

#endif

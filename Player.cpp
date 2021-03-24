/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Player.h"
#include "Entity.h"
#include "Explosion.h"
#include "Header.h"
#include "Input.h"
#include "PaletteTable.h"
#include "Sparks.h"
#include "Vectors.h"
#include "Viewpoint.h"

#include <Fonts.h>

/****************************************************/
/*                    Constants                     */
/****************************************************/

const float kMaxSpeed = 0.5;
const float kMaxAccel = 0.05;
const float kRotationSpeed = 1.0 / 30.0;
const float kMaxBrake = 0.01;

const float kShotSize = 0.1;
const float kShotSparkSpeed = 0.25;
const float kShotSparkCollisionSpeed = 0.5;

const t_Vector2f kStringOffset(0.0, -4);

const int kShotTime = 25;

const float kBounce = 0.6;

enum {
	kPlayerColor = kPltt_White,
	kPlayerShotColor = kPltt_Cyan,
};

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

static t_Matrix2f m;   // The rotation matrix
static int shotRadius; // Radius of shot in pixels
char *type = "player";
char *type2 = "shot_player";
Str255 PlayerLabel = "\pPlayer 1";

/****************************************************/
/*                    Main Code                     */
/****************************************************/

// Call this once each time the application opens
void E_Init_Player(void) {
	m.setRotate((2 * pi) * kRotationSpeed);
	shotRadius = Viewpoint_Transform(kShotSize);
}

// Creates a new player character
// dir should be normalized
t_Entity *E_Player_Create(t_Vector2f loc, t_Vector2f dir) {
	t_Entity *e;

	e = Entity_Create();

	e->type = type;

	e->loc = loc;
	e->dir = dir;
	e->vel = t_Vector2f();

	e->radius = 3.0;
	e->moveType = kMoveType_Linear;

	e->health = 1.0;

	e->fThink = E_Player_Think;
	e->nextThink = gCurrentTime + 1;
	e->fDraw = E_Player_Draw;
	e->fCollide = E_Player_Collide;

	e->layer = kLayer_Player;

	e->touchFlags = kTF_PlayerClip;

	return e;
}

// Draws the player to the screen
void E_Player_Draw(t_Entity *e) {
	int c;
	t_Vector2f p[3];
	UInt8 pc[3] = {7, 0, 0};

	/*
	PmForeColor(kPlayerColor);
	*/
	t_Vector2f r;
	t_Vector2f &f = e->dir;
	t_Vector2f &l = e->loc;

	r = rotateCW_90(f);
	/*
	Draw_Line(2*f+l, r-2*f+l);
	Draw_Line(r-2*f+l, -r-2*f+l);
	Draw_Line(-r-2*f+l, 2*f+l);
	*/

	p[0] = 2 * f + l;
	p[1] = r - 2 * f + l;
	p[2] = -r - 2 * f + l;

	Draw_Triangle_Shaded(p, pc, gPltt_Gray_2_Red);

	c = round((1.0 - e->health) * 14);
	if (c > 14)
		c = 14;
	else if (c < 0)
		c = 0;
	PmForeColor(gPltt_Full_Red[c]);
	c = round(e->health * 2.49 + 0.5);
	PenSize(c, c);
	Draw_CircleOutline(e->loc, (float)2.8);
	PenSize(1, 1);

	PmForeColor(8);
	TextFont(kFontIDCourier);
	TextSize(10);
	Draw_String_Centered(e->loc + kStringOffset, PlayerLabel);
}

// Accepts keyboard inpu
void E_Player_Think(t_Entity *e) {
	if (gKeys[kKey_TurnLeft])
		e->dir = e->dir * m;
	if (gKeys[kKey_TurnRight])
		e->dir = m * e->dir;

	e->dir = normalize(e->dir);

	if (gKeys[kKey_Thrust]) {
		e->vel += e->dir * kMaxAccel;
		if (magnitude(e->vel) > kMaxSpeed)
			e->vel = normalize(e->vel) * kMaxSpeed;
	}
	if (gKeys[kKey_Brake]) {
		if (magnitude(e->vel) <= kMaxBrake)
			e->vel.set(0.0, 0.0);
		else {
			e->vel -= normalize(e->vel) * kMaxBrake;
		}
	}

	if (gKeys[kKey_Fire] == kKeyState_Down) {
		t_Entity *shot;

		shot = Entity_Create();

		shot->loc = e->loc + 2 * e->dir;
		shot->dir = t_Vector2f();
		shot->vel = e->dir * 0.75 + e->vel;

		shot->radius = 0.2;
		shot->touchFlags = kTF_MissileClip;
		shot->moveType = kMoveType_Linear;

		shot->fThink = E_PlayerShot_Think;
		shot->nextThink = gCurrentTime + kShotTime;
		shot->fDraw = E_PlayerShot_Draw;
		shot->fCollide = E_PlayerShot_Collide;

		shot->owner = e;
		shot->type = type2;

		shot->layer = kLayer_Fx;
	}

	e->health -= 0.003;

	if (e->health <= 0) { /*
		                     Explosion_Create(2,e->loc,e->vel);
		                     e->fThink = E_PlayerShot_Think2;
		                     e->fCollide = NULL;
		                     e->fDraw = NULL;*/
		e->health = 0;
	}

	e->nextThink += 1;
}

void E_Player_Collide(t_Entity *e, t_Entity *other) {
	t_Vector2f axis;
	t_Matrix2f m;

	axis = normalize(e->loc - other->loc);

	e->loc = (e->radius + other->radius + 0.01) * normalize(axis) + other->loc;

	axis = rotateCW_90(axis);
	m.set(axis[0], -axis[1], axis[1], axis[0]);
	e->vel = m * (((e->vel) * m) * t_Matrix2f(1, 0, 0, -1));
	e->vel *= kBounce;
}

// Draws the player to the screen
void E_PlayerShot_Draw(t_Entity *e) {
	PmForeColor(kPlayerShotColor);
	Draw_Circle(e->loc, shotRadius);
}

void E_PlayerShot_Think(t_Entity *e) {
	Sparks_Create(kSparks_Plasma, 10, e->loc, t_Vector2f(), kShotSparkSpeed);
	e->destroy();
}

void E_PlayerShot_Think2(t_Entity *e) {
	e->destroy();
}

void E_PlayerShot_Collide(t_Entity *e, t_Entity *other) {
	if (e->owner == other)
		return;
	else {
		t_Vector2f d, l;
		d = normalize(e->loc - other->loc);
		l = other->radius * d + other->loc;
		d *= 0.1;

		// Sparks_Create(kSparks_Hot,5,l,d,kShotSparkSpeed);

		e->vel = other->vel;

		Explosion_Create(0, l, d);

		e->fThink = E_PlayerShot_Think2;
		e->nextThink = gCurrentTime + 1;
		e->fCollide = NULL;
		e->fDraw = NULL;
	}
}

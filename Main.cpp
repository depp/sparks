/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Main.h"
#include "Entity.h"
#include "Error.h"
#include "Graphics.h"
#include "Header.h"
#include "Params.h"
#include "Player.h"
#include "ResourceList.h"
#include "Scenery.h"
#include "Sparks.h"
#include "Stars.h"
#include "Vectors.h"
#include "Viewpoint.h"

#include <LowMem.h>
#include <Sound.h>

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

QDGlobals qd;

GDHandle gTheDevice;
WindowPtr gWindPtr;
GWorldPtr gBackBuffer;
Rect gWindRect;
Rect gWindRect2;
Rect gLocalWindRect;
Rect gBufferRect;
PixMapHandle gPixMap;
short gOldDepth;
short gMBarHeight;
RgnHandle gOldRegion;
RgnHandle gOldRegion2;
WindowPtr gWindPtr2;
Rect gGameRect;

/****************************************************/
/*                    Main Code                     */
/****************************************************/

// Main
int main(void) {
	int t;
	t_Entity *player;

	Initialize();
	Start_Game();

	player = E_Player_Create(t_Vector2f(-2, 0), t_Vector2f(0, 1));
	player->follow();

	E_Scenery_Create(t_Vector2f(6, 0));

	while (!Button()) {
		t = TickCount() + 1;

		Game_RunFrame();

		while (TickCount() < t) {
		}
	}

	Terminate();
}

// Initialize everything
void Initialize(void) {
	OSErr err;
	SysEnvRec theWorld;

	// Initialize needed managers
	InitGraf(&qd.thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(nil);
	InitCursor();
	MaxApplZone();

	// See if we have color QuickDraw.
	err = SysEnvirons(1, &theWorld);
	if (!theWorld.hasColorQD) {
		ExitError(kErrNoColorQD);
	}

	// Initialize random seed
	GetDateTime((unsigned long *)&qd.randSeed);

	// Figure out how large the window is
	SetRect(&gBufferRect, 0, 0, kGameXSize, kGameYSize);
	gGameRect = gBufferRect;

	SetRect(&gWindRect, qd.screenBits.bounds.right / 2 - kWindXSize / 2,
	        qd.screenBits.bounds.bottom / 2 - kWindYSize / 2,
	        qd.screenBits.bounds.right / 2 + kWindXSize / 2,
	        qd.screenBits.bounds.bottom / 2 + kWindYSize / 2);
	SetRect(&gLocalWindRect, 0, 0, kWindXSize, kWindYSize);

	OffsetRect(&gGameRect, kGameXPos, kGameYPos);

	gTheDevice = GetGDevice();

	if (!HasDepth(gTheDevice, 8, 1, 1)) {
		ExitError(kErrNo8Bit);
	}
	gOldDepth = (**(**gTheDevice).gdPMap).pixelSize;
	if (gOldDepth != 8) {
		switch (Alert(rALRT_ChangeDepth, NULL)) {
		case 1:
			break;
		default:
			ExitToShell();
		}
		err = SetDepth(gTheDevice, 8, 1, 1);
		if (err != 0) {
			ExitErrorOS(kErrNone, err);
		}
	}

	if (!((qd.screenBits.bounds.right == 640) &&
	      (qd.screenBits.bounds.left == 0) &&
	      (qd.screenBits.bounds.bottom == 480) &&
	      (qd.screenBits.bounds.top == 0))) {
		gWindPtr2 = NewCWindow(nil, &(qd.screenBits.bounds), "\pHaHaHa", false,
		                       plainDBox, (WindowPtr)-1, false, 0);

		gWindRect2 = qd.screenBits.bounds;
	} else {
		gWindPtr2 = NULL;
	}

	// Create the window
	gWindPtr = NewCWindow(nil, &gWindRect, "\pClick mouse button to quit.",
	                      true, plainDBox, (WindowPtr)-1, false, 0);

	Graphics_LoadColors();
	// Clear any crap on the window
	SetPort(gWindPtr);
	ForeColor(blackColor);
	BackColor(whiteColor);
	EraseRect(&gWindRect);

	// Create back buffer
	err = NewGWorld(&gBackBuffer, 8, &gBufferRect, gCTable, gTheDevice,
	                noNewDevice);
	if (err != 0) {
		GracefulExit();
	}

	NSetPalette((WindowPtr)gBackBuffer, gPalette, pmNoUpdates);

	// Set up back buffer
	SetGWorld(gBackBuffer, gTheDevice);
	ForeColor(blackColor);
	BackColor(whiteColor);
	EraseRect(&gBufferRect);
	gPixMap = GetGWorldPixMap(gBackBuffer);
	LockPixels(gPixMap);

	Hide_Menu_Bar();

	Init_Graphics();
	Initialize_Viewpoint();
	Init_Entities();
	Init_Sparks();
	Init_Stars();
	E_Init_Player();
}

void Hide_Menu_Bar(void) {
	PicHandle thePict;

	gMBarHeight = LMGetMBarHeight();

	LMSetMBarHeight(0);

	if (gWindPtr2 != NULL) {
		ShowWindow(gWindPtr2);

		CopyRgn(gWindPtr2->visRgn, gOldRegion2);
		SetEmptyRgn(gWindPtr2->visRgn);
		RectRgn(gWindPtr2->visRgn, &gWindRect2);

		SetPort(gWindPtr2);
		ForeColor(blackColor);
		BackColor(whiteColor);
		PaintRect(&gWindRect2);
	} else {
		CopyRgn(gWindPtr->visRgn, gOldRegion);
		SetEmptyRgn(gWindPtr->visRgn);
		RectRgn(gWindPtr->visRgn, &gWindRect);
	}

	SetPort(gWindPtr);
	/*ForeColor(redColor);
	BackColor(whiteColor);
	PaintRect(&gLocalWindRect);*/

	thePict = GetPicture(rPICT_Interface);
	DrawPicture(thePict, &gLocalWindRect);
	KillPicture(thePict);

	SetGWorld(gBackBuffer, gTheDevice);

	HideCursor();
}

void Show_Menu_Bar(void) {
	LMSetMBarHeight(gMBarHeight);

	if (gWindPtr2 != NULL) {
		CopyRgn(gOldRegion2, gWindPtr2->visRgn);
		HideWindow(gWindPtr2);
	} else {
		CopyRgn(gOldRegion, gWindPtr->visRgn);
	}

	InitCursor();
}

// Clear stuff
void Terminate(void) {
	OSErr Error;

	Show_Menu_Bar();

	SetPort(gWindPtr);

	Terminate_Graphics();
	Terminate_Viewpoint();
	Terminate_Entities();
	Terminate_Sparks();
	Terminate_Stars();

	UnlockPixels(gPixMap);
	DisposeWindow(gWindPtr);
	DisposeGWorld(gBackBuffer);
	Terminate_Palettes();

	FlushEvents(everyEvent, 0);

	if (gOldDepth != 8)
		if (HasDepth(gTheDevice, gOldDepth, 0, 0))
			Error = SetDepth(gTheDevice, gOldDepth, 0, 0);
		else
			Error = 0;

	if (Error)
		ExitToShell();
}

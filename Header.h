#ifndef _H_HEADER_
#define _H_HEADER_

#include <Events.h>
#include <Palettes.h>
#include <Processes.h>
#include <QDOffscreen.h>

/****************************************************/
/*                      Macros                      */
/****************************************************/

inline void GracefulExit (void) { FlushEvents(everyEvent,0); ExitToShell(); }

/****************************************************/
/*                Class Definitions                 */
/****************************************************/

class t_Entity;

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

extern	GDHandle		gTheDevice;
extern	WindowPtr		gWindPtr;
extern	GWorldPtr		gBackBuffer;
extern	Rect			gWindRect;
extern	Rect			gWindRect2;
extern	Rect			gLocalWindRect;
extern	Rect			gBufferRect;
extern	PixMapHandle	gPixMap;
extern	short			gOldDepth;
extern	short			gMBarHeight;
extern	RgnHandle		gOldRegion;
extern	RgnHandle		gOldRegion2;
extern	WindowPtr		gWindPtr2;
extern	Rect			gGameRect;

extern	CTabHandle		gCTable;
extern	PaletteHandle	gPalette;

#endif


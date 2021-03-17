/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Header.h"
#include "ResourceList.h"
#include "PaletteTable.h"
#include "Graphics.h"

/****************************************************/
/*                  Variable Types                  */
/****************************************************/

typedef struct {
	short	begin;
	short	end;
} tMaskRow;

typedef struct {
	tMaskRow	rows[400];
} tMaskStructure;
typedef tMaskStructure * tMaskPtr;
typedef tMaskPtr * tMaskHandle;

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

CTabHandle		gCTable;
PaletteHandle	gPalette;
RgnHandle		gMaskRegion;

/****************************************************/
/*                    Main Code                     */
/****************************************************/

void Create_Off_Screen_Bit_Map (Rect *theRect, GrafPtr *offScreen)
{
	GrafPtr		theBWPort;
	BitMap		theBitMap;	
	long		theRowBytes;
	
	theBWPort = (GrafPtr)(NewPtr(sizeof(GrafPort)));							// Allocate memory
	OpenPort(theBWPort);														// Open the port
	theRowBytes = (long)((theRect->right - theRect->left + 15L) / 16L) * 2L;	// Figure out size
	theBitMap.rowBytes = (short)theRowBytes;									// and other stuff
	theBitMap.baseAddr = NewPtr((long)theBitMap.rowBytes * 
		(theRect->bottom - theRect->top));
	if (theBitMap.baseAddr == 0L)
		ExitToShell();
	theBitMap.bounds = *theRect;
	if (MemError() != noErr)
		ExitToShell();
	SetPortBits(&theBitMap);
	ClipRect(theRect);
	RectRgn(theBWPort->visRgn, theRect);
	EraseRect(theRect);
	*offScreen = theBWPort;
}

void Kill_Off_Screen_Bit_Map (GrafPtr *wasPort)
{
	if (wasPort != nil)			// Is it dead already?
	{
		ClosePort(*wasPort);	// Close it
		*wasPort = nil;			// Make it nil, so we know it's dead
	}
}

void Init_Graphics (void)
{
	PicHandle	thePict;
	GrafPtr		thePort;
	
	thePict = GetPicture(rPict_InterfaceMask);
	Create_Off_Screen_Bit_Map(&gLocalWindRect,&thePort);
	SetPort(thePort);
	DrawPicture(thePict,&gGameRect);
	KillPicture(thePict);
	
	gMaskRegion = NewRgn();
	BitMapToRegion(gMaskRegion,&(thePort->portBits));
	
	Kill_Off_Screen_Bit_Map(&thePort);
	
	SetGWorld(gBackBuffer,gTheDevice);
}

void Terminate_Graphics (void)
{
	DisposeRgn(gMaskRegion);
}

void CopyToScreen(void)
{
	ForeColor(blackColor);
	BackColor(whiteColor);
	CopyBits	( (BitMap*) *gPixMap,
				  &(gWindPtr->portBits),
				  &gBufferRect,
				  &gGameRect,
				  srcCopy,
				  /*gWindPtr->visRgn*/gMaskRegion/*NULL*/ );
}

void ClearBuffer(void)
{
	PmForeColor(kPltt_Black);
	PaintRect(&gBufferRect);
}

void Graphics_LoadColors (void)
{
	gCTable = GetCTable(rCLUT_Main);
	(**gCTable).ctSeed = (**(**(**gTheDevice).gdPMap).pmTable).ctSeed;
	
	gPalette = GetPalette(gWindPtr);
	
	if (gPalette == NULL)
	{
		gPalette = NewPalette((**gCTable).ctSize+1, gCTable, pmTolerant+pmExplicit, 0x0000);
	}
	else
	{
		CTab2Palette(gCTable, gPalette, pmTolerant+pmExplicit, 0x0000);
	}
	
	NSetPalette(gWindPtr, gPalette, pmNoUpdates);
	
	ActivatePalette(gWindPtr);
}

void Terminate_Palettes (void)
{
	DisposeCTable(gCTable);
	DisposePalette(gPalette);
}

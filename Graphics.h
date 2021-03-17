#ifndef _H_GRAPHICS_
#define _H_GRAPHICS_

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void		Create_Off_Screen_Bit_Map	(Rect *theRect, GrafPtr *offScreen);
void		Kill_Off_Screen_Bit_Map		(GrafPtr *wasPort);
void		Init_Graphics				(void);
void		Terminate_Graphics			(void);
void		CopyToScreen				(void);
void		ClearBuffer					(void);
void		Graphics_LoadColors			(void);
void		Terminate_Palettes			(void);

#endif

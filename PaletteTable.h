#ifndef _H_PALETTETABLE_
#define _H_PALETTETABLE_

enum {
	kPltt_White		= 0,
	kPltt_Black		= 1,
	kPltt_Gray		= 8,
	kPltt_Red		= 22,
	kPltt_Yellow	= 29,
	kPltt_Green		= 36,
	kPltt_Cyan		= 43,
	kPltt_Blue		= 50,
	kPltt_Magenta	= 57,
	kPltt_DkRed		= 136,
	kPltt_DkYellow	= 143,
	kPltt_DkGreen	= 150,
	kPltt_DkCyan	= 157,
	kPltt_DkBlue	= 164,
	kPltt_DkMagenta	= 171
};

extern	UInt8	gPltt_White_2_Black[16];
extern	UInt8	gPltt_Black_2_Red[8];
extern	UInt8	gPltt_Black_2_Yellow[8];
extern	UInt8	gPltt_Black_2_Green[8];
extern	UInt8	gPltt_Black_2_Cyan[8];
extern	UInt8	gPltt_Black_2_Blue[8];
extern	UInt8	gPltt_Black_2_Magenta[8];
extern	UInt8	gPltt_Gray_2_Red[8];
extern	UInt8	gPltt_Gray_2_Yellow[8];
extern	UInt8	gPltt_Gray_2_Green[8];
extern	UInt8	gPltt_Gray_2_Cyan[8];
extern	UInt8	gPltt_Gray_2_Blue[8];
extern	UInt8	gPltt_Gray_2_Magenta[8];
extern	UInt8	gPltt_White_2_Red[8];
extern	UInt8	gPltt_White_2_Yellow[8];
extern	UInt8	gPltt_White_2_Green[8];
extern	UInt8	gPltt_White_2_Cyan[8];
extern	UInt8	gPltt_White_2_Blue[8];
extern	UInt8	gPltt_White_2_Magenta[8];
extern	UInt8	gPltt_Gray_2_DkRed[8];
extern	UInt8	gPltt_Gray_2_DkYellow[8];
extern	UInt8	gPltt_Gray_2_DkGreen[8];
extern	UInt8	gPltt_Gray_2_DkCyan[8];
extern	UInt8	gPltt_Gray_2_DkBlue[8];
extern	UInt8	gPltt_Gray_2_DkMagenta[8];
extern	UInt8	gPltt_White_2_DkRed[8];
extern	UInt8	gPltt_White_2_DkYellow[8];
extern	UInt8	gPltt_White_2_DkGreen[8];
extern	UInt8	gPltt_White_2_DkCyan[8];
extern	UInt8	gPltt_White_2_DkBlue[8];
extern	UInt8	gPltt_White_2_DkMagenta[8];
extern	UInt8	gPltt_Rainbow[18];
extern	UInt8	gPltt_DarkRainbow[18];
extern	UInt8	gPltt_LiteRainbow[18];
extern	UInt8	gPltt_DimRainbow[18];

extern	UInt8	gPltt_Full_Red[15];
extern	UInt8	gPltt_Full_Yellow[15];
extern	UInt8	gPltt_Full_Green[15];
extern	UInt8	gPltt_Full_Cyan[15];
extern	UInt8	gPltt_Full_Blue[15];
extern	UInt8	gPltt_Full_Magenta[15];

#endif

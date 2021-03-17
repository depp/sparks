/*
The color table is a bunch of gradients.  

The total number of entries in all the
gradients is larger than 256, (in fact
there are 328) but there are only 256
colors.  This makes it easier to find
the color you are looking for.  
*/

#include <MacTypes.h>

UInt8 gPltt_White_2_Black[16] =		{  0, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1};

UInt8 gPltt_Black_2_Red[8] =		{  1, 16, 17, 18, 19, 20, 21, 22};
UInt8 gPltt_Black_2_Yellow[8] =		{  1, 23, 24, 25, 26, 27, 28, 29};
UInt8 gPltt_Black_2_Green[8] =		{  1, 30, 31, 32, 33, 34, 35, 36};
UInt8 gPltt_Black_2_Cyan[8] =		{  1, 37, 38, 39, 40, 41, 42, 43};
UInt8 gPltt_Black_2_Blue[8] =		{  1, 44, 45, 46, 47, 48, 49, 50};
UInt8 gPltt_Black_2_Magenta[8] =	{  1, 51, 52, 53, 54, 55, 56, 57};
/*
UInt8 * gPltt_Black_2_Color[6] = {
	gPltt_Black_2_Red,
	gPltt_Black_2_Yellow,
	gPltt_Black_2_Green,
	gPltt_Black_2_Cyan,
	gPltt_Black_2_Blue,
	gPltt_Black_2_Magenta
};
*/
UInt8 gPltt_Gray_2_Red[8] =			{  8, 58, 59, 60, 61, 62, 63, 22};
UInt8 gPltt_Gray_2_Yellow[8] =		{  8, 64, 65, 66, 67, 68, 69, 29};
UInt8 gPltt_Gray_2_Green[8] =		{  8, 70, 71, 72, 73, 74, 75, 36};
UInt8 gPltt_Gray_2_Cyan[8] =		{  8, 76, 77, 78, 79, 80, 81, 43};
UInt8 gPltt_Gray_2_Blue[8] =		{  8, 82, 83, 84, 85, 86, 87, 50};
UInt8 gPltt_Gray_2_Magenta[8] =		{  8, 88, 89, 90, 91, 92, 93, 57};

UInt8 gPltt_White_2_Red[8] =		{  0, 94, 95, 96, 97, 98, 99, 22};
UInt8 gPltt_White_2_Yellow[8] =		{  0,100,101,102,103,104,105, 29};
UInt8 gPltt_White_2_Green[8] =		{  0,106,107,108,109,110,111, 36};
UInt8 gPltt_White_2_Cyan[8] =		{  0,112,113,114,115,116,117, 43};
UInt8 gPltt_White_2_Blue[8] =		{  0,118,119,120,121,122,123, 50};
UInt8 gPltt_White_2_Magenta[8] =	{  0,124,125,126,127,128,129, 57};

UInt8 gPltt_Gray_2_DkRed[8] = 		{  8,130,131,132,133,134,135,136};
UInt8 gPltt_Gray_2_DkYellow[8] = 	{  8,137,138,139,140,141,142,143};
UInt8 gPltt_Gray_2_DkGreen[8] = 	{  8,144,145,146,147,148,149,150};
UInt8 gPltt_Gray_2_DkCyan[8] = 		{  8,151,152,153,154,155,156,157};
UInt8 gPltt_Gray_2_DkBlue[8] = 		{  8,158,159,160,161,162,163,164};
UInt8 gPltt_Gray_2_DkMagenta[8] = 	{  8,165,166,167,168,169,170,171};

UInt8 gPltt_White_2_DkRed[8] = 		{  0,172,173,174,175,176,177,136};
UInt8 gPltt_White_2_DkYellow[8] = 	{  0,178,179,180,181,182,183,143};
UInt8 gPltt_White_2_DkGreen[8] = 	{  0,184,185,186,187,188,189,150};
UInt8 gPltt_White_2_DkCyan[8] = 	{  0,190,191,192,193,194,195,157};
UInt8 gPltt_White_2_DkBlue[8] = 	{  0,196,197,198,199,200,201,164};
UInt8 gPltt_White_2_DkMagenta[8] = 	{  0,202,203,204,205,206,207,171};

UInt8 gPltt_Rainbow[18] =			{ 22,208,209, 29,210,211, 36,212,213, 43,214,215, 50,216,217, 57,218,219};
UInt8 gPltt_DarkRainbow[18] =		{136,220,221,143,222,223,150,224,225,157,226,227,164,228,229,171,230,231};
UInt8 gPltt_LiteRainbow[18] =		{ 96,232,233,102,234,235,108,236,237,114,238,239,120,240,241,126,242,243};
UInt8 gPltt_DimRainbow[18] =		{132,244,245,139,246,247,146,248,249,153,250,251,160,252,253,167,254,255};

/*
Combination Gradients
*/

UInt8 gPltt_Full_Red[15] =			{  0, 94, 95, 96, 97, 98, 99, 22, 21, 20, 19, 18, 17, 16,  1};
UInt8 gPltt_Full_Yellow[15] =		{  0,100,101,102,103,104,105, 29, 28, 27, 26, 25, 24, 23,  1};
UInt8 gPltt_Full_Green[15] =		{  0,106,107,108,109,110,111, 36, 35, 34, 33, 32, 31, 30,  1};
UInt8 gPltt_Full_Cyan[15] =			{  0,112,113,114,115,116,117, 43, 42, 41, 40, 39, 38, 37,  1};
UInt8 gPltt_Full_Blue[15] =			{  0,118,119,120,121,122,123, 50, 49, 48, 47, 46, 45, 44,  1};
UInt8 gPltt_Full_Magenta[15] =		{  0,124,125,126,127,128,129, 57, 56, 55, 54, 53, 52, 51,  1};

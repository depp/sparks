/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Params.h"
#include "Header.h"
#include "PaletteTable.h"
#include "Vectors.h"
#include "Entity.h"
#include "Viewpoint.h"
#include "Stars.h"

/****************************************************/
/*                    Constants                     */
/****************************************************/

#define	kNumLayers	sizeof(gLayerParallaxes)/sizeof(float)

const int	kStar_SequenceLength		= 32;
const int	kStar_NumTiles				= 8;
const int	kStar_TileSize				= 64;
const int	kStar_NumColors				= 6;

float gLayerParallaxes[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };

/****************************************************/
/*                  Variable Types                  */
/****************************************************/

typedef struct {
	SInt8	HOffset;
	SInt8	VOffset;
	UInt8	color;
	UInt8	padding;
} tStarTile;

typedef struct {
	float		parallax;
	UInt8		HSequence[kStar_SequenceLength];
	UInt8		VSequence[kStar_SequenceLength];
	tStarTile	tiles[kStar_NumTiles];
} tStar_Layer;

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

UInt8 StarColors[6] ={  94,100,106,112,118,124 };

Ptr				gStarData;
tStar_Layer		*gStarLayers;

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void Stars_Create_Layer (tStar_Layer * s);
void Draw_StarLayer (tStar_Layer * s);

/****************************************************/
/*                    Main Code                     */
/****************************************************/

void Init_Stars (void)
{
	int	i;
	
	gStarData = NewPtr(sizeof(tStar_Layer)*kNumLayers);
	
	if (gStarData == NULL)
		GracefulExit();
	
	gStarLayers = (tStar_Layer*)gStarData;
	
	for (i=0;i<kNumLayers;i++) {
		gStarLayers[i].parallax = gLayerParallaxes[i];
		
		Stars_Create_Layer(gStarLayers + i);
	}
}

void Stars_Create_Layer (tStar_Layer * s)
{
	UInt8		*ptrOne;
	tStarTile	*ptrTwo;
	int			i;
	//int			r;
	
	ptrOne = s->HSequence;
	for (i=0; i<kStar_SequenceLength; i++) {
		*ptrOne = (Random() & 0x7FFF) % kStar_NumTiles;
		ptrOne++;
	}
	
	ptrOne = s->VSequence;
	for (i=0; i<kStar_SequenceLength; i++) {
		*ptrOne = (Random() & 0x7FFF) % kStar_NumTiles;
		ptrOne++;
	}
	
	ptrTwo = s->tiles;
	for (i=0; i<kStar_NumTiles; i++) {
		ptrTwo->HOffset = (Random() & 0x7FFF) % kStar_TileSize;
		ptrTwo->VOffset = (Random() & 0x7FFF) % kStar_TileSize;
		ptrTwo->color = (Random() & 0x7FFF) % kStar_NumColors;
		ptrTwo->color = StarColors[ptrTwo->color];
		ptrTwo++;
	}
}

void Draw_Stars (void)
{
	int	c;
	
	for (c=0;c<kNumLayers;c++) {
		Draw_StarLayer(gStarLayers + c);
	}
}

void Draw_StarLayer (tStar_Layer * s)
{
	// Vars
	Point			tile_Left;
	Point			tile_Current;
	Point			loc_Left;
	Point			loc_Current;
	Point			starLoc;
	
	Ptr				addr_Left;
	Ptr				addr_Current;
	//Ptr				addr_Row;
	
	//int				hLoc;
	//int				currentRow;
	//int				rowCounter;
	
	int				bytesPerRow;
	Ptr				baseAddress;
	
	t_Vector2f		topLeft;
	t_Vector2f		temp;
	
	tStarTile		*curTile;
	
	// Init
	baseAddress = (**gPixMap).baseAddr;
	bytesPerRow = (**gPixMap).rowBytes & 0x7FFF;
	
	// Bottom
	topLeft.set(kVirtualXMin,kVirtualYMax);
	topLeft += gViewpoint.translate1 * s->parallax;
	topLeft *= gViewpoint.scale;
	
	tile_Left.h = floor(topLeft[0]/((float)kStar_TileSize));
	tile_Left.v = ceil(topLeft[1]/((float)kStar_TileSize));
	
	temp.set(tile_Left.h,tile_Left.v);
	temp *= kStar_TileSize;
	temp -= topLeft;
	
	loc_Left.h = floor(temp[0]);
	loc_Left.v = floor(-temp[1]);
	
	addr_Left = baseAddress + loc_Left.v * bytesPerRow +loc_Left.h;
	
	while (tile_Left.h < 0) { tile_Left.h += kStar_SequenceLength; }
	while (tile_Left.v < 0) { tile_Left.v += kStar_SequenceLength; }
	tile_Left.h += kStar_SequenceLength;
	tile_Left.v += kStar_SequenceLength;
	
	while (loc_Left.v < kGameYSize) {
		addr_Current = addr_Left;
		loc_Current = loc_Left;
		tile_Current = tile_Left;
		
		while (loc_Current.h < kGameXSize) {
			curTile = s->tiles + ( ( (s->HSequence[tile_Current.h % kStar_SequenceLength])
								   + (s->VSequence[tile_Current.v % kStar_SequenceLength]) )
								   % kStar_NumTiles );
			
			starLoc = loc_Current;
			starLoc.h += curTile->HOffset;
			starLoc.v += curTile->VOffset;
			
			if (!(	(starLoc.h < gBufferRect.left) ||
					(starLoc.v < gBufferRect.top) ||
					(starLoc.h > gBufferRect.right) ||
					(starLoc.v > gBufferRect.bottom)	) )
				*(addr_Current + curTile->HOffset + curTile->VOffset * bytesPerRow)
					= curTile->color;
			
			tile_Current.h++;
			addr_Current += kStar_TileSize;
			loc_Current.h += kStar_TileSize;
		}
		
		addr_Left += bytesPerRow * kStar_TileSize;
		loc_Left.v += kStar_TileSize;
		tile_Left.v--;
	}
}

void Terminate_Stars (void)
{
	DisposePtr(gStarData);
}

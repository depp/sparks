/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Header.h"
#include "Input.h"

/****************************************************/
/*                      Macros                      */
/****************************************************/

#define keyMapCheck(keycode,keymap) (((((char*)(keymap))[(keycode)>>3])&(1<<((keycode)&7)))!=0)

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

char			gKeys[kKeyEnd];
static	char	gOldKeys[kKeyEnd];
static	KeyMap	gK;
static	t_Key	gCommands[] = 
{
	{ 123, kKey_TurnLeft },
	{ 124, kKey_TurnRight },
	{ 126, kKey_Thrust },
	{ 49,  kKey_Fire },
	{ 125, kKey_Brake },
	{ -1, -1 }
};

/****************************************************/
/*                    Main Code                     */
/****************************************************/

void Update_Input (void)
{
	int	i;
	
	GetKeys(gK);
	BlockMoveData(gKeys,gOldKeys,kKeyEnd*sizeof(char));
	
	for (i=0;gCommands[i].command!=-1;i++)
	{
		if (keyMapCheck(gCommands[i].keyCode,gK))
		{
			if (gOldKeys[gCommands[i].command] != kKeyState_Up)
				gKeys[gCommands[i].command] = kKeyState_StillDown;
			else gKeys[gCommands[i].command] = kKeyState_Down;
		}
		else gKeys[gCommands[i].command] = kKeyState_Up;
	}
}

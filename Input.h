#ifndef _H_INPUT_
#define _H_INPUT_

/****************************************************/
/*                     Constants                    */
/****************************************************/

enum {
	kKey_TurnLeft,
	kKey_TurnRight,
	kKey_Thrust,
	kKey_Fire,
	kKey_Brake,
	kKeyEnd
};

enum {
	kKeyState_Up,
	kKeyState_Down,
	kKeyState_StillDown
};

/****************************************************/
/*                  Variable Types                  */
/****************************************************/

typedef struct {
	char	keyCode;
	char	command;
} t_Key;

/****************************************************/
/*                 Global Variables                 */
/****************************************************/

extern	char	gKeys[kKeyEnd];

/****************************************************/
/*                    Prototypes                    */
/****************************************************/

void		Update_Input			(void);

#endif

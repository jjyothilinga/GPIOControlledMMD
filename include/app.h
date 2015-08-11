#include "config.h"
#include "mmd.h"
#include "string.h"
#include "linearkeypad.h"



enum
{
	CMD_SET_MODEL = 0X80
};


/***************************************************************
*  	----------------------------------------
*	|  BIT 3  |  BIT 2  |  BIT 1  |  BIT 0 |
*	---------------------------------------- 
*	|   RC3   |   RC2   |   RC1   |   RC0  |
*	---------------------------------------- 
*
*	0001 -> Cycle complete/stopped
*	0010 -> Evacuation
*   0011 -> N2 Feeding
*	0100 -> Profile Heating 1
*	0101 -> Profile Heating 2
* 	0110 -> Vacuum Drying
*	0111 -> Cooling 1
*	1000 -> Cooling 2
* 	1001 -> N2 Cooling
*	
***************************************************************/
enum
{
	BIT_0 = KEY0,
	BIT_1 = KEY1,
	BIT_2 = KEY2,
	BIT_3 = KEY3
};


UINT8 APP_comCallBack( far UINT8 *rxPacket,  far UINT8* txCode, far UINT8** txPacket);
void APP_init(void);
void APP_task(void);

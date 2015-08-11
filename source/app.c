//#include "communication.h"
#include "mmd.h"
#include "string.h"
#include "app.h"
//#include "uart.h"
#include "typedefs.h"
#include "eep.h"
#include "linearkeypad.h"


typedef struct _APP
{
	//used to store the different receivedMsg 
	UINT8 	receivedMsg[MSG_LENGTH];
	UINT8 	eepUpdate;
	
	//used to store the receivedMsg index 
	UINT16 	receivedIndex;

	//Buffer used to store the receivedMsg messages
	UINT8 msg[MAX_PROCESS][MSG_LENGTH];

	//Used to store the input
	UINT8 previousInput;
	UINT8 currentInput;

	UINT8 currentIndex;

}APP;

#pragma idata APP_DATA
APP app = {{0},0};
MMD_Config mmdConfig = {0};
#pragma idata


void APP_init(void)
{
	UINT8 i = 0, j = 0;
	UINT8 receivedMsg = '1';
	UINT16 index = 0;
	UINT8 data = 0;
	UINT8 messageIndex = 0;

	//Read the receivedMsg from EEPROM and store it into 
	for( i = 0; i < MAX_PROCESS; i++ )
	{		
		j = 0;

		//store the message offset
		index = ( UINT16 ) i * INDEX_OFFSET;

		//read the data from eeprom check for null
		data = Read_b_eep( index + j );
		Busy_eep(  );

		if( data == '\0' )
			continue;

		while( data != '\0' )
		{
			data = app.msg[i][j++] = Read_b_eep( index + j );
			Busy_eep(  );
		}
		
	}



	//restore the current message
	index = ( UINT16 )MAX_PROCESS * INDEX_OFFSET;
	messageIndex = Read_b_eep( index );
	Busy_eep(  );

	app.previousInput = app.currentInput = messageIndex;
	app.currentIndex = messageIndex;

	if( messageIndex <= MAX_PROCESS )
	{
		MMD_clearSegment(0);
		mmdConfig.startAddress = 0;
		mmdConfig.length = MMD_MAX_CHARS;
		mmdConfig.symbolCount = strlen( app.msg[messageIndex] );
		mmdConfig.symbolBuffer = app.msg[messageIndex];
		mmdConfig.scrollSpeed = SCROLL_SPEED_LOW;
		MMD_configSegment( 0 , &mmdConfig);
	}


}

void APP_task(void)
{

	UINT8 i = 0, j = 0;
	UINT8 writeIndex = 0;
	UINT16 eepromIndex = 0;
	//update the new string in eeprom and buffer
	if(app.eepUpdate == TRUE)
	{

		//update EEPROM with new receivedMsg string
		while( app.receivedMsg[i] != '\0' )
		{
			Write_b_eep( (app.receivedIndex+i), app.receivedMsg[i] );
			Busy_eep();
			i++;
		}	

		//Store null eeprom
		Write_b_eep( (app.receivedIndex+i), '\0' );
		Busy_eep();

		//Get the write index of buffer by dividing message length
		writeIndex = ( UINT8 ) app.receivedIndex / INDEX_OFFSET;

		for( j = 0; j < i; j++ )
		{
			app.msg[writeIndex][j] = Read_b_eep( app.receivedIndex + j );
			Busy_eep(  );
		}

		app.msg[writeIndex][j] = '\0';

		if( writeIndex == app.currentIndex )
		{
			MMD_clearSegment(0);
			mmdConfig.startAddress = 0;
			mmdConfig.length = MMD_MAX_CHARS;
			mmdConfig.symbolCount = strlen( app.msg[writeIndex] );
			mmdConfig.symbolBuffer = app.msg[writeIndex];
			mmdConfig.scrollSpeed = SCROLL_SPEED_LOW;
			MMD_configSegment( 0 , &mmdConfig);
		}

		
		app.eepUpdate = FALSE;
	}	


	//scan the input for change and update mmd based on the input
	app.currentInput = 0;

	if ( (LinearKeyPad_getKeyState(BIT_0) == 1) )
		app.currentInput |= 0X01; 						//0b00000001;
	if ( (LinearKeyPad_getKeyState(BIT_1) == 1) )
		app.currentInput |= 0X02; 						//0b00000010;
	if ( (LinearKeyPad_getKeyState(BIT_2) == 1) )
		app.currentInput |= 0X04; 						//0b00000100;
	if ( (LinearKeyPad_getKeyState(BIT_3) == 1) )
		app.currentInput |= 0X08;						//0b00001000;
	
	if( app.previousInput != app.currentInput && app.currentInput != 0x00 )
	{
		if( app.currentInput <= MAX_PROCESS )
		{
			MMD_clearSegment(0);
			mmdConfig.startAddress = 0;
			mmdConfig.length = MMD_MAX_CHARS;
			mmdConfig.symbolCount = strlen( app.msg[app.currentInput-1] );
			mmdConfig.symbolBuffer = app.msg[app.currentInput-1];
			mmdConfig.scrollSpeed = SCROLL_SPEED_LOW;
			MMD_configSegment( 0 , &mmdConfig);
			app.previousInput = app.currentInput;

			app.currentIndex = app.currentInput-1;

			//store current message index into eeprom
			Write_b_eep( (UINT16)MAX_PROCESS * INDEX_OFFSET, app.currentInput-1 );
			Busy_eep();
		}
	}
}

UINT8 APP_comCallBack( far UINT8 *rxPacket, far UINT8* txCode,far UINT8** txPacket)
{

	UINT8 i = 0;
	UINT16 index = 0;

	UINT8 rxCode = rxPacket[0];
	UINT8 length = 0;

	switch( rxCode )
	{
		case CMD_SET_MODEL:
			app.eepUpdate = TRUE;

			//store the index
			app.receivedIndex = ( UINT16 )rxPacket[1];
			
			//calculate the correct index based on its index offset
			app.receivedIndex =  app.receivedIndex * INDEX_OFFSET;

			while( rxPacket[i+2] != '\0' )
				app.receivedMsg[i++] = rxPacket[i+2];

			app.receivedMsg[i] = '\0';

			*txCode = CMD_SET_MODEL;
			break;

		default:
		break;

	}

	return length;

}

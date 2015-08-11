#ifndef CONFIG_H
#define CONFIG_H

/*
*------------------------------------------------------------------------------
* config.h
*
*/

#define DEVICE_ADDRESS			01

/*----------------------------------------
*	BOARD MOULE CONFIG
*----------------------------------------*/

#define MHz_64					(64000000UL)	// Hz
#define MHz_32					(32000000UL)	// Hz
#define MHz_16					(16000000UL)	// Hz
#define MHz_10					(10000000UL)	// Hz

/*----------------------------------------
*	OSCILLATOR CONFIG
*----------------------------------------*/

#define SYSTEM_CLOCK			(MHz_16)	


/*----------------------------------------
*	TIMER CONFIG
*----------------------------------------*/
#define FULLSCALE_16BIT				(65535)
#define TIMER0_TIMEOUT_DURATION 	(1000UL)			//1ms			

#define TIMESTAMP_DURATION 			(200)

/*----------------------------------------
*	DEVICE CONFIG
*----------------------------------------*/
#define __FACTORY_CONFIGURATION__

//MMD module configuration
#define MMD_MAX_CHARS		8
#define MMD_MAX_SEGMENTS	1
#define MMD_MAX_ADDRESS		128
//#define __MMD_STATIC__
//#define MMD_TEST
/*----------------------------------------
*	COM module configuration
*----------------------------------------*/

#define ACTIVE_USARTS			1	
#define UART1_BAUDRATE			19200
#define UART_TEST

#define __BCC_XOR__
//#define __RESPONSE_ENABLED__
//#define __LOOP_BACK__
#define BROADCAST_ADDRESS		0xFF
#define CMD_SOP					0xAA
#define CMD_EOP 				0xBB
#define RESP_SOP				0xCC
#define RESP_EOP				0xDD
//#define __NO_CHECKSUM__

enum
{
	CMD_PACKET_SIZE = 60,
	RESP_PACKET_SIZE = 30
};

#define 	RX_PACKET_SIZE		(60)	
#define 	TX_PACKET_SIZE		(60)

/*----------------------------------------
*	Display module configuration
*----------------------------------------*/
#define __DISPLAY_TEST__
#define MAX_MSG 7
//#define COMMON_CATHODE


// Enable for external eeprom access
// Comment out this line if internal eeprom access required
#define EEP_EXTERRNAL
// For uart enable
//#define EN_UART
// Enable for hardware i2c module usage
//#define USE_MSSP_I2C

/*----------------------------------------
*	RTC CONFIGURATION
*----------------------------------------*/

//#define TIME_DEBUG

//#define RTC_DS1307
//#define RTC_DS3232


/*----------------------------------------
*	Keypad Configurations
*----------------------------------------*/

//#define __FACTORY_CONFIGURATION__
//#define __INPUT_SIMULATION__

/*----------------------------------------
*	APP Configurations
*----------------------------------------*/

#define MSG_LENGTH		20
#define EEPROM_ADDRESS	0
#define MAX_PROCESS   	10
#define INDEX_OFFSET	0X20
/*
*------------------------------------------------------------------------------
* Public Data Types
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Variables (extern)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Constants (extern)
*------------------------------------------------------------------------------
*/


/*
*------------------------------------------------------------------------------
* Public Function Prototypes (extern)
*------------------------------------------------------------------------------
*/

#endif
/*
*  End of config.h
*/




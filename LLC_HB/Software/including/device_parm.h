
#ifndef DEVICE_PARM_H 
#define DEVICE_PARM_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
/*------------------------------Device macro----------------------------------*/
#define DEVICE           	 UCD3100ISO1  				//Device Name

#define SETUP_ID            "VERSION1|LLC001"			//Generic setup id
#define MFR_ID				"TI"						//Hardware Manufacturer

#define MFR_MODEL			"UCD3138ALLCEVM150"			//Hardware Model

#define MFR_REVISION    	"E3"						//Hardware revision
#define MFR_DATE			"YYMMDD"					//Manufacturer date
#define MFR_LOCATION		"Dallas, TX"				//Manufacturer location
#define MFR_SERIAL			"XXXXX"						//Serial number
#define MFR_IC_DEVICE		"UCD3138RGC"				//TI device part number
#define MFR_IC_DEVICE_REV	"0"							//TI device revision

#define DEVICE_ID           	 "UCD3100ISO1|0.0.11.0106|141031"  				//Device id

#define MFR_ID_LENGTH 				sizeof(MFR_ID)
#define SETUP_ID_LENGTH 			sizeof(SETUP_ID)
#define MFR_MODEL_LENGTH 			sizeof(MFR_MODEL)
#define MFR_REVISION_LENGTH 		sizeof(MFR_REVISION)
#define MFR_DATE_LENGTH				sizeof(MFR_DATE)
#define MFR_LOCATION_LENGTH			sizeof(MFR_LOCATION)
#define MFR_SERIAL_LENGTH			sizeof(MFR_SERIAL)
#define MFR_IC_DEVICE_LENGTH		sizeof(MFR_IC_DEVICE)
#define MFR_IC_DEVICE_REV_LENGTH	sizeof(MFR_IC_DEVICE_REV)
#define DEVICE_ID_LENGTH			sizeof(DEVICE_ID)

/*--------------------------------Flash macro---------------------------------*/
//=============================================================================
// variables for PARM_INFO and PARM_VAR
//=============================================================================

//  Memory limits used by the PARM_INFO and PARM_VALUE commands.
#define	RAM_START_ADDRESS	0x00019000	// Beginning of RAM
#define	RAM_END_ADDRESS		0x00019FFF	// End of RAM
#define RAM_LENGTH			(RAM_END_ADDRESS - RAM_START_ADDRESS + 1)

// Allow access to peripherals, but not core ARM regs.
#define	REG_START_ADDRESS	0xFFF7d100	// Beginning of Register space
#define	REG_END_ADDRESS		0xFFF7fdff	// End of Register space
#define REG_LENGTH			(REG_END_ADDRESS - REG_START_ADDRESS + 1)

// Allow read-only access to Data Flash
#define	DFLASH_START_ADDRESS	0x00018800	// Beginning of DFLASH
#define	DFLASH_END_ADDRESS		0x00018FFF	// End of DFLASH
#define DFLASH_LENGTH			(DFLASH_END_ADDRESS - DFLASH_START_ADDRESS + 1)
#define	DATA_FLASH_SEGMENT_SIZE		(32)
#define	DATA_FLASH_NUM_SEGMENTS		(DATA_FLASH_LENGTH / DATA_FLASH_SEGMENT_SIZE)

// Allow read-only access to Constants in Program Flash
#define	PFLASH_CONST_START_ADDRESS	0x00000000	// Beginning of PFLASH Constants
#define	PFLASH_CONST_END_ADDRESS   	0x00007FFF	// End of PFLASH Constants
#define PFLASH_CONST_LENGTH			(PFLASH_CONST_END_ADDRESS - PFLASH_CONST_START_ADDRESS + 1)

// Allow read-only access to Program in Program Flash
#define	PFLASH_PROG_START_ADDRESS	0x00000000	// Beginning of PFLASH Program
#define	PFLASH_PROG_END_ADDRESS   	0x00007FFF	// End of PFLASH Program
#define PFLASH_PROG_LENGTH			(PFLASH_PROG_END_ADDRESS - PFLASH_PROG_START_ADDRESS + 1)

 //Cyclone 2 extra addresses
#define LOOP_MUX_START_ADDRESS  0x00020000
#define LOOP_MUX_LENGTH         0x00000090    //changed from 78

#define FAULT_MUX_START_ADDRESS 0x00030000
#define FAULT_MUX_LENGTH        0x00000080

#define ADC_START_ADDRESS       0x00040000
#define ADC_LENGTH              0x00000098

#define DPWM3_START_ADDRESS     0x00050000
#define DPWM3_LENGTH            0x0000008c

#define FILTER2_START_ADDRESS   0x00060000
#define FILTER2_LENGTH          0x00000064

#define DPWM2_START_ADDRESS     0x00070000
#define DPWM2_LENGTH            0x0000008c

#define FE_CTRL2_START_ADDRESS  0x00080000
#define FE_CTRL2_LENGTH         0x00000044

#define FILTER1_START_ADDRESS   0x00090000
#define FILTER1_LENGTH          0x00000064

#define DPWM1_START_ADDRESS     0x000a0000
#define DPWM1_LENGTH            0x0000008c

#define FE_CTRL1_START_ADDRESS  0x000b0000
#define FE_CTRL1_LENGTH         0x00000044

#define FILTER0_START_ADDRESS   0x000c0000
#define FILTER0_LENGTH          0x00000064

#define DPWM0_START_ADDRESS     0x000d0000
#define DPWM0_LENGTH            0x0000008c

#define FE_CTRL0_START_ADDRESS  0x000e0000
#define FE_CTRL0_LENGTH         0x00000044

#define SYSTEM_REGS_START_ADDRESS 0xfffffd00
#define SYSTEM_REGS_LENGTH        0x2d0

#define	NUM_MEMORY_SEGMENTS	19	// 19 memory segments for Cyclone 2
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/
//=============================================================================
// Start of MFR message 
//=============================================================================
const Uint8 setup_id[]          = SETUP_ID;
const Uint8 mfr_model[]			= MFR_MODEL;
const Uint8 mfr_revision[]		= MFR_REVISION;
const Uint8 mfr_date[]			= MFR_DATE;
const Uint8 mfr_location[]		= MFR_LOCATION;
const Uint8 mfr_serial[]		= MFR_SERIAL;
const Uint8 mfr_ic_device[]		= MFR_IC_DEVICE;
const Uint8 mfr_ic_device_rev[]	= MFR_IC_DEVICE_REV;
const Uint8 mfr_id[]			= MFR_ID;

#pragma DATA_SECTION (device_id_string, "FixedDeviceID");
const Uint8  device_id_string[] = DEVICE_ID;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* DEVICE_PARM_H */

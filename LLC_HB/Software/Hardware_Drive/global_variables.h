
#ifndef GLOBAL_VARIABLES_H 
#define GLOBAL_VARIABLES_H 

#ifdef __cplusplus
extern "C"{
#endif

#ifdef MAIN 					// If it is the main routine
	#define EXTERN	 			// If it isn't extern, so define it as nothing
#else 							// If it isn't the main routine
	#define EXTERN extern 		// If it is extern
#endif
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
/*-----------------------------------macro------------------------------------*/
#define MFBALR2_HALF0_DATA_FLASH_BASE_ADDRESS (0x9800)
#define MFBALRX_BYTE0_BLOCK_SIZE_2K     	(0x20) 		
#define MFBALRX_BYTE0_RONLY					(0x02)		   //Read-only protection
#define MFBALRX_BYTE0_BLOCK_SIZE_32K    	(0x60)

EXTERN volatile Uint32 FAULTMUXINTSTAT_value;
EXTERN Uint8 erase_segment_counter;	// Number of DFlash segment remaining to be erased
EXTERN Uint8 erase_segment_number;	
/*----------------------------------typedef-----------------------------------*/
typedef struct  
{
	Uint32 address;		//Value from adc for device address
	Uint32 vin_mon; 	//Value from adc for Vin 
	Uint32 ishare; 		//Value from adc for Ishare
	Uint32 vo_sense; 	//Value from adc for Vout
	Uint32 ips; 		//Value from adc for primary current sense
	Uint32 vo_ovp; 		//Value from adc for Vin  
	Uint32 pri_temp;	//Value from adc for SR MOSFET temperature
	Uint32 io_sense; 	//Value from adc for Iout
	Uint32 device_temp;	//Value from adc for internal device temperature
	Uint32 ips_hr;
	Uint32 address_hr;
	Uint32 sec_temp;
	Uint32 adc_scale_factor;
} ADC_VALUES_STRUCT;

EXTERN ADC_VALUES_STRUCT adc_values; 	//ADC Readings
EXTERN ADC_VALUES_STRUCT adc_values_avg;//ADC Readings Averaged
/*----------------------------------variable----------------------------------*/
EXTERN Uint8 flash_write_status;	// Global status while attempting to write to Data Flash.
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* GLOBAL_VARIABLES_H */

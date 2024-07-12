
#ifndef PMBUS_DCDC_PARM_H 
#define PMBUS_DCDC_PARM_H 

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
#define ROM_PASSWORD_BYTES      (4)
#define DCDC_PAGE_NUMS (1)
/*----------------------------------typedef-----------------------------------*/
//=============================================================================
// Start of power parameter
//=============================================================================
typedef struct{
    Uint16 vout_cal_offset;
    Uint16 iout_cal_gain;
    Uint16 iout_cal_offset;
    Uint16 temperature_cal_offset;
    Uint16 temperature_cal_gain;
    Uint16 vout_cal_monitor;
}PMBUS_DCDC_CAL;//must be even number of int16

typedef struct{
    Uint16 vin_scale;
    Uint16 vin_offset;
}PMBUS_DCDC_CAL_NONPAGED; //must be even number of int16

typedef struct{
    Uint16 ot_limit_DCDC_1;
    Uint16 ot_limit_DCDC_2;
    Uint16 ot_limit_DCDC_3;
    Uint16 ot_limit_DCDC_4;
    int16  deadband_config[8];
    Uint16 vin_ov_fault_limit;
    Uint16 vin_uv_fault_limit;
    Uint16 vin_uv_warn_limit;
    char  mfr_date[14];
    char  rom_password[ROM_PASSWORD_BYTES];
}PMBUS_DCDC_CONFIG_NONPAGED; //must be even number int16

typedef struct{
    Uint16 vout_cmd;
    Uint16 vout_ov_fault_limit;
    Uint16 vout_ov_warn_limit;
    Uint16 vout_uv_fault_limit;
    Uint16 vout_uv_warn_limit;
    Uint16 iout_oc_fault_limit;
    Uint16 iout_oc_warn_limit;
    Uint16 temp_ot_fault_limit;
    Uint16 temp_ot_warn_limit;
    Uint16 vin_ov_fault_limit;
    Uint16 vin_ov_warn_limit;
    Uint16 vin_uv_fault_limit;
    Uint16 vin_uv_warn_limit;
    Uint16 iin_oc_fault_limit;
    Uint16 iin_oc_warn_limit;
    Uint16 pgood_on_limit;
    Uint16 pgood_off_limit;
    Uint16 vin_on_limit;
    Uint16 vin_off_limit;
    Uint32 ton_rise;
    Uint32 vout_transition_rate;
    Uint16 dead_time_1;
    Uint16 dead_time_2;
    Uint16 dead_time_3;
    Uint16 dead_time_4;
    Uint16 sample_rate;
    Uint16 min_period;
    Uint16 max_period;
    Uint16 tsrmax;
    Uint32 ll_turn_on_thresh;
    Uint32 ll_turn_off_thresh;
    Uint8  ll_en;
    Uint16 cpcc_pmax;
    Uint16 cpcc_imax;
    Uint16	cpcc_ton;
    Uint8	cpcc_enable;
    Uint8  cpcc_time_out_en;
    Uint8	ishare_enable;
    Uint8  iout_oc_fault_response;
    Uint8  vout_uv_fault_response;
    Uint8 rsvd;
    Uint16 frequency_switch;
}PMBUS_DCDC_CONFIG; //must be even number of int16

/*----------------------------------variable----------------------------------*/
//constants.c  Flash
extern volatile const Uint32 pmbus_checksum;
// extern volatile const Uint32 pmbus_checksum_b;
extern volatile const PMBUS_DCDC_CONFIG pmbus_dcdc_config_constants[DCDC_PAGE_NUMS];
// extern volatile const PMBUS_DCDC_CONFIG pmbus_dcdc_config_constants_b[DCDC_PAGE_NUMS];
extern volatile const PMBUS_DCDC_CONFIG_NONPAGED pmbus_dcdc_config_nonpaged_constants;
// extern volatile const PMBUS_DCDC_CONFIG_NONPAGED pmbus_dcdc_config_nonpaged_constants_b;
extern volatile const PMBUS_DCDC_CAL pmbus_dcdc_cal_constants[DCDC_PAGE_NUMS];
// extern volatile const PMBUS_DCDC_CAL pmbus_dcdc_cal_constants_b[DCDC_PAGE_NUMS];
extern volatile const PMBUS_DCDC_CAL_NONPAGED pmbus_dcdc_cal_nonpaged_constants;
// extern volatile const PMBUS_DCDC_CAL_NONPAGED pmbus_dcdc_cal_nonpaged_constants_b;

//RAM
EXTERN PMBUS_DCDC_CONFIG             pmbus_dcdc_config[DCDC_PAGE_NUMS];
EXTERN PMBUS_DCDC_CONFIG             pmbus_dcdc_config_translated[DCDC_PAGE_NUMS];
EXTERN PMBUS_DCDC_CAL                pmbus_dcdc_cal[DCDC_PAGE_NUMS];

EXTERN PMBUS_DCDC_CONFIG_NONPAGED    pmbus_dcdc_config_nonpaged;
EXTERN PMBUS_DCDC_CONFIG_NONPAGED    pmbus_dcdc_config_nonpaged_translated;
EXTERN PMBUS_DCDC_CAL_NONPAGED       pmbus_dcdc_cal_nonpaged;

/*-----------------------------------macro------------------------------------*/
//first rail
#define DEFAULT_PMBUS_DCDC_1_CAL {0, 0, 0, 0, 0, 0}

#define DEFAULT_PMBUS_DCDC_CONFIG_NONPAGED \
{81, 82, 83, 84, {1 ,400 ,400 ,400 ,400 , 0, 0, 0}, 56, 36, 38,{'1','1','/','1','2','/','2','0','0','9',0,0,0,0},{'A','B','C','D'}}

#define DEFAULT_PMBUS_DCDC_CAL_NONPAGED    {0, 0}

#define VOUT_0 				(8810) // 12V * 2^MODE, MODE is 9
#define VOUT_OV_FAULT_LIMIT (8800) //(8800) //(7770) // 14V * 2^MODE, MODE is 9
#define VOUT_OV_WARN_LIMIT 	(7800)
#define VOUT_UV_FAULT_LIMIT (2400)
#define VOUT_UV_WARN_LIMIT 	(2520)
#define IOUT_OC_FAULT_LIMIT (110)
#define IOUT_OC_WARN_LIMIT 	(80) //(65)
#define TEMP_OT_FAULT_LIMIT (106)
#define TEMP_OT_WARN_LIMIT 	(90)
#define VIN_OV_FAULT_LIMIT 	(60) //
#define VIN_OV_WARN_LIMIT 	(58) //
#define VIN_UV_FAULT_LIMIT 	(23) //
#define VIN_UV_WARN_LIMIT 	(25) // //
#define IIN_OC_FAULT_LIMIT	(5) //5A
#define IIN_OC_WARN_LIMIT	(3)
#define PGOOD_ON_LIMIT		(5888)
#define PGOOD_OFF_LIMIT		(5632)
#define VIN_ON_LIMIT		(26) // Original
#define VIN_OFF_LIMIT		(23) // Original
#define TON_RISE 			(200) //50ms
#define VOUT_0_TRAN 		(1) //( 0xA58) //(0x9B33)
#define DEADTIME1			((int)(DT1 / TDPWM + 0.5))    // Multiplied by 4  //
#define DEADTIME2			((int)(DT2 / TDPWM + 0.5))
#define DEADTIME3			((int)(DT1SR / TDPWM + 0.5))   // Multiplied by 4
#define DEADTIME4			((int)(DT2SR / TDPWM + 0.5))
#define SAMPLERATE 			((int)(TSAMP / TDPWM / 16 + 0.5))
#define MINPER				((int)(TH / TDPWM / 16 + 0.5))
#define MAXPER				((int)(TL / TDPWM / 16 + 0.5))
#define TSRMAX	 			((int)((TSR - DT2SR) / TDPWM / 16 + 0.5))
#define TURN_ON_THRESHOLD	(0) //((int)(MINPER * 8 + 0.5)) //added ZCS feature
#define TURN_OFF_THRESHOLD	(0) //((int)(MINPER * 8 + 0.5)) //added ZCS feature
#define LL_ENABLE			(0)
#define CPCC_PMAX			(516) //516W
#define CPCC_IMAX			(43)  //43A
#define CPCC_TON			(8817) //Time in milli-seconds, linear 11
#define CPCC_ENABLE			(0)
#define CPCC_TIME_OUT_EN	(0)
#define ISHARE_ENABLE		(0)
#define IOUT_OC_FAULT_RESPONSE	(0)
#define VOUT_UV_FAULT_RESPONSE	(192)
#define SWITCHING_FREQUENCY (1000) //(0x3E8) //(0xFBE8)       //1MHz

//first rail default value
#define DEFAULT_PMBUS_DCDC_1_CONFIG  {\
    VOUT_0, \
    VOUT_OV_FAULT_LIMIT, \
    VOUT_OV_WARN_LIMIT, \
    VOUT_UV_FAULT_LIMIT,\
    VOUT_UV_WARN_LIMIT, \
    IOUT_OC_FAULT_LIMIT,\
    IOUT_OC_WARN_LIMIT,\
    TEMP_OT_FAULT_LIMIT,\
    TEMP_OT_WARN_LIMIT,\
    VIN_OV_FAULT_LIMIT,\
    VIN_OV_WARN_LIMIT, \
    VIN_UV_FAULT_LIMIT,\
    VIN_UV_WARN_LIMIT, \
    IIN_OC_FAULT_LIMIT,\
    IIN_OC_WARN_LIMIT,\
    PGOOD_ON_LIMIT,\
    PGOOD_OFF_LIMIT, \
    VIN_ON_LIMIT,\
    VIN_OFF_LIMIT,\
    TON_RISE, \
    VOUT_0_TRAN,\
    DEADTIME1,\
    DEADTIME2,\
    DEADTIME3,\
    DEADTIME4,\
    SAMPLERATE,\
    MINPER,\
    MAXPER,\
    TSRMAX,\
    TURN_ON_THRESHOLD,\
    TURN_OFF_THRESHOLD,\
    LL_ENABLE,\
    CPCC_PMAX,\
    CPCC_IMAX,\
    CPCC_TON,\
    CPCC_ENABLE,\
    CPCC_TIME_OUT_EN,\
    ISHARE_ENABLE,\
    IOUT_OC_FAULT_RESPONSE,\
    VOUT_UV_FAULT_RESPONSE,\
    0,\
    SWITCHING_FREQUENCY\
}


/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* PMBUS_DCDC_PARM_H */

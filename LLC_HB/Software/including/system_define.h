
#ifndef SYSTEM_DEFINE_H 
#define SYSTEM_DEFINE_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/

/*-----------------------------------macro------------------------------------*/
#define min(a,b)  (((a)>(b)) ? (b):(a))
#define max(a,b)  (((a)>(b)) ? (a):(b))
#define ENABLE (1)
#define DISABLE (0)
//=============================================================================
//                       frequency and time parameter
//=============================================================================
#define TDPWM (250e-12)					//High resolution DPWM step size
#define TSAMP (1 / (1000e3))				//EADC sample rate

#define TH (1 / (1000e3))				// 1005e3   --used  // 1500e3 PWM mode period. This is also the maximum resonant frequency (ZCS feature increased from 1500KHz)
#define TL (1 / (200e3))				//Lowest resonant mode period.
#define DT0 (35e-9)					    //Primary MOSFET dead time in ns
#define DT0SR (60e-9)					// dead time was set to SR dead time in ns          
#define TSR (0.4e-6 + DT0SR)                 //reduced by 20ns//Maximum SR on time

#define DT1 (DT0 / 2)					//Primary switches dead time from start of period to EV1
#define DT2 (DT0)						//Primary switches dead time from EV2 to EV3
#define DT3 (DT0 / 2)					//Primary switches dead time from EV4 to end of period
#define DT1SR (DT0SR / 2)				//SR switches dead time from start of period to EV1
#define DT2SR (DT0SR)					//SR switches dead time from EV2 to EV3
#define DT3SR (DT0SR / 2)				//SR switches dead time from EV4 to end of period
#define DT (DT1 + DT2 + DT3) 			//Primary switches total dead time
#define DTSR (DT1SR + DT2SR + DT3SR)	//SR switches total dead time

//=============================================================================
//                       Limit parameters
//=============================================================================
//how to get it?
#define VOUT_MODE_EXP	 (9)
#define DAC_VALUE_SCALER (931)
#define VIN_REF (380)
#define OVP_EXP (6)
#define DAC_OVP (289)
#define CBC_DISABLE_VALUE	(100)

#define MAX_FILTER_VALUE	(0x7FFFFF)
#define FILTER_CONFIG_BIN1  (0x99999999)

//=============================================================================
//                     GPIO Mask bits
//=============================================================================
#define MASK_PSON (FAULT3_GLBIO_BIT_MASK )//(1 << 29)
#define MASK_PGOOD (SYNC_GLBIO_BIT_MASK) //(1 << 8)
#define MASK_FAILURE (ADC_EXT_TRIG_GLBIO_BIT_MASK) //(1 << 28)
#define MASK_AC_FAIL (TMR_PWM1_GLBIO_BIT_MASK) //(1 << 18)
#define MASK_ORING_CTRL (FAULT1_GLBIO_BIT_MASK)

#define GLBEN_BIT_MASK_DPWM0 	(1)
#define GLBEN_BIT_MASK_DPWM1 	(1 << 1)
#define GLBEN_BIT_MASK_DPWM2 	(1 << 2)
#define GLBEN_BIT_MASK_DPWM3 	(1 << 3)
#define GLBEN_BIT_MASK_FE0 		(1 << 8)
#define GLBEN_BIT_MASK_FE1 		(1 << 9)
#define GLBEN_BIT_MASK_FE2 		(1 << 10)

//=============================================================================
//                     Dpwm
//=============================================================================
// ----------------------Intra-Mux
#define  PASS_THROUGH   (0)
#define  EDGEGEN        (1)
#define  PWMC           (2)
#define  CROSSOVER      (3)
#define  BELOW_A        (4)
#define  BELOW_B        (5)
#define  BELOW_C        (6)
#define  BELOW2_C       (7)
#define  BELOW3_C       (8)
// ----------------------Edge-Gen
#define  CURRENT_POS_A  (0)
#define  CURRENT_NEG_A  (1)
#define  CURRENT_POS_B  (2)
#define  CURRENT_NEG_B  (3)
#define  NEXT_POS_A     (4)
#define  NEXT_NEG_A     (5)
#define  NEXT_POS_B     (6)
#define  NEXT_NEG_B     (7)
// ----------------------PWM modes
#define  NORMAL         (0)
#define  RESONANT       (1)
#define  MULTI          (2)
//=============================================================================
//                     DecRegs Mask bits
//=============================================================================
#define MFBALR2_HALF0_DATA_FLASH_BASE_ADDRESS (0x9800)
#define MFBALRX_BYTE0_BLOCK_SIZE_2K     	  (0x20) 		
#define MFBALRX_BYTE0_RONLY					  (0x02)		   //Read-only protection
#define MFBALRX_BYTE0_BLOCK_SIZE_32K    	  (0x60)

//=============================================================================
//                     pmbus_write_filter_select states
//=============================================================================
#define FILTER_VOLTAGE_LOOP_START_UP	 	(0)
#define FILTER_VOLTAGE_LOOP_STEADY_STATE 	(1)
#define FILTER_VOLTAGE_LOOP_CONSTANT_POWER	(2)
#define FILTER_CURRENT_LOOP_STEADY_STATE 	(3)

//=============================================================================
//                     Flash Error codes
//=============================================================================
#define FLASH_SUCCESS 				(0)
#define FLASH_INVALID_SEGMENT 		(1)
#define	FLASH_INVALID_ADDRESS		(2)
#define	FLASH_MISCOMPARE			(3)


/*----------------------------------pmbus----------------------------------*/
#define NULL					(0)
#define NUMBER_OF_FAULTY_TRIALS (5) // Number of time wrog password may be entered


#define PSON (1) //((MiscAnalogRegs.GLBIOREAD.all & (CONTROL_GLBIO_BIT_MASK | MASK_PSON)) && enable_turn_on)
#define TON_RISE_EXP (1)


//=============================================================================
//                     Fault mask
//=============================================================================
#define DCOMP0_INT_STATUS_MASK 	(1 << 13)
#define DCOMP1_INT_STATUS_MASK 	(1 << 14)
#define DCOMP2_INT_STATUS_MASK 	(1 << 15)
#define DCOMP3_INT_STATUS_MASK 	(1 << 16)

#define ACOMPA_INT_STATUS_MASK 	(0x01)
#define ACOMPB_INT_STATUS_MASK 	(0x02)
#define ACOMPC_INT_STATUS_MASK 	(0x04)
#define ACOMPD_INT_STATUS_MASK 	(0x08)
#define ACOMPE_INT_STATUS_MASK 	(0x10)
#define ACOMPF_INT_STATUS_MASK 	(0x20)
#define ACOMPG_INT_STATUS_MASK 	(0x40)

#define COMP_INT_STATUS_MASK	(ACOMPB_INT_STATUS_MASK | ACOMPE_INT_STATUS_MASK)
#define OVER_VOLTAGE_FAULT 		(ACOMPB_INT_STATUS_MASK & fiq_data.fault_status)
#define OVER_CURRENT_PEAK_FAULT	(ACOMPF_INT_STATUS_MASK & fiq_data.fault_status)
#define UV_SEC_FAULT  (ACOMPC_INT_STATUS_MASK & fiq_data.fault_status)
#define OVER_CURRENT_SEC_FAULT  (ACOMPE_INT_STATUS_MASK & fiq_data.fault_status)

#define CS_INT_MAN (1)
#define KI_STALL_MASK (1 << 6)
#define KD_STALL_MASK (1 << 7)
#define DPWM_FAULT_AB_STATUS_MASK (0x2)

//=============================================================================
//                     Fault and Warn
//=============================================================================
#define qnote_int16_multiply_fit(x_qnote, var_int16, max_value) qnote_linear16_multiply_fit(x_qnote, var_int16, 0, max_value)

#define ABOVE_VIN_ON_LIMIT  (adc_values.vin_mon > pmbus_dcdc_config_translated[0].vin_on_limit) // (1)
#define BELOW_VIN_OFF_LIMIT (adc_values.vin_mon < pmbus_dcdc_config_translated[0].vin_off_limit) // (0)

#define OVOUT_WARN 	 (adc_values.vo_sense  > pmbus_dcdc_config_translated[0].vout_ov_warn_limit)
#define UVOUT_WARN 	 (adc_values.vo_sense  < pmbus_dcdc_config_translated[0].vout_uv_warn_limit)
#define OCOUT_WARN 	 (adc_values_avg.io_sense  > pmbus_dcdc_config_translated[0].iout_oc_warn_limit)
#define OCIN_WARN 	 (adc_values_avg.ips 	   > pmbus_dcdc_config_translated[0].iin_oc_warn_limit)
#define OT_WARN 	 (adc_values_avg.pri_temp 	   < pmbus_dcdc_config_translated[0].temp_ot_warn_limit)
#define OVVIN_WARN 	 (adc_values_avg.vin_mon   > pmbus_dcdc_config_translated[0].vin_ov_warn_limit)
#define UVVIN_WARN 	 (adc_values_avg.vin_mon   < pmbus_dcdc_config_translated[0].vin_uv_warn_limit)

#define UVOUT_FAULT  ((adc_values.vo_sense  < pmbus_dcdc_config_translated[0].vout_uv_fault_limit) && (supply_state == STATE_REGULATED)) //(0) //
#define OT_FAULT_PRI  (adc_values.pri_temp > pmbus_dcdc_config_translated[0].temp_ot_fault_limit) // (0) //
#define OVVIN_FAULT  (adc_values.vin_mon   > pmbus_dcdc_config_translated[0].vin_ov_fault_limit) // (0) //
#define UVVIN_FAULT  ((adc_values.vin_mon   < pmbus_dcdc_config_translated[0].vin_uv_fault_limit) && (supply_state == STATE_REGULATED)) // (0) //
#define OT_FAULT_SEC     (adc_values.sec_temp > (pmbus_dcdc_config_translated[0].temp_ot_fault_limit + 30)) //

#define OT_FAULT_PRI_RESTART     (adc_values.pri_temp < (pmbus_dcdc_config_translated[0].temp_ot_fault_limit -100)) // (0) //
#define OT_FAULT_SEC_RESTART     (adc_values.sec_temp < (pmbus_dcdc_config_translated[0].temp_ot_fault_limit -100))   //

#define OC_SHUTDOWN_SLOW (adc_values.io_sense > 70)


#define PGOOD_ON     (adc_values_avg.vo_sense  > pmbus_dcdc_config_translated[0].pgood_on_limit)
#define PGOOD_OFF    (adc_values_avg.vo_sense  < pmbus_dcdc_config_translated[0].pgood_off_limit)



//=============================================================================
//                     SCALER
//=============================================================================
#define ADC12_VOUT_SCALER_MANTISSA  (19065)
#define	ADC12_VOUT_SCALER_EXPONENT  (-7)

#define ADC12_VOUT_TO_LITERAL_SCALER_MANTISSA  (28180)   //3.4375 is translated from 1 ADC LSB X Volt x Vout_Loop_Scaler * 512/512 is 2^(VOUT_MODE_EXP)
#define ADC12_VOUT_TO_LITERAL_SCALER_EXPONENT  (-13)

#define ADC12_IOUT_SCALER_MANTISSA  (19965)
#define ADC12_IOUT_SCALER_EXPONENT  (-10)
#define ADC12_IIN_SCALER_MANTISSA   (32716)
#define ADC12_IIN_SCALER_EXPONENT   (-6)

#define ADC12_VIN_TO_LITERAL_SCALER_MANTISSA   (21045) //(25469) //(26844)
#define ADC12_VIN_TO_LITERAL_SCALER_EXPONENT   (-20)

#define ADC12_VIN_SCALER_MANTISSA   (25469) //(26844)
#define ADC12_VIN_SCALER_EXPONENT   (-9)

#define ADC12_TEMP_SCALER_MANTISSA  (4857) //(17000) //(8843) //(19623)
#define ADC12_TEMP_SCALER_EXPONENT  (-9)
#define ADC12_TEMP_OFFSET 			(3058)


#define AVERAGE_Vout_SHIFT (11)
#define AVERAGE_IOUT_SHIFT (11)

#define FILTER_RAMP_STEP (5000)//(10000)
#define SWITCHING_PERIOD_KI  (0x2FFFFF) //(0x1AC73A) for 1MH//(0x1BA000) for 940kHz ////(0x195000) for 1.05MH //1MHz switching frequency

#define SWITCHING_PERIOD_YN_CLAMP  (0x197B70)
#define PID_PERIOD_FACTOR   (418)

#define MAX_VALUE_FIT_5_BITS  (0x0001F)
#define MAX_VALUE_FIT_6_BITS  (0x0003F)
#define MAX_VALUE_FIT_7_BITS  (0x0007F)
#define MAX_VALUE_FIT_8_BITS  (0x000FF)
#define MAX_VALUE_FIT_9_BITS  (0x001FF)
#define MAX_VALUE_FIT_10_BITS (0x003FF)
#define MAX_VALUE_FIT_11_BITS (0x007FF)
#define MAX_VALUE_FIT_12_BITS (0x00FFF)
#define MAX_VALUE_FIT_13_BITS (0x01FFF)
#define MAX_VALUE_FIT_14_BITS (0x03FFF)
#define MAX_VALUE_FIT_15_BITS (0x07FFF)
#define MAX_VALUE_FIT_16_BITS (0x0FFFF)
#define MAX_VALUE_FIT_17_BITS (0x1FFFF)
#define MAX_VALUE_FIT_18_BITS (0x3FFFF)
#define MAX_VALUE_FIT_19_BITS (0x7FFFF)
#define MAX_VALUE_FIT_20_BITS (0xFFFFF)

#ifdef __cplusplus
}
#endif

#endif	/* SYSTEM_DEFINE_H */

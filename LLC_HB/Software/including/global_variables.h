
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

/*----------------------------------typedef-----------------------------------*/
typedef void (*FUNC_PTR)(); 	//used for zeroing instruction word.

//ADC data
typedef struct{
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

typedef struct{
	Uint16 burst_mode_i_turn_on;
	Uint16 burst_mode_i_turn_off;
	int16 burst_mode_v_hys;
	Uint32 burst_mode_int_jam_value;
	Uint8 burst_mode_en;  //ZCS feature
	Uint8 burst_on;   //ZCS feature
	int32 vloop_filter;
	int32 iloop_filter;
	Uint8 cbc_enabled;
	Uint8 cc_detected;
	Uint8 cbc_detected;
	Uint32 cbc_current_loop_integrator_jam_value;
	Uint32 cbc_voltage_loop_integrator_jam_value;
	Uint32 dpwm_status;
	Uint32 fault_status;
	Uint32 fault_status_raw;
	Uint8 ll_en;
	Uint8 cpcc_en;
	Uint8 cbc_counter;
	Uint8 cbc_max;
} FIQ_DATA;

//Interrupt state
typedef enum{
	STATE_IDLE,
	STATE_CHECK_RAMP_UP,
	STATE_WAIT_DRIVEON,
	STATE_HIGH_CURRENT_DURING_RAMP_UP,
	STATE_BOUNCE_TO_RAMP_UP_AFTER_WAITING,
	STATE_RAMP_UP,		
	STATE_RAMP_DOWN,	
	STATE_REGULATED,	
	STATE_LIGHT_LOAD,	
	STATE_CPCC,	
	STATE_FAULT,
	STATE_HICCUP,
	STATE_VOUT_TRANSITION,
	NONE
} SUPPLY_STATE;

struct PFC_OUT_STRUCT{
	unsigned char pfc_status0;
    unsigned char pfc_status1;
    unsigned int  pfc_vac;
    unsigned int  pfc_iac;
    unsigned int  pfc_pin;
	unsigned int  pfc_pout;
    unsigned int  pfc_vdc_bus;
    unsigned int  pfc_sw_frequency;
    unsigned char pfc_temperature;
};

struct qnote{
  int16 mantissa;
  int16 exponent;
};

/*----------------------------------variable----------------------------------*/
EXTERN ADC_VALUES_STRUCT adc_values; 	//ADC Readings
EXTERN ADC_VALUES_STRUCT adc_values_avg;//ADC Readings Averaged
EXTERN FIQ_DATA fiq_data; 
EXTERN SUPPLY_STATE supply_state;//Supply state enum for state machine

//=============================================================================
//                     start interrupt
//=============================================================================
EXTERN Uint32 start_up_delay_over;
EXTERN Uint32 count;
EXTERN Uint32 count_end;

EXTERN Uint32 delay_counter;

EXTERN Uint32 max_period;
EXTERN Uint32 min_period;
EXTERN Uint32 updated_period_target;
EXTERN Uint32 temperory_period;
EXTERN Uint32 default_period;
EXTERN Uint32 period_change_enable;
EXTERN Uint32 min_mode_switching;
EXTERN Uint32 default_mode_switching;
EXTERN Uint32 delay_counter;

//=============================================================================
//                   fault handler
//=============================================================================
EXTERN volatile Uint32 FAULTMUXINTSTAT_value;

EXTERN int32 shut_down_fault_detected;
EXTERN Uint32 firmware_error_flag;
EXTERN Uint32 uv_latch_flag;
EXTERN Uint32 ov_latch_flag;
EXTERN Uint32 oc_latch_flag;
EXTERN Uint32 oc_fault_limit;
EXTERN Uint32 restart_counter;
EXTERN Uint32 retry_enable;
EXTERN Uint32 oc_counter;

//=============================================================================
//                   pmbus handler
//=============================================================================
EXTERN Uint16 period;

EXTERN Uint8 filter_select;
EXTERN Uint8 filter_activate;
EXTERN Uint64 p_out;

EXTERN Uint8 erase_segment_counter;	// Number of DFlash segment remaining to be erased
EXTERN Uint8 erase_segment_number;		// DFlash segment number being erased
EXTERN Uint8 flash_write_status;	// Global status while attempting to write to Data Flash.


EXTERN struct qnote temp_qnote1;
EXTERN struct qnote temp_qnote_scale1;
EXTERN struct qnote adc12_vin_scaler;
EXTERN int16 temp_qnote_value1;

EXTERN int32 temp_debug_buffer;

//=============================================================================
//                              uart and pfc
//=============================================================================
#define UART_RX_SIZE (10) //total number of bytes for received data packet
#define UART_TX_SIZE (10) //total number of bytes for transmitted data packet

EXTERN Uint8 uart_text_rx_buf[UART_RX_SIZE*2 + 2]; //UART receive buffer in text mode
EXTERN Uint8 uart_text_tx_buf[UART_TX_SIZE*2 + 2]; //UART transmit buffer in text mode
EXTERN Uint8 uart_rx_buf[UART_RX_SIZE]; //UART receive buffer
EXTERN Uint8 uart_tx_buf[UART_TX_SIZE]; //UART transmit buffer
EXTERN Uint8 uart_rx_data_rdy; //flag, received a new data packet
EXTERN Uint8 uart_tx_data_rdy; //flag, a new data packet is ready for transmit
EXTERN Uint8 uart_rx_buf_ptr; //point to the buffer which will store the coming byte
EXTERN Uint8 uart_tx_buf_ptr; //point to buffer whose data is going to be sent out 
EXTERN Uint16 uart_rx_timeout; //count IRQ, UART receiver will start over when timeout
EXTERN Uint16 uart_tx_timeout; //count IRQ, UART needs to wait for a certain period before send the next data packet

EXTERN struct PFC_OUT_STRUCT pfc_out_struct;

EXTERN Uint8 pfc_command;//for APEC demo
EXTERN Uint8 pfc_phase_2_enable;//for APEC demo
EXTERN Uint8 pfc_zvs_enable;//for APEC demo
EXTERN Uint8 pfc_os_enable;//for APEC demo
EXTERN Uint8 llc_sr_enable;//for APEC demo
EXTERN Uint8 previous_llc_sr_command;
/*----------------------------------variable----------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* GLOBAL_VARIABLES_H */

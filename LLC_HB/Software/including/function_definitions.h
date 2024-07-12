
#ifndef FUNCTION_DEFINITIONS_H 
#define FUNCTION_DEFINITIONS_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "pmbus_dcdc_parm.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
//=============================================================================
//                                    DPP
//=============================================================================
/*------------------------------------dpwm-----------------------------------*/
void init_dpwms(void);
void init_dpwm0(void);
void init_dpwm1(void);
void init_dpwm2(void);
void init_dpwm3(void);
void configure_dpwm_timing(PMBUS_DCDC_CONFIG *dpwm_timings);
void init_sample_trigger(void);
/*------------------------------------filter---------------------------------*/
void init_filter0(void);
void init_filter0_states(void);
/*---------------------------------front end---------------------------------*/
void init_front_end0(void);
/*------------------------------------gpio-----------------------------------*/
void init_gpio(void);
void gpio_sr_on(void);
void gpio_sr_off(void);
void gpio_dpwm_on(void);
void gpio_dpwm_off(void);
/*----------------------------------loop mux---------------------------------*/
void init_loop_mux(void);
void global_enable(void);
void global_disable(void);
void init_DTC(void);

//=============================================================================
//                                    ADC & Fault
//=============================================================================
void init_adc12(void);
void poll_adc(void);

void init_uvp(void);
void init_ovp(void);
void init_sec_ocp(void);
void init_ipri_cycle_by_cycle(void);

//=============================================================================
//                                    Flash
//=============================================================================
void look_for_interrupted_dflash_erase(void);
Uint8 update_data_flash(void* dest_ptr, const void* src_ptr, Uint16 byte_count);
Uint8 start_erase_task(const void* dest_ptr, Uint16 byte_count);
void erase_task(void);
Uint32 calculate_dflash_checksum(Uint8 *start_addr, Uint8 *end_addr);
inline Uint8 calc_flash_segments(const void* dest_ptr, Uint16 byte_count, Uint8* first_segment);
void erase_one_section(int first_segment, int byte_count);
void restore_default_all(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* FUNCTION_DEFINITIONS_H */

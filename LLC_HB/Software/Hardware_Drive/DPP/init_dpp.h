#ifndef INIT_DPP_H 
#define INIT_DPP_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "pmbus.h"
/*-----------------------------------macro------------------------------------*/
/*-----------------------------------Dpwms------------------------------------*/
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

#define PID_PERIOD_FACTOR   (418)

#define TDPWM (250e-12)	
#define TH (1 / (1000e3))	
#define MINPER				((int)(TH / TDPWM / 16 + 0.5))
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void init_dpwms(void);
void init_dpwm0(void);
void init_dpwm1(void);
void init_dpwm2(void);
void init_dpwm3(void);
void configure_dpwm_timing(PMBUS_DCDC_CONFIG *dpwm_timings);
void init_sample_trigger(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* INIT_DPP_H */

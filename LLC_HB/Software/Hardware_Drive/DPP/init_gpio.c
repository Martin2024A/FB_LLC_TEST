
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
/*-----------------------------------macro------------------------------------*/
#define MASK_PGOOD (SYNC_GLBIO_BIT_MASK) //(1<<8)
#define MASK_FAILURE (ADC_EXT_TRIG_GLBIO_BIT_MASK) //(1<<28)
#define MASK_AC_FAIL (TMR_PWM1_GLBIO_BIT_MASK) //(1<<18)
#define MASK_ORING_CTRL (FAULT1_GLBIO_BIT_MASK) //(1<<10)
#define MASK_TMS (TMS_GLBIO_BIT_MASK) //(1<<25)
#define MASK_PSON (FAULT3_GLBIO_BIT_MASK )//(1 << 29)
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/
void init_gpio(void);
void gpio_sr_on(void);
void gpio_sr_off(void);
void gpio_dpwm_on(void);
void gpio_dpwm_off(void);
/*----------------------------------function----------------------------------*/
void init_gpio(void)
{
    MiscAnalogRegs.GLBIOVAL.all = 0;//Set outputs to 0

    // 0 - Indicates that control is done by the default peripherial.
    // 1 - Indicates that control is governed by the GPIO module.
    MiscAnalogRegs.GLBIOEN.all = MASK_PGOOD | MASK_FAILURE | MASK_AC_FAIL | MASK_ORING_CTRL |
                                 MASK_TMS | MASK_PSON |
                                 TDI_GLBIO_BIT_MASK | CONTROL_GLBIO_BIT_MASK;

    // 1 - Output, 0 - Input
    MiscAnalogRegs.GLBIOOE.all = MASK_PGOOD | MASK_FAILURE | MASK_AC_FAIL | MASK_ORING_CTRL |
                                 MASK_TMS | 
								 DPWM0A_GLBIO_BIT_MASK | DPWM0B_GLBIO_BIT_MASK |
								 DPWM1A_GLBIO_BIT_MASK | DPWM1B_GLBIO_BIT_MASK | 
								 DPWM2A_GLBIO_BIT_MASK | DPWM2B_GLBIO_BIT_MASK | 
								 DPWM3A_GLBIO_BIT_MASK | DPWM3B_GLBIO_BIT_MASK;

    //Setting this to 1 disables the external oring control. The Oring MOSFET will always be off.
	//Set it to 0 and diode oring will operate normally.
	MiscAnalogRegs.GLBIOVAL.bit.FAULT1_IO_VALUE = 0;
	MiscAnalogRegs.GLBIOVAL.bit.DPWM2A_IO_VALUE = 0;
	MiscAnalogRegs.GLBIOVAL.bit.DPWM2B_IO_VALUE = 0;
	MiscAnalogRegs.GLBIOVAL.bit.DPWM3A_IO_VALUE = 0; //ZCS feature to enable DTC in UCD7138.
	MiscAnalogRegs.GLBIOVAL.bit.DPWM3B_IO_VALUE = 0; //ZCS feature
}

void gpio_sr_on(void)
{
    MiscAnalogRegs.GLBIOEN.all &= ~((Uint32)(DPWM1A_GLBIO_BIT_MASK | DPWM1B_GLBIO_BIT_MASK));
}

void gpio_sr_off(void)
{
	MiscAnalogRegs.GLBIOEN.all |=  ((Uint32)(DPWM1A_GLBIO_BIT_MASK | DPWM1B_GLBIO_BIT_MASK));
}

void gpio_dpwm_on(void)
{
	//Following Change made by ZCS feature so that SRs are not enabled on a subsequent PSON 
    //if llc_sr_enable=DISABLE. handle_idle_state() calls this for Ramp Up
	MiscAnalogRegs.GLBIOEN.all &= ~((Uint32)(DPWM0A_GLBIO_BIT_MASK | DPWM0B_GLBIO_BIT_MASK |
                                            DPWM1A_GLBIO_BIT_MASK | DPWM1B_GLBIO_BIT_MASK |
                                            DPWM2A_GLBIO_BIT_MASK | DPWM2B_GLBIO_BIT_MASK |
                                            DPWM3A_GLBIO_BIT_MASK | DPWM3B_GLBIO_BIT_MASK ));
    //(DPWM1A_GLBIO_BIT_MASK & (llc_sr_enable << 2))  |(DPWM1B_GLBIO_BIT_MASK & (llc_sr_enable << 3))));
}

void gpio_dpwm_off(void)
{
	MiscAnalogRegs.GLBIOEN.all |=  ((Uint32)(DPWM0A_GLBIO_BIT_MASK | DPWM0B_GLBIO_BIT_MASK |DPWM2A_GLBIO_BIT_MASK | DPWM2B_GLBIO_BIT_MASK |
								 		     DPWM1A_GLBIO_BIT_MASK | DPWM1B_GLBIO_BIT_MASK | DPWM3A_GLBIO_BIT_MASK | DPWM3B_GLBIO_BIT_MASK));
}
/*------------------------------------test------------------------------------*/


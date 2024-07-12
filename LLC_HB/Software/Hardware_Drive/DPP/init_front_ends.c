
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/
void init_front_end0(void);

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/
void init_front_end0(void)
{
    FeCtrl0Regs.EADCDAC.bit.DAC_VALUE = 0;
    FeCtrl0Regs.EADCCTRL.bit.AFE_GAIN = 3;
    FeCtrl0Regs.EADCCTRL.bit.SCFE_CLK_DIV_2 = 0;
    FeCtrl0Regs.EADCCTRL.bit.EADC_MODE = 0;//Standard mode 

	// FeCtrl0Regs.EADCCTRL.bit.AVG_MODE_SEL = 2;//Averaging config 0 - 2x, 1 - 4x, 2 - 8x
	// FeCtrl0Regs.EADCCTRL.bit.AVG_SPATIAL_EN = 1;//Sample triggers are configured by the DPWM

	// Configure soft start ramp
	FeCtrl0Regs.RAMPCYCLE.bit.DELAY_CYCLES = 0;
	FeCtrl0Regs.RAMPCYCLE.bit.SWITCH_CYC_PER_STEP = 0;
	FeCtrl0Regs.RAMPCTRL.bit.RAMP_SAT_EN = 0;
	FeCtrl0Regs.RAMPCTRL.bit.RAMP_EN = 1;
}



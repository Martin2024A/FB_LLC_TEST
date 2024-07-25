
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "function_definitions.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/
void init_front_end0(void)
{
    FeCtrl0Regs.EADCDAC.bit.DAC_VALUE = 0;
    FeCtrl0Regs.EADCCTRL.bit.AFE_GAIN = 3;
    FeCtrl0Regs.EADCCTRL.bit.SCFE_CLK_DIV_2 = 0;
    FeCtrl0Regs.EADCCTRL.bit.EADC_MODE = 0;//Standard mode 

	// Configure soft start ramp
	FeCtrl0Regs.RAMPCYCLE.bit.DELAY_CYCLES = 0;
	FeCtrl0Regs.RAMPCYCLE.bit.SWITCH_CYC_PER_STEP = 0;
	FeCtrl0Regs.RAMPCTRL.bit.RAMP_SAT_EN = 0;
	FeCtrl0Regs.RAMPCTRL.bit.RAMP_EN = 1;
}



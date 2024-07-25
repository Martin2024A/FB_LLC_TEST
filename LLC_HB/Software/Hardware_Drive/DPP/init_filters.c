
/*----------------------------------include-----------------------------------*/
#include "system_define.h"
#include "pmbus_filter_parm.h"
#include "pmbus_dcdc_parm.h"

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void init_filter0(void)
{
    Filter0Regs.FILTERCTRL.bit.FILTER_EN = 1;
	//Input to filter for DUTY max comes from DPWM
    Filter0Regs.FILTERCTRL.bit.OUTPUT_MULT_SEL = 3;//Use Resonant DUTY
	//Selects source of switching cycle period for Filter 0 Module
	//maybe not used it,to delete it,because OUTPUT_MULT_SEL = 3
	LoopMuxRegs.FILTERMUX.bit.FILTER0_PER_SEL = 0;
	Dpwm0Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;
	Dpwm1Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;
	Dpwm2Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;
	Dpwm3Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;

	Filter0Regs.FILTERCTRL.bit.PERIOD_MULT_SEL = 1; // Use KCOM
  	LoopMuxRegs.FILTERMUX.bit.FILTER0_KCOMP_SEL = 0;

	Filter0Regs.FILTERCTRL.bit.OUTPUT_SCALE = -1;
    Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 0; //default

    copy_coefficients_to_filter(&Filter0Regs, &filter0_pmbus_regs);
	//config_timing后 再copy_coefficients,参数被覆盖
	//后续重新调用config_timing
	// update the YN clamp
	Filter0Regs.FILTERYNCLPHI.all = ((int32)((pmbus_dcdc_config[0].min_period  << 4)* PID_PERIOD_FACTOR * 1026)) >> 10;
}


void init_filter0_states(void)
{
    LoopMuxRegs.SAMPTRIGCTRL.bit.FE0_TRIG_DPWM0_EN = 0;
    Filter0Regs.FILTERCTRL.bit.FILTER_EN = 0;
    //Jam XN_M1 to 0
    Filter0Regs.FILTERPRESET.bit.PRESET_REG_SEL = 0; 
	Filter0Regs.FILTERPRESET.bit.PRESET_VALUE = 0;
	Filter0Regs.FILTERPRESET.bit.PRESET_EN = 1;
	//PRESET KI_YN to 0
	Filter0Regs.FILTERPRESET.bit.PRESET_REG_SEL = 1; 
	Filter0Regs.FILTERPRESET.bit.PRESET_VALUE = 0;
	Filter0Regs.FILTERPRESET.bit.PRESET_EN = 1;
	//PRESET KD_YN to 0
	Filter0Regs.FILTERPRESET.bit.PRESET_REG_SEL = 2; 
	Filter0Regs.FILTERPRESET.bit.PRESET_VALUE = 0;
	Filter0Regs.FILTERPRESET.bit.PRESET_EN = 1;
	//PRESET YN to 0
	Filter0Regs.FILTERPRESET.bit.PRESET_REG_SEL = 3; 
	Filter0Regs.FILTERPRESET.bit.PRESET_VALUE = 0;
	Filter0Regs.FILTERPRESET.bit.PRESET_EN = 1;
	//PRESET 18 bit filter duty register (after multiplication) to 0
	Filter0Regs.FILTERPRESET.bit.PRESET_REG_SEL = 4; 
	Filter0Regs.FILTERPRESET.bit.PRESET_VALUE = 0;
	Filter0Regs.FILTERPRESET.bit.PRESET_EN = 1;

    //Preset 
    Filter0Regs.CPUXN.all = 0;
    Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 1;
	Filter0Regs.FILTERCTRL.bit.FILTER_EN = 1;

	Filter0Regs.FILTERCTRL.bit.FORCE_START = 1;
	Filter0Regs.FILTERCTRL.bit.FORCE_START = 0;
    Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 0;

    LoopMuxRegs.SAMPTRIGCTRL.bit.FE0_TRIG_DPWM0_EN = 1;
}

void copy_coefficients_to_filter(volatile struct FILTER_REGS *dest, const FILTER_PMBUS_REGS *source)
{
	dest->COEFCONFIG.all    	 = source->COEFCONFIG.all;
	dest->FILTERKPCOEF0.all 	 = source->FILTERKPCOEF0.all;
	dest->FILTERKPCOEF1.all 	 = source->FILTERKPCOEF1.all;
	dest->FILTERKICOEF0.all 	 = source->FILTERKICOEF0.all;
	dest->FILTERKICOEF1.all 	 = source->FILTERKICOEF1.all;
	dest->FILTERKDCOEF0.all 	 = source->FILTERKDCOEF0.all;
	dest->FILTERKDCOEF1.all  	 = source->FILTERKDCOEF1.all;
	dest->FILTERKDALPHA.all 	 = source->FILTERKDALPHA.all;
	dest->FILTERNL0.all     	 = source->FILTERNL0.all;
	dest->FILTERNL1.all     	 = source->FILTERNL1.all;
	dest->FILTERNL2.all     	 = source->FILTERNL2.all;
	dest->FILTERKICLPHI.all 	 = source->FILTERKICLPHI.all;
	dest->FILTERKICLPLO.all 	 = source->FILTERKICLPLO.all;
	dest->FILTERYNCLPHI.all 	 = source->FILTERYNCLPHI.all;
	dest->FILTERYNCLPLO.all 	 = source->FILTERYNCLPLO.all;
	dest->FILTEROCLPHI.all		 = source->FILTEROCLPHI.all;
	dest->FILTEROCLPLO.all		 = source->FILTEROCLPLO.all;
	dest->FILTERCTRL.bit.NL_MODE = source->FILTER_MISC.bit.NL_MODE;

	if(source == &filter1_pmbus_regs)
	{
		FeCtrl1Regs.EADCCTRL.bit.AFE_GAIN = source->FILTER_MISC.bit.AFE_GAIN;
	}
	else
	{
		FeCtrl0Regs.EADCCTRL.bit.AFE_GAIN = source->FILTER_MISC.bit.AFE_GAIN;
	}
}
/*------------------------------------test------------------------------------*/

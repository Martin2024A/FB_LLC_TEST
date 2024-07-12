
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "function_definitions.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void init_filter0(void)
{
    Filter0Regs.FILTERCTRL.bit.FILTER_EN = 1;
 
    Filter0Regs.FILTERCTRL.bit.OUTPUT_MULT_SEL = 3;//Input to filter for DUTY max comes from DPWM
    Filter0Regs.FILTERCTRL.bit.PERIOD_MULT_SEL = 1;//Input to filter for PERIOD max comes from LOOP MUX (KCOMP)
    Filter0Regs.FILTERCTRL.bit.OUTPUT_SCALE = -1;
    Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 0; //default

    //filter ????
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
/*------------------------------------test------------------------------------*/

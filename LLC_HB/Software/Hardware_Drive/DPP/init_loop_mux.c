
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "system_define.h"
#include "function_definitions.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void init_loop_mux(void)
{
    LoopMuxRegs.DPWMMUX.bit.DPWM0_FILTER_SEL = 0;//Connect FILTER-0 to DPWM-0
    LoopMuxRegs.DPWMMUX.bit.DPWM1_FILTER_SEL = 0;
    LoopMuxRegs.DPWMMUX.bit.DPWM2_FILTER_SEL = 0;
    LoopMuxRegs.DPWMMUX.bit.DPWM3_FILTER_SEL = 0;

    LoopMuxRegs.FILTERMUX.bit.FILTER0_FE_SEL = 0;//Connect filter0 to front end 0
    
    LoopMuxRegs.FECTRL0MUX.bit.DPWM3_FRAME_SYNC_EN  = 1;
    //轻载设置_没使用
    LoopMuxRegs.LLCTRL.bit.LL_FILTER_SEL = 0;
    LoopMuxRegs.LLCTRL.bit.DPWM_ON_TIME = 0;
    LoopMuxRegs.LLCTRL.bit.CYCLE_CNT_EN = 0;
    LoopMuxRegs.LLENTHRESH.bit.CYCLE_CNT_THRESH = 0;
    LoopMuxRegs.LLCTRL.bit.LL_EN =1;
    //DAC VALUE
}


void global_enable(void)
{
	//Enable DPWM0, DPWM1, FE_CTRL0 AND FE_CTRL1 simultaneously. ZCS feature adds in FE2
	LoopMuxRegs.GLBEN.all = GLBEN_BIT_MASK_FE0 	 | GLBEN_BIT_MASK_FE1 | GLBEN_BIT_MASK_FE2 |
							GLBEN_BIT_MASK_DPWM0 | GLBEN_BIT_MASK_DPWM1 | 
							GLBEN_BIT_MASK_DPWM2 | GLBEN_BIT_MASK_DPWM3;
}

void global_disable(void)
{
	//Disable DPWM0, DPMW1 simultaneously. ZCS feature adds in FE2 and DPWM2 (test output for ZCS occurrence) and corrects error.
		//LoopMuxRegs.GLBEN.all = GLBEN_BIT_MASK_FE0 	 | GLBEN_BIT_MASK_FE1 | GLBEN_BIT_MASK_FE2 | GLBEN_BIT_MASK_DPWM2;
		//ZCS feature rewrites as
		LoopMuxRegs.GLBEN.all &= ~(GLBEN_BIT_MASK_FE0 	 | GLBEN_BIT_MASK_FE1 | GLBEN_BIT_MASK_FE2 | GLBEN_BIT_MASK_DPWM2);
}

//DTC 还没看
//Advandanced Dead Time Compensation (DTC) module initialization
void init_DTC(void)
{
	//Enable DTC interrupt
	LoopMuxRegs.DTCCTRL.bit.FLT_INT_EN = 1;
	//Set the number of consecutive detected faults before a fault step is utilized
	LoopMuxRegs.DTCCTRL.bit.FLT_MAX_CNT = 3;
	//Set the fault step size to be -10*4ns
	LoopMuxRegs.DTCCTRL.bit.FLT_STEP = 2;
	//Set the fault threshold to be 3*4ns
	LoopMuxRegs.DTCCTRL.bit.FLT_THRESH = 2;
	//Select DPWM1B falling edge as reference by DTC Phase A (ACNT)
	LoopMuxRegs.DTCCTRL.bit.PWM_A_SEL = 6;
	//Select DPWM1A falling edge as reference by DTC Phase B (BCNT)
	LoopMuxRegs.DTCCTRL.bit.PWM_B_SEL = 2;
	//Set the signal polarity of DCT pin to be active low
	LoopMuxRegs.DTCCTRL.bit.A_POL = 0;
	LoopMuxRegs.DTCCTRL.bit.B_POL = 0;
	//Phase A and Phase B operates on separate inputs
	LoopMuxRegs.DTCCTRL.bit.INPUT_MODE = 0;
	//Automatic control mode
	LoopMuxRegs.DTCCTRL.bit.MODE = 1; //1- Manual control mode; 0- Automatic control mode
	//Enable DTC module
	LoopMuxRegs.DTCCTRL.bit.DTC_EN = 1;

	//Set body diode conduction time detection window blanking time
	LoopMuxRegs.DTCTARGET.bit.DETECT_BLANK = 8;
	//Set body diode conduction time detection window length
	LoopMuxRegs.DTCTARGET.bit.DETECT_LEN = 80;
	//Set DTC control target offset. Target offset + target low = target high
	LoopMuxRegs.DTCTARGET.bit.TARGET_OFFSET = 2;
	//Set DTC control target low
	LoopMuxRegs.DTCTARGET.bit.TARGET_LOW = 4; //1/250MHz *5 = 20nS

	//Set maximum accumulator clamp
	LoopMuxRegs.DTCLIMIT.bit.ADJ_MAX = 4; //8;
	//Set minimum accumulator clamp
	LoopMuxRegs.DTCLIMIT.bit.ADJ_MIN = -20; //-30;

	LoopMuxRegs.DTCMANUAL.bit.A_ADJ = -6; // make the same pulse width
	LoopMuxRegs.DTCMANUAL.bit.B_ADJ = -1; //

	//Initialize IOMUX
	//DTC Phase A input from TDI pin
	MiscAnalogRegs.IOMUX.bit.DTC_A_SEL = 0;
	//DTC Phase B input from TDO pin
	MiscAnalogRegs.IOMUX.bit.DTC_B_SEL = 0;

	//Initialize DTC registers in DPWM module
	//Only DTC phase adjust B utilized in edge adjustments
	Dpwm1Regs.DPWMCTRL2.bit.DTC_MODE = 2;
	//Enable DTC in DPWM module
	Dpwm1Regs.DPWMCTRL2.bit.DTC_EN = 1;
}
/*------------------------------------test------------------------------------*/

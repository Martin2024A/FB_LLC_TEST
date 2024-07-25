
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "function_definitions.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void init_uvp(void)
{
    FaultMuxRegs.ACOMPCTRL1.bit.ACOMP_C_SEL = 0;
    FaultMuxRegs.ACOMPCTRL1.bit.ACOMP_C_POL = 0;
    // FaultMuxRegs.ACOMPCTRL1.bit.ACOMP_C_INT_EN = 1;
    FaultMuxRegs.DPWM0FLTABDET.bit.ACOMP_C_EN = 1;
    FaultMuxRegs.DPWM1FLTABDET.bit.ACOMP_C_EN = 1;
    FaultMuxRegs.DPWM2FLTABDET.bit.ACOMP_C_EN = 1;
    FaultMuxRegs.DPWM3FLTABDET.bit.ACOMP_C_EN = 1;
    configure_uvp();
}
void init_ovp(void)
{
    FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_SEL = 0;
    FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_POL = 1;
    FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_INT_EN = 1;

    FaultMuxRegs.DPWM0FLTABDET.bit.ACOMP_B_EN = 1;
    FaultMuxRegs.DPWM1FLTABDET.bit.ACOMP_B_EN = 1;
    FaultMuxRegs.DPWM2FLTABDET.bit.ACOMP_B_EN = 1;
    FaultMuxRegs.DPWM3FLTABDET.bit.ACOMP_B_EN = 1;
    configure_ovp();
}
void init_sec_ocp(void)
{
    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_SEL = 0;        //Configures reference of analog comparator E to ACOMP_E_THRESH
	FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_POL = 1;        //Polarity of comparator when an event is detected.
	FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_INT_EN = 1;

    FaultMuxRegs.DPWM0FLTABDET.bit.ACOMP_E_EN = 1;
	FaultMuxRegs.DPWM1FLTABDET.bit.ACOMP_E_EN = 1;
	FaultMuxRegs.DPWM2FLTABDET.bit.ACOMP_E_EN = 1;
	FaultMuxRegs.DPWM3FLTABDET.bit.ACOMP_E_EN = 1;
	configure_iout_ocp();
}


//
void init_ipri_cycle_by_cycle(void)
{
    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_F_REF_SEL = 0;
    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_F_SEL = 0;
    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_F_POL = 1;
    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_F_INT_EN = 1;
    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_THRESH = 30;

    FaultMuxRegs.DPWM0FLTABDET.bit.ACOMP_F_EN = 1;
	FaultMuxRegs.DPWM1FLTABDET.bit.ACOMP_F_EN = 1;
	FaultMuxRegs.DPWM2FLTABDET.bit.ACOMP_F_EN = 1;
	FaultMuxRegs.DPWM3FLTABDET.bit.ACOMP_F_EN = 1;
    
    Dpwm0Regs.DPWMCTRL0.bit.BLANK_A_EN = 1;
    Dpwm0Regs.DPWMBLKABEG.bit.BLANK_A_BEGIN = 0;
    Dpwm0Regs.DPWMBLKAEND.bit.BLANK_A_END = 30;//30*4ns = 120ns

    Dpwm0Regs.DPWMCTRL0.bit.CBC_PWM_AB_EN = 1;
    Dpwm0Regs.DPWMCTRL0.bit.CBC_ADV_CNT_EN = 1;
    Dpwm0Regs.DPWMAUTOMID.bit.CBC_PWM_AB_EN = 1;
    Dpwm0Regs.DPWMAUTOMID.bit.CBC_ADV_CNT_EN = 1;
    Dpwm0Regs.DPWMAUTOMAX.bit.CBC_PWM_AB_EN = 1;
    Dpwm0Regs.DPWMAUTOMAX.bit.CBC_ADV_CNT_EN = 1;

    // Dpwm0Regs.DPWMCTRL1.bit.CBC_BSIDE_ACTIVE_EN = 1;   
}

void init_fault(void)
{
    FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_EN = 1;

    Dpwm0Regs.DPWMFLTCTRL.bit.ALL_FAULT_EN = 1;
    Dpwm0Regs.DPWMFLTCTRL.bit.AB_MAX_COUNT = 0;
    Dpwm1Regs.DPWMFLTCTRL.bit.ALL_FAULT_EN = 1;
    Dpwm1Regs.DPWMFLTCTRL.bit.AB_MAX_COUNT = 0;    
    Dpwm2Regs.DPWMFLTCTRL.bit.ALL_FAULT_EN = 1;
    Dpwm2Regs.DPWMFLTCTRL.bit.AB_MAX_COUNT = 0;
    Dpwm3Regs.DPWMFLTCTRL.bit.ALL_FAULT_EN = 1;
    Dpwm3Regs.DPWMFLTCTRL.bit.AB_MAX_COUNT = 0;
}
/*------------------------------------test------------------------------------*/


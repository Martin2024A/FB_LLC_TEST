#include "Cyclone_Device.h"
#include "interrupt.h"
#include "global_variables.h"

#pragma INTERRUPT(undefined_instruction_exception,UDEF)
void undefined_instruction_exception(void)
{
}

#pragma INTERRUPT(abort_prefetch_exception,PABT)
void abort_prefetch_exception(void)
{
}

#pragma INTERRUPT(abort_data_fetch_exception,DABT)
void abort_data_fetch_exception(void)
{
}

#pragma INTERRUPT(fast_interrupt,FIQ)
void fast_interrupt(void)
{
}

void init_interrupt(void)
{
    //Threshold to send the pwm low. Approx 10KHz. by spec.64ns clock period
	TimerRegs.T16PWM2CMP0DAT.all = 1587;
	//Threshold to send the pwm high
	TimerRegs.T16PWM2CMP1DAT.all = 0xFFFF;
	//Enables compare 0 (reset) interrupt
	TimerRegs.T16PWM2CMPCTRL.all = 2;
	//PWM counter is running & enables PWM counter reset by compare action on compare 0
	TimerRegs.T16PWM2CNTCTRL.all = 0x00C;
	//Disable interrupts
	disable_interrupt();
	disable_fast_interrupt();
	//This is necessary to make sure all interrupt status values are
	//cleared. Added here by ZCS feature
	FAULTMUXINTSTAT_value =	FaultMuxRegs.FAULTMUXINTSTAT.all;
	//Configure IRQ
	write_reqmask(CIMINT_ALL_PWM2_COMP | CIMINT_ALL_DPWM0 | CIMINT_ALL_FAULT_MUX);
	//Configure FIQ
	write_firqpr(CIMINT_ALL_DPWM0 | CIMINT_ALL_FAULT_MUX);
	//Enable interrupts
	enable_fast_interrupt();
	enable_interrupt();
}


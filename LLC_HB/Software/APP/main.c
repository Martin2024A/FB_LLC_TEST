/**
 * *****************************************************************************
 * @file        main.c
 * @brief       
 * @author      Martin (you@example.com)
 * @date        2024-06-21
 * @copyright   ETRON
 * *****************************************************************************
 */

#define MAIN 1
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "device_parm_define.h"
#include "system_define.h"
#include "pmbus_dcdc_parm.h"
#include "pmbus_filter_parm.h"
#include "pmbus_common.h"
#include "global_variables.h"
#include "interrupt.h"
#include "function_definitions.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

void main()
{
	//backdoor1:enable JTAG
	MiscAnalogRegs.IOMUX.all = 0;
	//backdoor2
	if (MiscAnalogRegs.GLBIOREAD.bit.FAULT2_IO_READ && !MiscAnalogRegs.GLBIOREAD.bit.FAULT3_IO_READ)
	{
		pmbus_read_write_rom_mode(PMBUS_WRITE);
	}

	global_disable();
	restore_default_all();
	init_variables();
	init_gpio();
	init_dpwms();
	init_sample_trigger();
	init_loop_mux();
	init_front_end0();
	init_filter0();
	init_DTC();
	init_adc12();
	init_ovp();
	init_uvp();
	init_sec_ocp();
	init_ipri_cycle_by_cycle();
	init_fault();

	look_for_interrupted_dflash_erase(); 
	transition_to_idle_state();
	global_enable();
	init_pmbus(0x58);
	init_interrupt();	

	//This is necessary to make sure all interrupt status values are cleared.
	FAULTMUXINTSTAT_value =	FaultMuxRegs.FAULTMUXINTSTAT.all;

	for(;;)
	{
		if (erase_segment_counter > 0)
		{
			//Handle the DFlash segment erases
			erase_task();
		}
		//Run the PMBus handler
		pmbus_handler();
	}
}

void c_int00(void)
{
	main();
}

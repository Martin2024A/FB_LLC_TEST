
/*----------------------------------include-----------------------------------*/
#include "device_parm_define.h"
#include "system_define.h"
#include "pmbus_dcdc_parm.h"
#include "pmbus_filter_parm.h"
#include "pmbus_common.h"
#include "global_variables.h"
#include "function_definitions.h"

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
#pragma INTERRUPT(standard_interrupt,IRQ)
void standard_interrupt(void)
{
	handle_standard_interrupt_global_tasks();
	handle_faults();

	switch (supply_state)
	{
	case STATE_IDLE:
		handle_idle_state();
		break;

	case STATE_RAMP_UP:
		handle_ramp_up_state();
		break;

	case STATE_CHECK_RAMP_UP:
	    handle_delay_rampup_state();
	    break;

	case STATE_REGULATED:
		handle_regulation_state();
		break;
	case STATE_VOUT_TRANSITION:
		handle_vout_transition_state();
		break;

	// case STATE_HICCUP:
	// 	handle_hiccup_state();
	// 	break;
	case STATE_FAULT:
		handle_fault_state();
		break;
	}
	Dpwm0Regs.DPWMCTRL1.bit.GPIO_A_VAL =1;   //test

	//clear interrupt flag by a read/write to register.
	TimerRegs.T16PWM2CMPCTRL.all = 3;
	//Clear the GPIO to signify the end of the interrupt
//	MiscAnalogRegs.GLBIOVAL.bit.DPWM2A_IO_VALUE = 0;
}
void handle_standard_interrupt_global_tasks(void)
{
	poll_adc();
	handle_pgood();
}

void handle_idle_state(void)
{
	if (!start_up_delay_over)
	{
	    if (count == count_end)
		{
			start_up_delay_over = 1;
		}
		else
		{
			count++;
		}
	}

	if (PSON && start_up_delay_over && (!firmware_error_flag))
	{
	    configure_dpwm_timing(&pmbus_dcdc_config[0]);
	    if(ABOVE_VIN_ON_LIMIT)
	    {
	        count =0;

	        Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE =1;
	        Filter0Regs.CPUXN.bit.CPU_SAMPLE =0;

	        handle_softstart(); //Closed loop to start up

	        supply_state = STATE_RAMP_UP;

	        gpio_dpwm_on();
	    }
	}
}

void handle_softstart(void)
{
	FeCtrl0Regs.EADCDAC.bit.DAC_VALUE = 0;   //Set the DAC for Error ~ 0
    FeCtrl0Regs.RAMPDACEND.all = 16300; //pmbus_dcdc_config_translated[0].vout_cmd;//Set the DAC end for the desired output voltage

    configure_vout_timing();

    FeCtrl0Regs.DACSTEP.bit.DAC_STEP = pmbus_dcdc_config_translated[0].vout_transition_rate;//200ms default
    Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 1;
    Filter0Regs.CPUXN.all =0;
    LoopMuxRegs.SAMPTRIGCTRL.bit.FE0_TRIG_DPWM0_EN = 0; //Stop triggering EADC0

    //Initialize filter

    Filter0Regs.FILTERCTRL.bit.FILTER_EN =0;
    Filter0Regs.FILTERCTRL.bit.KI_STALL = 1;
    Filter0Regs.FILTERPRESET.bit.PRESET_VALUE = 0;  //360000 can avoid small pulses//Place a predetermined value
    Filter0Regs.FILTERPRESET.bit.PRESET_REG_SEL = 1;    //into the I value register
    Filter0Regs.FILTERPRESET.bit.PRESET_EN = 1;         //then set bit to enable preset; ("save" it there)
    Filter0Regs.FILTERCTRL.bit.KI_STALL = 0;
    Filter0Regs.FILTERCTRL.bit.FILTER_EN =1;
    LoopMuxRegs.SAMPTRIGCTRL.bit.FE0_TRIG_DPWM0_EN = 1; //Resume triggering EADC0 Filter0


    FeCtrl0Regs.RAMPCTRL.bit.FIRMWARE_START = 1;//Begin the DAC Ramp


    Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 0;
}

void handle_ramp_up_state(void)
{
	Uint32 DAC_temp;
    //Check for and handle any faults
    if ((!PSON) || BELOW_VIN_OFF_LIMIT)
    {

        //Check to see if PSON is still valid. If no go to idle.
        transition_to_idle_state();
    }

    else if(FeCtrl0Regs.RAMPSTAT.bit.RAMP_COMP_INT_STATUS == 1)//Ramp is completed
    {
        DAC_temp = FeCtrl0Regs.RAMPDACEND.bit.RAMP_DAC_VALUE;   //Move the DACEND value
        FeCtrl0Regs.EADCDAC.bit.DAC_VALUE = DAC_temp;           //To now be the DAC value

        FeCtrl0Regs.RAMPCTRL.bit.FIRMWARE_START = 0;//Turn off the Ramp Module

//        supply_state = STATE_REGULATED;
        supply_state = STATE_CHECK_RAMP_UP;

        default_period = Filter0Regs.FILTERYNCLPHI.all;
        max_period = default_period * 1.25;
        min_period = default_period * 0.84;   //still in Resonant mode, 1200kHz min period

        default_mode_switching = Dpwm0Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER;
        min_mode_switching = default_mode_switching * 0.8;   //mode switching

    }
}

void transition_to_idle_state(void)
{
    gpio_dpwm_off();

    FaultMuxRegs.DPWM1FLTABDET.bit.ACOMP_C_EN = 0;
    FaultMuxRegs.DPWM2FLTABDET.bit.ACOMP_C_EN = 0;
    FaultMuxRegs.DPWM3FLTABDET.bit.ACOMP_C_EN = 0;
    FaultMuxRegs.DPWM0FLTABDET.bit.ACOMP_C_EN = 0;
    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_THRESH = 35;

    Dpwm0Regs.DPWMCTRL0.bit.PWM_EN = 0;
    Dpwm0Regs.DPWMCTRL0.bit.PWM_EN = 1;
    Dpwm1Regs.DPWMCTRL0.bit.PWM_EN = 0;
    Dpwm1Regs.DPWMCTRL0.bit.PWM_EN = 1;
    Dpwm2Regs.DPWMCTRL0.bit.PWM_EN = 0;
    Dpwm2Regs.DPWMCTRL0.bit.PWM_EN = 1;
    Dpwm3Regs.DPWMCTRL0.bit.PWM_EN = 0;
    Dpwm3Regs.DPWMCTRL0.bit.PWM_EN = 1;

    supply_state = STATE_IDLE;

	//Disable DPWMs
    Dpwm0Regs.DPWMINT.bit.PRD_INT_EN = 0;
    configure_dpwm_timing(&pmbus_dcdc_config[0]);

	init_filter0_states();

	clear_faults();
	//Reset the PMBus status word to the idle state values.
	pmbus_status_word = PMBUS_STATUS_WORD_HIGH_BYTE | PMBUS_STATUS_WORD_OFF | PMBUS_STATUS_WORD_POWER_GOOD_NOT;
	//Reset the fault status flags.
	fiq_data.fault_status = 0;
	start_up_delay_over =0;
	ramp_complete = 0;				//Value stored in FeCtrl0Regs.RAMPSTAT.bit.RAMP_COMP_INT_STATUS
	count =0;
	FaultMuxRegs.ACOMPCTRL1.bit.ACOMP_C_INT_EN = 0;
	uv_latch_flag =0;
	ov_latch_flag =0;
	oc_latch_flag =0;
	retry_enable =1;
	restart_counter =0;
	oc_counter =0;
	period_change_enable =0;
	delay_counter =0;
}

void clear_faults(void)
{
	global_disable();
	global_enable();
	//This is necessary to make sure all interrupt status values are 
	//cleared.
	FAULTMUXINTSTAT_value =	FaultMuxRegs.FAULTMUXINTSTAT.all;
}

void handle_delay_rampup_state(void)
{
    handle_faults();
    delay_counter++;
    if(delay_counter > 15000)    //1.5s
    {
        delay_counter =15002;
        if(Dpwm0Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER >= min_mode_switching)
        {
            Dpwm0Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = Dpwm0Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER -1;
            Dpwm0Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER =  Dpwm0Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER -1;
            Dpwm0Regs.DPWMPRD.bit.PRD = Dpwm0Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER << 1;

            Dpwm0Regs.DPWMEV4.bit.EVENT4 = Dpwm0Regs.DPWMPRD.bit.PRD *16 - Dpwm0Regs.DPWMEV1.all;

            Dpwm1Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = Dpwm1Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER -1;
            Dpwm1Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER =  Dpwm1Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER -1;
            Dpwm1Regs.DPWMPRD.bit.PRD = Dpwm1Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER << 1;
            Dpwm1Regs.DPWMEV4.bit.EVENT4 = Dpwm1Regs.DPWMPRD.bit.PRD *16 - Dpwm1Regs.DPWMEV1.all;

            Dpwm2Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = Dpwm2Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER -1;
            Dpwm2Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER =  Dpwm2Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER -1;
            Dpwm2Regs.DPWMPRD.bit.PRD = Dpwm2Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER << 1;
            Dpwm2Regs.DPWMEV4.bit.EVENT4 = Dpwm2Regs.DPWMPRD.bit.PRD*16 - Dpwm2Regs.DPWMEV1.all;

            Dpwm3Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = Dpwm3Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER -1;
            Dpwm3Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER =  Dpwm3Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER -1;
            Dpwm3Regs.DPWMPRD.bit.PRD = Dpwm3Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER << 1;
            Dpwm3Regs.DPWMEV4.bit.EVENT4 = Dpwm3Regs.DPWMPRD.bit.PRD*16 - Dpwm3Regs.DPWMEV1.all;

            LoopMuxRegs.PWMGLBPER.bit.PRD = Dpwm3Regs.DPWMPRD.bit.PRD;


            Dpwm2Regs.DPWMPHASETRIG.all =  (Dpwm2Regs.DPWMPRD.bit.PRD * 8 + 32);  //180 degree phase offset

            Dpwm3Regs.DPWMBLKBEND.all = (Dpwm2Regs.DPWMPRD.bit.PRD * 8 + Dpwm3Regs.DPWMEV1.bit.EVENT1 * 16 - pmbus_dcdc_config[0].dead_time_2);
            Dpwm2Regs.DPWMBLKBEND.all = (Dpwm2Regs.DPWMPRD.bit.PRD * 8 + Dpwm2Regs.DPWMEV1.bit.EVENT1 * 16 - pmbus_dcdc_config[0].dead_time_2);
            Dpwm1Regs.DPWMBLKBEND.all = (Dpwm2Regs.DPWMPRD.bit.PRD * 8 + Dpwm2Regs.DPWMEV1.bit.EVENT1 * 16 - pmbus_dcdc_config[0].dead_time_2);


        }
        else
        {
            supply_state = STATE_REGULATED;
            FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_THRESH = 9;
            configure_iout_ocp();
        }
    }
}

void handle_regulation_state(void)
{	
    updated_period_target = pmbus_dcdc_config_translated[0].frequency_switch * PID_PERIOD_FACTOR;
	//Control the state of the SR's
	control_sr_on_off();
	//is large enough to operate.
	if ((!PSON) || BELOW_VIN_OFF_LIMIT)
//	if (!PSON)
	{
		transition_to_idle_state();
	}
	else 
	{
		//Check for and handle any faults
	    handle_faults();
		//Check for and handle and warnings
		handle_warnings();
		if(period_change_enable == 1)
		{
		    // period_change();
		}
		//to add UCD7138 deadtime control and SR control
	}
}

void handle_vout_transition_state(void)
{
	//Read the ramp complete status bit. It is clear on read.
	// to call filter ramp up here
	//If not transition to the idle state.
	if ((!PSON) || BELOW_VIN_OFF_LIMIT)
	{
		transition_to_idle_state();
	}
	else if (ramp_complete)
	{

		supply_state = STATE_REGULATED;
	}
}

void handle_fault_state(void)
{
	//Check to see if the turn on command is still valid.
	//If not transition to the idle state.
    gpio_dpwm_off();

    if(!PSON)
	{
		transition_to_idle_state();
	}

	restart_counter++;
	if(restart_counter > 50000)  //5s
	{
	    restart_counter =50001;
	    if (OT_FAULT_PRI_RESTART && OT_FAULT_SEC_RESTART)
	    {
	        if(retry_enable ==1)
	        {
//                if ((ov_latch_flag ==0) && (oc_latch_flag ==0))                        // restart capability
	            if ((uv_latch_flag == 0) && (ov_latch_flag ==0) && (oc_latch_flag ==0)) //any fault latch
	            {
	              transition_to_idle_state();   //soft start
	              firmware_error_flag = 0;
	            }
	        }
	    }

	}
	else
	{
	    ;
	}


}

void init_variables(void)
{
	//Initialization for PFC UART commands
	pfc_phase_2_enable = ENABLE;
	pfc_zvs_enable = DISABLE;
	pfc_os_enable = ENABLE;

	//Initialization for LLC SR operation.
	llc_sr_enable = ENABLE;
//    llc_sr_enable = DISABLE;
	previous_llc_sr_command = DISABLE;
	//Fault status indicators
	fiq_data.fault_status = 0;

	//Initialzie Debug Buffer
	debug_buffer[0]=1;
	debug_buffer[1]=2;
	debug_buffer[2]=3;
	debug_buffer[3]=4;
	debug_buffer[4]=5;
	debug_buffer[5]=6;
	debug_buffer[6]=7;
	debug_buffer[7]=8;

	//Resolution selection parameter for ADC firmware averaging.
	adc_values_avg.adc_scale_factor = 5;

	//Configure the input voltage at which the power converter will allow turn on
	//and the voltage level that it will turn off.
	configure_vin_on_off_thresholds();
	//Configure the fault levels.
	configure_fault_levels();
	//Configure the warning levels.
	configure_warning_levels();
	//Configure the PGOOD levels.
	configure_pgood_levels();

	//Calculate translated values of the vout timing.
	configure_vout_timing();
	//Calculate a translated value of the vout_cmd.
	configure_vout_cmd();

	adc12_vin_scaler.mantissa = ADC12_VIN_SCALER_MANTISSA;
	adc12_vin_scaler.exponent = ADC12_VIN_SCALER_EXPONENT;

	fiq_data.cbc_voltage_loop_integrator_jam_value = 2000000;
	fiq_data.cbc_current_loop_integrator_jam_value = 1000000;
	fiq_data.cc_detected = 0;
	fiq_data.cbc_detected = 0;

	filter_select = 1;
	filter_activate = 0;
	filter_destination = &filter0_pmbus_regs;
	fiq_data.burst_mode_en = 0;
	fiq_data.burst_mode_i_turn_off = 170;
	fiq_data.burst_mode_i_turn_on = 130;
	fiq_data.burst_mode_int_jam_value = 2210000;
	fiq_data.burst_mode_v_hys = 4;
	fiq_data.cbc_counter = 0;
	fiq_data.cbc_max = 1;
	start_up_delay_over = 0;
	count = 0;
	count_end = 1000;
	oc_fault_limit =250;
}

/*------------------------------------test------------------------------------*/

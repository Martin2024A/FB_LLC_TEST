
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

void configure_vout_timing(void)
{
//	struct qnote constant_3_73555 = {30602 , -13};

	struct qnote constant_3_73555 = {23000, -13};
	struct qnote tran_scaler;
	struct qnote slew_rate_qnote;
	struct qnote ton;
	struct qnote vcmd;
	Uint32 ramp_step;
	Uint16 slew_rate;
	// Uint16 ramp_DAC_step;
	// Uint16 slew_sample_rate;

	vcmd.mantissa = pmbus_dcdc_config[0].vout_cmd;
	vcmd.exponent = -VOUT_MODE_EXP;

	ton = linear11_to_qnote(pmbus_dcdc_config[0].ton_rise);

    pmbus_dcdc_config_translated[0].ton_rise = (Uint32)qnote_to_linear11(ton);

	slew_rate_qnote.mantissa = ((Uint32)(vcmd.mantissa << TON_RISE_EXP)) / ((Uint32)ton.mantissa);
	slew_rate_qnote.exponent = vcmd.exponent - ton.exponent - TON_RISE_EXP;
	slew_rate = qnote_to_linear11(slew_rate_qnote);

	tran_scaler = qnote_scale_int32(constant_3_73555, pmbus_dcdc_config[0].sample_rate);

	ramp_step = qnote_linear11_multiply_fit(tran_scaler, slew_rate, MAX_VALUE_FIT_18_BITS);

	pmbus_dcdc_config_translated[0].vout_transition_rate = ramp_step;

}

void configure_iout_ocp(void)
{
	//This struct represents the floating point number: 0.60928
	//struct qnote constant_0_60928 = {19965 , -15};

	FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_THRESH = (Uint8)(pmbus_dcdc_config_translated[0].iout_oc_fault_limit / 238);


}
void control_sr_on_off(void)
{
    if (llc_sr_enable ^ previous_llc_sr_command)
    {
        if (llc_sr_enable)
        {
            //Turn on SR
            gpio_sr_on();
        }
        else
        {
            //Turn off SR
            gpio_sr_off();
        }
        previous_llc_sr_command = llc_sr_enable;
    }
}

void configure_vin_on_off_thresholds(void)
{
	struct qnote adc12_vin_scaler  = {ADC12_VIN_SCALER_MANTISSA,  ADC12_VIN_SCALER_EXPONENT}; 
	pmbus_dcdc_config_translated[0].vin_on_limit  = qnote_linear11_multiply_fit(adc12_vin_scaler, pmbus_dcdc_config[0].vin_on_limit,  MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].vin_off_limit = qnote_linear11_multiply_fit(adc12_vin_scaler, pmbus_dcdc_config[0].vin_off_limit, MAX_VALUE_FIT_12_BITS);
}

void configure_fault_levels(void)
{
	struct qnote adc12_vout_scaler = {ADC12_VOUT_SCALER_MANTISSA, ADC12_VOUT_SCALER_EXPONENT};
	struct qnote adc12_vin_scaler  = {ADC12_VIN_SCALER_MANTISSA,  ADC12_VIN_SCALER_EXPONENT}; 
	struct qnote adc12_temp_scaler = {ADC12_TEMP_SCALER_MANTISSA, ADC12_TEMP_SCALER_EXPONENT}; 
    struct qnote adc12_iout_scaler = {ADC12_IOUT_SCALER_MANTISSA, ADC12_IOUT_SCALER_EXPONENT};

	pmbus_dcdc_config_translated[0].vout_uv_fault_limit = qnote_linear16_multiply_fit(adc12_vout_scaler, pmbus_dcdc_config[0].vout_uv_fault_limit, -VOUT_MODE_EXP, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].iout_oc_fault_limit = qnote_linear11_multiply_fit(adc12_iout_scaler, pmbus_dcdc_config[0].iout_oc_fault_limit, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].temp_ot_fault_limit = 2720 + qnote_linear11_multiply_fit(adc12_temp_scaler, (pmbus_dcdc_config[0].temp_ot_fault_limit - 23), MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].vin_ov_fault_limit  = qnote_linear11_multiply_fit(adc12_vin_scaler, pmbus_dcdc_config[0].vin_ov_fault_limit, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].vin_uv_fault_limit  = qnote_linear11_multiply_fit(adc12_vin_scaler, pmbus_dcdc_config[0].vin_uv_fault_limit, MAX_VALUE_FIT_12_BITS);
}

void configure_warning_levels(void)
{
	struct qnote adc12_vout_scaler = {ADC12_VOUT_SCALER_MANTISSA, ADC12_VOUT_SCALER_EXPONENT};
	struct qnote adc12_iout_scaler = {ADC12_IOUT_SCALER_MANTISSA, ADC12_IOUT_SCALER_EXPONENT};  
	struct qnote adc12_iin_scaler  = {ADC12_IIN_SCALER_MANTISSA,  ADC12_IIN_SCALER_EXPONENT};  
	struct qnote adc12_vin_scaler  = {ADC12_VIN_SCALER_MANTISSA,  ADC12_VIN_SCALER_EXPONENT}; 
	struct qnote adc12_temp_scaler = {ADC12_TEMP_SCALER_MANTISSA, ADC12_TEMP_SCALER_EXPONENT};
	pmbus_dcdc_config_translated[0].vout_ov_warn_limit = qnote_linear16_multiply_fit(adc12_vout_scaler, pmbus_dcdc_config[0].vout_ov_warn_limit, -VOUT_MODE_EXP, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].vout_uv_warn_limit = qnote_linear16_multiply_fit(adc12_vout_scaler, pmbus_dcdc_config[0].vout_uv_warn_limit, -VOUT_MODE_EXP, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].iout_oc_warn_limit = qnote_linear11_multiply_fit(adc12_iout_scaler, pmbus_dcdc_config[0].iout_oc_warn_limit, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].iin_oc_warn_limit  = qnote_linear11_multiply_fit(adc12_iin_scaler, pmbus_dcdc_config[0].iin_oc_warn_limit, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].temp_ot_warn_limit =  qnote_linear11_multiply_fit(adc12_temp_scaler, pmbus_dcdc_config[0].temp_ot_warn_limit, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].vin_ov_warn_limit  = qnote_linear11_multiply_fit(adc12_vin_scaler, pmbus_dcdc_config[0].vin_ov_warn_limit, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].vin_uv_warn_limit  = qnote_linear11_multiply_fit(adc12_vin_scaler, pmbus_dcdc_config[0].vin_uv_warn_limit, MAX_VALUE_FIT_12_BITS);
}

void configure_pgood_levels(void)
{
	struct qnote adc12_vout_scaler = {ADC12_VOUT_SCALER_MANTISSA, ADC12_VOUT_SCALER_EXPONENT};
	pmbus_dcdc_config_translated[0].pgood_on_limit  = qnote_linear16_multiply_fit(adc12_vout_scaler, pmbus_dcdc_config[0].pgood_on_limit, -VOUT_MODE_EXP, MAX_VALUE_FIT_12_BITS);
	pmbus_dcdc_config_translated[0].pgood_off_limit = qnote_linear16_multiply_fit(adc12_vout_scaler, pmbus_dcdc_config[0].pgood_off_limit, -VOUT_MODE_EXP, MAX_VALUE_FIT_12_BITS);
}


void configure_vout_cmd(void)
{
	struct qnote dac_value_scaler = {DAC_VALUE_SCALER, 0};
	pmbus_dcdc_config_translated[0].vout_cmd = qnote_linear16_multiply_fit(dac_value_scaler, pmbus_dcdc_config[0].vout_cmd,-VOUT_MODE_EXP,	MAX_VALUE_FIT_14_BITS);
}


void configure_uvp(void)
{
	Uint16 uvp_limit;
	struct qnote vdac_scaler = {DAC_OVP, -OVP_EXP};
	uvp_limit = qnote_linear16_multiply_fit(vdac_scaler, pmbus_dcdc_config[0].vout_uv_fault_limit, -VOUT_MODE_EXP, MAX_VALUE_FIT_7_BITS);
	FaultMuxRegs.ACOMPCTRL1.bit.ACOMP_C_THRESH = uvp_limit;

}

void configure_ovp(void)
{
	Uint16 ovp_limit;
	//This struct represents the floating point number: 4.65455
	struct qnote constant_4_65455 = {19065 , -12};
	ovp_limit = qnote_linear16_multiply_fit(constant_4_65455 ,
		pmbus_dcdc_config[0].vout_ov_fault_limit, -VOUT_MODE_EXP,
		MAX_VALUE_FIT_7_BITS);
	FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_THRESH = ovp_limit;                //ACOMP threshold
	pmbus_dcdc_config_translated[0].vout_ov_fault_limit = ovp_limit;
}



void configure_cc_dac_value(void)
{
	int16 imax_value;
	//This struct represents the floating point number: 7.616
	struct qnote constant_7_616 = {31195 , -12};
	imax_value = qnote_linear11_multiply_fit(constant_7_616,
		pmbus_dcdc_config[0].cpcc_imax,
		MAX_VALUE_FIT_10_BITS) << 4;
	// Set Processor DAC to MAX_CURRENT value for Error calculation
	FeCtrl1Regs.EADCDAC.bit.DAC_VALUE = imax_value;
}
/*------------------------------------test------------------------------------*/

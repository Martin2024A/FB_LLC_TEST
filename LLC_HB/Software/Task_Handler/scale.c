
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
struct qnote linear11_to_qnote (int16 linear11)
{
	struct qnote final;

	if(linear11 & 0x0400)             // if mantissa is negative
		final.mantissa = linear11 | 0xFC00;
	else
		final.mantissa = linear11 & 0x07FF;

	final.exponent = linear11 >> 11;

	return final;
}
//----------------------------------------------------------------------
//         Change data from Qnote to Linear11 Data Format
//----------------------------------------------------------------------
int16 qnote_to_linear11 (struct qnote x)
{
	int16 linear11;

	while(abs(x.mantissa) > 0x3FF)
	{
		x.mantissa = x.mantissa >> 1;
		x.exponent = x.exponent + 1;
	}
	linear11 = (x.exponent << 11) + (x.mantissa & 0x07FF);

	return linear11;
}

//--------------------------------------------------------------
//               int32 qnote scale
//--------------------------------------------------------------
struct qnote qnote_scale_int32 (struct qnote x, int32 y)
{
	struct qnote final;
	int64 mantissa;
	final.exponent = x.exponent;

	mantissa = (int64)x.mantissa * (int64)y; 
	while(abs(mantissa) > 0x7FFF)
	{
		mantissa = mantissa >> 1;
		final.exponent = final.exponent + 1;
	}
	final.mantissa = mantissa;

	return final;
}

//--------------------------------------------------------------
//               Uint32 qnote multiply linear 11 fit
//--------------------------------------------------------------
Uint32 qnote_linear11_multiply_fit(struct qnote x, int16 linear11, Uint32 max_value)
{
	struct qnote final,y;
	int32 mantissa;

	if(linear11 & 0x0400)             // if mantissa is negative
		y.mantissa = linear11 | 0xFC00;
	else
		y.mantissa = linear11 & 0x07FF;

	y.exponent = linear11 >> 11;

	final.exponent = x.exponent + y.exponent;
	mantissa = (int32)x.mantissa * (int32)y.mantissa; 

	while(final.exponent > 0)
	{
		mantissa = mantissa << 1;
		final.exponent = final.exponent - 1; 
	}            
	while(final.exponent < 0)
	{
		mantissa = mantissa >> 1;
		final.exponent = final.exponent + 1;
	}
	final.mantissa = mantissa;

	if(mantissa > max_value)
		mantissa = max_value;

	return mantissa;             
}

//--------------------------------------------------------------
//               Uint32 qnote multiply linear 16 fit
//--------------------------------------------------------------
Uint32 qnote_linear16_multiply_fit(struct qnote x, Uint16 linear16_mantissa, int8 vout_mode, Uint32 max_value)
{
	struct qnote final;
	Uint32 mantissa;

	if(vout_mode & 0x0010)             // if exponent is negative
		vout_mode = vout_mode | 0xFFE0;
	else
		vout_mode = vout_mode & 0x001F;

		final.exponent = x.exponent + vout_mode;
	mantissa = (Uint32)x.mantissa * (Uint32)linear16_mantissa; 

	while(final.exponent > 0)
	{
		mantissa = mantissa << 1;
		final.exponent = final.exponent - 1; 
	}            
	while(final.exponent < 0)
	{
		mantissa = mantissa >> 1;
		final.exponent = final.exponent + 1;
	}
	final.mantissa = mantissa;

	if(mantissa > max_value) 
		mantissa = max_value;

	return mantissa;             
}
/*------------------------------------test------------------------------------*/

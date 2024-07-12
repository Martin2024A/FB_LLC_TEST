
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "global_variables.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/
void init_adc12(void);
void poll_adc(void);
/*----------------------------------function----------------------------------*/
void init_adc12(void)
{
    AdcRegs.ADCCTRL.bit.SAMPLING_SEL = 6;// 267*1000 sample points per second

    AdcRegs.ADCCTRL.bit.MAX_CONV = 7;//8 conversion selection 
    AdcRegs.ADCCTRL.bit.SINGLE_SWEEP = 1;//Single conversion

    //转化通道-ADC序号
    AdcRegs.ADCSEQSEL0.bit.SEQ0  = 3; 	//VO_SENSE
	AdcRegs.ADCSEQSEL0.bit.SEQ1  = 2;	//Vin_SENSE
	AdcRegs.ADCSEQSEL0.bit.SEQ2  = 1;	//primary side TEMP
	AdcRegs.ADCSEQSEL0.bit.SEQ3  = 13;	//output current
	AdcRegs.ADCSEQSEL1.bit.SEQ4  = 6; 	//CBC protection
	AdcRegs.ADCSEQSEL1.bit.SEQ5 = 14;   //Device temp
    AdcRegs.ADCSEQSEL1.bit.SEQ6 = 4;   //secondary side temp
    AdcRegs.ADCSEQSEL1.bit.SEQ7 = 3;   //Vo_SENSE

    AdcRegs.ADCAVGCTRL.bit.AVG0_EN = 1;	
	AdcRegs.ADCAVGCTRL.bit.AVG1_EN = 1;
	AdcRegs.ADCAVGCTRL.bit.AVG2_EN = 1;	
	AdcRegs.ADCAVGCTRL.bit.AVG3_EN = 1;	
	AdcRegs.ADCAVGCTRL.bit.AVG4_EN = 1;	
	AdcRegs.ADCAVGCTRL.bit.AVG5_EN = 1;	

    //0-4x average, 1-8x average, 2-16x average, 3-32x average
	AdcRegs.ADCAVGCTRL.bit.AVG1_CONFIG = 3;
    AdcRegs.ADCAVGCTRL.bit.AVG0_CONFIG = 0;
	AdcRegs.ADCAVGCTRL.bit.AVG2_CONFIG = 3;
	AdcRegs.ADCAVGCTRL.bit.AVG3_CONFIG = 3;
	AdcRegs.ADCAVGCTRL.bit.AVG4_CONFIG = 3;
	AdcRegs.ADCAVGCTRL.bit.AVG5_CONFIG = 3;

    AdcRegs.ADCCTRL.bit.ADC_EN = 1;		//Enable ADC
	AdcRegs.ADCCTRL.bit.SW_START = 1;	//Send start bit high
	AdcRegs.ADCCTRL.bit.SW_START = 0;	//Send start bit low
}

//通过宏定义 MAIN 实现声明 和定义
void poll_adc(void)
{
	if(AdcRegs.ADCSTAT.bit.ADC_INT == 1) //If the conversion is complete
	{
		//Collect raw ADC values
		adc_values.vo_sense 		= AdcRegs.ADCRESULT[0].bit.RESULT;
		adc_values.io_sense 		= AdcRegs.ADCRESULT[3].bit.RESULT;
		adc_values.pri_temp 			= AdcRegs.ADCRESULT[2].bit.RESULT;    //Primary side temperature
		adc_values.vin_mon 			= AdcRegs.ADCRESULT[1].bit.RESULT;
//		adc_values.ishare 			= AdcRegs.ADCRESULT[4].bit.RESULT;  //CBC
		adc_values.device_temp		= AdcRegs.ADCRESULT[5].bit.RESULT;
        adc_values.sec_temp      = AdcRegs.ADCRESULT[6].bit.RESULT;
        adc_values.ips           = AdcRegs.ADCRESULT[4].bit.RESULT;  //CBC

		//Collect averaged ADC values
		adc_values_avg.vo_sense 	= AdcRegs.ADCAVGRESULT[0].bit.RESULT;
		adc_values_avg.io_sense	 	= AdcRegs.ADCAVGRESULT[3].bit.RESULT;
		adc_values_avg.pri_temp 		= AdcRegs.ADCAVGRESULT[2].bit.RESULT;
		adc_values_avg.vin_mon  	= AdcRegs.ADCAVGRESULT[1].bit.RESULT;
//		adc_values_avg.ishare   	= AdcRegs.ADCAVGRESULT[4].bit.RESULT;  //CBC
		adc_values_avg.device_temp	= AdcRegs.ADCAVGRESULT[5].bit.RESULT;
	}
	AdcRegs.ADCCTRL.bit.SW_START = 1; //Start a conversion 
	AdcRegs.ADCCTRL.bit.SW_START = 0; //Clear trigger, so we don't restart
}

/*------------------------------------test------------------------------------*/

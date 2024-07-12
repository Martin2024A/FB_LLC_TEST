
/*----------------------------------include-----------------------------------*/
#include "pmbus_dcdc_parm.h"
#include "pmbus_filter_parm.h"
#include "system_define.h"
#include "function_definitions.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void init_dpwms(void)
{
  init_dpwm0();
  init_dpwm1();
  init_dpwm2();
  init_dpwm3();
  configure_dpwm_timing(&pmbus_dcdc_config[0]);
}

/*
# 控制连接
* dpwm0、dpwm2控制原边
* dpwm1控制副边 
* dpwm3在INTRA_MUX下提供输出

# 控制逻辑
* 自动模式切换
  * 频率f高于界限(1000Khz)进入移相模式(start时修改成了1250Khz)
  * 频率f低于界限(1000Khz)处于谐振模式
  * 但f低于下限时，副边最大时间锁定

* 启动时，设置f为1M，移向
* 然后，重新设置界限，f为1M处于谐振模式

*/
void init_dpwm0(void)
{
  Dpwm0Regs.DPWMCTRL0.bit.PWM_EN = 1;               
  Dpwm0Regs.DPWMCTRL0.bit.MSYNC_SLAVE_EN = 1;

  Dpwm0Regs.DPWMCTRL0.bit.CLA_EN = 1;
  Dpwm0Regs.DPWMCTRL0.bit.PWM_MODE = NORMAL;
  Dpwm0Regs.DPWMCTRL0.bit.PWM_A_INTRA_MUX = BELOW_C;    //DPWM1C
  Dpwm0Regs.DPWMCTRL0.bit.PWM_B_INTRA_MUX = BELOW2_C;   //DPWM2C
  //RESON_MODE_FIXED_DUTY_EN = 0; default 0

  //-----------AUTOMID
  Dpwm0Regs.DPWMAUTOMID.bit.CLA_EN = 1;
  Dpwm0Regs.DPWMAUTOMID.bit.PWM_MODE = RESONANT;
  Dpwm0Regs.DPWMAUTOMID.bit.PWM_A_INTRA_MUX = PASS_THROUGH;
  Dpwm0Regs.DPWMAUTOMID.bit.PWM_B_INTRA_MUX = PASS_THROUGH;

  //-----------AUTOMAX
  Dpwm0Regs.DPWMAUTOMAX.bit.CLA_EN = 1;
  Dpwm0Regs.DPWMAUTOMAX.bit.PWM_MODE = RESONANT;
  Dpwm0Regs.DPWMAUTOMAX.bit.PWM_A_INTRA_MUX = PASS_THROUGH;
  Dpwm0Regs.DPWMAUTOMAX.bit.PWM_B_INTRA_MUX = PASS_THROUGH;

  Dpwm0Regs.DPWMCTRL1.bit.HIRES_DIS = 1;
  Dpwm0Regs.DPWMCTRL1.bit.CHECK_OVERRIDE = 1;
  Dpwm0Regs.DPWMCTRL1.bit.EVENT_UP_SEL = 1;
  Dpwm0Regs.DPWMCTRL1.bit.AUTO_MODE_SEL = 1;

  Dpwm0Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;

  Dpwm0Regs.DPWMINT.bit.PRD_INT_SCALE =2;//every 4 cycles
  Dpwm0Regs.DPWMINT.bit.PRD_INT_EN = 1;
}

void init_dpwm1(void)
{
  Dpwm1Regs.DPWMCTRL0.bit.PWM_EN = 1;
  Dpwm1Regs.DPWMCTRL0.bit.MSYNC_SLAVE_EN = 1;

  Dpwm1Regs.DPWMCTRL0.bit.CLA_EN = 1;
  Dpwm1Regs.DPWMCTRL0.bit.PWM_MODE = MULTI;
  Dpwm1Regs.DPWMCTRL0.bit.PWM_A_INTRA_MUX = PASS_THROUGH;
  Dpwm1Regs.DPWMCTRL0.bit.PWM_B_INTRA_MUX = PASS_THROUGH;

  //-----------AUTOMID
  Dpwm1Regs.DPWMAUTOMID.bit.CLA_EN = 1;
  Dpwm1Regs.DPWMAUTOMID.bit.PWM_MODE = RESONANT;
  Dpwm1Regs.DPWMAUTOMID.bit.PWM_A_INTRA_MUX = PASS_THROUGH;
  Dpwm1Regs.DPWMAUTOMID.bit.PWM_B_INTRA_MUX = PASS_THROUGH;

  //-----------AUTOMAX
  Dpwm1Regs.DPWMAUTOMAX.bit.CLA_EN = 1;
  Dpwm1Regs.DPWMAUTOMAX.bit.PWM_MODE = RESONANT;
  Dpwm1Regs.DPWMAUTOMAX.bit.PWM_A_INTRA_MUX = PASS_THROUGH;
  Dpwm1Regs.DPWMAUTOMAX.bit.PWM_B_INTRA_MUX  = PASS_THROUGH;
  Dpwm1Regs.DPWMAUTOMAX.bit.RESON_MODE_FIXED_DUTY_EN = 1;// Enable fixed duty for SR

  Dpwm1Regs.DPWMCTRL1.bit.HIRES_DIS = 1;
  Dpwm1Regs.DPWMCTRL1.bit.CHECK_OVERRIDE = 1;
  Dpwm1Regs.DPWMCTRL1.bit.EVENT_UP_SEL = 1;
  Dpwm1Regs.DPWMCTRL1.bit.AUTO_MODE_SEL = 1;

  Dpwm1Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;
}

void init_dpwm2(void)
{
  Dpwm2Regs.DPWMCTRL0.bit.PWM_EN = 1;
  Dpwm2Regs.DPWMCTRL0.bit.MSYNC_SLAVE_EN = 0;//Maater

  Dpwm2Regs.DPWMCTRL0.bit.CLA_EN = 1;
  Dpwm2Regs.DPWMCTRL0.bit.PWM_MODE = NORMAL;
  Dpwm2Regs.DPWMCTRL0.bit.PWM_A_INTRA_MUX = EDGEGEN;   
  Dpwm2Regs.DPWMCTRL0.bit.PWM_B_INTRA_MUX = EDGEGEN;

  //-----------AUTOMID
  Dpwm2Regs.DPWMAUTOMID.bit.CLA_EN = 1;
  Dpwm2Regs.DPWMAUTOMID.bit.PWM_MODE = RESONANT;
  Dpwm2Regs.DPWMAUTOMID.bit.PWM_A_INTRA_MUX = BELOW_A;
  Dpwm2Regs.DPWMAUTOMID.bit.PWM_B_INTRA_MUX = BELOW_B;

  //-----------AUTOMAX
  Dpwm2Regs.DPWMAUTOMAX.bit.CLA_EN = 1;
  Dpwm2Regs.DPWMAUTOMAX.bit.PWM_MODE = RESONANT;
  Dpwm2Regs.DPWMAUTOMAX.bit.PWM_A_INTRA_MUX = BELOW_A;
  Dpwm2Regs.DPWMAUTOMAX.bit.PWM_B_INTRA_MUX = BELOW_B;

  Dpwm2Regs.DPWMCTRL1.bit.HIRES_DIS = 1;
  Dpwm2Regs.DPWMCTRL1.bit.CHECK_OVERRIDE = 1;
  Dpwm2Regs.DPWMCTRL1.bit.EVENT_UP_SEL = 1;
  Dpwm2Regs.DPWMCTRL1.bit.AUTO_MODE_SEL = 1;

  Dpwm2Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;

  // ---------------- Edge-generation setup
  Dpwm2Regs.DPWMEDGEGEN.bit.A_ON_EDGE = CURRENT_POS_B;
  Dpwm2Regs.DPWMEDGEGEN.bit.A_OFF_EDGE = NEXT_NEG_A;
  Dpwm2Regs.DPWMEDGEGEN.bit.B_ON_EDGE = NEXT_POS_B;
  Dpwm2Regs.DPWMEDGEGEN.bit.B_OFF_EDGE = CURRENT_NEG_A;

  // When using edgegen, may need to enable all other DPWMS
  // to ensure same path delay, default is passthru on others (1234)
  Dpwm0Regs.DPWMEDGEGEN.bit.EDGE_EN = 1;
  Dpwm1Regs.DPWMEDGEGEN.bit.EDGE_EN = 1;
  Dpwm2Regs.DPWMEDGEGEN.bit.EDGE_EN = 1;
  Dpwm3Regs.DPWMEDGEGEN.bit.EDGE_EN = 1;
}

void init_dpwm3(void)
{
  Dpwm3Regs.DPWMCTRL0.bit.PWM_EN = 1;
  Dpwm3Regs.DPWMCTRL0.bit.MSYNC_SLAVE_EN = 1;

  Dpwm3Regs.DPWMCTRL0.bit.CLA_EN = 1;
  Dpwm3Regs.DPWMCTRL0.bit.PWM_MODE = NORMAL;
  Dpwm3Regs.DPWMCTRL0.bit.PWM_A_INTRA_MUX = PASS_THROUGH; 
  Dpwm3Regs.DPWMCTRL0.bit.PWM_B_INTRA_MUX = PASS_THROUGH;

  //-----------AUTOMAX
  Dpwm3Regs.DPWMAUTOMID.bit.CLA_EN = 1;
  Dpwm3Regs.DPWMAUTOMID.bit.PWM_MODE = RESONANT;
  Dpwm3Regs.DPWMAUTOMID.bit.PWM_A_INTRA_MUX = PASS_THROUGH;
  Dpwm3Regs.DPWMAUTOMID.bit.PWM_B_INTRA_MUX = PASS_THROUGH;

  //-----------AUTOMAX
  Dpwm3Regs.DPWMAUTOMAX.bit.CLA_EN = 1;
  Dpwm3Regs.DPWMAUTOMAX.bit.PWM_MODE = RESONANT;
  Dpwm3Regs.DPWMAUTOMAX.bit.PWM_A_INTRA_MUX = PASS_THROUGH;
  Dpwm3Regs.DPWMAUTOMAX.bit.PWM_B_INTRA_MUX = PASS_THROUGH;

  Dpwm3Regs.DPWMCTRL1.bit.HIRES_DIS = 1;
  Dpwm3Regs.DPWMCTRL1.bit.CHECK_OVERRIDE = 1;
  Dpwm3Regs.DPWMCTRL1.bit.EVENT_UP_SEL = 1;
  Dpwm3Regs.DPWMCTRL1.bit.AUTO_MODE_SEL = 1;

  Dpwm3Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;
}

void init_sample_trigger(void)
{
    //Sample trigger configuration for samples synchronized to DPWM0
    LoopMuxRegs.SAMPTRIGCTRL.bit.FE0_TRIG_DPWM0_EN = 1;
    LoopMuxRegs.SAMPTRIGCTRL.bit.FE1_TRIG_DPWM0_EN = 1;
    LoopMuxRegs.SAMPTRIGCTRL.bit.FE2_TRIG_DPWM0_EN = 1;

    Dpwm0Regs.DPWMCTRL2.bit.SAMPLE_TRIG_1_EN = 1;//Enable sample trigger 1
    Dpwm0Regs.DPWMCTRL2.bit.SAMPLE_TRIG_2_EN = 0;//default is 1 so disable

    Dpwm0Regs.DPWMCTRL2.bit.SAMPLE_TRIG1_MODE = 0;
    Dpwm0Regs.DPWMCTRL2.bit.SAMPLE_TRIG1_OVERSAMPLE = 0;//0-1x,1-2x,2-4x,3-8x
    Dpwm0Regs.DPWMSAMPTRIG1.bit.SAMPLE_TRIGGER = 5;     //Sample trigger 1 position
    Dpwm0Regs.DPWMADAPTIVE.bit.ADAPT_SAMP = 0;          //Adaptive trigger offset
}

void configure_dpwm_timing(PMBUS_DCDC_CONFIG *dpwm_timings)
{
  Uint32 dead_time_1_local;
  Uint32 dead_time_3_local;
  Uint32 dead_time_4_local;
  Uint32 clamp_value;

  dead_time_1_local = (dpwm_timings->dead_time_1 + 8)>>4;
  dead_time_3_local = (dpwm_timings->dead_time_3 + 8)>>4;
  dead_time_4_local = (dpwm_timings->dead_time_4 + 8)>>4;
  clamp_value = (((Uint64)dpwm_timings->dead_time_2 * ((1 << 23) - 1)) / (dpwm_timings->max_period * 8));


  LoopMuxRegs.PWMGLBPER.bit.PRD = dpwm_timings->min_period;
  //The resolution is different
  Dpwm0Regs.DPWMEV1.bit.EVENT1 = dead_time_1_local;
  Dpwm0Regs.DPWMEV2.bit.EVENT2 = dpwm_timings->min_period * 8 + dead_time_1_local * 16 -dpwm_timings->dead_time_2;
  Dpwm0Regs.DPWMEV3.bit.EVENT3 = dpwm_timings->min_period * 8 + dead_time_1_local * 16;
  Dpwm0Regs.DPWMEV4.bit.EVENT4 = dpwm_timings->min_period * 16 + dead_time_1_local * 16 -dpwm_timings->dead_time_2;
  Dpwm0Regs.DPWMPRD.bit.PRD = dpwm_timings->min_period;
  Dpwm0Regs.DPWMCYCADJA.bit.CYCLE_ADJUST_A = (int16)(-dpwm_timings->dead_time_2);
  Dpwm0Regs.DPWMCYCADJB.bit.CYCLE_ADJUST_B = (int16)(-dpwm_timings->dead_time_2);
  Dpwm0Regs.DPWMRESDUTY.bit.RESONANT_DUTY  =  (dpwm_timings->max_period + 1) >> 1;  // modulate the duty cycle
  Dpwm0Regs.DPWMAUTOSWHILOWTHRESH.bit.AUTO_SWITCH_HIGH_LOWER = dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm0Regs.DPWMAUTOSWHIUPTHRESH.bit.AUTO_SWITCH_HIGH_UPPER =  dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm0Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm0Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm0Regs.DPWMMINDUTYLO.bit.MIN_DUTY_LOW  =        (dpwm_timings->dead_time_2 + 8) >> 4;
  Dpwm0Regs.DPWMMINDUTYHI.bit.MIN_DUTY_HIGH =        (dpwm_timings->dead_time_2 + 8) >> 4;

  Dpwm1Regs.DPWMEV1.bit.EVENT1 = dead_time_3_local;
  Dpwm1Regs.DPWMEV2.bit.EVENT2 = dpwm_timings->min_period * 8 + dead_time_3_local * 16 - dpwm_timings->dead_time_4;
  Dpwm1Regs.DPWMEV3.bit.EVENT3 = dead_time_3_local * 16 + dpwm_timings->min_period * 8;
  Dpwm1Regs.DPWMEV4.bit.EVENT4 = dpwm_timings->min_period * 16 - dpwm_timings->dead_time_4 + dead_time_3_local * 16;
  Dpwm1Regs.DPWMPRD.bit.PRD = dpwm_timings->min_period;
  Dpwm1Regs.DPWMCYCADJA.bit.CYCLE_ADJUST_A = (int16)(-dpwm_timings->dead_time_4);
  Dpwm1Regs.DPWMCYCADJB.bit.CYCLE_ADJUST_B = (int16)(-dpwm_timings->dead_time_4);
  Dpwm1Regs.DPWMRESDUTY.bit.RESONANT_DUTY  =         (dpwm_timings->max_period + 1) >> 1;
  Dpwm1Regs.DPWMAUTOSWHILOWTHRESH.bit.AUTO_SWITCH_HIGH_LOWER = dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm1Regs.DPWMAUTOSWHIUPTHRESH.bit.AUTO_SWITCH_HIGH_UPPER =  dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm1Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm1Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm1Regs.DPWMMINDUTYLO.bit.MIN_DUTY_LOW  =        (dpwm_timings->dead_time_4 + 8) >> 4;
  Dpwm1Regs.DPWMMINDUTYHI.bit.MIN_DUTY_HIGH =        (dpwm_timings->dead_time_4 + 8) >> 4;

  Dpwm2Regs.DPWMEV1.bit.EVENT1 = dead_time_1_local;
  Dpwm2Regs.DPWMEV2.bit.EVENT2 = dpwm_timings->min_period * 8 + dead_time_1_local * 16 - dpwm_timings->dead_time_2;
  Dpwm2Regs.DPWMEV3.bit.EVENT3 = dpwm_timings->min_period * 8 + dead_time_1_local * 16;
  Dpwm2Regs.DPWMEV4.bit.EVENT4 = dpwm_timings->min_period * 16 - dpwm_timings->dead_time_2 + dead_time_1_local * 16;
  Dpwm2Regs.DPWMPRD.bit.PRD = dpwm_timings->min_period;
  Dpwm2Regs.DPWMCYCADJA.bit.CYCLE_ADJUST_A = (int16)(-dpwm_timings->dead_time_2);
  Dpwm2Regs.DPWMCYCADJB.bit.CYCLE_ADJUST_B = (int16)(-dpwm_timings->dead_time_2);
  Dpwm2Regs.DPWMRESDUTY.bit.RESONANT_DUTY  =         (dpwm_timings->max_period + 1) >> 1;  // modulate the duty cycle
  Dpwm2Regs.DPWMAUTOSWHILOWTHRESH.bit.AUTO_SWITCH_HIGH_LOWER = dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm2Regs.DPWMAUTOSWHIUPTHRESH.bit.AUTO_SWITCH_HIGH_UPPER =  dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm2Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm2Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm2Regs.DPWMMINDUTYLO.bit.MIN_DUTY_LOW  =        (dpwm_timings->dead_time_2 + 8) >> 4;
  Dpwm2Regs.DPWMMINDUTYHI.bit.MIN_DUTY_HIGH =        (dpwm_timings->dead_time_2 + 8) >> 4;

  Dpwm3Regs.DPWMEV1.bit.EVENT1 = dead_time_1_local;
  Dpwm3Regs.DPWMEV2.bit.EVENT2 = dpwm_timings->min_period * 8 + dead_time_1_local * 16 - dpwm_timings->dead_time_2;
  Dpwm3Regs.DPWMEV3.bit.EVENT3 = dpwm_timings->min_period * 8 + dead_time_1_local * 16;
  Dpwm3Regs.DPWMEV4.bit.EVENT4 = dpwm_timings->min_period * 16 - dpwm_timings->dead_time_2 + dead_time_1_local * 16;
  Dpwm3Regs.DPWMPRD.bit.PRD = dpwm_timings->min_period;
  Dpwm3Regs.DPWMCYCADJA.bit.CYCLE_ADJUST_A = (int16)(-dpwm_timings->dead_time_2);  //16 bits with signed. Don't apply to resonant mode
  Dpwm3Regs.DPWMCYCADJB.bit.CYCLE_ADJUST_B = (int16)(-dpwm_timings->dead_time_2);
  Dpwm3Regs.DPWMRESDUTY.bit.RESONANT_DUTY  =         (dpwm_timings->max_period + 1) >> 1;  // modulate the duty cycle
  Dpwm3Regs.DPWMAUTOSWHILOWTHRESH.bit.AUTO_SWITCH_HIGH_LOWER = dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm3Regs.DPWMAUTOSWHIUPTHRESH.bit.AUTO_SWITCH_HIGH_UPPER =  dpwm_timings->tsrmax + dead_time_4_local;
  Dpwm3Regs.DPWMAUTOSWLOLOWTHRESH.bit.AUTO_SWITCH_LOW_LOWER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm3Regs.DPWMAUTOSWLOUPTHRESH.bit.AUTO_SWITCH_LOW_UPPER = (dpwm_timings->min_period + 1) >> 1;
  Dpwm3Regs.DPWMMINDUTYLO.bit.MIN_DUTY_LOW  =        (dpwm_timings->dead_time_2 + 8) >> 4;    //18 bits with 4 right shift
  Dpwm3Regs.DPWMMINDUTYHI.bit.MIN_DUTY_HIGH =        (dpwm_timings->dead_time_2 + 8) >> 4;

  Filter0Regs.FILTERYNCLPHI.all = ((int32)((dpwm_timings->min_period  << 4)* PID_PERIOD_FACTOR * 1026)) >> 10;

  Filter0Regs.FILTERYNCLPLO.all = clamp_value;
  Filter1Regs.FILTERYNCLPLO.all = clamp_value;
  

  filter0_pmbus_regs.FILTER_MISC_GAIN.bit.KCOMP           = pmbus_dcdc_config[0].max_period;
  filter0_start_up_pmbus_regs.FILTER_MISC_GAIN.bit.KCOMP  = pmbus_dcdc_config[0].max_period;
  filter0_cp_pmbus_regs.FILTER_MISC_GAIN.bit.KCOMP        = pmbus_dcdc_config[0].max_period;
  filter1_pmbus_regs.FILTER_MISC_GAIN.bit.KCOMP           = pmbus_dcdc_config[0].max_period;


  Filter0Regs.FILTERCTRL.bit.PERIOD_MULT_SEL = 1; // Use KCOM
  LoopMuxRegs.FILTERMUX.bit.FILTER0_KCOMP_SEL = 0;
  LoopMuxRegs.FILTERKCOMPA.bit.KCOMP0 = dpwm_timings->max_period;

  Filter0Regs.FILTERCTRL.bit.OUTPUT_MULT_SEL = 3;   // Use Resonant DUTY
  Dpwm0Regs.DPWMCTRL2.bit.FILTER_DUTY_SEL = 2;
  LoopMuxRegs.FILTERMUX.bit.FILTER0_PER_SEL = 0;//Selects source of switching cycle period for Filter 0 Module


  Dpwm2Regs.DPWMPHASETRIG.all =  (MINPER * 8 + 32);  //180 degree phase offset
  // Connect to dpwm2
  LoopMuxRegs.DPWMMUX.bit.DPWM0_SYNC_SEL = 2;
  // Connect to dpwm2
  LoopMuxRegs.DPWMMUX.bit.DPWM1_SYNC_SEL = 2;
  // Connect to dpwm2
  LoopMuxRegs.DPWMMUX.bit.DPWM3_SYNC_SEL = 2;
}

/*------------------------------------test------------------------------------*/

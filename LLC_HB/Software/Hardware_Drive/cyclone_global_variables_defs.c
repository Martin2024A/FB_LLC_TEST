
/*----------------------------------include-----------------------------------*/
#include "Cyclone_Device.h"
/*-----------------------------------macro------------------------------------*/
// Define Global Peripheral Variables:
//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("AdcRegsFile")
#else
#pragma DATA_SECTION(AdcRegs,"AdcRegsFile");
#endif
volatile struct ADC_REGS AdcRegs;
//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("CimRegsFile")
#else
#pragma DATA_SECTION(CimRegs,"CimRegsFile");
#endif
volatile struct CIM_REGS CimRegs;
//----------------------------------------
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("DecRegsFile")
#else
#pragma DATA_SECTION(DecRegs,"DecRegsFile");
#endif
volatile struct DEC_REGS DecRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Dpwm0RegsFile")
#else
#pragma DATA_SECTION(Dpwm0Regs,"Dpwm0RegsFile");
#endif
volatile struct DPWM_REGS Dpwm0Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Dpwm1RegsFile")
#else
#pragma DATA_SECTION(Dpwm1Regs,"Dpwm1RegsFile");
#endif
volatile struct DPWM_REGS Dpwm1Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Dpwm2RegsFile")
#else
#pragma DATA_SECTION(Dpwm2Regs,"Dpwm2RegsFile");
#endif
volatile struct DPWM_REGS Dpwm2Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Dpwm3RegsFile")
#else
#pragma DATA_SECTION(Dpwm3Regs,"Dpwm3RegsFile");
#endif
volatile struct DPWM_REGS Dpwm3Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("FaultMuxRegsFile")
#else
#pragma DATA_SECTION(FaultMuxRegs,"FaultMuxRegsFile");
#endif
volatile struct FAULT_MUX_REGS FaultMuxRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("FeCtrl0RegsFile")
#else
#pragma DATA_SECTION(FeCtrl0Regs,"FeCtrl0RegsFile");
#endif
volatile struct FE_CTRL_REGS FeCtrl0Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("FeCtrl1RegsFile")
#else
#pragma DATA_SECTION(FeCtrl1Regs,"FeCtrl1RegsFile");
#endif
volatile struct FE_CTRL_REGS FeCtrl1Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("FeCtrl2RegsFile")
#else
#pragma DATA_SECTION(FeCtrl2Regs,"FeCtrl2RegsFile");
#endif
volatile struct FE_CTRL_REGS FeCtrl2Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Filter0RegsFile")
#else
#pragma DATA_SECTION(Filter0Regs,"Filter0RegsFile");
#endif
volatile struct FILTER_REGS Filter0Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Filter1RegsFile")
#else
#pragma DATA_SECTION(Filter1Regs,"Filter1RegsFile");
#endif
volatile struct FILTER_REGS Filter1Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("GioRegsFile")
#else
#pragma DATA_SECTION(GioRegs,"GioRegsFile");
#endif
volatile struct GIO_REGS GioRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Filter2RegsFile")
#else
#pragma DATA_SECTION(Filter2Regs,"Filter2RegsFile");
#endif
volatile struct FILTER_REGS Filter2Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("LoopMuxRegsFile")
#else
#pragma DATA_SECTION(LoopMuxRegs,"LoopMuxRegsFile");
#endif
volatile struct LOOP_MUX_REGS LoopMuxRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("MiscAnalogRegsFile")
#else
#pragma DATA_SECTION(MiscAnalogRegs,"MiscAnalogRegsFile");
#endif
volatile struct MISC_ANALOG_REGS MiscAnalogRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("MmcRegsFile")
#else
#pragma DATA_SECTION(MmcRegs,"MmcRegsFile");
#endif
volatile struct MMC_REGS MmcRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("PMBusRegsFile")
#else
#pragma DATA_SECTION(PMBusRegs,"PMBusRegsFile");
#endif
volatile struct PMBUS_REGS PMBusRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SysRegsFile")
#else
#pragma DATA_SECTION(SysRegs,"SysRegsFile");
#endif
volatile struct SYS_REGS SysRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("TimerRegsFile")
#else
#pragma DATA_SECTION(TimerRegs,"TimerRegsFile");
#endif
volatile struct TIMER_REGS TimerRegs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Uart0RegsFile")
#else
#pragma DATA_SECTION(Uart0Regs,"Uart0RegsFile");
#endif
volatile struct UART_REGS Uart0Regs;
//-------------------------------------------------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("Uart1RegsFile")
#else
#pragma DATA_SECTION(Uart1Regs,"Uart1RegsFile");
#endif
volatile struct UART_REGS Uart1Regs;
/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

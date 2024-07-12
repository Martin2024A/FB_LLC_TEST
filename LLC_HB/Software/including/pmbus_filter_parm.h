#ifndef FILTER_H 
#define FILTER_H 

#ifdef __cplusplus
extern "C"{
#endif

#ifdef MAIN 					// If it is the main routine
	#define EXTERN	 			// If it isn't extern, so define it as nothing
#else 							// If it isn't the main routine
	#define EXTERN extern 		// If it is extern
#endif

/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
/*----------------------------------typedef-----------------------------------*/
//=============================================================================
// Start of filter parameter
//=============================================================================
struct FILTER_MISC_REG_BITS{
    Uint32 rsvd0:28;                // Reserved
	Uint32 AUTO_GEAR_SHIFT:1;		// AUTO_GEAR_SHIFT - configuration bit to control the automatic gear shifting function
	Uint32 AFE_GAIN:2;				// AFE_GAIN - AFE gain
    Uint32 NL_MODE:1;          		// NL_MODE - stored in Filter Control Register
};

union FILTER_MISC_REG{  
    struct FILTER_MISC_REG_BITS bit;
    Uint32                 all;
};

struct FILTER_MISC_GAIN_BITS{
    Uint32 rsvd0:12;    //Reserved
	Uint32 KCOMP:14;	//KCOMP
    Uint32 CLA_SCALE:3;	//CLA_SCALE
    Uint32 YN_SCALE:3;  //YN_SCALE
};

union FILTER_MISC_GAIN{  
    struct FILTER_MISC_GAIN_BITS bit;
    Uint32                 all;
};
//=============================================================================
// Filter Module Register File
//=============================================================================
typedef struct  
{
    union COEFCONFIG_REG        COEFCONFIG;         // Coefficient Configuration Register
    union FILTERKPCOEF0_REG     FILTERKPCOEF0;      // Filter KP Coefficient 0 Register
    union FILTERKPCOEF1_REG     FILTERKPCOEF1;      // Filter KP Coefficient 1 Register
    union FILTERKICOEF0_REG     FILTERKICOEF0;      // Filter KI Coefficient 0 Register
    union FILTERKICOEF1_REG     FILTERKICOEF1;      // Filter KI Coefficient 1 Register
    union FILTERKDCOEF0_REG     FILTERKDCOEF0;      // Filter KD Coefficient 0 Register
    union FILTERKDCOEF1_REG     FILTERKDCOEF1;      // Filter KD Coefficient 1 Register
    union FILTERKDALPHA_REG     FILTERKDALPHA;      // Filter KD Alpha Register
    union FILTERNL0_REG         FILTERNL0;          // Filter Non-Linear Limit 0 Register
    union FILTERNL1_REG         FILTERNL1;          // Filter Non-Linear Limit 1 Register
    union FILTERNL2_REG         FILTERNL2;          // Filter Non-Linear Limit 2 Register
    union FILTERKICLPHI_REG     FILTERKICLPHI;      // Filter KI Feedback Clamp High Register
    union FILTERKICLPLO_REG     FILTERKICLPLO;      // Filter KI Feedback Clamp Low Register
    union FILTERYNCLPHI_REG     FILTERYNCLPHI;      // Filter YN Clamp High Register
    union FILTERYNCLPLO_REG     FILTERYNCLPLO;      // Filter YN Clamp Low Register
	union FILTEROCLPHI_REG		FILTEROCLPHI;       // Filter Output Clamp High Register
	union FILTEROCLPLO_REG		FILTEROCLPLO;       // Filter Output Clamp Low Register
	union FILTER_MISC_REG		FILTER_MISC;        // Miscellaneous bits
	union FILTER_MISC_GAIN		FILTER_MISC_GAIN;   //
}FILTER_PMBUS_REGS;
/*----------------------------------variable----------------------------------*/
//constants.c——Flash
extern volatile const FILTER_PMBUS_REGS filter0_pmbus_regs_constants;
// extern volatile const FILTER_PMBUS_REGS filter0_pmbus_regs_constants_b;
extern volatile const FILTER_PMBUS_REGS filter0_start_up_pmbus_regs_constants;
// extern volatile const FILTER_PMBUS_REGS filter0_start_up_pmbus_regs_constants_b;
extern volatile const FILTER_PMBUS_REGS filter0_cp_pmbus_regs_constants;
// extern volatile const FILTER_PMBUS_REGS filter0_cp_pmbus_regs_constants_b;
extern volatile const FILTER_PMBUS_REGS filter1_pmbus_regs_constants;
// extern volatile const FILTER_PMBUS_REGS filter1_pmbus_regs_constants_b;

//RAM
EXTERN FILTER_PMBUS_REGS filter0_pmbus_regs;
EXTERN FILTER_PMBUS_REGS filter0_start_up_pmbus_regs;
EXTERN FILTER_PMBUS_REGS filter0_cp_pmbus_regs;
EXTERN FILTER_PMBUS_REGS filter1_pmbus_regs;
EXTERN FILTER_PMBUS_REGS *filter_destination;

/*----------------------------------function----------------------------------*/
void copy_coefficients_to_filter(volatile struct FILTER_REGS *dest, const FILTER_PMBUS_REGS *source);
void copy_coefficients_to_ram(volatile FILTER_PMBUS_REGS *dest, volatile struct FILTER_REGS *source);
/*-----------------------------------macro------------------------------------*/
//=============================================================================
// FILTER 0 pmbus controlled coefficients
//=============================================================================
#define INIT_FILTER_0_BIN0_ALPHA (0)           // 3      Bin0 Alpha Configuration
#define INIT_FILTER_0_BIN0_CONFIG (0)          // 2:0    Bin0 Configuration
#define INIT_FILTER_0_BIN1_ALPHA (0)           // 7      Bin1 Alpha Configuration
#define INIT_FILTER_0_BIN1_CONFIG (0)          // 6:4    Bin1 Configuration
#define INIT_FILTER_0_BIN2_ALPHA (0)           // 11     Bin2 Alpha Configuration
#define INIT_FILTER_0_BIN2_CONFIG (0)          // 10:8   Bin2 Configuration
#define INIT_FILTER_0_BIN3_ALPHA (0)           // 15     Bin3 Alpha Configuration
#define INIT_FILTER_0_BIN3_CONFIG (0)          // 14:12  Bin3 Configuration
#define INIT_FILTER_0_BIN4_ALPHA (0)           // 19     Bin4 Alpha Configuration
#define INIT_FILTER_0_BIN4_CONFIG (0)          // 18:16  Bin4 Configuration
#define INIT_FILTER_0_BIN5_ALPHA (0)           // 23     Bin5 Alpha Configuration
#define INIT_FILTER_0_BIN5_CONFIG (0)          // 22:20  Bin5 Configuration
#define INIT_FILTER_0_BIN6_ALPHA (0)           // 27     Bin6 Alpha Configuration
#define INIT_FILTER_0_BIN6_CONFIG (0)          // 26:24  Bin6 Configuration

#define INIT_FILTER_0_KP_COEF_0 (1000) //(1700)	//(10000)//(18781)//(2486)          // 15:0   KP Coefficient 0
#define INIT_FILTER_0_KP_COEF_1 (0)             // 31:16  KP Coefficient 1
#define INIT_FILTER_0_KP_COEF_2 (0)             // 15:0   KP Coefficient 2

#define INIT_FILTER_0_KI_COEF_0 (2000) //(15000)	//(15000)//(115)//(1374)          // 15:0   KI Coefficient 0
#define INIT_FILTER_0_KI_COEF_1 (0)             // 31:16  KI Coefficient 1
#define INIT_FILTER_0_KI_COEF_2 (0)             // 15:0   KI Coefficient 2
#define INIT_FILTER_0_KI_COEF_3 (0)             // 31:16  KI Coefficient 3

#define INIT_FILTER_0_KD_COEF_0 (1500) //(3600)	//(8000)//(7337)//(24969)         // 15:0   KD Coefficient 0
#define INIT_FILTER_0_KD_COEF_1 (0)             // 31:16  KD Coefficient 1
#define INIT_FILTER_0_KD_COEF_2 (0)             // 15:0   KD Coefficient 2

#define INIT_FILTER_0_KD_ALPHA_0 (0)	//(246)//(248)//(0)             // 24:16  KD Alpha 1 Value
#define INIT_FILTER_0_KD_ALPHA_1 (0)             // 8:0    KD Alpha 0 Value

#define INIT_FILTER_0_LIMIT0 (0)              // 8:0    Non-Linear Limit 0 Value
#define INIT_FILTER_0_LIMIT1 (0)              // 24:16  Non-Linear Limit 1 Value
#define INIT_FILTER_0_LIMIT2 (0)              // 8:0    Non-Linear Limit 2 Value
#define INIT_FILTER_0_LIMIT3 (0)              // 24:16  Non-Linear Limit 3 Value
#define INIT_FILTER_0_LIMIT4 (0)              // 8:0    Non-Linear Limit 4 Value
#define INIT_FILTER_0_LIMIT5 (0)              // 24:16  Non-Linear Limit 5 Value


#define INIT_FILTER_0_KI_CLAMP_HIGH (SWITCHING_PERIOD_KI) //(0x7FFFFF)       // 23:0   KI Clamp High
#define INIT_FILTER_0_KI_CLAMP_LOW (0)       // 23:0   KI Clamp Low

#define INIT_FILTER_0_YN_CLAMP_HIGH (SWITCHING_PERIOD_YN_CLAMP) //(0x7FFFFF)//Set to 2^23-1;)       // 23:0   Output Clamp High
#define INIT_FILTER_0_YN_CLAMP_LOW  (180000) //(80000) //(205000) //((int)(DT / TL * ((1<<23) - 1) + 0.5))    //(205000) // // /   // 23:0   Output Clamp Low

#define INIT_FILTER_0_OUTPUT_CLAMP_HIGH (0x3FFFF)
#define INIT_FILTER_0_OUTPUT_CLAMP_LOW  (0) //((int)((MINPER/2)*16-5)) //(0) ZCS feature

#define INIT_FILTER_0_AUTO_GEAR_SHIFT (0)
#define INIT_FILTER_0_AFE_GAIN (3)
#define INIT_FILTER_0_NL_MODE (1)                // written to FILTERCTRL

#define INIT_FILTER_0_KCOMP     (0)
#define INIT_FILTER_0_CLA_SCALE (0)
#define INIT_FILTER_0_YN_SCALE  (0)

//=============================================================================
// FILTER 0  START_UP pmbus controlled coefficients
//=============================================================================
#define INIT_FILTER_0_START_UP_BIN0_ALPHA (0)           // 3      Bin0 Alpha Configuration
#define INIT_FILTER_0_START_UP_BIN0_CONFIG (0)          // 2:0    Bin0 Configuration
#define INIT_FILTER_0_START_UP_BIN1_ALPHA (0)           // 7      Bin1 Alpha Configuration
#define INIT_FILTER_0_START_UP_BIN1_CONFIG (0)          // 6:4    Bin1 Configuration
#define INIT_FILTER_0_START_UP_BIN2_ALPHA (0)           // 11     Bin2 Alpha Configuration
#define INIT_FILTER_0_START_UP_BIN2_CONFIG (0)          // 10:8   Bin2 Configuration
#define INIT_FILTER_0_START_UP_BIN3_ALPHA (0)           // 15     Bin3 Alpha Configuration
#define INIT_FILTER_0_START_UP_BIN3_CONFIG (0)          // 14:12  Bin3 Configuration
#define INIT_FILTER_0_START_UP_BIN4_ALPHA (0)           // 19     Bin4 Alpha Configuration
#define INIT_FILTER_0_START_UP_BIN4_CONFIG (0)          // 18:16  Bin4 Configuration
#define INIT_FILTER_0_START_UP_BIN5_ALPHA (0)           // 23     Bin5 Alpha Configuration
#define INIT_FILTER_0_START_UP_BIN5_CONFIG (0)          // 22:20  Bin5 Configuration
#define INIT_FILTER_0_START_UP_BIN6_ALPHA (0)           // 27     Bin6 Alpha Configuration
#define INIT_FILTER_0_START_UP_BIN6_CONFIG (0)          // 26:24  Bin6 Configuration

#define INIT_FILTER_0_START_UP_KP_COEF_0 (15000)//(7972)          // 15:0   KP Coefficient 0
#define INIT_FILTER_0_START_UP_KP_COEF_1 (0)             // 31:16  KP Coefficient 1
#define INIT_FILTER_0_START_UP_KP_COEF_2 (0)             // 15:0   KP Coefficient 2

#define INIT_FILTER_0_START_UP_KI_COEF_0 (200)//(165)           // 15:0   KI Coefficient 0
#define INIT_FILTER_0_START_UP_KI_COEF_1 (0)             // 31:16  KI Coefficient 1
#define INIT_FILTER_0_START_UP_KI_COEF_2 (0)             // 15:0   KI Coefficient 2
#define INIT_FILTER_0_START_UP_KI_COEF_3 (0)             // 31:16  KI Coefficient 3

#define INIT_FILTER_0_START_UP_KD_COEF_0 (10000)//(24402)         // 15:0   KD Coefficient 0
#define INIT_FILTER_0_START_UP_KD_COEF_1 (0)             // 31:16  KD Coefficient 1
#define INIT_FILTER_0_START_UP_KD_COEF_2 (0)             // 15:0   KD Coefficient 2

#define INIT_FILTER_0_START_UP_KD_ALPHA_0 (248)//(112)          // 24:16  KD Alpha 1 Value
#define INIT_FILTER_0_START_UP_KD_ALPHA_1 (0)            // 8:0    KD Alpha 0 Value

#define INIT_FILTER_0_START_UP_LIMIT0 (0)              // 8:0    Non-Linear Limit 0 Value
#define INIT_FILTER_0_START_UP_LIMIT1 (0)              // 24:16  Non-Linear Limit 1 Value
#define INIT_FILTER_0_START_UP_LIMIT2 (0)              // 8:0    Non-Linear Limit 2 Value
#define INIT_FILTER_0_START_UP_LIMIT3 (0)              // 24:16  Non-Linear Limit 3 Value
#define INIT_FILTER_0_START_UP_LIMIT4 (0)              // 8:0    Non-Linear Limit 4 Value
#define INIT_FILTER_0_START_UP_LIMIT5 (0)              // 24:16  Non-Linear Limit 5 Value


#define INIT_FILTER_0_START_UP_KI_CLAMP_HIGH (0x7FFFFF)       // 23:0   KI Clamp High
#define INIT_FILTER_0_START_UP_KI_CLAMP_LOW (0)       // 23:0   KI Clamp Low

#define INIT_FILTER_0_START_UP_YN_CLAMP_HIGH (0x7FFFFF) //(0x7FFFFF)//Set to 2^23-1;)       // 23:0   Output Clamp High
#define INIT_FILTER_0_START_UP_YN_CLAMP_LOW (70000) //(1000000) //((int)(DT / TL * ((1<<23) - 1) + 0.5))       // 23:0   Output Clamp Low

#define INIT_FILTER_0_START_UP_OUTPUT_CLAMP_HIGH (0x3FFFF)
#define INIT_FILTER_0_START_UP_OUTPUT_CLAMP_LOW  (0)

#define INIT_FILTER_0_START_UP_AUTO_GEAR_SHIFT (0)
#define INIT_FILTER_0_START_UP_AFE_GAIN (3)
#define INIT_FILTER_0_START_UP_NL_MODE (1)                // written to FILTERCTRL

#define INIT_FILTER_0_START_UP_KCOMP     (0)
#define INIT_FILTER_0_START_UP_CLA_SCALE (0)
#define INIT_FILTER_0_START_UP_YN_SCALE  (0)

//=============================================================================
// FILTER 0 CP pmbus controlled coefficients
//=============================================================================
#define INIT_FILTER_0_CP_BIN0_ALPHA (0)           // 3      Bin0 Alpha Configuration
#define INIT_FILTER_0_CP_BIN0_CONFIG (0)          // 2:0    Bin0 Configuration
#define INIT_FILTER_0_CP_BIN1_ALPHA (0)           // 7      Bin1 Alpha Configuration
#define INIT_FILTER_0_CP_BIN1_CONFIG (0)          // 6:4    Bin1 Configuration
#define INIT_FILTER_0_CP_BIN2_ALPHA (0)           // 11     Bin2 Alpha Configuration
#define INIT_FILTER_0_CP_BIN2_CONFIG (0)          // 10:8   Bin2 Configuration
#define INIT_FILTER_0_CP_BIN3_ALPHA (0)           // 15     Bin3 Alpha Configuration
#define INIT_FILTER_0_CP_BIN3_CONFIG (0)          // 14:12  Bin3 Configuration
#define INIT_FILTER_0_CP_BIN4_ALPHA (0)           // 19     Bin4 Alpha Configuration
#define INIT_FILTER_0_CP_BIN4_CONFIG (0)          // 18:16  Bin4 Configuration
#define INIT_FILTER_0_CP_BIN5_ALPHA (0)           // 23     Bin5 Alpha Configuration
#define INIT_FILTER_0_CP_BIN5_CONFIG (0)          // 22:20  Bin5 Configuration
#define INIT_FILTER_0_CP_BIN6_ALPHA (0)           // 27     Bin6 Alpha Configuration
#define INIT_FILTER_0_CP_BIN6_CONFIG (0)          // 26:24  Bin6 Configuration

#define INIT_FILTER_0_CP_KP_COEF_0 (1000)          // 15:0   KP Coefficient 0
#define INIT_FILTER_0_CP_KP_COEF_1 (0)             // 31:16  KP Coefficient 1
#define INIT_FILTER_0_CP_KP_COEF_2 (0)             // 15:0   KP Coefficient 2

#define INIT_FILTER_0_CP_KI_COEF_0 (10)           // 15:0   KI Coefficient 0
#define INIT_FILTER_0_CP_KI_COEF_1 (0)             // 31:16  KI Coefficient 1
#define INIT_FILTER_0_CP_KI_COEF_2 (0)             // 15:0   KI Coefficient 2
#define INIT_FILTER_0_CP_KI_COEF_3 (0)             // 31:16  KI Coefficient 3

#define INIT_FILTER_0_CP_KD_COEF_0 (0)         // 15:0   KD Coefficient 0
#define INIT_FILTER_0_CP_KD_COEF_1 (0)             // 31:16  KD Coefficient 1
#define INIT_FILTER_0_CP_KD_COEF_2 (0)             // 15:0   KD Coefficient 2

#define INIT_FILTER_0_CP_KD_ALPHA_0 (0)          // 24:16  KD Alpha 1 Value
#define INIT_FILTER_0_CP_KD_ALPHA_1 (0)            // 8:0    KD Alpha 0 Value

#define INIT_FILTER_0_CP_LIMIT0 (0)              // 8:0    Non-Linear Limit 0 Value
#define INIT_FILTER_0_CP_LIMIT1 (0)              // 24:16  Non-Linear Limit 1 Value
#define INIT_FILTER_0_CP_LIMIT2 (0)              // 8:0    Non-Linear Limit 2 Value
#define INIT_FILTER_0_CP_LIMIT3 (0)              // 24:16  Non-Linear Limit 3 Value
#define INIT_FILTER_0_CP_LIMIT4 (0)              // 8:0    Non-Linear Limit 4 Value
#define INIT_FILTER_0_CP_LIMIT5 (0)              // 24:16  Non-Linear Limit 5 Value


#define INIT_FILTER_0_CP_KI_CLAMP_HIGH (0x7FFFFF)       // 23:0   KI Clamp High
#define INIT_FILTER_0_CP_KI_CLAMP_LOW (0)       // 23:0   KI Clamp Low

#define INIT_FILTER_0_CP_YN_CLAMP_HIGH (0x7FFFFF)//Set to 2^23-1;)       // 23:0   Output Clamp High
#define INIT_FILTER_0_CP_YN_CLAMP_LOW (70000) //(1000000) //((int)(DT / TL * ((1<<23) - 1) + 0.5))       // 23:0   Output Clamp Low

#define INIT_FILTER_0_CP_OUTPUT_CLAMP_HIGH (0x3FFFF)
#define INIT_FILTER_0_CP_OUTPUT_CLAMP_LOW  (0)

#define INIT_FILTER_0_CP_AUTO_GEAR_SHIFT (0)
#define INIT_FILTER_0_CP_AFE_GAIN (3)
#define INIT_FILTER_0_CP_NL_MODE (1)                // written to FILTERCTRL

#define INIT_FILTER_0_CP_KCOMP     (0)
#define INIT_FILTER_0_CP_CLA_SCALE (0)
#define INIT_FILTER_0_CP_YN_SCALE  (0)

//=============================================================================
// FILTER 1  pmbus controlled coefficients
//=============================================================================
#define INIT_FILTER_1_BIN0_ALPHA (0)           // 3      Bin0 Alpha Configuration
#define INIT_FILTER_1_BIN0_CONFIG (0)          // 2:0    Bin0 Configuration
#define INIT_FILTER_1_BIN1_ALPHA (0)           // 7      Bin1 Alpha Configuration
#define INIT_FILTER_1_BIN1_CONFIG (0)          // 6:4    Bin1 Configuration
#define INIT_FILTER_1_BIN2_ALPHA (0)           // 11     Bin2 Alpha Configuration
#define INIT_FILTER_1_BIN2_CONFIG (0)          // 10:8   Bin2 Configuration
#define INIT_FILTER_1_BIN3_ALPHA (0)           // 15     Bin3 Alpha Configuration
#define INIT_FILTER_1_BIN3_CONFIG (0)          // 14:12  Bin3 Configuration
#define INIT_FILTER_1_BIN4_ALPHA (0)           // 19     Bin4 Alpha Configuration
#define INIT_FILTER_1_BIN4_CONFIG (0)          // 18:16  Bin4 Configuration
#define INIT_FILTER_1_BIN5_ALPHA (0)           // 23     Bin5 Alpha Configuration
#define INIT_FILTER_1_BIN5_CONFIG (0)          // 22:20  Bin5 Configuration
#define INIT_FILTER_1_BIN6_ALPHA (0)           // 27     Bin6 Alpha Configuration
#define INIT_FILTER_1_BIN6_CONFIG (0)          // 26:24  Bin6 Configuration

#define INIT_FILTER_1_KP_COEF_0 (10)             // 15:0   KP Coefficient 0
#define INIT_FILTER_1_KP_COEF_1 (0)             // 31:16  KP Coefficient 1
#define INIT_FILTER_1_KP_COEF_2 (0)             // 15:0   KP Coefficient 2

#define INIT_FILTER_1_KI_COEF_0 (1)             // 15:0   KI Coefficient 0
#define INIT_FILTER_1_KI_COEF_1 (0)             // 31:16  KI Coefficient 1
#define INIT_FILTER_1_KI_COEF_2 (0)             // 15:0   KI Coefficient 2
#define INIT_FILTER_1_KI_COEF_3 (0)             // 31:16  KI Coefficient 3

#define INIT_FILTER_1_KD_COEF_0 (0)             // 15:0   KD Coefficient 0
#define INIT_FILTER_1_KD_COEF_1 (0)             // 31:16  KD Coefficient 1
#define INIT_FILTER_1_KD_COEF_2 (0)             // 15:0   KD Coefficient 2

#define INIT_FILTER_1_KD_ALPHA_0 (0)             // 24:16  KD Alpha 1 Value
#define INIT_FILTER_1_KD_ALPHA_1 (0)             // 8:0    KD Alpha 0 Value

#define INIT_FILTER_1_LIMIT0 (0)              // 8:0    Non-Linear Limit 0 Value
#define INIT_FILTER_1_LIMIT1 (0)              // 24:16  Non-Linear Limit 1 Value
#define INIT_FILTER_1_LIMIT2 (0)              // 8:0    Non-Linear Limit 2 Value
#define INIT_FILTER_1_LIMIT3 (0)              // 24:16  Non-Linear Limit 3 Value
#define INIT_FILTER_1_LIMIT4 (0)              // 8:0    Non-Linear Limit 4 Value
#define INIT_FILTER_1_LIMIT5 (0)              // 24:16  Non-Linear Limit 5 Value


#define INIT_FILTER_1_KI_CLAMP_HIGH (0x7FFFFF)       // 23:0   KI Clamp High
#define INIT_FILTER_1_KI_CLAMP_LOW (0)       // 23:0   KI Clamp Low

#define INIT_FILTER_1_YN_CLAMP_HIGH (0x7FFFFF)//Set to 2^23-1;)       // 23:0   Output Clamp High
#define INIT_FILTER_1_YN_CLAMP_LOW ((int)(DT / TL * ((1<<23) - 1) + 0.5))       // 23:0   Output Clamp Low

#define INIT_FILTER_1_OUTPUT_CLAMP_HIGH (0x3FFFF)
#define INIT_FILTER_1_OUTPUT_CLAMP_LOW  (0)

#define INIT_FILTER_1_AUTO_GEAR_SHIFT (0)
#define INIT_FILTER_1_AFE_GAIN (3)
#define INIT_FILTER_1_NL_MODE (1)                // written to FILTERCTRL

#define INIT_FILTER_1_KCOMP     (0)
#define INIT_FILTER_1_CLA_SCALE (0)
#define INIT_FILTER_1_YN_SCALE  (0)
//=============================================================================
// FILTER struct define
//=============================================================================
#define DEFAULT_FILTER_0_PMBUS_REGS \
{\
	{\
		0,\
	    INIT_FILTER_0_BIN6_ALPHA,\
	    INIT_FILTER_0_BIN6_CONFIG,\
	    INIT_FILTER_0_BIN5_ALPHA,\
	    INIT_FILTER_0_BIN5_CONFIG,\
	    INIT_FILTER_0_BIN4_ALPHA,\
	    INIT_FILTER_0_BIN4_CONFIG,\
	    INIT_FILTER_0_BIN3_ALPHA,\
	    INIT_FILTER_0_BIN3_CONFIG,\
	    INIT_FILTER_0_BIN2_ALPHA,\
	    INIT_FILTER_0_BIN2_CONFIG,\
	    INIT_FILTER_0_BIN1_ALPHA,\
	    INIT_FILTER_0_BIN1_CONFIG,\
	    INIT_FILTER_0_BIN0_ALPHA,\
	    INIT_FILTER_0_BIN0_CONFIG\
	},\
	{\
		INIT_FILTER_0_KP_COEF_1,\
	    INIT_FILTER_0_KP_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_KP_COEF_2\
	},\
	{\
		INIT_FILTER_0_KI_COEF_1,\
	    INIT_FILTER_0_KI_COEF_0\
	},\
	{\
		INIT_FILTER_0_KI_COEF_3,\
	    INIT_FILTER_0_KI_COEF_2\
	},\
	{\
		INIT_FILTER_0_KD_COEF_1,\
	    INIT_FILTER_0_KD_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_KD_COEF_2\
	},\
	{\
		0,\
		INIT_FILTER_0_KD_ALPHA_1,\
		0,\
	    INIT_FILTER_0_KD_ALPHA_0\
	},\
	{\
		0,\
		INIT_FILTER_0_LIMIT1,\
		0,\
	    INIT_FILTER_0_LIMIT0\
	},\
	{\
		0,\
		INIT_FILTER_0_LIMIT3,\
		0,\
	    INIT_FILTER_0_LIMIT2\
	},\
	{\
		0,\
		INIT_FILTER_0_LIMIT5,\
		0,\
	    INIT_FILTER_0_LIMIT4\
	},\
	{\
		0,\
	    INIT_FILTER_0_KI_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_KI_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_YN_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_YN_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_OUTPUT_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_OUTPUT_CLAMP_LOW\
	},\
	{\
		0,\
		INIT_FILTER_0_AUTO_GEAR_SHIFT,\
		INIT_FILTER_0_AFE_GAIN,\
	    INIT_FILTER_0_NL_MODE\
	},\
	{\
		0,\
		INIT_FILTER_0_KCOMP,\
		INIT_FILTER_0_CLA_SCALE,\
		INIT_FILTER_0_YN_SCALE\
	},\
}

#define DEFAULT_FILTER_0_START_UP_PMBUS_REGS \
{\
	{\
		0,\
	    INIT_FILTER_0_START_UP_BIN6_ALPHA,\
	    INIT_FILTER_0_START_UP_BIN6_CONFIG,\
	    INIT_FILTER_0_START_UP_BIN5_ALPHA,\
	    INIT_FILTER_0_START_UP_BIN5_CONFIG,\
	    INIT_FILTER_0_START_UP_BIN4_ALPHA,\
	    INIT_FILTER_0_START_UP_BIN4_CONFIG,\
	    INIT_FILTER_0_START_UP_BIN3_ALPHA,\
	    INIT_FILTER_0_START_UP_BIN3_CONFIG,\
	    INIT_FILTER_0_START_UP_BIN2_ALPHA,\
	    INIT_FILTER_0_START_UP_BIN2_CONFIG,\
	    INIT_FILTER_0_START_UP_BIN1_ALPHA,\
	    INIT_FILTER_0_START_UP_BIN1_CONFIG,\
	    INIT_FILTER_0_START_UP_BIN0_ALPHA,\
	    INIT_FILTER_0_START_UP_BIN0_CONFIG\
	},\
	{\
		INIT_FILTER_0_START_UP_KP_COEF_1,\
	    INIT_FILTER_0_START_UP_KP_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_KP_COEF_2\
	},\
	{\
		INIT_FILTER_0_START_UP_KI_COEF_1,\
	    INIT_FILTER_0_START_UP_KI_COEF_0\
	},\
	{\
		INIT_FILTER_0_START_UP_KI_COEF_3,\
	    INIT_FILTER_0_START_UP_KI_COEF_2\
	},\
	{\
		INIT_FILTER_0_START_UP_KD_COEF_1,\
	    INIT_FILTER_0_START_UP_KD_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_KD_COEF_2\
	},\
	{\
		0,\
		INIT_FILTER_0_START_UP_KD_ALPHA_1,\
		0,\
	    INIT_FILTER_0_START_UP_KD_ALPHA_0\
	},\
	{\
		0,\
		INIT_FILTER_0_START_UP_LIMIT1,\
		0,\
	    INIT_FILTER_0_START_UP_LIMIT0\
	},\
	{\
		0,\
		INIT_FILTER_0_START_UP_LIMIT3,\
		0,\
	    INIT_FILTER_0_START_UP_LIMIT2\
	},\
	{\
		0,\
		INIT_FILTER_0_START_UP_LIMIT5,\
		0,\
	    INIT_FILTER_0_START_UP_LIMIT4\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_KI_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_KI_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_YN_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_YN_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_OUTPUT_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_START_UP_OUTPUT_CLAMP_LOW\
	},\
	{\
		0,\
		INIT_FILTER_0_START_UP_AUTO_GEAR_SHIFT,\
		INIT_FILTER_0_START_UP_AFE_GAIN,\
	    INIT_FILTER_0_START_UP_NL_MODE\
	},\
	{\
		0,\
		INIT_FILTER_0_START_UP_KCOMP,\
		INIT_FILTER_0_START_UP_CLA_SCALE,\
		INIT_FILTER_0_START_UP_YN_SCALE\
	},\
}

#define DEFAULT_FILTER_0_CP_PMBUS_REGS \
{\
	{\
		0,\
	    INIT_FILTER_0_CP_BIN6_ALPHA,\
	    INIT_FILTER_0_CP_BIN6_CONFIG,\
	    INIT_FILTER_0_CP_BIN5_ALPHA,\
	    INIT_FILTER_0_CP_BIN5_CONFIG,\
	    INIT_FILTER_0_CP_BIN4_ALPHA,\
	    INIT_FILTER_0_CP_BIN4_CONFIG,\
	    INIT_FILTER_0_CP_BIN3_ALPHA,\
	    INIT_FILTER_0_CP_BIN3_CONFIG,\
	    INIT_FILTER_0_CP_BIN2_ALPHA,\
	    INIT_FILTER_0_CP_BIN2_CONFIG,\
	    INIT_FILTER_0_CP_BIN1_ALPHA,\
	    INIT_FILTER_0_CP_BIN1_CONFIG,\
	    INIT_FILTER_0_CP_BIN0_ALPHA,\
	    INIT_FILTER_0_CP_BIN0_CONFIG\
	},\
	{\
		INIT_FILTER_0_CP_KP_COEF_1,\
	    INIT_FILTER_0_CP_KP_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_KP_COEF_2\
	},\
	{\
		INIT_FILTER_0_CP_KI_COEF_1,\
	    INIT_FILTER_0_CP_KI_COEF_0\
	},\
	{\
		INIT_FILTER_0_CP_KI_COEF_3,\
	    INIT_FILTER_0_CP_KI_COEF_2\
	},\
	{\
		INIT_FILTER_0_CP_KD_COEF_1,\
	    INIT_FILTER_0_CP_KD_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_KD_COEF_2\
	},\
	{\
		0,\
		INIT_FILTER_0_CP_KD_ALPHA_1,\
		0,\
	    INIT_FILTER_0_CP_KD_ALPHA_0\
	},\
	{\
		0,\
		INIT_FILTER_0_CP_LIMIT1,\
		0,\
	    INIT_FILTER_0_CP_LIMIT0\
	},\
	{\
		0,\
		INIT_FILTER_0_CP_LIMIT3,\
		0,\
	    INIT_FILTER_0_CP_LIMIT2\
	},\
	{\
		0,\
		INIT_FILTER_0_CP_LIMIT5,\
		0,\
	    INIT_FILTER_0_CP_LIMIT4\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_KI_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_KI_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_YN_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_YN_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_OUTPUT_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_CP_OUTPUT_CLAMP_LOW\
	},\
	{\
		0,\
		INIT_FILTER_0_CP_AUTO_GEAR_SHIFT,\
		INIT_FILTER_0_CP_AFE_GAIN,\
	    INIT_FILTER_0_CP_NL_MODE\
	},\
	{\
		0,\
		INIT_FILTER_0_CP_KCOMP,\
		INIT_FILTER_0_CP_CLA_SCALE,\
		INIT_FILTER_0_CP_YN_SCALE\
	},\
}

#define DEFAULT_FILTER_1_PMBUS_REGS \
{\
	{\
		0,\
	    INIT_FILTER_1_BIN6_ALPHA,\
	    INIT_FILTER_1_BIN6_CONFIG,\
	    INIT_FILTER_1_BIN5_ALPHA,\
	    INIT_FILTER_1_BIN5_CONFIG,\
	    INIT_FILTER_1_BIN4_ALPHA,\
	    INIT_FILTER_1_BIN4_CONFIG,\
	    INIT_FILTER_1_BIN3_ALPHA,\
	    INIT_FILTER_1_BIN3_CONFIG,\
	    INIT_FILTER_1_BIN2_ALPHA,\
	    INIT_FILTER_1_BIN2_CONFIG,\
	    INIT_FILTER_1_BIN1_ALPHA,\
	    INIT_FILTER_1_BIN1_CONFIG,\
	    INIT_FILTER_1_BIN0_ALPHA,\
	    INIT_FILTER_1_BIN0_CONFIG\
	},\
	{\
		INIT_FILTER_1_KP_COEF_1,\
	    INIT_FILTER_1_KP_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_1_KP_COEF_2\
	},\
	{\
		INIT_FILTER_1_KI_COEF_1,\
	    INIT_FILTER_1_KI_COEF_0\
	},\
	{\
		INIT_FILTER_1_KI_COEF_3,\
	    INIT_FILTER_1_KI_COEF_2\
	},\
	{\
		INIT_FILTER_1_KD_COEF_1,\
	    INIT_FILTER_1_KD_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_1_KD_COEF_2\
	},\
	{\
		0,\
		INIT_FILTER_1_KD_ALPHA_1,\
		0,\
	    INIT_FILTER_1_KD_ALPHA_0\
	},\
	{\
		0,\
		INIT_FILTER_1_LIMIT1,\
		0,\
	    INIT_FILTER_1_LIMIT0\
	},\
	{\
		0,\
		INIT_FILTER_1_LIMIT3,\
		0,\
	    INIT_FILTER_1_LIMIT2\
	},\
	{\
		0,\
		INIT_FILTER_1_LIMIT5,\
		0,\
	    INIT_FILTER_1_LIMIT4\
	},\
	{\
		0,\
	    INIT_FILTER_1_KI_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_1_KI_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_1_YN_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_1_YN_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_1_OUTPUT_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_1_OUTPUT_CLAMP_LOW\
	},\
	{\
		0,\
		INIT_FILTER_1_AUTO_GEAR_SHIFT,\
		INIT_FILTER_1_AFE_GAIN,\
	    INIT_FILTER_1_NL_MODE\
	},\
	{\
		0,\
		INIT_FILTER_1_KCOMP,\
		INIT_FILTER_1_CLA_SCALE,\
		INIT_FILTER_1_YN_SCALE\
	},\
}
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* FILTER_H */

#ifndef PMBUS_COMMON_H 
#define PMBUS_COMMON_H 

#ifdef __cplusplus
extern "C"{
#endif

#ifdef MAIN 					// If it is the main routine
	#define EXTERN	 			// If it isn't extern, so define it as nothing
#else 							// If it isn't the main routine
	#define EXTERN extern 		// If it is extern
#endif
/*

*/
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "device.h"
/*-----------------------------------macro------------------------------------*/
#define min(a,b)  (((a)>(b)) ? (b):(a))
#define max(a,b)  (((a)>(b)) ? (a):(b))
#define PMBUS_SUCCESS               0
//PMBus State
#define PMBUS_STATE_IDLE 0
#define PMBUS_STATE_WRITE_BLOCK 1
#define PMBUS_STATE_READ_BLOCK 2
#define PMBUS_STATE_READ_WAIT_FOR_EOM 3

//PMBus Flag
// ***KKN***HEM	It would be nice to get rid of these _BYTE0_ and _HALF0_ values.
// *** 			Requires change to _ALL_ in multiple places in pmbus.c.
#define PMBST_HALF0_MASTER					(0x8000)		// 15  Master/Slave mode flag
#define PMBST_HALF0_LOST_ARB				(0x4000)		// 14  Lost arbitration flag
#define PMBST_HALF0_BUS_FREE				(0x2000)		// 13  Bus free flag
#define PMBST_HALF0_UNIT_BUSY				(0x1000)		// 12  Unit busy flag
#define PMBST_HALF0_RPT_START				(0x0800)		// 11  Repeated start condition flag
#define PMBST_HALF0_SLAVE_ADDR_READY		(0x0400)		// 10  Slave address ready flag
#define PMBST_HALF0_CLK_HIGH_TIMEOUT		(0x0200)		// 9   Clock high timeout flag
#define PMBST_HALF0_CLK_LOW_TIMEOUT			(0x0100)		// 8   Clock low timeout flag
#define PMBST_HALF0_PEC_VALID				(0x0080)		// 7   PEC valid flag
#define PMBST_HALF0_NACK					(0x0040)		// 6   NACK condition received flag
#define PMBST_HALF0_EOM						(0x0020)		// 5   End of message flag
#define PMBST_HALF0_DATA_REQUEST			(0x0010)		// 4   Data request flag
#define PMBST_HALF0_DATA_READY				(0x0008)		// 3   Data ready flag
#define PMBST_HALF0_RD_BYTE_COUNT			(0x0007)		// 2:0 Read byte count mask

#define PMBST_BYTE0_PEC_VALID				(0x80)			// 7   PEC valid flag
#define PMBST_BYTE0_NACK					(0x40)			// 6   NACK condition received flag
#define PMBST_BYTE0_EOM						(0x20)			// 5   End of message flag
#define PMBST_BYTE0_DATA_REQUEST			(0x10)			// 4   Data request flag
#define PMBST_BYTE0_DATA_READY				(0x08)			// 3   Data ready flag
#define PMBST_BYTE0_RD_BYTE_COUNT			(0x07)			// 2:0 Read byte count mask

#define PMBST_HALF0_CHECK_BITS \
    (PMBST_BYTE0_EOM + \
     PMBST_BYTE0_DATA_READY + \
     PMBST_BYTE0_DATA_REQUEST + \
     PMBST_BYTE0_PEC_VALID + \
     PMBST_HALF0_CLK_LOW_TIMEOUT + \
     PMBST_HALF0_CLK_HIGH_TIMEOUT)


// PMBCTRL2 Register
#define PMBCTRL2_ALL_RX_BYTE_ACK_CNT		(0x00600000)	// 22:21  Received byte acknowledge count
#define PMBCTRL2_BYTE2_TX_PEC				(0x08)			// 19     Transmited PEC flag
#define PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT		(0x60)			// 22:21  Received byte acknowledge count


#define PMBUS_BUFFER_SIZE 50



EXTERN Uint8  				debug_buffer[8];
#define DEBUG_0_TEXT "Debug 0"
#define DEBUG_1_TEXT "Debug 1"
#define DEBUG_2_TEXT "Debug 2"
#define DEBUG_3_TEXT "Debug 3"
#define DEBUG_4_TEXT "Debug 4"
#define DEBUG_5_TEXT "Debug 5"
#define DEBUG_6_TEXT "Debug 6"
#define DEBUG_7_TEXT "Debug 7"
EXTERN Uint8 gui_constant_pointer;
EXTERN Uint8 user_ram_00;
/*----------------------------------typedef-----------------------------------*/
#define	CML_INVALID_CMD			(7)		// Invalid or Unsupported Command Received
#define	CML_INVALID_DATA		(6)		// Invalid or Unsupported Data Received
#define	CML_PEC_FAILED			(5)		// Packet Error Check Failed
#define	CML_MEMORY_FAULT	  	(4)		// Memory Fault Detected
#define	CML_PROC_FAULT			(3)		// Processor Fault Detected
#define	CML_RSVD2 				(2)		// Reserved
#define	CML_COMM_OTHER_FAULT	(1)		// Unlisted communication fault
#define	CML_OTHER_FAULT			(0)		// Other Memory or Logic fault has occurred
// These error codes are masks based on bits in the CML_STATUS byte.  This allows the
// pmbus_error_handler() function to do a simple 'OR' instead of a big 'switch' statement.
#define	PMBUS_INVALID_CMD		(1<<CML_INVALID_CMD)		// bit7 Invalid or Unsupported Command Received
#define	PMBUS_INVALID_DATA		(1<<CML_INVALID_DATA)		// bit6 Invalid or Unsupported Data Received
#define	PMBUS_PEC_FAILED		(1<<CML_PEC_FAILED)			// bit5 Packet Error Check Failed
#define	PMBUS_MEMORY_FAULT	 	(1<<CML_MEMORY_FAULT)	  	// bit4 Memory Fault Detected
#define	PMBUS_PROC_FAULT		(1<<CML_PROC_FAULT)			// bit3 Processor Fault Detected
#define	PMBUS_RSVD2 			(1<<CML_RSVD2) 				// bit2 Reserved
#define	PMBUS_COMM_OTHER_FAULT	(1<<CML_COMM_OTHER_FAULT)	// bit1 Unlisted communication fault
#define	PMBUS_OTHER_FAULT		(1<<CML_OTHER_FAULT)		// bit0 Other Memory or Logic fault has occurred

EXTERN	Uint8	parm_index;
EXTERN	int16	parm_offset;
EXTERN	Uint8	parm_count;
EXTERN	Uint8	parm_size;
/*----------------------------------variable----------------------------------*/
EXTERN Uint8 pmbus_state;
EXTERN Uint16 pmbus_status_half_word_0_value_ored; //for debug
EXTERN Uint8 pmbus_buffer[PMBUS_BUFFER_SIZE];
EXTERN Uint8 pmbus_number_of_bytes;
EXTERN Uint8 pmbus_buffer_position;
/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void pmbus_handler(void);
void pmbus_write_block_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes);
void pmbus_idle_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes);
void pmbus_read_block_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes);
void pmbus_read_wait_for_eom_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes);
void init_pmbus(int32 pmbus_address);

Uint8 pmbus_read_write_message(Uint8 pmbus_read);

void init_pmbus(int32 pmbus_address);
//##############################################################################
//                      device and software information
//##############################################################################
Uint8 pmbus_read_device_id(void);
Uint8 pmbus_invalid_write(void);
Uint8 pmbus_read_mfr_id(void);
Uint8 pmbus_read_setup_id(void);
Uint8 pmbus_read_mfr_model(void);
Uint8 pmbus_read_mfr_revision(void);
Uint8 pmbus_read_mfr_date(void);
Uint8 pmbus_read_mfr_location(void);
Uint8 pmbus_read_mfr_serial(void);
Uint8 pmbus_read_mfr_ic_device(void);
/*----------------------------------------------------------------------------*/
Uint8 pmbus_read_write_device_id(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_id(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_setup_id(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_model(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_revision(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_date(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_location(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_serial(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_ic_device(Uint8 pmbus_read);
Uint8 pmbus_read_write_mfr_ic_device_rev(Uint8 pmbus_read);

//##############################################################################
//                      pmbus read write
//##############################################################################
void watchdog_reset(void);
int32 pmbus_read_one_byte_handler(Uint8 value);
int32 pmbus_read_two_byte_handler(Uint16 value);
Uint8 pmbus_invalid_read(void);
void send_string(const Uint8 string_to_send[], Uint8 num_bytes);
Uint8 pmbus_read_debug_buffer(void);
Uint8 pmbus_write_gui_constant(void);//Don't be used!
Uint8 pmbus_write_user_ram_00(void);
Uint8 pmbus_read_user_ram_00(void);
int pmbus_write_rom_mode(void);
/*----------------------------------------------------------------------------*/
Uint8 pmbus_read_write_invalid_command(Uint8 pmbus_read);
Uint8 pmbus_read_write_debug_buffer(Uint8 pmbus_read);
Uint8 pmbus_read_write_user_ram_00(Uint8 pmbus_read);
Uint8 pmbus_read_write_rom_mode(Uint8 pmbus_read);

//##############################################################################
//                      pmbus read write Register
//##############################################################################
Uint8 pmbus_write_parm_info(void);
Uint8 pmbus_read_parm_info(void);
Uint8 pmbus_write_parm_value(void);
Uint8 pmbus_read_parm_value(void);

/*----------------------------------------------------------------------------*/
Uint8 pmbus_read_write_parm_info(Uint8 pmbus_read);
Uint8 pmbus_read_write_parm_value(Uint8 pmbus_read);
Uint8 pmbus_read_write_pmbus_revision(Uint8 pmbus_read);
Uint8 pmbus_read_write_capability(Uint8 pmbus_read);

//##############################################################################
//                      command
//##############################################################################
#define PMBUS_READ	(1)
#define PMBUS_WRITE	(0)

#define QUERY_COMMAND_SUPPORTED 0x80
#define QUERY_WRITE_SUPPORTED 	0x40
#define QUERY_READ_SUPPORTED 	0x20

#define QUERY_LINEAR 		0x00   //000 Linear Data Format used
#define QUERY_16_BIT_SIGNED 0x04  //001 16 bit signed number
                                    //010 Reserved
#define QUERY_DIRECT_MODE 		0x0C   //011 Direct Mode Format used
#define QUERY_8_BIT_UNSIGNED 	0x10 // 100 8 bit unsigned number
#define QUERY_VID 				0x14 //101 VID Mode Format used
#define QUERY_MAN_SPEC 			0x18 //110 Manufacturer specific format used
#define QUERY_NON_NUMERIC 		0x1C //111 Command does not return numeric data.
										//This is also used for commands that return blocks of data.
#define INVALID_COMMAND_INDEX	(0)

#define PMBUS_INVALID_COMMAND_FUNCTION_POINTER pmbus_read_write_invalid_command
#define PMBUS_INVALID_COMMAND_QUERY (0)

#define PMBUS_CMD_19_FUNCTION_POINTER pmbus_read_write_capability
#define PMBUS_CMD_19_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_98_FUNCTION_POINTER pmbus_read_write_pmbus_revision
#define PMBUS_CMD_98_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_99_FUNCTION_POINTER pmbus_read_write_mfr_id
#define PMBUS_CMD_99_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_9A_FUNCTION_POINTER pmbus_read_write_mfr_model
#define PMBUS_CMD_9A_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_9B_FUNCTION_POINTER pmbus_read_write_mfr_revision
#define PMBUS_CMD_9B_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_9C_FUNCTION_POINTER pmbus_read_write_mfr_location
#define PMBUS_CMD_9C_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_9D_FUNCTION_POINTER pmbus_read_write_mfr_date
#define PMBUS_CMD_9D_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_9E_FUNCTION_POINTER pmbus_read_write_mfr_serial
#define PMBUS_CMD_9E_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_AD_FUNCTION_POINTER pmbus_read_write_mfr_ic_device
#define PMBUS_CMD_AD_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_AE_FUNCTION_POINTER pmbus_read_write_mfr_ic_device_rev
#define PMBUS_CMD_AE_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_D9_FUNCTION_POINTER pmbus_read_write_rom_mode
#define PMBUS_CMD_D9_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_WRITE_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_DA_FUNCTION_POINTER pmbus_read_write_user_ram_00
#define PMBUS_CMD_DA_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_WRITE_SUPPORTED + QUERY_8_BIT_UNSIGNED)

#define PMBUS_CMD_E2_FUNCTION_POINTER pmbus_read_write_parm_info
#define PMBUS_CMD_E2_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_WRITE_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_MAN_SPEC)

#define PMBUS_CMD_E3_FUNCTION_POINTER pmbus_read_write_parm_value
#define PMBUS_CMD_E3_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_WRITE_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_MAN_SPEC)

#define PMBUS_CMD_E7_FUNCTION_POINTER pmbus_read_write_mfr_setup_id
#define PMBUS_CMD_E7_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_F0_FUNCTION_POINTER pmbus_read_write_debug_buffer
#define PMBUS_CMD_F0_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)

#define PMBUS_CMD_FD_FUNCTION_POINTER pmbus_read_write_device_id
#define PMBUS_CMD_FD_QUERY (QUERY_COMMAND_SUPPORTED + QUERY_READ_SUPPORTED + QUERY_NON_NUMERIC)


#define PMBUS_CMD_00_ENABLE (0)
#define PMBUS_CMD_01_ENABLE (0)
#define PMBUS_CMD_02_ENABLE (0)
#define PMBUS_CMD_03_ENABLE (0)//
#define PMBUS_CMD_04_ENABLE (0)
#define PMBUS_CMD_05_ENABLE (0)
#define PMBUS_CMD_06_ENABLE (0)
#define PMBUS_CMD_07_ENABLE (0)
#define PMBUS_CMD_08_ENABLE (0)
#define PMBUS_CMD_09_ENABLE (0)
#define PMBUS_CMD_0A_ENABLE (0)
#define PMBUS_CMD_0B_ENABLE (0)
#define PMBUS_CMD_0C_ENABLE (0)
#define PMBUS_CMD_0D_ENABLE (0)
#define PMBUS_CMD_0E_ENABLE (0)
#define PMBUS_CMD_0F_ENABLE (0)
#define PMBUS_CMD_10_ENABLE (0)
#define PMBUS_CMD_11_ENABLE (0)//
#define PMBUS_CMD_12_ENABLE (0)//
#define PMBUS_CMD_13_ENABLE (0)
#define PMBUS_CMD_14_ENABLE (0)
#define PMBUS_CMD_15_ENABLE (0)
#define PMBUS_CMD_16_ENABLE (0)
#define PMBUS_CMD_17_ENABLE (0)
#define PMBUS_CMD_18_ENABLE (0)
#define PMBUS_CMD_19_ENABLE (1)
#define PMBUS_CMD_1A_ENABLE (0)
#define PMBUS_CMD_1B_ENABLE (0)
#define PMBUS_CMD_1C_ENABLE (0)
#define PMBUS_CMD_1D_ENABLE (0)
#define PMBUS_CMD_1E_ENABLE (0)
#define PMBUS_CMD_1F_ENABLE (0)
#define PMBUS_CMD_20_ENABLE (0)//
#define PMBUS_CMD_21_ENABLE (0)//
#define PMBUS_CMD_22_ENABLE (0)
#define PMBUS_CMD_23_ENABLE (0)
#define PMBUS_CMD_24_ENABLE (0)
#define PMBUS_CMD_25_ENABLE (0)
#define PMBUS_CMD_26_ENABLE (0)
#define PMBUS_CMD_27_ENABLE (0)//
#define PMBUS_CMD_28_ENABLE (0)
#define PMBUS_CMD_29_ENABLE (0)
#define PMBUS_CMD_2A_ENABLE (0)
#define PMBUS_CMD_2B_ENABLE (0)
#define PMBUS_CMD_2C_ENABLE (0)
#define PMBUS_CMD_2D_ENABLE (0)
#define PMBUS_CMD_2E_ENABLE (0)
#define PMBUS_CMD_2F_ENABLE (0)
#define PMBUS_CMD_30_ENABLE (0)
#define PMBUS_CMD_31_ENABLE (0)
#define PMBUS_CMD_32_ENABLE (0)
#define PMBUS_CMD_33_ENABLE (0)//
#define PMBUS_CMD_34_ENABLE (0)
#define PMBUS_CMD_35_ENABLE (0)//
#define PMBUS_CMD_36_ENABLE (0)//
#define PMBUS_CMD_37_ENABLE (0)
#define PMBUS_CMD_38_ENABLE (0)
#define PMBUS_CMD_39_ENABLE (0)
#define PMBUS_CMD_3A_ENABLE (0)
#define PMBUS_CMD_3B_ENABLE (0)
#define PMBUS_CMD_3C_ENABLE (0)
#define PMBUS_CMD_3D_ENABLE (0)
#define PMBUS_CMD_3E_ENABLE (0)
#define PMBUS_CMD_3F_ENABLE (0)
#define PMBUS_CMD_40_ENABLE (0)//
#define PMBUS_CMD_41_ENABLE (0)
#define PMBUS_CMD_42_ENABLE (0) //1
#define PMBUS_CMD_43_ENABLE (0)//
#define PMBUS_CMD_44_ENABLE (0)//
#define PMBUS_CMD_45_ENABLE (0)//
#define PMBUS_CMD_46_ENABLE (0)//
#define PMBUS_CMD_47_ENABLE (0)//
#define PMBUS_CMD_48_ENABLE (0)
#define PMBUS_CMD_49_ENABLE (0)
#define PMBUS_CMD_4A_ENABLE (0)   //Iout warning
#define PMBUS_CMD_4B_ENABLE (0)
#define PMBUS_CMD_4C_ENABLE (0)
#define PMBUS_CMD_4D_ENABLE (0)
#define PMBUS_CMD_4E_ENABLE (0)
#define PMBUS_CMD_4F_ENABLE (0)//
#define PMBUS_CMD_50_ENABLE (0)
#define PMBUS_CMD_51_ENABLE (0)  //1
#define PMBUS_CMD_52_ENABLE (0)
#define PMBUS_CMD_53_ENABLE (0)
#define PMBUS_CMD_54_ENABLE (0)
#define PMBUS_CMD_55_ENABLE (0)//
#define PMBUS_CMD_56_ENABLE (0)
#define PMBUS_CMD_57_ENABLE (0)  //1
#define PMBUS_CMD_58_ENABLE (0)   //1
#define PMBUS_CMD_59_ENABLE (0)//
#define PMBUS_CMD_5A_ENABLE (0)
#define PMBUS_CMD_5B_ENABLE (0)   
#define PMBUS_CMD_5C_ENABLE (0)
#define PMBUS_CMD_5D_ENABLE (0)   
#define PMBUS_CMD_5E_ENABLE (0)//
#define PMBUS_CMD_5F_ENABLE (0)//
#define PMBUS_CMD_60_ENABLE (0)
#define PMBUS_CMD_61_ENABLE (0)//
#define PMBUS_CMD_62_ENABLE (0)
#define PMBUS_CMD_63_ENABLE (0)
#define PMBUS_CMD_64_ENABLE (0)
#define PMBUS_CMD_65_ENABLE (0)
#define PMBUS_CMD_66_ENABLE (0)
#define PMBUS_CMD_67_ENABLE (0)
#define PMBUS_CMD_68_ENABLE (0)
#define PMBUS_CMD_69_ENABLE (0)
#define PMBUS_CMD_6A_ENABLE (0)
#define PMBUS_CMD_6B_ENABLE (0)
#define PMBUS_CMD_6C_ENABLE (0)
#define PMBUS_CMD_6D_ENABLE (0)
#define PMBUS_CMD_6E_ENABLE (0)
#define PMBUS_CMD_6F_ENABLE (0)
#define PMBUS_CMD_70_ENABLE (0)
#define PMBUS_CMD_71_ENABLE (0)
#define PMBUS_CMD_72_ENABLE (0)
#define PMBUS_CMD_73_ENABLE (0)
#define PMBUS_CMD_74_ENABLE (0)
#define PMBUS_CMD_75_ENABLE (0)
#define PMBUS_CMD_76_ENABLE (0)
#define PMBUS_CMD_77_ENABLE (0)
#define PMBUS_CMD_78_ENABLE (0)//
#define PMBUS_CMD_79_ENABLE (0)//
#define PMBUS_CMD_7A_ENABLE (0)
#define PMBUS_CMD_7B_ENABLE (0)
#define PMBUS_CMD_7C_ENABLE (0)
#define PMBUS_CMD_7D_ENABLE (0)
#define PMBUS_CMD_7E_ENABLE (0)
#define PMBUS_CMD_7F_ENABLE (0)
#define PMBUS_CMD_80_ENABLE (0)
#define PMBUS_CMD_81_ENABLE (0)
#define PMBUS_CMD_82_ENABLE (0)
#define PMBUS_CMD_83_ENABLE (0)
#define PMBUS_CMD_84_ENABLE (0)
#define PMBUS_CMD_85_ENABLE (0)
#define PMBUS_CMD_86_ENABLE (0)
#define PMBUS_CMD_87_ENABLE (0)
#define PMBUS_CMD_88_ENABLE (0)//
#define PMBUS_CMD_89_ENABLE (0)
#define PMBUS_CMD_8A_ENABLE (0)
#define PMBUS_CMD_8B_ENABLE (0)//
#define PMBUS_CMD_8C_ENABLE (0)//
#define PMBUS_CMD_8D_ENABLE (0)//
#define PMBUS_CMD_8E_ENABLE (0)  //(1)  Devcie temperature
#define PMBUS_CMD_8F_ENABLE (0)
#define PMBUS_CMD_90_ENABLE (0)
#define PMBUS_CMD_91_ENABLE (0)
#define PMBUS_CMD_92_ENABLE (0)
#define PMBUS_CMD_93_ENABLE (0)
#define PMBUS_CMD_94_ENABLE (0)
#define PMBUS_CMD_95_ENABLE (0)   //1
#define PMBUS_CMD_96_ENABLE (0)
#define PMBUS_CMD_97_ENABLE (0)
#define PMBUS_CMD_98_ENABLE (1) //done
#define PMBUS_CMD_99_ENABLE (1)
#define PMBUS_CMD_9A_ENABLE (1)
#define PMBUS_CMD_9B_ENABLE (1)
#define PMBUS_CMD_9C_ENABLE (1)
#define PMBUS_CMD_9D_ENABLE (1)
#define PMBUS_CMD_9E_ENABLE (1)
#define PMBUS_CMD_9F_ENABLE (0)
#define PMBUS_CMD_A0_ENABLE (0)
#define PMBUS_CMD_A1_ENABLE (0)
#define PMBUS_CMD_A2_ENABLE (0)
#define PMBUS_CMD_A3_ENABLE (0)
#define PMBUS_CMD_A4_ENABLE (0)
#define PMBUS_CMD_A5_ENABLE (0)
#define PMBUS_CMD_A6_ENABLE (0)
#define PMBUS_CMD_A7_ENABLE (0)
#define PMBUS_CMD_A8_ENABLE (0)
#define PMBUS_CMD_A9_ENABLE (0)
#define PMBUS_CMD_AA_ENABLE (0)
#define PMBUS_CMD_AB_ENABLE (0)
#define PMBUS_CMD_AC_ENABLE (0)
#define PMBUS_CMD_AD_ENABLE (0)
#define PMBUS_CMD_AE_ENABLE (1)
#define PMBUS_CMD_AF_ENABLE (0)
#define PMBUS_CMD_B0_ENABLE (0)
#define PMBUS_CMD_B1_ENABLE (0)
#define PMBUS_CMD_B2_ENABLE (0)
#define PMBUS_CMD_B3_ENABLE (0)
#define PMBUS_CMD_B4_ENABLE (0)
#define PMBUS_CMD_B5_ENABLE (0)
#define PMBUS_CMD_B6_ENABLE (0)
#define PMBUS_CMD_B7_ENABLE (0)
#define PMBUS_CMD_B8_ENABLE (0)
#define PMBUS_CMD_B9_ENABLE (0)
#define PMBUS_CMD_BA_ENABLE (0)
#define PMBUS_CMD_BB_ENABLE (0)
#define PMBUS_CMD_BC_ENABLE (0)
#define PMBUS_CMD_BD_ENABLE (0)
#define PMBUS_CMD_BE_ENABLE (0)
#define PMBUS_CMD_BF_ENABLE (0)
#define PMBUS_CMD_C0_ENABLE (0)
#define PMBUS_CMD_C1_ENABLE (0)
#define PMBUS_CMD_C2_ENABLE (0)
#define PMBUS_CMD_C3_ENABLE (0)
#define PMBUS_CMD_C4_ENABLE (0)
#define PMBUS_CMD_C5_ENABLE (0)
#define PMBUS_CMD_C6_ENABLE (0)
#define PMBUS_CMD_C7_ENABLE (0)
#define PMBUS_CMD_C8_ENABLE (0)
#define PMBUS_CMD_C9_ENABLE (0)
#define PMBUS_CMD_CA_ENABLE (0)
#define PMBUS_CMD_CB_ENABLE (0)
#define PMBUS_CMD_CC_ENABLE (0)
#define PMBUS_CMD_CD_ENABLE (0)
#define PMBUS_CMD_CE_ENABLE (0)
#define PMBUS_CMD_CF_ENABLE (0)
#define PMBUS_CMD_D0_ENABLE (0) //double comfirm
#define PMBUS_CMD_D1_ENABLE (0)
#define PMBUS_CMD_D2_ENABLE (0)
#define PMBUS_CMD_D3_ENABLE (0)//
#define PMBUS_CMD_D4_ENABLE (0)
#define PMBUS_CMD_D5_ENABLE (0)//
#define PMBUS_CMD_D6_ENABLE (0)
#define PMBUS_CMD_D7_ENABLE (0)
#define PMBUS_CMD_D8_ENABLE (0)
#define PMBUS_CMD_D9_ENABLE (1) //done
#define PMBUS_CMD_DA_ENABLE (1) //done
#define PMBUS_CMD_DB_ENABLE (0)
#define PMBUS_CMD_DC_ENABLE (0)
#define PMBUS_CMD_DD_ENABLE (0)
#define PMBUS_CMD_DE_ENABLE (0)
#define PMBUS_CMD_DF_ENABLE (0)
#define PMBUS_CMD_E0_ENABLE (0)
#define PMBUS_CMD_E1_ENABLE (0)
#define PMBUS_CMD_E2_ENABLE (1) //done
#define PMBUS_CMD_E3_ENABLE (1) //done
#define PMBUS_CMD_E4_ENABLE (0)//
#define PMBUS_CMD_E5_ENABLE (0)//
#define PMBUS_CMD_E6_ENABLE (0) //double comfirm
#define PMBUS_CMD_E7_ENABLE (1)
#define PMBUS_CMD_E8_ENABLE (0)
#define PMBUS_CMD_E9_ENABLE (0)
#define PMBUS_CMD_EA_ENABLE (0)//
#define PMBUS_CMD_EB_ENABLE (0)
#define PMBUS_CMD_EC_ENABLE (0)
#define PMBUS_CMD_ED_ENABLE (0)
#define PMBUS_CMD_EE_ENABLE (0)
#define PMBUS_CMD_EF_ENABLE (0)
#define PMBUS_CMD_F0_ENABLE (1) //done
#define PMBUS_CMD_F1_ENABLE (0)
#define PMBUS_CMD_F2_ENABLE (0)//
#define PMBUS_CMD_F3_ENABLE (0)
#define PMBUS_CMD_F4_ENABLE (0)
#define PMBUS_CMD_F5_ENABLE (0)
#define PMBUS_CMD_F6_ENABLE (0)
#define PMBUS_CMD_F7_ENABLE (0)
#define PMBUS_CMD_F8_ENABLE (0)
#define PMBUS_CMD_F9_ENABLE (0)
#define PMBUS_CMD_FA_ENABLE (0)
#define PMBUS_CMD_FB_ENABLE (0)
#define PMBUS_CMD_FC_ENABLE (0)//
#define PMBUS_CMD_FD_ENABLE (1)
#define PMBUS_CMD_FE_ENABLE (0)
#define PMBUS_CMD_FF_ENABLE (0)

#ifdef __cplusplus
}
#endif

#endif	/* PMBUS_COMMON_H */


#ifndef SOFTWARE_INTERRUPT_H 
#define SOFTWARE_INTERRUPT_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
/*-----------------------------------macro------------------------------------*/


/*----------------------------------typedef-----------------------------------*/
typedef void (*FUNC_PTR)(); 	//used for zeroing instruction word.
/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
#pragma SWI_ALIAS (swi_single_entry, 0)
void swi_single_entry(Uint32 arg1, Uint32 arg2, Uint32 arg3, Uint8 swi_number);

void clear_program_flash(void);
void zero_out_integrity_word(void);

void init_interrupt(void);

void erase_data_flash_segment_case0(Uint8 segment);
void erase_data_flash_segment_no_delay_case1(Uint8 segment);
void write_data_flash_word_case3(Uint32 address,unsigned long data);
void enable_fast_interrupt_case4(void);
void disable_fast_interrupt_case5(void);
void enable_interrupt_case6(void);
void disable_interrupt_case7(void);
void write_firqpr_case8(unsigned long value);
void write_reqmask_case9(unsigned long value);
void set_supervisor_mode_case10(void);
void set_user_mode_case11(void);
void clear_integrity_word_case12(void);
void write_data_flash_block_case13(Uint32 arg1, Uint32  arg2, Uint32 arg3);
void erase_pflash_case14(void);

void erase_data_flash_segment(Uint8 segment);
void erase_dflash_segment_no_delay(Uint8 segment);
void write_data_flash_word(Uint32 address,unsigned long data);
void enable_fast_interrupt(void);
void disable_fast_interrupt(void);
void enable_interrupt(void);
void disable_interrupt(void);
void write_firqpr(unsigned long value);
void write_reqmask(unsigned long value);
void clear_integrity_word(void);
void write_data_flash_block();
void erase_pflash(void);
/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* SOFTWARE_INTERRUPT_H */

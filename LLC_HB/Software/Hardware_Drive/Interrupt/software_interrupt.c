
/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "device_parm_define.h"
#include "system_define.h"
#include "interrupt.h"
#include "global_variables.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
#pragma INTERRUPT(software_interrupt,SWI)
void software_interrupt(Uint32 arg1, Uint32 arg2, Uint32 arg3, Uint8 swi_number)
{
    //make sure interrupts are disabled
	asm(" MRS     r4, cpsr "); 		// get psr
	asm(" ORR     r4, r4, #0xc0 "); // set interrupt disables
	asm(" MSR     cpsr_cf, r4"); 		// restore psr

    switch (swi_number)
    {
        case 0:
        {
            erase_data_flash_segment_case0(arg1);
        }
        case 1:
        {
            erase_data_flash_segment_no_delay_case1(arg1);
            return;
        }
        case 3:
        {
            write_data_flash_word_case3(arg1,arg2);
        }
        case 4:
        {
            enable_fast_interrupt_case4();
        }
        case 5:
        {
            disable_fast_interrupt_case5();
        }
        case 6:
        {
            enable_interrupt_case6();
        }
        case 7:
        {
            disable_interrupt_case7();
        }
        case 8:
        {
            write_firqpr_case8(arg1);
        }
        case 9:
        {
            write_reqmask_case9(arg1);
        }
        case 10:
        {
            set_supervisor_mode_case10();
        }
        case 11:
        {
            set_user_mode_case11();
        }
        case 12:
        {
            clear_integrity_word_case12();
        }
        case 13:
        {
            write_data_flash_block_case13(arg1,arg2,arg3);
        }
        case 14:
        {
            erase_pflash_case14();
        }
        default:
            break;
    }
}

void erase_data_flash_segment_case0(Uint8 segment)
{
    erase_data_flash_segment_no_delay_case1(segment);
    while(DecRegs.DFLASHCTRL.bit.BUSY != 0)
    {
        ;
    }
    return;
}

void erase_data_flash_segment_no_delay_case1(Uint8 segment)
{
    union DFLASHCTRL_REG dflashctrl_shadow;

    if(segment >= DATA_FLASH_NUM_SEGMENTS)
    {
        return;
    }
    DecRegs.FLASHILOCK.all = 0X42DC157E;
    dflashctrl_shadow.all = DecRegs.DFLASHCTRL.all;
    dflashctrl_shadow.bit.PAGE_ERASE = 1; 		
    dflashctrl_shadow.bit.PAGE_SEL = segment;		
    DecRegs.DFLASHCTRL.all = dflashctrl_shadow.all;
}

void write_data_flash_word_case3(Uint32 address,unsigned long data)
{
    if(((address) < DATA_FLASH_START_ADDRESS) || ((address) > DATA_FLASH_END_ADDRESS))
    {
		return;
	}

    DecRegs.FLASHILOCK.all = 0x42DC157E; //unlock flash write
    DecRegs.MFBALR2.bit.RONLY = 0; 

    *(Uint32 *)(address & 0xfffffffc) = data ;
    DecRegs.MFBALR2.bit.RONLY = 1;
    while(DecRegs.DFLASHCTRL.bit.BUSY != 0)
    {
        ; //do nothing while it programs
    }
    return;
}


void enable_fast_interrupt_case4(void)
{
    asm(" MRS     r0, spsr "); //get saved psr
    asm(" BIC     r0, r0, #0x40 "); // clear fiq disable
    asm(" MSR     spsr_cf, r0"); //restore saved psr
    return;
}


void disable_fast_interrupt_case5(void)
{
    asm(" MRS     r0, spsr "); //get saved psr
    asm(" ORR     r0, r0, #0x40 "); // set fiq disable
    asm(" MSR     spsr_cf, r0"); //restore saved psr
    return;
}


void enable_interrupt_case6(void)
{
    asm(" MRS     r0, spsr "); //get saved psr
    asm(" BIC     r0, r0, #0x80 "); // clear irq disable
    asm(" MSR     spsr_cf, r0"); //restore saved psr
    return;
}


void disable_interrupt_case7(void)
{
    asm(" MRS     r0, spsr "); //get saved psr
    asm(" ORR     r0, r0, #0x80 "); // set irq disable
    asm(" MSR     spsr_cf, r0"); //restore saved psr
    return;
}


void write_firqpr_case8(unsigned long value)
{
    CimRegs.FIRQPR.all = value;
    return;
}

void write_reqmask_case9(unsigned long value)
{
    CimRegs.REQMASK.all = value;
	return;
}

void set_supervisor_mode_case10(void)
{
    asm(" MRS     r0, spsr "); //get saved psr
    asm(" BIC	  r0, r0, #0x1F "); // clear 5 lsbs.
    asm(" ORR     r0, r0, #0x13 "); // set mode bits to 13.
    asm(" MSR     spsr_cf, r0"); //restore saved psr
    return;
}

void set_user_mode_case11(void)
{
    asm(" MRS     r0, spsr "); //get saved psr
    asm(" BIC	  r0, r0, #0x1F "); // clear 5 lsbs.
    asm(" ORR     r0, r0, #0x10 "); // set mode bits to 10.
    asm(" MSR     spsr_cf, r0"); //restore saved psr
    return;
}

void clear_integrity_word_case12(void)
{
    register Uint32 * program_index =(Uint32 *) 0x19000; //store destination address for program
    register Uint32 * source_index = (Uint32 *)zero_out_integrity_word; //Set source address of PFLASH;

    register Uint32 counter;

    for(counter=0; counter < 32; counter++) //Copy program from PFLASH to RAM
    {
        *(program_index++)=*(source_index++);
    }

    register FUNC_PTR func_ptr;
    func_ptr=(FUNC_PTR)0x19000;     //Set function to 0x19000
    func_ptr();
    DecRegs.MFBALR1.bit.RONLY = 1; //restore it to read only
    DecRegs.MFBALR17.bit.RONLY = 1; //restore it to read only
    SysRegs.SYSECR.bit.RESET= 2; //reset device
    
    return;
}
void write_data_flash_block_case13(Uint32 arg1, Uint32  arg2, Uint32 arg3)
{
    volatile Uint32* dest_ptr = (volatile Uint32*)(arg1 & 0xfffffffc);
    Uint32* src_ptr =  (Uint32*)(arg2);
    int32   byte_counter = (int32)arg3; // Use int instead of Uint in case count is not a multiple of 4

    if(  ((arg1) < DATA_FLASH_START_ADDRESS) ||((arg1) > DATA_FLASH_END_ADDRESS)  )
    {//if out of data flash range
        flash_write_status = FLASH_INVALID_ADDRESS;
        return; // Return without writing to DFlash
    }

    DecRegs.MFBALR2.bit.RONLY = 0;

    while (byte_counter > 0)
    {
        Uint32  temp_word = *src_ptr++;
        DecRegs.FLASHILOCK.all = 0x42DC157E; //unlock flash write
        // Write the temp word to DFlash.
        *dest_ptr = temp_word;

        while(DecRegs.DFLASHCTRL.bit.BUSY != 0)
        {
            ; //do nothing while it programs
        }

        // Read back value from DFlash. Abort if it does not match intended value.
        if (*dest_ptr != temp_word)
        {
            // Set an error flag to indicate write failure.
            flash_write_status = FLASH_MISCOMPARE;
            return;
        }

        dest_ptr++;
        byte_counter -= 4;
    }

    // Set read-only bit to protect Data Flash
    DecRegs.MFBALR2.bit.RONLY = 1;

    flash_write_status = FLASH_SUCCESS;
    return;
}

void erase_pflash_case14(void)
{
    register Uint32 * program_index = (Uint32 *) 0x19000; //store destination address for program
    register Uint32 * source_index = (Uint32 *)clear_program_flash; //Set source address of PFLASH;

    register Uint32 counter;

    for(counter=0; counter < 500; counter++) //Copy program from PFLASH to RAM
    {
    *(program_index++)=*(source_index++);
    }

    register FUNC_PTR func_ptr;
    func_ptr=(FUNC_PTR)0x19000;     //Set function to 0x19000
    func_ptr();
    func_ptr=(FUNC_PTR)0x70000;

    func_ptr();
        //execute mass erase PFLASH
    return;
}


/*------------------------------------test------------------------------------*/


/*----------------------------------include-----------------------------------*/
#include "cyclone_device.h"
#include "system_define.h"
#include "device_parm_define.h"

#include "pmbus_filter_parm.h"
#include "pmbus_dcdc_parm.h"
#include "global_variables.h"

#include "function_definitions.h"
#include "interrupt.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
void look_for_interrupted_dflash_erase(void)
{
	volatile Uint32	bytes_to_erase, checksum, checksum_b,blank_checksum;
	bytes_to_erase = ((Uint8*)&pmbus_checksum - (Uint8*)&filter0_pmbus_regs);
	blank_checksum = 0xff * ((Uint8*)&pmbus_checksum - (Uint8*)&filter0_pmbus_regs);
	checksum = calculate_dflash_checksum((Uint8*)&filter0_pmbus_regs, 
		(Uint8*)&pmbus_checksum);
	if(checksum != blank_checksum)
	{
		if((checksum!=pmbus_checksum)&&(pmbus_checksum!=0x87654321))
		{	//erase BANK A
			start_erase_task((void*)&filter0_pmbus_regs_constants, (bytes_to_erase + 4));	
			return;
		}
	}
	erase_segment_counter = 0;
	return;
}

//==========================================================================================
// update_data_flash() 
//	Writes a variable-length block of data to Data Flash.  This function is the one and 
//	only function that should be called by the application code (i.e. STORE_DEFAULT_ALL
//	and WRITE_CLA_GAINS).  This function will take care of writing partial segments or
//	full segments of Data Flash as needed.
//
// Modified Globals:
//==========================================================================================
Uint8 update_data_flash(void* dest_ptr, const void* src_ptr, Uint16 byte_count)                   
{
	// Copy block from RAM to DFlash.
	// The write_data_flash_block function is a SWI, which cannot return a value.
	// Its response code is stored in the global var flash_write_status.
	write_data_flash_block((Uint32)dest_ptr, (Uint32)src_ptr, byte_count);

	return	flash_write_status;
}

//==========================================================================================
// start_erase_task():
// 	Sets up the erase task to erase one or more segments of Data Flash.
// The erase task will be periodically polled and updated from main_loop().  This frees
// the processor to do other operations while the DFlash is being erased rather than 
// hogging the processor for 20-450 milliseconds at a time
//
// // Assumptions: Destination pointer should be word aligned, or it could erase parts of 
// // other blocks.
//  
//==========================================================================================
Uint8 start_erase_task(const void* dest_ptr, Uint16 byte_count)
{
	Uint8	first_segment;	// 
	//	Uint32	segment_number;	// Holds the segment currently being updated
	//	Uint32	num_segments;	// Number of DFlash segments, including any partials
	Uint8	status;

	// Validate destination and calculate which segment(s) of Data Flash to erase
	status = calc_flash_segments(dest_ptr, byte_count, &first_segment);
	if(status != FLASH_SUCCESS)
	{ 
		return status;	// Error: Starting or Ending addr out of range
	}
	// Calculate the number of segments required to store the desired number of bytes.
	// Round up to include any partial segments.
	erase_segment_counter = (byte_count + DATA_FLASH_SEGMENT_SIZE-1) / DATA_FLASH_SEGMENT_SIZE;
	// Set the segment number for the last segment to be erased.
	// This will erase the required segments in reverse order.  
	// The checksum will be the first to go, guaranteeing that the partially erased segment
	// will not be accidentally considered valid when reading DFlash.
	erase_segment_number = first_segment + erase_segment_counter - 1; 

	// Call the SWI to start erasing the indicated segment and return without waiting for
	// the erasure to complete.
	erase_dflash_segment_no_delay(erase_segment_number);
	// Each segment takes ~20ms to erase.  Return and let the erase_task called from 
	// main_loop() handle the delays and the erasing of multiple segments.
	return FLASH_SUCCESS;
}	

//==========================================================================================
// erase_task():
//
//	If there are still DFlash segments that need erasing and the DFlash is not busy
// erasing one of them, start erasing the next segment.
//==========================================================================================
void erase_task(void)
{
	// 	if (erase_segment_counter == 0)
	// 	{
	// 		return; // No erase in progress.  Bail immediately.
	// 	}

	if (DecRegs.DFLASHCTRL.bit.BUSY != 0)
	{
		return;	// Previous segment erase still in progress
	}

	// Decrement the number of segments left to erase.
	erase_segment_counter--;
	if (erase_segment_counter > 0)
	{
		erase_segment_number--;
		// Still segments left to erase. 
		// Call the SWI to start erasing the next segment and return without waiting for
		// the erasure to complete.
		erase_dflash_segment_no_delay(erase_segment_number);
		// Each segment takes ~20ms to erase.  Leave for now.  
		// We will come back later to handle the next segment.
	}
	return;	
}

//==========================================================================================
// calculate_dflash_checksum:
//  Calculates a 32-bit checksum by adding up the bytes starting at the specified address 
//	for the specified number of bytes.
//==========================================================================================
Uint32 calculate_dflash_checksum(Uint8 *start_addr, Uint8 *end_addr)
{
	Uint8 *addr = start_addr;
	Uint32	checksum = 0;

	while(addr < end_addr)
	{
		checksum = checksum + (Uint32)*addr++ ;
	}
	return (checksum);
}

//==========================================================================================
// calc_flash_segments()
// This function validates the destination address range and calculates the Data Flash 
//	segment numbers for the area of flash specified by the DEST_PTR and BYTE_COUNT 
//	and returns a structure containing the first and last segments needed. 
//
// Modified Globals:
//==========================================================================================
inline Uint8 calc_flash_segments(const void* dest_ptr, Uint16 byte_count, Uint8* first_segment)                   
{                                                                                           

	Uint32 dest_addr = (Uint32)dest_ptr;	// Cast away the CONST nature of these pointer
	// but only within this function

	// Verify that the starting address is within the valid memory range
	if(   (dest_addr > DATA_FLASH_END_ADDRESS) 
		|| (dest_addr < DATA_FLASH_START_ADDRESS) )
	{

		return FLASH_INVALID_SEGMENT;	// Error: Starting addr out of range
	}

	// Verify that the ending address is within the valid memory range
	// 16-bit byte_count can't force the end to "wrap".
	if(dest_addr+byte_count-1 > DATA_FLASH_END_ADDRESS)
	{
		return FLASH_INVALID_SEGMENT;	// Error: Ending addr out of range
	}

	// Calculate which segment(s) of Data Flash to erase
	if(first_segment != NULL)
	{
		*first_segment = (Uint8)( (dest_addr - DATA_FLASH_START_ADDRESS) / DATA_FLASH_SEGMENT_SIZE );
	}

	return FLASH_SUCCESS;
}

//==========================================================================================
// erase_one_section(int first_segment, int byte_count)
// This function erases the section starting at the first_segment and the section is
// of byte_count.
// Modified Globals:
//==========================================================================================
void erase_one_section(int first_segment, int byte_count)
{
	while (byte_count > 0)
	{
		erase_data_flash_segment(first_segment);
		byte_count -= 32;
		first_segment++;
	}
}

void restore_default_all(void)
{
	Uint32 	checksum;

	// Pointers to structures in Data Flash 
	// These vairiables are used temporarly, just to select between DFLASH A and DFLASH B.
	// Then later or use memcopy to copy the data from DFLASH to RAM.
	volatile const  FILTER_PMBUS_REGS*	           filter0_pmbus_regs_ptr;
	volatile const  FILTER_PMBUS_REGS*	           filter0_start_up_pmbus_regs_ptr;
	volatile const  FILTER_PMBUS_REGS*	           filter0_cp_pmbus_regs_ptr;
	volatile const  FILTER_PMBUS_REGS*	           filter1_pmbus_regs_ptr;
	volatile const  PMBUS_DCDC_CONFIG*             dcdc_config_ptr;
	volatile const  PMBUS_DCDC_CONFIG_NONPAGED*    dcdc_config_nonpaged_ptr;
	volatile const  PMBUS_DCDC_CAL*                dcdc_cal_ptr;
	volatile const  PMBUS_DCDC_CAL_NONPAGED*       dcdc_cal_nonpaged_ptr;

	// ----- Look for a copy of default values in Data FLASH that looks valid. -----
	// If none found, use the hard-coded values from Program FLASH.

	// Wait for any erase that might be in progress to complete.
	// IMPORTANT!  This must be done before attempting to access any DFlash location, 
	// even if it is not in the segment being erased.
	while(DecRegs.DFLASHCTRL.bit.BUSY != 0)
	{
		; //do nothing while busy erasing DFlash
	}	

	// Clear latching status bits except MFR_CONFIG_CHANGED which only gets reset by reset.  
	// Each condition will be tested and set as needed below.
	// 	status_mfr_flags &= (1<<MFR_CONFIG_CHANGED);

	// Look in Data Flash A for valid values.
	checksum = calculate_dflash_checksum((Uint8*)&filter0_pmbus_regs_constants, (Uint8*)&pmbus_checksum);
	// A zero checksum only occurs when the segment is all zeroes, which is not valid.
	// If the calculated checksum is nonzero and matches the checksum in the DFlash,  
	// that segment is good, so use it.

	if(   (pmbus_checksum == 0x87654321)	// Hardcoded exception for parms written directly to data flash
		// (GUI download tool does not calculate checksum)
		||((checksum != 0) && (checksum == pmbus_checksum)) )	// Checksum is valid and matches.
	{
		// Checksum A Good: Use default values from DFlash A
		filter0_pmbus_regs_ptr	 = &filter0_pmbus_regs_constants;
		filter0_start_up_pmbus_regs_ptr	 = &filter0_start_up_pmbus_regs_constants;
		filter0_cp_pmbus_regs_ptr	 = &filter0_cp_pmbus_regs_constants;
		filter1_pmbus_regs_ptr	 = &filter1_pmbus_regs_constants;
		dcdc_config_ptr          = &pmbus_dcdc_config_constants[0];
		dcdc_config_nonpaged_ptr = &pmbus_dcdc_config_nonpaged_constants;
		dcdc_cal_ptr             = &pmbus_dcdc_cal_constants[0];
		dcdc_cal_nonpaged_ptr 	 = &pmbus_dcdc_cal_nonpaged_constants;
	}
    	else
	{
/*************************************************************
		// Look in Data Flash B for valid values
		checksum = calculate_dflash_checksum((Uint8*)&filter0_pmbus_regs_constants_b, (Uint8*)&pmbus_checksum_b);
		// A zero checksum only occurs when the segment is all zeroes, which is not valid.
		// If the calculated checksum is nonzero and matches the checksum in the DFlash,  
		// that segment is good, so use it.
		if ((checksum != 0) && (checksum == pmbus_checksum_b))
		{
			// Checksum B Good: Use default values from DFlash B
			filter0_pmbus_regs_ptr	 = &filter0_pmbus_regs_constants_b;
			filter0_start_up_pmbus_regs_ptr	 = &filter0_start_up_pmbus_regs_constants_b;
			filter0_cp_pmbus_regs_ptr	 = &filter0_cp_pmbus_regs_constants_b;
			filter1_pmbus_regs_ptr	 = &filter1_pmbus_regs_constants_b;
			dcdc_config_ptr          = &pmbus_dcdc_config_constants_b[0];
			dcdc_config_nonpaged_ptr = &pmbus_dcdc_config_nonpaged_constants_b;
			dcdc_cal_ptr             = &pmbus_dcdc_cal_constants_b[0];
			dcdc_cal_nonpaged_ptr 	 = &pmbus_dcdc_cal_nonpaged_constants_b;
		}	
*********************************************************************/
	}


	// ----- Copy default variables from Flash to RAM -----
					// RAM variables                    // DFLASH variables with data
	memcpy((void *)&filter0_pmbus_regs,    	    (void *)filter0_pmbus_regs_ptr,   		sizeof(filter0_pmbus_regs_constants));
	memcpy((void *)&filter0_start_up_pmbus_regs,(void *)filter0_start_up_pmbus_regs_ptr,sizeof(filter0_start_up_pmbus_regs_constants));
	memcpy((void *)&filter0_cp_pmbus_regs,		(void *)filter0_cp_pmbus_regs_ptr,		sizeof(filter0_cp_pmbus_regs_constants));
	memcpy((void *)&filter1_pmbus_regs,    	    (void *)filter1_pmbus_regs_ptr,   		sizeof(filter1_pmbus_regs_constants));
	memcpy((void *)&pmbus_dcdc_config[0],       (void *)dcdc_config_ptr,          		sizeof(pmbus_dcdc_config_constants));
	memcpy((void *)&pmbus_dcdc_config_nonpaged, (void *)dcdc_config_nonpaged_ptr, 		sizeof(pmbus_dcdc_config_nonpaged_constants));
	memcpy((void *)&pmbus_dcdc_cal[0],          (void *)dcdc_cal_ptr,             		sizeof(pmbus_dcdc_cal_constants));
	memcpy((void *)&pmbus_dcdc_cal_nonpaged,    (void *)dcdc_cal_nonpaged_ptr,    		sizeof(pmbus_dcdc_cal_nonpaged_constants));	
}
/*------------------------------------test------------------------------------*/

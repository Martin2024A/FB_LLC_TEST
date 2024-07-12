
/*----------------------------------include-----------------------------------*/
#include "pmbus_common.h"
/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

void pmbus_handler(void)
{
	if(pmbus_state == PMBUS_STATE_IDLE)
	{
		pmbus_idle_handler(&pmbus_status_half_word_0_value_ored,pmbus_buffer,&pmbus_number_of_bytes);
		return;
	}
	else if(pmbus_state == PMBUS_STATE_WRITE_BLOCK)
	{
		pmbus_write_block_handler(&pmbus_status_half_word_0_value_ored,pmbus_buffer,&pmbus_number_of_bytes);
		return;
	}
	else if(pmbus_state == PMBUS_STATE_READ_BLOCK)
	{
		pmbus_read_block_handler(&pmbus_status_half_word_0_value_ored,pmbus_buffer,&pmbus_number_of_bytes);
		return;
	}
	else if(pmbus_state == PMBUS_STATE_READ_WAIT_FOR_EOM)
	{
		pmbus_read_wait_for_eom_handler(&pmbus_status_half_word_0_value_ored,pmbus_buffer,&pmbus_number_of_bytes);
		return;
	}
	else
	{
		pmbus_state = PMBUS_STATE_IDLE;
		pmbus_idle_handler(&pmbus_status_half_word_0_value_ored,pmbus_buffer,&pmbus_number_of_bytes);
		return ;
	}
}


void pmbus_write_block_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes)
{
    Uint16 pmbus_status_half_word_0_value;

    pmbus_status_half_word_0_value = PMBusRegs.PMBST.half.HALF0;
    *pmbus_status_debug = *pmbus_status_debug | pmbus_status_half_word_0_value;

    if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) == 0)
    {
        return;
    }

    else if ((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS)) == 
            (PMBST_BYTE0_EOM + PMBST_BYTE0_DATA_READY + PMBST_BYTE0_PEC_VALID))
    {
        pbuffer[*pnumber_of_bytes] = PMBusRegs.PMBRXBUF.byte.BYTE0;
        pbuffer[*pnumber_of_bytes + 1] = PMBusRegs.PMBRXBUF.byte.BYTE1;
        pbuffer[*pnumber_of_bytes + 2] = PMBusRegs.PMBRXBUF.byte.BYTE2;
        pbuffer[*pnumber_of_bytes + 3] = PMBusRegs.PMBRXBUF.byte.BYTE3;

        *pnumber_of_bytes = *pnumber_of_bytes + (pmbus_status_half_word_0_value & PMBST_BYTE0_RD_BYTE_COUNT);

        pmbus_read_write_message(PMBUS_WRITE);
		PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack these 4 bytes;
		pmbus_state = PMBUS_STATE_IDLE;
		return;
    }

    else if ((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) ==
			(4 + PMBST_BYTE0_DATA_READY))
    {
        pbuffer[*pnumber_of_bytes++] = PMBusRegs.PMBRXBUF.byte.BYTE0;
        pbuffer[*pnumber_of_bytes++] = PMBusRegs.PMBRXBUF.byte.BYTE1;
        pbuffer[*pnumber_of_bytes++] = PMBusRegs.PMBRXBUF.byte.BYTE2;
        pbuffer[*pnumber_of_bytes++] = PMBusRegs.PMBRXBUF.byte.BYTE3;
        
        if(*pnumber_of_bytes >= PMBUS_BUFFER_SIZE)
        {
			PMBusRegs.PMBACK.byte.BYTE0 = 1;  //NACK it;
			pmbus_state = PMBUS_STATE_IDLE;
			return;
        }

        PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack these 4 bytes;
		return;
    }

    else if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS )) ==
		(PMBST_BYTE0_EOM + PMBST_BYTE0_PEC_VALID))
		//end of message, no new data ready, pec valid; was exact multiple of 4 bytes, already acked last time
	{
		//pmbus_write_message();
		pmbus_read_write_message(PMBUS_WRITE);
		PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack the message;
		pmbus_state = PMBUS_STATE_IDLE;
		return;
	}
	else //here if something has happened on bus, not covered by anything above
	{
		PMBusRegs.PMBACK.byte.BYTE0 = 1;  //nack them
		pmbus_state = PMBUS_STATE_IDLE;
		return;
	}
}

void pmbus_idle_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes)
{
    int32 i;
    Uint16 pmbus_status_half_word_0_value;
    union
	{
		Uint32 pmbus_transmit_load;
		Uint8 pmbus_transmit_bytes[4];
	}u;

    pmbus_status_half_word_0_value = PMBusRegs.PMBST.half.HALF0;
    *pmbus_status_debug = *pmbus_status_debug | pmbus_status_half_word_0_value;

	if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) == 0)
	{//if no activity on PMBus, do nothing
		return ;
	}

    if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) == 
				PMBST_BYTE0_EOM)
	{
		PMBusRegs.PMBACK.byte.BYTE0 = 1;  //nack them
		return ;
	}
	else if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS )) ==
			(PMBST_BYTE0_EOM + PMBST_BYTE0_DATA_READY + PMBST_BYTE0_PEC_VALID))
			//end of message, good data ready, pec valid, must be 2 to 4 bytes
	{
        pbuffer[0] = PMBusRegs.PMBRXBUF.byte.BYTE0;
        pbuffer[1] = PMBusRegs.PMBRXBUF.byte.BYTE1;
        pbuffer[2] = PMBusRegs.PMBRXBUF.byte.BYTE2;
        pbuffer[3] = PMBusRegs.PMBRXBUF.byte.BYTE3;

        *pnumber_of_bytes = pmbus_status_half_word_0_value & PMBST_BYTE0_RD_BYTE_COUNT;

        pmbus_read_write_message(PMBUS_WRITE);
		PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack them
		return;
    }

    else if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) ==
        (4 + PMBST_BYTE0_DATA_READY))
        //no end of message, good data ready, 4 bytes of data - must be a send block 
    {
        pbuffer[0] = PMBusRegs.PMBRXBUF.byte.BYTE0;
        pbuffer[1] = PMBusRegs.PMBRXBUF.byte.BYTE1;
        pbuffer[2] = PMBusRegs.PMBRXBUF.byte.BYTE2;
        pbuffer[3] = PMBusRegs.PMBRXBUF.byte.BYTE3;

        *pnumber_of_bytes = 4;

        PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack first 4 bytes;
		pmbus_state = PMBUS_STATE_WRITE_BLOCK;
    }

    else if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) ==
        (1 + PMBST_BYTE0_DATA_READY ))
    {
        pbuffer[0] = PMBusRegs.PMBRXBUF.byte.BYTE0;

        pmbus_read_write_message(PMBUS_READ);

        if(*pnumber_of_bytes == 0)
        {
            PMBusRegs.PMBACK.byte.BYTE0 = 1;  //nack them
			return;
        }
        else if (*pnumber_of_bytes < 5)
        {
            PMBusRegs.PMBCTRL2.byte.BYTE2 = PMBCTRL2_BYTE2_TX_PEC + *pnumber_of_bytes
											+ PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT;
            for(i = 0; i < *pnumber_of_bytes; i++)
            {
                u.pmbus_transmit_bytes[3-i] = pbuffer[i];
            }
            PMBusRegs.PMBTXBUF.all = u.pmbus_transmit_load; //this sends message
			PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack command;
			pmbus_state = PMBUS_STATE_READ_WAIT_FOR_EOM;
			return ;
        }
        else
        {
            PMBusRegs.PMBCTRL2.byte.BYTE2 =  4 + PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT;
            for(i = 0;i < 4;i++)
			{
				u.pmbus_transmit_bytes[3-i] = pbuffer[i]; //big endian stuff - great fun
			}

			PMBusRegs.PMBTXBUF.all = u.pmbus_transmit_load; //this sends message
			PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack command;
			pmbus_buffer_position = 4;

			pmbus_state = PMBUS_STATE_READ_BLOCK;
	
			return ;
        }
    }
    else
    {
        PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack them
		pmbus_state = PMBUS_STATE_IDLE;
		return;
    }

}

void pmbus_read_block_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes)
{
    Uint16 pmbus_status_half_word_0_value;
	union
	{
		Uint32 pmbus_transmit_load;
		Uint8 pmbus_transmit_bytes[4];
	}
	 u;

	pmbus_status_half_word_0_value = PMBusRegs.PMBST.half.HALF0 ; //assign to temporary value
	*pmbus_status_debug = *pmbus_status_debug | pmbus_status_half_word_0_value;	

	if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) == 0) 
	{//if no activity on PMBus, do nothing
		return ; 
	}
	else if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) ==
				PMBST_BYTE0_DATA_REQUEST)

	{
		u.pmbus_transmit_bytes[3] = pbuffer[pmbus_buffer_position++] ; //put out byte 0
		if(pmbus_buffer_position >= *pnumber_of_bytes) //if last byte
		{
			PMBusRegs.PMBCTRL2.byte.BYTE2 = 1 + PMBCTRL2_BYTE2_TX_PEC
											+ PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT;  //send byte and PEC;
			PMBusRegs.PMBTXBUF.all = u.pmbus_transmit_load; //
			pmbus_state = PMBUS_STATE_READ_WAIT_FOR_EOM;
			return  ;
		}
		u.pmbus_transmit_bytes[2] = pbuffer[pmbus_buffer_position++] ; //put out byte 1
		if(pmbus_buffer_position >= *pnumber_of_bytes) //if last byte
		{
			PMBusRegs.PMBCTRL2.byte.BYTE2 = 2 + PMBCTRL2_BYTE2_TX_PEC
											+ PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT;  //send bytes and PEC;
			PMBusRegs.PMBTXBUF.all = u.pmbus_transmit_load; //
			pmbus_state = PMBUS_STATE_READ_WAIT_FOR_EOM;
			return  ;
		}
		u.pmbus_transmit_bytes[1] = pbuffer[pmbus_buffer_position++] ; //put out byte 2
		if(pmbus_buffer_position >= *pnumber_of_bytes) //if last byte
		{
			PMBusRegs.PMBCTRL2.byte.BYTE2 = 3 + PMBCTRL2_BYTE2_TX_PEC
											+ PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT;  //send bytes and PEC;
			PMBusRegs.PMBTXBUF.all = u.pmbus_transmit_load; //
			pmbus_state = PMBUS_STATE_READ_WAIT_FOR_EOM;
			return  ;
		}
		u.pmbus_transmit_bytes[0] = pbuffer[pmbus_buffer_position++] ; //put out byte 3
		if(pmbus_buffer_position >= *pnumber_of_bytes) //if last byte
		{
			PMBusRegs.PMBCTRL2.byte.BYTE2 = 4 + PMBCTRL2_BYTE2_TX_PEC
											+ PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT;  //send bytes and PEC;
			PMBusRegs.PMBTXBUF.all = u.pmbus_transmit_load; //
			pmbus_state = PMBUS_STATE_READ_WAIT_FOR_EOM;
			return  ;
		}
		PMBusRegs.PMBCTRL2.byte.BYTE2 = 4 + PMBCTRL2_BYTE2_RX_BYTE_ACK_CNT ;  //send bytes, no PEC;
		PMBusRegs.PMBTXBUF.all = u.pmbus_transmit_load; //
		return; //don't change status, we're not done yet.
	}
	else  //if we get something other than a data request
	{
		PMBusRegs.PMBACK.byte.BYTE0 = 1;  //nack them
		return  ; //and return
	}
	
}

void pmbus_read_wait_for_eom_handler(Uint16 *pmbus_status_debug, Uint8 *pbuffer, Uint8 *pnumber_of_bytes)
{
	Uint16 pmbus_status_half_word_0_value; //save pmbus status, since cleared on read.

	pmbus_status_half_word_0_value = PMBusRegs.PMBST.half.HALF0 ; //assign to temporary value
	*pmbus_status_debug = *pmbus_status_debug | pmbus_status_half_word_0_value;	

	if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) == 0)
	{//if no activity on PMBus, do nothing
		return ;
	}

	else if((pmbus_status_half_word_0_value & (PMBST_HALF0_CHECK_BITS + PMBST_BYTE0_RD_BYTE_COUNT)) == PMBST_BYTE0_EOM)
	{//if eom, done
		pmbus_state = PMBUS_STATE_IDLE;
		PMBusRegs.PMBACK.byte.BYTE0 = 1;  //ack them
		return ;
	}
	else //some other error, still go back to idle.
	{
		pmbus_state = PMBUS_STATE_IDLE;
		return;
	}
}


/*------------------------------------test------------------------------------*/

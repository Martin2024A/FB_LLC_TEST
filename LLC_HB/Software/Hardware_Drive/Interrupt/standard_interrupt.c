
/*----------------------------------include-----------------------------------*/

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/
typedef enum
{
	STATE_IDLE,
	STATE_CHECK_RAMP_UP,
	STATE_WAIT_DRIVEON,
	STATE_HIGH_CURRENT_DURING_RAMP_UP,
	STATE_BOUNCE_TO_RAMP_UP_AFTER_WAITING,
	STATE_RAMP_UP,		
	STATE_RAMP_DOWN,	
	STATE_REGULATED,	
	STATE_LIGHT_LOAD,	
	STATE_CPCC,	
	STATE_FAULT,
	STATE_HICCUP,
	STATE_VOUT_TRANSITION,
	NONE
} SUPPLY_STATE;

SUPPLY_STATE supply_state; 
/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/
#pragma INTERRUPT(standard_interrupt,IRQ)
void standard_interrupt(void)
{
	handle_standard_interrupt_global_tasks();
	handle_faults();

	switch(supply_state)
	{
		case STATE_IDLE:
		{

		}
	}

}



/*------------------------------------test------------------------------------*/

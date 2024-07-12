
#ifndef DEVICE_H 
#define DEVICE_H 

#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/

/*-----------------------------------macro------------------------------------*/
// Memory allocation constants
// ****VOYAGER#define MFBALR2_HALF0_DATA_FLASH_BASE_ADDRESS 0x8800



// Flash Error codes
#define FLASH_SUCCESS 				(0)
#define FLASH_INVALID_SEGMENT 		(1)
#define	FLASH_INVALID_ADDRESS		(2)
#define	FLASH_MISCOMPARE			(3)

#define NULL						(0)


#define PMBUS_DATA_LENGTH (32)         // the max number of data bytes in a command


/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* DEVICE_H */

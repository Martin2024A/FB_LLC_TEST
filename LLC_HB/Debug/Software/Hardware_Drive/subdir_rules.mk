################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Software/Hardware_Drive/%.obj: ../Software/Hardware_Drive/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/APP/CCS/ccs/tools/compiler/ti-cgt-arm_5.2.9/bin/armcl" -mv4 --code_state=16 --abi=ti_arm9_abi -O2 --include_path="D:/Workspace/Power/5.Code/FB_LLC/FB_LLC_Test/LLC_HB/Software/Device/Header" --include_path="D:/Workspace/Power/5.Code/FB_LLC/FB_LLC_Test/LLC_HB/Software/Hardware_Drive/Interrupt" --include_path="D:/Workspace/Power/5.Code/FB_LLC/FB_LLC_Test/LLC_HB/Software/Task_Handler/Pmbus_handler_more" --include_path="D:/Workspace/Power/5.Code/FB_LLC/FB_LLC_Test/LLC_HB/Software/Hardware_Drive/Pmbus" --include_path="D:/Workspace/Power/5.Code/FB_LLC/FB_LLC_Test/LLC_HB/Software/APP/Global_value" --include_path="D:/Workspace/Power/5.Code/FB_LLC/FB_LLC_Test/LLC_HB" --include_path="D:/APP/CCS/ccs/tools/compiler/ti-cgt-arm_5.2.9/include" -g --preproc_with_comment --preproc_with_compile --define=UCD3138A --diag_warning=225 --diag_wrap=off --display_error_number --pp_directory="D:/Workspace/Power/5.Code/FB_LLC/FB_LLC_Test/LLC_HB/Debug/UCD3138A" --obj_directory="Software/Hardware_Drive" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



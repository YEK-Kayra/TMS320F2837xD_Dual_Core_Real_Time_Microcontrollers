################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/yunus/workspace_v12_new/TUBITAK_ADC_ReadingVoltage_From_CurrentSensor" --include_path="C:/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/c2000/C2000Ware_5_04_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_5_04_00_00/device_support/f2837xd/headers/include" --include_path="C:/Users/yunus/workspace_v12_new/TUBITAK_ADC_ReadingVoltage_From_CurrentSensor/include" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=CPU1 --define=_LAUNCHXL_F28379D --define=_DUAL_HEADERS --define=_FLASH --define=DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


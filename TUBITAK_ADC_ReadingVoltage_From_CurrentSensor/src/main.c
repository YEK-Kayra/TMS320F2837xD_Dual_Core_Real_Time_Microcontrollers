
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "device.h"
#include "driverlib.h"
#include "F28x_Project.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#define EX_ADC_RESULATION 12

void configADC(Uint32 ADC_Base);
void initADC_SOC(void);

uint16_t ADC_result_1, ADC_result_2, ADC_result_3 = 0;
float ADCINA0_1A, ADCINA4_1B, ADCINA2_1C = 0;



void main(void){

    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    configADC(ADCA_BASE);
    initADC_SOC();

    EINT;
    ERTM;

    while(1){


        //Convert and wait for complation, and store results
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER2);
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER4);


        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == FALSE)
        {

        }


        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);


        //Store Result
        ADC_result_1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        ADC_result_2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4);
        ADC_result_3 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);

        //Convert into Voltage
        ADCINA0_1A = (ADC_result_1*(3.3/4069));
        ADCINA4_1B = (ADC_result_2*(3.3/4069));
        ADCINA2_1C = (ADC_result_3*(3.3/4069));


    }



}


void configADC(Uint32 ADC_Base){

    //Enable Protected Register Access
    EALLOW;

    //Default clock freq. is 200MHz
    //We use port of A for ADC. its clock freq will be 50MHz
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

#if(EX_ADC_RESULATION == 12)
    {
    ADC_setMode(ADC_Base, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    }
#elif(EX_ADC_RESULATION == 16)
    {
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
    }

#endif

    ADC_setInterruptPulseMode(ADC_Base, ADC_PULSE_END_OF_CONV);
    ADC_enableConverter(ADC_Base);
    DEVICE_DELAY_US(1000);

    //Disable Protected Register Access
    EDIS;
}



void initADC_SOC(void){

#if(EX_ADC_RESULATION == 12)
    {
     ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0 , ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 15);
     ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER2 , ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 15);
     ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER4 , ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 15);
    }
#elif(EX_ADC_RESULATION == 16)
    {
     ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0 , ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 64);
    }
#endif

    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER2);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER4);



    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

}

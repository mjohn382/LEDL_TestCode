#ifndef __ADC_setup
  #define __ADC_setup

void adc_int(void);
void adcsetup(void);

extern int handle_adc; //extern will reference the int handle_adc that is written in ADC_setup file

#endif

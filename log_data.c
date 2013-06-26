#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "ADC_setup.h"
#include "I2C_sensor.h"
#include "timer_setup.h"
#include "log_data.h"

void ADC_test(void){

 
 unsigned long test=0;//counter for rows also called SFID
  int accel_count=0;//counter to display last two rows of data
  int gyro_count=0;//counter to display gyro
  int frame_100=0;//counter to display temperature 
  int temp_display=0;//counter to display zeros or temp
  int i; //counter to cycle through six adc measurements 
  int signal_mux=0;// making signal that will cause mux to switch between gyro 2 (G2) when signal_mux=0 and gyro 3 (G3) when signal_mux=1 
  int k; //counter for loops of reading data 
  int ADCread;
 

printf("\rLEDL ADC test\r\n");// 
printf("\rmeasure voltage with the MSP ADC.\r\n");
printf("\rtest#\tA0\tA1\tA2\tA3\tA4\tA5\tA6\tA7\r\n");//gives a column title
  timersetup4kHz();//start timer
 // timersetup();//start timer
  adcsetup();//adc setup
   __enable_interrupt();// THIS IS A PREDEFINED GLOBAL INTERRUPT ENABLE BIT IN THE MSP LIBRARY 
  

  //for(;;)
  for(k=0;k<2;k++)//make two loops to makes measurements 
  {
    volatile unsigned int *arr = &ADC12MEM0;// creates a pointer, looks at the memory of mem0
    while(handle_adc!=0)//in adc interrupt handle_adc is set high, so this code can become initialized
    {
      handle_adc = 0;//reset my personal flag to zero
      if (accel_count==0)// only when accel_count=0 will the row number be displayed
      {
      printf("%d\t", test);//prints row number
      test++;//add count to test 
      }  
        for (i=0; i<8; ++i)// print first 6 adc measurements  
         {
          printf("%d\t", arr[i]);
         }  

         printf("\r\nPlace the results in Document ARC1-LEDL-TST-LEDLPROTO-R01 section ADC Test.\r\n");
         printf("When finished press the space bar to continue.\r\n");
         while(ADCread!=' '){//continues to check to see if the space bar was hit.  
         ADCread = Getc();//We expect the ascii key for return to be in the return value.  
         }ADCread=0;
     }
    }
    }

void launch_data_log(void){
  unsigned long row=0;//counter for rows also called SFID
  int accel_count=0;//counter to display last two rows of data
  int gyro_count=0;//counter to display gyro
  int frame_100=0;//counter to display temperature 
  int temp_display=0;//counter to display zeros or temp
  int i; //counter to cycle through six adc measurements 
  int signal_mux=0;// making signal that will cause mux to switch between gyro 2 (G2) when signal_mux=0 and gyro 3 (G3) when signal_mux=1 
  int temp_measure[TEMP_ARRAY_SIZE];
  
  //timersetup();//start timer //using jesse's timer in main
  adcsetup();//adc setup
   __enable_interrupt();// THIS IS A PREDEFINED GLOBAL INTERRUPT ENABLE BIT IN THE MSP LIBRARY 
  printf("\rLEDL Sensor read test\r\n>");// 

  printf("\rrow\tA0\tA1\tA2\tA3\tA4\tA5\tA0\tA1\tA2\tA3\tA4\tA5\tA0\tA1\tA2\tA3\tA4\tA5\tA0\tA1\tA2\tA3\tA4\tA5\tA6\tA7\r\n>");//gives columns titles 
  for(;;)
  {
    volatile unsigned int *arr = &ADC12MEM0;// creates a pointer, looks at the memory of mem0
    if (handle_adc)//in adc interrupt handle_adc is set high, so this code become initialized
      {
      handle_adc = 0;//reset my personal flag to zero
      if (accel_count==0)// only when accel_count=0 will the row number be displayed
      {
      printf("%d\t", row);//prints row number
      row++;//add count to rows this is also SFID
      }  
        for (i=0; i<6; ++i)// print first 6 adc measurements  
         {
          printf("%d\t", arr[i]);
          accel_count++;//add a count to accel_count,
         }  
          
          if (accel_count==24)// when accel_count is 24 it print last two columns
          {
          switch (gyro_count)
          {
          case 0:
                 printf("%d(G1)\t", arr[6]);
           
                 gyro_count++;
                 break;
          case 1:
                 printf("%d(G2)\t", arr[7]);
                 gyro_count++;
                 signal_mux=1;//selecting G3 on mux for next pass
                 break;
          case 2:
                 printf("%d(G3)\t", arr[7]);
                 gyro_count=0;
                 signal_mux=0;//selecting G2 on mux for next pass
                 break;
          }
          
          switch (temp_display)
          {
           
          case 0: 
            if (frame_100==0)
            {
            Temp_I2C_sensor(temp_measure);//here is the first temperature measurement passing an array 7 length long //at some point I will need to measure temperature sensors as a 
            //different task so that as I am waiting for the the return values I can be taking my other measurements. 
            printf("%d\t",temp_measure[0]);//this is the spot for temperature data
            }
            else
            {
            printf("0000\t");
            }
            temp_display++;
            break;
          case 1:
            if (frame_100==0)
            {
            printf("%d\t",temp_measure[1]);//this is the spot for temperature data
            }
            else
            {
            printf("0000\t");
            }
            temp_display++;
            break;
          case 2:
            if (frame_100==0)
            {
            printf("%d\t",temp_measure[2]);//this is the spot for temperature data
            }
            else
            {
            printf("0000\t");
            }
            temp_display++;
            break;
          case 3:
            if (frame_100==0)
            {
            printf("%d\t",temp_measure[3]);//this is the spot for temperature data
            }
            else
            {
            printf("0000\t");
            }
            temp_display++;
            break;
          case 4:
            if (frame_100==0)
            {
            printf("%d\t",temp_measure[4]);//this is the spot for temperature data
            }
            else
            {
            printf("0000\t");
            }
            temp_display++;
            break;
          case 5:
            if (frame_100==0)
            {
           printf("%d\t",temp_measure[5]);//this is the spot for temperature data
            }
            else
            {
            printf("0000\t");
            }
            temp_display++;
            break;
          case 6:
            if (frame_100==0)
            {
           printf("%d\t",temp_measure[6]);//this is the spot for temperature data
            frame_100=0;
            }
            else
            {
            printf("0000\t");
            frame_100++;
            }
            temp_display++;
            break;
          case 7:
            printf("TIME1\t");//this is the spot for time1 data
            temp_display++;
            break;
          case 8: 
            printf("TIME2\t");
            temp_display=0;
            break; 
            //add a count for incrementing frame number
          } 
          printf("\r\n");
          accel_count=0;
          }
        
         } 
      
   }
   }

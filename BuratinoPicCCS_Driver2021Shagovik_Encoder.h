#include <16F1827.h>
#device ADC=16

#define  WDT_ON_DEFINE 1


#FUSES WDT                   	//Watch Dog Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
////////////// int     //////////// int     
#USE FAST_IO(B)
//#USE FAST_IO(C)
//a eto pravilnie flagi !!!!
////////////// int     //////////// int     
#use FIXED_IO( A_outputs=PIN_A4,PIN_A0 )
#use FIXED_IO( B_outputs=PIN_B0,PIN_B1, PIN_B6,PIN_B7)
#use delay(crystal=30000000)
////////////// int     //////////// int     
//#USE FAST_IO(A)#USE FAST_IO(B)
//a eto pravilnie flagi !!!!
////////////// int     //////////// int     


#BYTE   IOCBP = 0x394
#BYTE   IOCBN = 0x395
#BYTE   IOCBF = 0x396

//+#USE FAST_IO(PIN_B1)IOCBP
//#use STANDARD_IO( D )
//#use STANDARD_IO( C,D )
//#use FIXED_IO( A_outputs=PIN_A0,PIN_A4 )

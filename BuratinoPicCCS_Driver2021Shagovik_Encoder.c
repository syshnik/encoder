#include <BuratinoPicCCS_Driver2021Shagovik_Encoder.h>
 

#define GCC_COMPILER555555555 1
#define USE_CAN_PIC18_MY 1
#include "C:\Save\WORK\Programm\h\Macro.h"

#include "C:\Save\WORK\Programm\h\BCommands.h"
//#include "C:\Save\WORK\Programm\h\Paket.h"
//#include "C:\Save\WORK\Programm\h\PaketC.h"


#define SPI_SPI_CS   PIN_A3
#define SPI_SPI_SI   PIN_A2
#define SPI_SPI_SO   PIN_A0
#define SPI_SPI_SCK  PIN_A1
#define SPI_SPI_SLAVE 1
//#USE SPI (SLAVE, CLK=PIN_A1, DI=PIN_A2, DO=PIN_A0, ENABLE=PIN_A3, BITS=8, STREAM=SPI_SPI_STREAM)
//#USE SPI (SLAVE, CLK=PIN_A1, DI=PIN_A2, DO=PIN_A0, ENABLE=PIN_A3, BITS=8, STREAM=SPI_SPI_STREAM)
//ok #use spi(SLAVE,DI=SPI_SPI_SI,DO=SPI_SPI_SO,CLK=SPI_SPI_SCK,ENABLE=SPI_SPI_CS,bits=8,stream=SPI_SPI_STREAM)
//#use spi(SLAVE,DI=SPI_SPI_SI,DO=SPI_SPI_SO,CLK=SPI_SPI_SCK,ENABLE=SPI_SPI_CS,bits=8,stream=SPI_SPI_STREAM)
#use spi(SLAVE,MODE=0, DI=SPI_SPI_SI,DO=SPI_SPI_SO,CLK=SPI_SPI_SCK,ENABLE=SPI_SPI_CS,bits=8, stream=SPI_SPI_STREAM)
#include "C:\Save\WORK\Programm\h\spi_spi.h"


#define PIN_SECUNDOMER PIN_A4
void can_init() {}
#define COUNT_FOR_ADD_151_MS 950
#include "C:\Save\WORK\Programm\h\Zavisalka.h"

//#define MLP_A_ON input(PIN_B5)
//#define MLP_A_OFF input(PIN_B3)
//#define MLP_B_ON input(PIN_B4)
//#define MLP_B_OFF input(PIN_B2)
#define MPORT_A_ON input(PIN_B5)
#define MPORT_B_ON input(PIN_B4)
#ifdef TEST_ENCODER_SHAGI
S4 _test_count_int;
#endif

#include "encodercontrols.h"
#include "encodercontrols_c.h"

U1 _init_flag, _revers_flag;


int GetEncoderPinsInByte() {
    int ret=0;
    if(input(PIN_B5)) ret|=1;
    if(input(PIN_B3)) ret|=2;
    if(input(PIN_B4)) ret|=4;
    if(input(PIN_B2)) ret|=8;
    return ret;
}
#INT_RB
void  RB_isr(void) 
{
    {
        Encoder_AB_Timer_On() ;
    }
    {
        //---VOT TAK FLAG PRERIVANIY SBRASIVAEM 
        //---A ETA HERNYA ---clear_interrupt(INT_RB);    clear_interrupt(INT_EXT);---  NE RABOTAET
        IOCBF=0;
    }
    //DLYA KRASOTI
#ifdef TEST_ENCODER_SHAGI
    _test_count_int++;
    _flag_diodik=!_flag_diodik;
#endif
    //shtob ne zavis
#ifdef WDT_ON_DEFINE
        restart_wdt();
#endif
}


void OshiySbros() {
    EncoderSbros();
    ZavisalkaInit();
    _init_flag=FALSE;
    output_high(PIN_A0);
    output_high(PIN_A4);
    _ssi_in_mp=0;
    _ssi_out_mp=0;
}
#ifdef TEST_SPI
BOOL led1=0;
#endif

void SaveInBeferForTest() {
#ifdef TEST_ENCODER_SPI    
        //
        _ssi_in_mp++;
        if(_ssi_in_mp >= DEBUG_COUNT) _ssi_in_mp=0;
        _ssi_in_m[_ssi_in_mp]=_ssi_in;
        //
        //
        _ssi_out_mp++;
        if(_ssi_out_mp >= DEBUG_COUNT) _ssi_out_mp=0;
        _ssi_out_m[_ssi_out_mp]=_ssi_out;
        //
#endif
}
        
void main()
{
   OshiySbros();

#ifdef WDT_ON_DEFINE
	setup_wdt(WDT_512MS);		//~32,0 ms reset
#endif


    //=============NASTROYKA PRERIVAniy===================
	enable_interrupts(INT_RB);
    IOCBP=0B00111100;
    IOCBN=0B00000000;
	enable_interrupts(GLOBAL);
    //=============NASTROYKA PRERIVAniy===================

#ifdef TEST_SPI
   _ssi_out._s4_massiv._sm[0]=0x55;
   _ssi_out._s4_massiv._sm[1]=0x66;
   _ssi_out._s4_massiv._sm[2]=0x77;
   _ssi_out._s4_massiv._sm[3]=0x88;
#endif           

	while(TRUE)
	{
        //obmen
        BOOL ret1=spi_spi_obmen_slave();
        //
        if(ret1) {
            //obrabotka
            if(_ssi_in._command == SPI_SPI_COMMAND_PROVERKA_SVYAZI) {
                //
                ZavisalkaInit();
                _ssi_out._s4_massiv._ssss = 0x4444;
                _ssi_out._command=_ssi_in._command;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            } else if(_ssi_in._command == SPI_SPI_COMMAND_ZIRO_ENCODER) {
                //
                EncoderSbros();
                _ssi_out._s4_massiv._ssss = 0x1111;
                _ssi_out._command=_ssi_in._command;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            } else if(_ssi_in._command == SPI_SPI_COMMAND_GET_ANSER) {
                //vozvrat rezultata comand in _ssi_out
            } else if(_init_flag && _ssi_in._command == SPI_SPI_COMMAND_RETURN_ENCODER_POSICION) {
                //konec nayden vernem posiciyu
                _ssi_out._s4_massiv._ssss = (_revers_flag ? (-_enc_position) : _enc_position);
                _ssi_out._command=_ssi_in._command;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            } else if(_init_flag && _ssi_in._command == SPI_SPI_COMMAND_RETURN_ENCODER_POSICION_AFTER_FIND_END) {
                //staroe znachenie   dlya kalibrovki
                _ssi_out._s4_massiv._ssss = (_revers_flag ? (-_enc_position_AFTER_FIND_END) : _enc_position_AFTER_FIND_END);
                _ssi_out._command=_ssi_in._command;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            } else if(_ssi_in._command == SPI_SPI_COMMAND_ENCODER_INIT) {
                //init revers flag and int flag
                _init_flag=TRUE;
                if(_ssi_in._s4_massiv._sm[0]) _revers_flag=TRUE;
                else _revers_flag=FALSE;
                _ssi_out._s4_massiv._ssss = 0x2222;
                _ssi_out._command=_ssi_in._command;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            } else if(_ssi_in._command == SPI_SPI_COMMAND_RETURN_ENCODER_PINS_IN_BYTE) {
                //vozvrat flagov envodera dlya tladki
                _ssi_out._s4_massiv._ssss = (S4)GetEncoderPinsInByte();
                _ssi_out._command=_ssi_in._command;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            } else if(_ssi_in._command == SPI_SPI_COMMAND_GET_TEST_ENCODER_SHAGI) {
                //vozvrat flagov envodera dlya tladki
                #ifdef TEST_ENCODER_SHAGI
                _ssi_out._s4_massiv._ssss = _test_count_int;
                #else
                _ssi_out._s4_massiv._ssss = -1;
                #endif
                _ssi_out._command=_ssi_in._command;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            } else {
                //bez koncov vernem oshibku
                _ssi_out._s4_massiv._ssss = 0x3333;
                _ssi_out._command=SPI_SPI_COMMAND_RETURN_ERROR;
                _ssi_out._test_summ=Get_SPI_SPI_SumControl((U1*)&_ssi_out);
            }
        }
#ifdef TEST_SPI
        _ssi_out._s4_massiv._ssss++;
#endif
#ifdef WDT_ON_DEFINE
        restart_wdt();
#endif
#ifndef TEST_KVARC
        Add_next_from_timer_151_ms();
#endif
        ShowPinSecundomer();

	}

}

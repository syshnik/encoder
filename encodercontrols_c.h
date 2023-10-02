

void EncoderSbros() {
	//
        _ENC_NEW = _ENC_OLD = 0;

        //INIT FLAGS//INIT FLAGS//INIT FLAGS//INIT FLAGS//INIT FLAGS//INIT FLAGS//INIT FLAGS//INIT FLAGS
        _enc_position_PERESKOK=0;
        _enc_position_AFTER_FIND_END=_enc_position;
        _enc_position=0;
        _PERESKOK_FLAG=FALSE;
#ifdef TEST_ENCODER_SHAGI
        _test_count_int=0;
#endif

}
#define PLUSPLUS ++
#define MINUSMINUS --
/*
#if MY_NAME == USEL_X
#define PLUSPLUS ++
#define MINUSMINUS --
#endif
#if MY_NAME == USEL_Y
#define PLUSPLUS ++
#define MINUSMINUS --
#endif
#if MY_NAME == USEL_Z
#define PLUSPLUS --
#define MINUSMINUS ++
#endif
#if MY_NAME == USEL_A
#define PLUSPLUS --
#define MINUSMINUS ++
#endif
#if MY_NAME == USEL_B
#define PLUSPLUS --
#define MINUSMINUS ++
#endif

*/
inline void EncoderScan5(void)
{
        BOOL _OK_EncoderScan5;
        //right-00-10-11-01-00-10-11-01-00-10-11-01-00-10-11-01-00-10-11-01-00-10-11-01
        //left -00-10-00-01-11-10-00-01-11-10-00-01-11-10-00-01-11-10-00-01-11-10-00-01-11-10-00-01-11-10-00-01-11-10
        _OK_EncoderScan5=false;
        switch(_ENC_OLD)
	{
	case 2://d-10
		{
		if(_ENC_NEW == 3) {//d-11
                        _enc_position PLUSPLUS ;
                        _ENC_NEW_LEFT=false;
                        _OK_EncoderScan5=TRUE;
                } else if(_ENC_NEW == 0) {//d-00 
                        _enc_position MINUSMINUS ;
                        _ENC_NEW_LEFT=TRUE;
                        _OK_EncoderScan5=TRUE;
                }// else pereskochim=TRUE;
		break;
		}
 
	case 0://d-00
		{
		if(_ENC_NEW == 2) {//d-10
                        _enc_position PLUSPLUS ;
                        _ENC_NEW_LEFT=false;
                        _OK_EncoderScan5=TRUE;
                } else if(_ENC_NEW == 1) {//d-01
                        _enc_position MINUSMINUS ;
                        _ENC_NEW_LEFT=TRUE;
                        _OK_EncoderScan5=TRUE;
                }// else pereskochim=TRUE;
		break;
		}
	case 1://d-01
		{
		if(_ENC_NEW == 0) {//d-00
                        _enc_position  PLUSPLUS ;
                        _ENC_NEW_LEFT=false;
                        _OK_EncoderScan5=TRUE;
                } else if(_ENC_NEW == 3) {//d-11
                        _enc_position  MINUSMINUS ;
                        _ENC_NEW_LEFT=TRUE;
                        _OK_EncoderScan5=TRUE;
                }// else pereskochim=TRUE;
		break;
		}
	case 3://d-11
		{
		if(_ENC_NEW == 1) {//d-01
                        _enc_position PLUSPLUS ;
                        _ENC_NEW_LEFT=false;
                        _OK_EncoderScan5=TRUE;
                } else  if(_ENC_NEW == 2) {//d-10
                        _enc_position  MINUSMINUS ;
                        _ENC_NEW_LEFT=TRUE;
                        _OK_EncoderScan5=TRUE;
                }
		break;
		}
	}
        if(_OK_EncoderScan5) {
                _PERESKOK_FLAG=FALSE;
                _ENC_OLD = _ENC_NEW;
        } else {
                //pereskakivaem cherez shag
                if(_PERESKOK_FLAG) {
                        //2 pereskoka ne dopuskaem
                        //vosstanovim znacheniya
                        _PERESKOK_FLAG=FALSE;   
                        _ENC_NEW=_ENC_NEW_PERESKOK;
                        _ENC_OLD=_ENC_OLD_PERESKOK;
                        _enc_position=_enc_position_PERESKOK;
                } else {
                        //save
                        _ENC_NEW_PERESKOK=_ENC_NEW;
                        _ENC_OLD_PERESKOK=_ENC_OLD;
                        _enc_position_PERESKOK=_enc_position;
                        //init
                        if(_ENC_NEW_LEFT) {
                                _enc_position MINUSMINUS ;
                                _enc_position MINUSMINUS ;
                        } else  {
                                _enc_position PLUSPLUS ;
                                _enc_position PLUSPLUS ;
                        }
                        _ENC_OLD = _ENC_NEW;
                        //
                        _PERESKOK_FLAG=TRUE;   
                }
                
        }
}
/*
inline void SmenaNapravliniyaINTEXT_0_1() {
    //smena napravleniya srabativaniya prerivaniya
        if(!MPORT_A_ON) ext_int_edge(0, L_TO_H);
        else ext_int_edge(0, H_TO_L);
        if(!MPORT_B_ON) ext_int_edge(1, L_TO_H);
        else ext_int_edge(1, H_TO_L);
}*/

#ifdef TEST_DEBUG_MASSIVE1_IN_SHAGOVIK
inline void Encoder_AB_Timer_On(U1 bit3_A_0__B_1, U1 bit4_from_timer) {
#else
inline void Encoder_AB_Timer_On() {
#endif
        //BOOL propustim=FALSE;
        //test for right aon-aoff...
        //if(_epins.aon == _epins.aoff) propustim=TRUE;
        //if(_epins.bon == _epins.boff) propustim=TRUE;
        {//if(!propustim)  {
                //init
                _ENC_NEW=0;//(MPORT_A_ON ? 2 : 0)+(MPORT_B_ON ? 1 : 0);
                if(MPORT_A_ON == 0) _ENC_NEW|=2;
                if(MPORT_B_ON == 0) _ENC_NEW|=1;
#ifdef TEST_DEBUG_MASSIVE1_IN_SHAGOVIK
                _next_int_99++;
                /*Debug_Wright_IN_DEBUG_MASSIVE1_2_BIT((_ENC_NEW & 2), (_ENC_NEW & 1), bit3_A_0__B_1, bit4_from_timer);
                if(_vr_add_a_on_and_b_on) 
                        if(bit3_A_0__B_1==0) _vr_a_on++;
                if(_vr_add_a_on_and_b_on) 
                        if(bit3_A_0__B_1!=0) _vr_b_on++;
                
                if(_vr_add_a_on_and_b_on) 
                        if((_ENC_OLD & 2) != (_ENC_NEW & 2) && (_ENC_OLD & 1) != (_ENC_NEW & 1)) _vr_b_on++;
                if(_vr_add_a_on_and_b_on) 
                        if(_ENC_OLD == _ENC_NEW) _vr_a_on++;
                 
                //if((_ENC_OLD & 2) != (_ENC_NEW & 2) && (_ENC_OLD & 1) != (_ENC_NEW & 1)) _vr_a_on++;
                //if(propustim) if(bit4_from_timer)
               
                //if(propustim) if(bit3_A_0__B_1 && !bit4_from_timer) _vr_b_on++; */
                if(_ENC_OLD == _ENC_NEW) _vr_b_on++;
                else _vr_a_on++;
#endif
                //encoder
#ifdef TEST_TestSpeedFor_LocAL_restart_wdt_and_CAN_GET_and_INT_EXT_AND_INT_EXT1
                EncoderScan5();
                //SmenaNapravliniyaINTEXT_0_1();
#else
                if(_ENC_OLD != _ENC_NEW) {
                        EncoderScan5();
                        //SmenaNapravliniyaINTEXT_0_1();
                } 
#endif
        }
}










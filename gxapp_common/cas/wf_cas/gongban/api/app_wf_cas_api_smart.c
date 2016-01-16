/*****************************************************************************
* 						   CONFIDENTIAL
*        Hangzhou GuoXin Science and Technology Co., Ltd.
*                      (C)2012, All right reserved
******************************************************************************

******************************************************************************
* File Name :	app_ca_api.c
* Author    : 	zhouhm
* Project   :	goxceed dvbc
* Type      :
******************************************************************************
* Purpose   :	ģ��ͷ�ļ�
******************************************************************************
* Release History:
VERSION	Date			  AUTHOR         Description
1.0  	2012.12.02		  zhouhm 	 			creation
*****************************************************************************/
#include "app_common_play.h"
#include "app_common_porting_stb_api.h"
#include "app_common_search.h"
#include "app_common_porting_ca_flash.h"
#include "app_common_porting_ca_smart.h"
#include "app_common_porting_ca_demux.h"
#include "app_common_porting_ca_descramble.h"
//#include "app_wf_cas_api_demux.h"
#include "app_wf_cas_api_smart.h"

#include "wanfacas.h"

#define RUNTIME_ETU                         (372)
#define RUNTIME_BAUD_RATE                   (9600*RUNTIME_ETU)
#if (RC_VERSION>=GOXCEED_v1_9_4)
#define RUNTIME_EGT                         (RUNTIME_ETU * 2)
#define RUNTIME_WDT                         (15 * RUNTIME_ETU)
#else
#define RUNTIME_EGT                         (RUNTIME_ETU * 20)
#define RUNTIME_WDT                         (45 * RUNTIME_ETU)
#endif

#define RUNTIME_TGT                         (0)
#define RUNTIME_TWDT                        (3*9600 * RUNTIME_ETU)


uint8_t app_wf_cas_api_smart_check_valid(void)
{
    uint8_t valid_art[]={0x3b,0x6d,0x00,0x00,0x57};
	uint8_t len;
	uint8_t i;
	uint8_t atr[ATR_MAX_LEN] = {0,};
	uint8_t ret = 0;

	app_wf_cas_api_smart_init();
	ret = app_wf_cas_api_smart_reset(atr, &len);
	if (FALSE == ret)
	{
		printf(" smart card is not wf cas smart \n");
		return FALSE;
	}
    
	for (i=0; i<sizeof(valid_art); i++)
	{
		if (valid_art[i]!=atr[i])
		{
			printf(" smart card is not wf cas smart \n");
			return FALSE;
		}
	}
	printf(" smart card is wf cas smart\n");
    
	return TRUE;	
}

void app_wf_cas_api_smart_init(void)
{

	   GxSmcParams	  param;
	   GxSmcTimeParams	  time;
	   
	   memset(&time,0,sizeof(GxSmcTimeParams));
	   memset(&param,0,sizeof(GxSmcParams));
   
	   time.baud_rate  = RUNTIME_BAUD_RATE;
	   time.egt 	   = RUNTIME_EGT;
	   time.etu 	   = RUNTIME_ETU;
	   time.tgt 	   = RUNTIME_TGT;
	   time.twdt	   = RUNTIME_TWDT;
	   time.wdt 	   = RUNTIME_WDT;
   
	   param.detect_pole = GXSMC_DETECT_HIGH_LEVEL;
	   param.io_conv = GXSMC_DATA_CONV_DIRECT;
	   param.parity = GXSMC_PARITY_ODD;//GXSMC_PARITY_EVEN;
	   param.protocol = DISABLE_REPEAT_WHEN_ERR;
	   param.sci_sel = __GXSMART_SCI2;
	   param.stop_len = GXSMC_STOPLEN_0BIT;
	   param.vcc_pole = GXSMC_VCC_HIGH_LEVEL;
	   param.default_etu = 372;
	   param.auto_etu = 1;
	   param.auto_parity = 1;
 //    param.debug_info = O_BDBG|O_CDBG;
   
        return app_porting_ca_smart_card_init(param,time);
	
}

uint8_t app_wf_cas_api_smart_reset(uint8_t* pbyATR, uint8_t *pbyLen )
{
	 GxSmcTimeParams    time;
	 time.baud_rate  = RUNTIME_BAUD_RATE;
	 time.egt        = RUNTIME_EGT;
	 time.etu        = RUNTIME_ETU;
	 time.tgt        = RUNTIME_TGT;
	 time.twdt       = RUNTIME_TWDT;
	 time.wdt        = RUNTIME_WDT;

	 return app_porting_ca_smart_reset(time,pbyATR,pbyLen);
}

uint8_t app_wf_cas_api_card_in(char* atr,uint8_t len)
{
	CAS_Dbg("%s\n",__FUNCTION__);
	WFCAS_CardEventNotify(TRUE);
	app_play_clear_ca_msg();
	app_play_set_msg_pop_type(50);		//��ʾ���ܿ����ڳ�ʼ��
	return 1;
}

uint8_t app_wf_cas_api_card_out(void)
{
	CAS_Dbg("%s\n",__FUNCTION__);
	WFCAS_CardEventNotify(FALSE);
	return 1;
}
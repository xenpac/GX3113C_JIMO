/*****************************************************************************
* 						   CONFIDENTIAL
*        Hangzhou GuoXin Science and Technology Co., Ltd.
*                      (C)2012, All right reserved
******************************************************************************

******************************************************************************
* File Name :	app_mg_cas_api_smart.c
* Author    : 	zhouhm
* Project   :	goxceed dvbc
* Type      :
******************************************************************************
* Purpose   :	
******************************************************************************
* Release History:
VERSION	Date			  AUTHOR         Description
1.0  	2014.04.11		  zhouhm 	 			creation
2.0  2014.12.16              wangjian         modify for Runde 3113c mgcas3.1.2
*****************************************************************************/
#include "app_common_play.h"
#include "app_common_porting_stb_api.h"
#include "app_mg_cas312_api_smart.h"
#include "app_common_porting_ca_flash.h"
#include "app_common_porting_ca_smart.h"
#include "app_common_porting_ca_demux.h"
#include "app_common_porting_ca_descramble.h"
#include "app_mg_cas312_api_demux.h"
#include "mg312def.h"

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

extern char*  MGCA312_Get_Config_Serial(void);

uint8_t app_mg_cas312_api_smart_check_valid(void)
{
	uint8_t valid_art[4] = {0x3B,0x6f,0x00,0x00};
	uint8_t len;
	uint8_t i;
	uint8_t atr[ATR_MAX_LEN] = {0,};
	uint8_t ret = 0;

	app_mg_cas312_api_smart_init();
	ret = app_mg_cas312_api_smart_reset(atr, &len);
	if (FALSE == ret)
	{
		printf("Smartcard is not mg cas312 smart!!!\n");
		return FALSE;
	}
	
	for (i = 0; i < 4; i++)
	{
		if (valid_art[i] != atr[i])
		{
			printf("Smartcard is not mg cas312 smart!!!\n");
			return FALSE;
		}
	}
	
	printf("Smartcard is mg cas312 smart!!!\n");
	return TRUE;	
}

//智能卡初始化
void app_mg_cas312_api_smart_init(void)
{
	GxSmcParams    param;
	GxSmcTimeParams    time;
	
	memset(&time,0,sizeof(GxSmcTimeParams));
	memset(&param,0,sizeof(GxSmcParams));

	time.baud_rate  = RUNTIME_BAUD_RATE;
	time.egt        = RUNTIME_EGT;
	time.etu        = RUNTIME_ETU;
	time.tgt        = RUNTIME_TGT;
	time.twdt       = RUNTIME_TWDT;
	time.wdt        = RUNTIME_WDT;

	param.detect_pole = GXSMC_DETECT_HIGH_LEVEL;
    param.io_conv = GXSMC_DATA_CONV_DIRECT;
	param.parity = GXSMC_PARITY_ODD;
    param.protocol = DISABLE_REPEAT_WHEN_ERR;
    param.sci_sel = __GXSMART_SCI2;
    param.stop_len = GXSMC_STOPLEN_0BIT;
    param.vcc_pole = GXSMC_VCC_HIGH_LEVEL;
    param.default_etu = 372;
	param.auto_etu = 1;
	param.auto_parity = 1;

    return app_porting_ca_smart_card_init(param,time);
}

//智能卡复位
uint8_t app_mg_cas312_api_smart_reset(uint8_t *pbyATR, uint8_t *pbyLen)
{
	 GxSmcTimeParams    time;
	memset(&time,0,sizeof(GxSmcTimeParams));
	 time.baud_rate  = RUNTIME_BAUD_RATE;
	 time.egt        = RUNTIME_EGT;
	 time.etu        = RUNTIME_ETU;
	 time.tgt        = RUNTIME_TGT;
	 time.twdt       = RUNTIME_TWDT;
	 time.wdt        = RUNTIME_WDT;

	 return app_porting_ca_smart_reset(time, pbyATR, pbyLen);
}

//智能卡插入回调
uint8_t app_mg_cas312_api_card_in(char *atr, uint8_t len)
{
	char* mgcas_serial = NULL;
	
	mgcas_serial = MGCA312_Get_Config_Serial();
	MG_Info_CardInserted((MG_U8 *)atr, (MG_U8 *)mgcas_serial);

    //清除告警消息
	app_play_clear_msg_pop_type(MSG_POP_COMMON_END+CA_MG_ERR_CARD_NOTFOUND+1); 
	app_mg_cas312_api_reset_emm_filter();
	return 1;
}

uint8_t app_mg_cas312_api_card_out(void)
{
	MG_Info_CardRemoved();

	return 1;
}



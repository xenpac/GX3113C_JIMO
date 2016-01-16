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
#include "app_cd_cas_3.0_api_smart.h"
#include "app_common_porting_ca_flash.h"
#include "app_common_porting_ca_smart.h"
#include "app_common_porting_ca_demux.h"
#include "app_common_porting_ca_descramble.h"
#include "app_cd_cas_3.0_api_demux.h"
#include "CDCASS.h"

#define RUNTIME_ETU                         (372)
#define RUNTIME_BAUD_RATE                   (9600*RUNTIME_ETU)
#if defined(APP_SD) && (RC_VERSION>=GOXCEED_v1_9_3_1)
#define RUNTIME_EGT                         (RUNTIME_ETU * 2)
#define RUNTIME_WDT                         (15 * RUNTIME_ETU)
#else
#define RUNTIME_EGT                         (RUNTIME_ETU * 20)
#define RUNTIME_WDT                         (45 * RUNTIME_ETU)
#endif
#define RUNTIME_TGT                         (0)
#define RUNTIME_TWDT                        (3*9600 * RUNTIME_ETU)

uint8_t app_cd_cas30_api_smart_check_valid(void)
{
	uint8_t valid_art[8]={0x3B,0x6C,0x00,0x00,0x4E,0x54,0x49,0x43};
	uint8_t len;
	uint8_t i;
	uint8_t atr[ATR_MAX_LEN] = {0,};
	uint8_t ret = 0;

	app_cd_cas30_api_smart_init();
	ret = app_cd_cas30_api_smart_reset(atr, &len);
	if (FALSE == ret)
	{
		printf(" smart card is not cd cas30 smart \n");
		return FALSE;
	}
	if((atr[0] != 0x3B) && (atr[0] != 0x3F))
	{
		printf(" ATR[0] is not 0x3b or 0x3f \n");
		return FALSE;
	}
	for (i=1; i<8; i++)
	{
		if (valid_art[i]!=atr[i])
		{
			printf(" smart card is not cd cas30 smart \n");
			return FALSE;
		}
	}
		printf(" smart card is cd cas30 smart\n");
		return TRUE;	
}

void app_cd_cas30_api_smart_init(void)
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
#if (PANEL_TYPE == PANEL_TYPE_CT1642_JINYA)||(PANEL_TYPE == PANEL_TYPE_2KEY)
	param.detect_pole = GXSMC_DETECT_LOW_LEVEL;
#else
	param.detect_pole = GXSMC_DETECT_HIGH_LEVEL;
#endif
    param.io_conv = GXSMC_DATA_CONV_DIRECT;
	param.parity = GXSMC_PARITY_ODD;// GXSMC_PARITY_EVEN;
    param.protocol = DISABLE_REPEAT_WHEN_ERR;
    param.sci_sel = __GXSMART_SCI2;
    param.stop_len = GXSMC_STOPLEN_0BIT;
    param.vcc_pole = GXSMC_VCC_HIGH_LEVEL;
    param.default_etu = 372;
	param.auto_etu = 1;
	param.auto_parity = 1;
//	param.debug_info = O_BDBG|O_CDBG;

    return app_porting_ca_smart_card_init(param,time);
	
}

uint8_t app_cd_cas30_api_smart_reset(uint8_t* pbyATR, uint8_t *pbyLen )
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


uint8_t app_cd_cas30_api_card_in(char* atr,uint8_t len)
{
	CDCA_BOOL bRet = CDCA_FALSE;
	bRet = CDCASTB_SCInsert();
	CAS_Dbg("CDCASTB_SCInsert ret=%d\n",bRet);
	if (CDCA_FALSE == bRet)
		return 0;
	
	return 1;
}

uint8_t app_cd_cas30_api_card_out(void)
{
	CAS_Dbg("CDCASTB_SCRemove\n");
	CDCASTB_SCRemove();
	return 1;
}



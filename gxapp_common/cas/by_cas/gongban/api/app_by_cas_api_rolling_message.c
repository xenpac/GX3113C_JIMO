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
* Purpose   :	模块头文件
******************************************************************************
* Release History:
VERSION	Date			  AUTHOR         Description
1.0  	2012.12.02		  zhouhm 	 			creation
*****************************************************************************/
#include "BYCAca_stb.h"
#include "app_common_porting_stb_api.h"
#include "app_by_cas_api_pop.h"
#include "app_by_cas_api_rolling_message.h"
#include "gxmsg.h"


static by_ca_rolling_message_st ca_rolling_msg = {0};
static GxTime nowtime={0};
static GxTime starttime={0};

extern 	void by_cas_rolling_message_show(uint8_t byStyle,uint8_t showFlag,char* message);
extern 	int32_t by_cas_rolling_message_get_times(void);

int32_t app_by_cas_gxmsg_ca_on_event_rolling(GxMsgProperty0_OnEvent* event)
{
	by_ca_rolling_message_st* rolling_msg = NULL;
	if (NULL == event)
		return 0;

	rolling_msg = (by_ca_rolling_message_st*)(event->buf);

	if (NULL == rolling_msg)
		return 0;
	
	memcpy(&ca_rolling_msg,rolling_msg,sizeof(by_ca_rolling_message_st));

	by_cas_rolling_message_show(0,DVB_CA_ROLLING_FLAG_RESET,(char*)ca_rolling_msg.content);
	ca_rolling_msg.wTimes= 0;
	ca_rolling_msg.roll_status=FALSE;
	ca_rolling_msg.wStatus = TRUE;
	
	return 1;
}

int32_t app_by_cas_rolling_message_exec(void)
{
	char* curFocusWin = (char *)GUI_GetFocusWindow();
	
	if ((NULL != curFocusWin) && (strcasecmp(curFocusWin, "win_full_screen") != 0))
	{
		return TRUE;
	}

	if (TRUE == ca_rolling_msg.wStatus )
		{
			if (FALSE == ca_rolling_msg.roll_status)
				{
					by_cas_rolling_message_show(0,DVB_CA_ROLLING_FLAG_SHOW,(char*)ca_rolling_msg.content);
					ca_rolling_msg.roll_status= TRUE;	
					GxCore_GetTickTime(&starttime);	
					ca_rolling_msg.wStartTime = starttime.seconds;	
				}

			if (0 != ca_rolling_msg.wDuration)
				{
						GxCore_GetTickTime(&nowtime);	
						if (nowtime.seconds - starttime.seconds >= ca_rolling_msg.wDuration)				
						{
							ca_rolling_msg.wTimes = by_cas_rolling_message_get_times();
							if (ca_rolling_msg.wTimes >=  1)
								{	
									by_cas_rolling_message_show(0,DVB_CA_ROLLING_FLAG_HIDE,NULL);
									ca_rolling_msg.wStatus = FALSE;
									ca_rolling_msg.roll_status= FALSE;
									ca_rolling_msg.wTimes= 0;
			//						ca_rolling_msg.wDuration=0;
			//						ca_rolling_msg.wStartTime=0; 
		//							BYCASTB_ShowOSDMsgOver(nowtime.seconds - starttime.seconds);								
								}
						}					
				}
			else
				{
					ca_rolling_msg.wTimes = by_cas_rolling_message_get_times();
					if (ca_rolling_msg.wTimes >=  1)
					{
//						GxCore_GetTickTime(&nowtime);	
					       // 查询滚动结束，清除OSD滚动标志
						ca_rolling_msg.wStatus = FALSE;
						ca_rolling_msg.roll_status= FALSE;	
						by_cas_rolling_message_show(0,DVB_CA_ROLLING_FLAG_HIDE,NULL);
						ca_rolling_msg.wTimes= 0;
	//					ca_rolling_msg.wDuration=0;
	//					ca_rolling_msg.wStartTime=0; 
//						BYCASTB_ShowOSDMsgOver(nowtime.seconds - starttime.seconds);
					}
				
				}
		}
	else
		{
			if (TRUE == ca_rolling_msg.roll_status)
				{
					by_cas_rolling_message_show(0,DVB_CA_ROLLING_FLAG_HIDE,NULL);
					ca_rolling_msg.roll_status= FALSE;
	//				ca_rolling_msg.wTimes= 0;
	//				ca_rolling_msg.wDuration=0;
	//				ca_rolling_msg.wStartTime=0; 
				}
		}
	return TRUE;
}


void app_by_cas_rolling_message_hide(void)
{
	printf("[app_qz_cas_rolling_message_hide]----------\n");
	if (TRUE == ca_rolling_msg.roll_status)
	{
		by_cas_rolling_message_show(0, DVB_CA_ROLLING_FLAG_RESET,\
				   				(char *)ca_rolling_msg.content);
		ca_rolling_msg.roll_status = FALSE;
	}
	return;
}






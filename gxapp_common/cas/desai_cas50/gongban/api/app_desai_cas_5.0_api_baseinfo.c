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
#include "desai_ca_api.h"
#include "app_common_porting_stb_api.h"
#include "app_desai_cas_5.0_api_baseinfo.h"

#define LANGUAGE_CHINESE ("Chinese")
#define LANGUAGE_ENGLISH ("English")

UINT8 * app_desai_cas50_api_get_baseinfo_data(ca_get_date_t *data)
{
	uint32_t pos = 0 ;                             
	uint32_t ID = 0;  

	EN_ERR_CAS ret;

    	static UINT8 s_text_buffer[200]={0};
	char* osd_language=NULL;

	uint8_t  pucCardType;
	ST_WORKTIME_INFO pstWorkTime;
	uint8_t pucWorkLevel;

	if (NULL == data)
		return NULL;
	
	if (DVB_CA_BASE_INFO != data->date_type)
		return NULL;

	pos = data->pos;
	ID = data->ID;

	memset(s_text_buffer,0,sizeof(s_text_buffer));

	switch(ID)
		{
			case DS_BASEINFO_OPERATE_ID:
				if(DSCA_GetOperatorID(s_text_buffer) == CA_ERROR_OK)
				{			
					return s_text_buffer;	
				}
				break;
			case DS_BASEINFO_CARD_SN_ID:
				if(DSCA_GetCardNo(s_text_buffer, &pucCardType)==CA_ERROR_OK)
				{
					return s_text_buffer;
				}
				break;
			case DS_BASEINFO_GROUP_ID:
				if(DSCA_GetGroupId(s_text_buffer)==CA_ERROR_OK)
				{
					return s_text_buffer;
				}
				break;
			case DS_BASEINFO_LCO_ID:
				if(DSCA_GetLCO(s_text_buffer)==CA_ERROR_OK)
				{
					return s_text_buffer;
				}
				break;
			case DS_BASEINFO_CARDREG_ID:
				if(DSCA_GetCardRegion(s_text_buffer)==CA_ERROR_OK)
				{
					return s_text_buffer;
				}
				break;
			case DS_BASEINFO_CARDSTATE_ID:
				ret=DSCA_GetCardState();
				
				osd_language = app_flash_get_config_osd_language();
				if (0 == strcmp(osd_language,LANGUAGE_CHINESE))
				{
					switch(ret)
					{
						case CA_ERROR_CARD_CANCELED://卡已注销 
							sprintf((char *)s_text_buffer,"%s", "卡已注销 ");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_PENDING://卡未激活 
							sprintf((char *)s_text_buffer,"%s", "卡未激活 ");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_OUTTIME ://卡已过期
							sprintf((char *)s_text_buffer,"%s", "卡已过期");
							return s_text_buffer;
							break;
						case CA_ERROR_IC_INVALID://卡无效 
							sprintf((char *)s_text_buffer,"%s", "卡无效 ");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_NOPAIR://不要求配对 
							sprintf((char *)s_text_buffer,"%s", "不要求配对 ");
							return s_text_buffer;
							break;
						case CA_ERROR_OK://已和本机配对
							sprintf((char *)s_text_buffer,"%s", "已和本机配对");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_PAIROTHER://已和其他的机顶盒配对
							sprintf((char *)s_text_buffer,"%s", "已和其他的机顶盒配对");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_STOP:
							sprintf((char *)s_text_buffer,"%s", "卡已停用");
							return s_text_buffer;
							break;
						default :
							sprintf((char *)s_text_buffer,"%s", "其他错误!");
							return s_text_buffer;
							break;
					}

				}
				else
				{
					switch(ret)
					{
						case CA_ERROR_CARD_CANCELED://卡已注销 
							sprintf((char *)s_text_buffer,"%s", "CARDLOGOUT");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_PENDING://卡未激活 
							sprintf((char *)s_text_buffer,"%s", "CARDNOTACTIVE");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_OUTTIME ://卡已过期
							sprintf((char *)s_text_buffer,"%s", "ENTITLE_EXPIRED");
							return s_text_buffer;
							break;
						case CA_ERROR_IC_INVALID://卡无效 
							sprintf((char *)s_text_buffer,"%s", "IC_INVALID");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_NOPAIR://不要求配对 
							sprintf((char *)s_text_buffer,"%s", "CARD_NOPAIR");
							return s_text_buffer;
							break;
						case CA_ERROR_OK://已和本机配对
							sprintf((char *)s_text_buffer,"%s", "CARD_MATCH");
							return s_text_buffer;
							break;
						case CA_ERROR_CARD_PAIROTHER://已和其他的机顶盒配对
							sprintf((char *)s_text_buffer,"%s", "CARD_PAIROTHER");
							return s_text_buffer;
							break;
						default :
							sprintf((char *)s_text_buffer,"%s", "Other Error!");
							return s_text_buffer;
							break;
					}
				}
				break;
			case DS_BASEINFO_WORK_TIME_ID:
				ret = DSCA_GetWorkTime(&pstWorkTime);
				if(ret == CA_CARD_SUCCESS)
				{
					sprintf((char *)s_text_buffer,"%02d:%02d-%02d:%02d",pstWorkTime.stBeginTime.ucHour,pstWorkTime.stBeginTime.ucMinute,
						pstWorkTime.stEndTime.ucHour,pstWorkTime.stEndTime.ucMinute);
					CAS_Dbg("s_text_buffer:%d==%s\n",__LINE__,s_text_buffer);
					return s_text_buffer;
				}
				break;
			case DS_BASEINFO_VERSION_ID:
				ret = DSCA_GetCAVer(s_text_buffer);
				CAS_Dbg("s_text_buffer:%d==%s\n",__LINE__,s_text_buffer);
				if(ret == CA_ERROR_OK)
					return s_text_buffer;
				break;
			case DS_BASEINFO_RATTING_ID:
				ret = DSCA_GetWorkLevel(&pucWorkLevel);
				if(ret == CA_CARD_SUCCESS)
					sprintf((char *)s_text_buffer,"%d",pucWorkLevel);
				return s_text_buffer;
				break;
			case DS_BASEINFO_CARDVER_ID:
				if(DSCA_GetCardVersion(s_text_buffer)==CA_ERROR_OK)
				{
					return s_text_buffer;
				}
				break;
			case DS_BASEINFO_MOTHER_CARD_ID:
				if(DSCA_GetMasterCard(s_text_buffer) == CA_ERROR_OK)
				{
					return s_text_buffer;
				}
				break;
			default:
				break;
		}
	return NULL;

}







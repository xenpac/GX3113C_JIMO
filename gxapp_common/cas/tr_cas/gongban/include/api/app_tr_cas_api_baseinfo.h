/**
 *
 * @file        app_tr_cas_api_baseinfo.h
 * @brief
 * @version     1.1.0
 * @date        12/04/2013 
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_TR_CAS_API_BASEINFO_H__
#define __APP_TR_CAS_API_BASEINFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app_common_play.h"

typedef enum 
{
	TR_BASEINFO_SERIAL_ID = 0,
	TR_BASEINFO_COS_VER_ID,
	TR_BASEINFO_CAS_VER_ID,
	TR_BASEINFO_MANU_NAME_ID,
	TR_BASEINFO_MOTHER_ID,
	TR_BASEINFO_MOTHER_NUMBER_ID,
	TR_BASEINFO_LOCK_ID,
	TR_BASEINFO_RATING_ID,
	TR_BASEINFO_WORK_TIME_ID,
	TR_BASEINFO_AREA_ID,
	TR_BASEINFO_AREA_LOCK,
	TR_BASEINFO_AREA_TIME,
	TR_BASEINFO_MARRY_STATE /*wangjian add on 20150107*/
}TRCA_BASEIINFO_ID_E;


int32_t app_tr_cas_api_init_baseinfo_data(void);
char* app_tr_cas_api_get_baseinfo_data(ca_get_date_t *data);


#ifdef __cplusplus
}
#endif

#endif /*__APP_DVT_CAS_API_BASEINFO_H__*/


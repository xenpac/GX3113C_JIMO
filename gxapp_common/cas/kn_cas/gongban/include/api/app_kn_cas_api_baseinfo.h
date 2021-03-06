/**
 *
 * @file        app_by_cas_api_baseinfo.h
 * @brief
 * @version     1.1.0
 * @date        11/30/2012 09:47:49 AM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_KNCAS_API_BASEINFO_H__
#define __APP_KNCAS_API_BASEINFO_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "app_common_play.h"

typedef enum 
{
	KN_BASEINFO_VERSION_ID=0,
	KN_BASEINFO_SYS_SP_ID,
	KN_BASEINFO_SYS_CT_ID,
	KN_BASEINFO_CARDID_ID
}KNCA_BASEIINFO_ID_E;

int32_t app_kn_cas_api_init_baseinfo_data(void);
char * app_kn_cas_api_get_baseinfo_data(ca_get_date_t *data);


#ifdef __cplusplus
}
#endif
#endif /*__APP_KNCAS_API_BASEINFO_H__*/


/**
 *
 * @file        divitone_ads_porting.h
 * @brief
 * @version     1.1.0
 * @date        11/27/2013 
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_DIVITONE_ADS_PORTING_H__
#define __APP_DIVITONE_ADS_PORTING_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <gxtype.h>
#include "gxbus.h"
typedef struct ad_divitone_items_s
{
	uint8_t		ads_Type;
	uint8_t		ads_file_type;
	uint16_t		lastSectionNum;
	uint16_t		recieveNum;
	uint8_t		ads_is_finish;
	uint8_t		ads_is_show;
	uint8_t		ads_show_time;
	uint8_t		ads_show_pos;
	uint32_t	ads_cmd;
}ad_divitone_items_t;
void app_divitone_ads_init(void);
void app_divitone_ads_filter_notify(handle_t Filter, const uint8_t* Section, size_t Size);
handle_t app_divitone_ads_get_filter_handle(void);
int GxAD_ItemFilterClose(void);
int GxAD_LoadData(void) ;

uint8_t advertisement_get_ad_version_flag();
void advertisement_set_ad_version_flag(uint8_t version_flag);
void advertisement_set_ad_version_flag(uint8_t version_flag);
uint8_t advertisement_set_timeout_flag(uint8_t flag);
uint8_t advertisement_get_timeout_flag();
uint8_t advertisement_get_startplayflag(void);
uint8_t advertisement_set_startplayflag(uint8_t flag);


#ifdef __cplusplus
}
#endif
#endif /*__APP_3H_ADS_PORTING_H__*/


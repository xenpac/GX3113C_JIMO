#ifndef _GXAPP_SYS_CONFIG_H_
#define _GXAPP_SYS_CONFIG_H_
  
  
#include "remote_enum.h"
#include "panel_enum.h"
#include "demod_enum.h"
#include "ota_enum.h"
#include "goxceed_csky.h"
#include "tuner_enum.h"
#define RC_VERSION GOXCEED_v1_9_4
#define LOGO_PATH "/theme/logo.bin"
#define I_FRAME_PATH "/theme/logo.bin"
  
  
#define CA_FLAG 
#define FACTORY_SERIALIZATION_SUPPORT  0
#define DVB_CA_DV DVB_CA_TYPE_MG
#define DVB_CA_TYPE_MG_FLAG
  
  
#define USB_FLAG 
#define CUST_SHANXI
#define DVB_JPG_LOGO 1
#define DVB_HD_LIST 0
#define AUDIO_DOLBY 0
#define DVB_PVR_FLAG 1
#define DVB_NETWORK_FLAG 0
#define LINUX_OTT_SUPPORT 0
#define MEDIA_SUBTITLE_SUPPORT 0
#define LOGO_SHOW_DELAY 1
  
  
#define DVB_DEMOD_TYPE DVB_DEMOD_ATBM886X
#define DVB_DEMOD_MODE DVB_DEMOD_DTMB
#define DVB_TS_SRC 2
  
#define TUNER_TYPE 62
#define REMOTE_TYPE KEY_THINEWTEC
  
#define PANEL_TYPE PANEL_TYPE_fd650_THINEWTEC
#define PANEL_CLK_GPIO 36
#define PANEL_DATA_GPIO 35
#define PANEL_STANDBY_GPIO 34
#define PANEL_LOCK_GPIO 33
  
#define DVB_OTA_TYPE DVB_NATIONALCHIP_OTA
  
  
#define APP_SD 1
#define SYSC_MODE 0
#define VIDEO_WINDOW_X 0
#define VIDEO_WINDOW_Y 0
#define VIDEO_WINDOW_W 720
#define VIDEO_WINDOW_H 576
#define SAT_MAX_NUM 1
#define TP_MAX_NUM 200
#define SERVICE_MAX_NUM 1000
#define PAT_FILTER_TIMEOUT 3000
#define SDT_FILTER_TIMEOUT 5000
#define NIT_FILTER_TIMEOUT 10000
#define PMT_FILTER_TIMEOUT 8000
#define TRICK_PLAY_SUPPORT 0
#define PROG_MAX_LCN 500
#define DVB_CENTER_FRE 690
#define DVB_CENTER_SYMRATE 6875
#define DVB_CENTER_QAM 2
  
  
#endif
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
#include "CDCASS.h"
#include "app_common_porting_ca_flash.h"
#include "app_common_porting_ca_demux.h"
#include "app_common_porting_ca_os.h"
#include "app_common_porting_ca_smart.h"
#include "app_common_porting_ca_descramble.h"
#include "app_common_play.h"
#include "app_cd_cas_3.0_api_demux.h"
#include "app_cd_cas_3.0_api_pop.h"
#include "app_common_porting_stb_api.h"
#include "app_cd_cas_3.0_api_smart.h"
#include "app_cd_cas_3.0_api_lock_service.h"
#include "gxplayer_url.h"
	
unsigned char CDCas_Flag = 0;

void Init_CAS(unsigned char bDebugOpen)
{
    CDCas_Flag = bDebugOpen;
}

#define CAS_PORTING_DEBUG(...)                   do {       if(CDCas_Flag){                                     \
                                                    printf("[CDCA PORTING]");                        \
                                                    printf(__VA_ARGS__);  }                      \
                                                } while(0)

#define CAS_PORTING_DUMP(str, ptr, size)                                                                    \
                do {   if(CDCas_Flag) {                                                                     \
                    int i;                                                                  \
                    printf("len:%d,%s=",size,str);		\
                    if (size != 0) {                                                        \
                        for (i = 0; i < (size); i++) {                                      \
                            printf("%02x ", (ptr)[i]);                                      \
                        }                                                                   \
                    }  \
                    printf("\n");   \
                    } \
                } while (0)

extern 	int32_t app_cd_cas30_api_get_uniqueid(uint32_t *pdwUniqueID);
static cd_cas30_finger_data_st  fingerdata = {0};
static cd_cas30_rolling_message_st  rollingmsg = {0};
static cd_cas30_detitle_st detitleflag = {0};
static cd_cas30_email_st emailflag= {0};
static cd_cas30_ippv_buy_st ippvbuy = {0};
static cd_cas30_card_update_st card_update = {0};
static cd_cas30_feed_st feed = {0};
uint16_t cdcasNeedNitDataFlag = 0;

void cd_cas_30_private_data_got( CDCA_U8        byReqID,
								  	CDCA_BOOL      bTimeout,
									CDCA_U16       wPid,
									const CDCA_U8* pbyReceiveData,
									CDCA_U16       wLen            )
{
	CAS_PORTING_DEBUG("CDCASTB_PrivateDataGot invoked:byReqID=0x%02x,bTimeout=%d,wPid=0x%x,wLen=%d,",
		byReqID,bTimeout,wPid,wLen);
//	CAS_PORTING_DUMP("pbyReceiveData",pbyReceiveData, wLen);
	printf("\n");

	CDCASTB_PrivateDataGot( byReqID,
							bTimeout,
							wPid,
							pbyReceiveData,
							wLen);
}
/* �ͷ�˽�����ݹ����� */
void CDSTBCA_ReleasePrivateDataFilter( CDCA_U8  byReqID, CDCA_U16 wPid )
{
	uint32_t filterId = 0;
	bool releaseChannel = TRUE;
	ca_filter_t sfilter = {0};

	/*
	* ���Ҷ�Ӧchannel id , filter id
	*/
	if (0x10 == wPid)
	{
		cdcasNeedNitDataFlag = 0;
		return;
	}
	
//	CAS_Dbg("CDSTBCA_ReleasePrivateDataFilter  byReqID=0x%x,  wPid=0x%x \n",
//		byReqID,wPid);

	for (filterId = 0; filterId< MAX_FILTER_COUNT;filterId++)
	{
		app_porting_ca_demux_get_by_filter_id(filterId,&sfilter);
		if (( 0 != sfilter.usedStatus)&&(0 != sfilter.handle)&&(0 != sfilter.channelhandle)
			&&(wPid == sfilter.pid)&&(byReqID == sfilter.byReqID))
		{
			releaseChannel = TRUE;

			app_porting_ca_demux_release_filter( filterId, releaseChannel);
			return ;

		}
	}

	return ;
}



/* ��ȡ�洢�ռ� */
void CDSTBCA_ReadBuffer( CDCA_U8   byBlockID,
                                CDCA_U8*  pbyData,
                                CDCA_U32* pdwLen )
{
	uint32_t  Offset = 0;
	if ((NULL == pbyData)||(NULL == pdwLen))
	{
		CA_FAIL(" CDSTBCA_ReadBuffer   failed \n");
		return ;
	}

	if (CDCA_FLASH_BLOCK_A == byBlockID)
	{
		Offset = 0;
	}
	else if (CDCA_FLASH_BLOCK_B == byBlockID)
	{
		Offset = 0x10000;
	}
	else
	{
		CA_FAIL(" CDSTBCA_ReadBuffer   failed \n");
		return ;
	}
		
	app_porting_ca_flash_read_data(Offset,(uint8_t *)pbyData,(uint32_t*)pdwLen);

	return ;
}


/* д��洢�ռ� */
void CDSTBCA_WriteBuffer( CDCA_U8        byBlockID,
                                 const CDCA_U8* pbyData,
                                 CDCA_U32       dwLen )
{
	uint32_t  Offset = 0;
	if (NULL == pbyData)
	{
//		CA_FAIL((" CDSTBCA_WriteBuffer   failed \n"));
		return ;
	}


	if (CDCA_FLASH_BLOCK_A == byBlockID)
	{
		Offset = 0;
	}
 	else if (CDCA_FLASH_BLOCK_B == byBlockID)
	{
		Offset = 0x10000;
	}
	else
	{
//				CA_FAIL((" CDSTBCA_WriteBuffer   failed \n"));
		return ;
	}

	app_porting_ca_flash_write_data(Offset,(uint8_t*)pbyData,dwLen);
	return ;
}




/* �̹߳��� */
void CDSTBCA_Sleep(CDCA_U16 wMilliSeconds)
{

	app_porting_ca_os_sleep(wMilliSeconds);
	return ;
}

/* ��ʼ���ź��� */
void CDSTBCA_SemaphoreInit( CDCA_Semaphore* pSemaphore,
                                   CDCA_BOOL       bInitVal )
{
	handle_t semaphore = 0;	
	if (NULL == pSemaphore)
	{
		return ;
	}
	
    app_porting_ca_os_sem_create(&semaphore,bInitVal);
	*pSemaphore = (handle_t)semaphore;
	return ;
}


/* �ź��������ź� */
void CDSTBCA_SemaphoreSignal( CDCA_Semaphore* pSemaphore )
{
	if (NULL == pSemaphore)
	{
		return ;
	}
	app_porting_ca_os_sem_signal((handle_t)*pSemaphore);
	return ;
}


/* �ź�����ȡ�ź� */
void CDSTBCA_SemaphoreWait( CDCA_Semaphore* pSemaphore )
{
	if (NULL == pSemaphore)
	{
		return ;
	}
	app_porting_ca_os_sem_wait((handle_t)*pSemaphore);
	return ;
}

/* ע������ */
CDCA_BOOL CDSTBCA_RegisterTask( const char* szName,
                                       CDCA_U8     byPriority,
                                       void*       pTaskFun,
                                       void*       pParam,
                                       CDCA_U16    wStackSize  )
{
    int         ret;
    handle_t    handle;
    uint32_t priority = GXOS_DEFAULT_PRIORITY;

	if ((NULL == szName)||(NULL == pTaskFun))
	{
		return CDCA_FALSE;
	}

	CAS_PORTING_DEBUG("CDSTBCA_RegisterTask szName=%s,byPriority=%d,wStackSize=0x%08x\n",szName,byPriority,wStackSize);

	if(1 /*== strcmp(szName,"CDCA_ECM_task")*/)
	{
		priority = GXOS_DEFAULT_PRIORITY;

	}
	else
	{
		priority = GXOS_DEFAULT_PRIORITY+1;
 	}

	ret = app_porting_ca_os_create_task(szName, &handle, pTaskFun,
                          pParam, wStackSize*10, priority);
	if (ret != GXCORE_SUCCESS)
	{
		CA_FAIL("CDSTBCA_RegisterTask return error = 0x%x\n", ret);
		return CDCA_FALSE;
	}

	return CDCA_TRUE;

}

/* �����ڴ� */
void* CDSTBCA_Malloc( CDCA_U32 byBufSize )
{
		return app_porting_ca_os_malloc(byBufSize);
}

/* �ͷ��ڴ� */
void  CDSTBCA_Free( void* pBuf )
{
	app_porting_ca_os_free(pBuf);
}

/* �ڴ渳ֵ */
void  CDSTBCA_Memset( void*    pDestBuf,
                             CDCA_U8  c,
                             CDCA_U32 wSize )
{
	memset(pDestBuf,c,wSize);
}

/* �ڴ渴�� */
void  CDSTBCA_Memcpy( void*       pDestBuf,
                             const void* pSrcBuf,
                             CDCA_U32    wSize )
{
	memcpy(pDestBuf,pSrcBuf,wSize);
}


/* ����˽�����ݹ����� */
CDCA_BOOL CDSTBCA_SetPrivateDataFilter( CDCA_U8        byReqID,
											   const CDCA_U8* pbyFilter,
											   const CDCA_U8* pbyMask,
											   CDCA_U8        byLen,
											   CDCA_U16       wPid,
											   CDCA_U8        byWaitSeconds )
{
	ca_filter_t filter = {0};
	bool repeatFlag = TRUE;
	uint8_t     match[18] = {0,};
	uint8_t     mask[18] = {0,};
    	uint16_t     i=0;

	if(pbyFilter == NULL || pbyMask == NULL )
	{
		return CDCA_FALSE;
	}
	CAS_PORTING_DEBUG("CDSTBCA_SetPrivateDataFilter invoked:byReqID=0x%02x,byLen=%d,wPid=0x%x,byWaitSeconds=%d,",
		byReqID,byLen,wPid,byWaitSeconds);
	CAS_PORTING_DUMP("pbyFilter",pbyFilter, byLen);
	CAS_PORTING_DUMP("pbyMask",pbyMask, byLen);
	printf("\n");
	if(wPid == 0x10)
	{
		cdcasNeedNitDataFlag = (byReqID << 8)|1;
		return CDCA_FALSE;
	}
	if (0x80 ==( 0x80&byReqID))
	{
		repeatFlag = FALSE;
	}

	for (i = 0; i< byLen; i++)
	{
		if (0 == i)
		{
			match[i] = pbyFilter[i];
			mask[i] = pbyMask[i];
		}
		else
		{
			match[i+2]	 = pbyFilter[i];
			mask[i+2] = pbyMask[i];
		}
	}
//	DUMP(DEMUX,INFO,byLen,pbyFilter,"%x");
//	DUMP(DEMUX,INFO,byLen,pbyMask,"%x");
//	CAS_DUMP("FILTER", pbyFilter, byLen);
	CDSTBCA_ReleasePrivateDataFilter(   byReqID, wPid );
	if (FALSE == repeatFlag)
	{
		/*
		* ����CA�޷����ţ�����Ƶ���޸Ĺ���������������Ӧ��
		*/
		for (i = MSG_POP_COMMON_END+CDCA_MESSAGE_BADCARD_TYPE+1;i<=MSG_POP_COMMON_END+CDCA_MESSAGE_STBFREEZE_TYPE;i++)
		{
			if (TRUE == app_play_get_msg_pop_type_state(i))
			{
				GxCore_ThreadDelay(20);	
				break;
			}
		}
	}

	filter.byReqID = byReqID;
	if (0x80 ==( 0x80&byReqID))
	{
		filter.crcFlag = FALSE;
	}
	else
	{
		filter.crcFlag = FALSE;
	}
	filter.filterLen = byLen+2;
	memcpy(filter.match,match,byLen+2);
	memcpy(filter.mask,mask,byLen+2);
	filter.nWaitSeconds = byWaitSeconds;
	filter.pid = wPid;
	filter.equalFlag = TRUE;
	filter.repeatFlag = repeatFlag;
	filter.Callback = app_cd_cas_30_filter_notify;
	filter.timeOutCallback = app_cd_cas_30_filter_timeout_notify;
	if(filter.filterLen <= 3)
	{
		filter.filterLen = 4;
	}
	return app_porting_ca_demux_start_filter(&filter);

}


/* ����CW�������� */
void CDSTBCA_ScrSetCW( CDCA_U16       wEcmPID,
							  const CDCA_U8* pbyOddKey,
							  const CDCA_U8* pbyEvenKey,
							  CDCA_U8        byKeyLen,
							  CDCA_BOOL      bTapingEnabled )
{
//	CAS_PORTING_DEBUG("CDSTBCA_ScrSetCW wEcmPID=%x,byKeyLen=%d,bTapingEnabled=%d",wEcmPID,byKeyLen,bTapingEnabled);
//	CAS_PORTING_DUMP("pbyOddKey", pbyOddKey, byKeyLen);
//	CAS_PORTING_DUMP("pbyEvenKey", pbyEvenKey, byKeyLen);
//	printf("\n");

	app_porting_ca_descramble_set_cw(wEcmPID,pbyOddKey,pbyEvenKey,byKeyLen,bTapingEnabled);

	return ;
}

/* ������Ϣ��� */
void CDSTBCA_Printf(CDCA_U8 byLevel, const char* szMesssage )
{
    if(CDCas_Flag)
	    printf("[DEBUG]===>%s",( char * ) szMesssage );
    
	return ;
}


/* ���ܿ���λ */
CDCA_BOOL CDSTBCA_SCReset( CDCA_U8* pbyATR, CDCA_U8* pbyLen )
{
	CAS_PORTING_DEBUG("CDSTBCA_SCReset pbyATR=0x%x,pbyLen=%d\n",(uint32_t)pbyATR,*pbyLen);

    if(pbyLen && pbyATR)
	{
        return app_cd_cas30_api_smart_reset(pbyATR,pbyLen);
	}
	return FALSE;
}

static int _get_take_millisecond(GxTime start, GxTime stop)
{
	int start_ms, stop_ms;

	start_ms = start.seconds * 1000 + start.microsecs / 1000;
	stop_ms = stop.seconds * 1000 + stop.microsecs / 1000;

	return (stop_ms - start_ms);
}

CDCA_BOOL CDSTBCA_SCPBRun( const CDCA_U8* pbyCommand,
								  CDCA_U16       wCommandLen,
								  CDCA_U8*       pbyReply,
								  CDCA_U16*      pwReplyLen)
{
	uint8_t reply[512] = {0};
	uint8_t send[512] = {0};
	uint8_t sc_result;
    //GxTime time1,time2;
	if(pbyCommand)
	{
		memcpy(send,pbyCommand,wCommandLen);
	}
    /*
    if(wCommandLen>50)
    {
       GxCore_GetLocalTime(&time1);
    }*/
    
	sc_result =  app_porting_ca_smart_sc_apdu(send,wCommandLen,reply,pwReplyLen);
    /*
    if(wCommandLen>50)
    {
       GxCore_GetLocalTime(&time2);
       printf("##########len:%d,take %d ms\n",wCommandLen,_get_take_millisecond(time1,time2));   
    }*/
    
    if (TRUE == sc_result)
	{
		memcpy(pbyReply, reply, *pwReplyLen);	
	}
	if(pbyReply && pwReplyLen)
	{
		//CAS_PORTING_DEBUG("CDSTBCA_SCPBRun RCV", pbyReply, *pwReplyLen);
	}
    
    CAS_PORTING_DEBUG("return %d :",sc_result);
	CAS_PORTING_DUMP("CDSTBCA_SCPBRun invoked:Command", pbyCommand, wCommandLen);
	CAS_PORTING_DUMP("OUT Reply",pbyReply,*pwReplyLen);
    
	return sc_result;
}
#if 0
uint8_t sendbuf0[] =
{
  0x00, 0x50, 0x00, 0x00, 0xda, 0x92, 0xf0, 0xf9, 0x1b, 0xb0, 0x0f, 0xcf,
  0xe3, 0xe6, 0x29, 0x1c, 0x4f, 0xd1, 0x09, 0xc9, 0xbb, 0x59, 0xbe, 0x67,
  0xf1, 0xc1, 0x83, 0x9b, 0xea, 0x43, 0xea, 0x01, 0xd3, 0x0e, 0x36, 0xc3,
  0x7a, 0x43, 0xc0, 0xa5, 0xaa, 0x7f, 0x0d, 0x6d, 0x86, 0x50, 0x18, 0xda,
  0x3a, 0xa8, 0x1a, 0xde, 0x47, 0xe7, 0x4e, 0x4c, 0xc0, 0x5f, 0x10, 0xd6,
  0xd1, 0x87, 0xee, 0x0a, 0xb8, 0xfa, 0xe8, 0xa1, 0x74, 0xff, 0x5a, 0x54,
  0xbb, 0x45, 0xdc, 0x1a, 0x43, 0xb4, 0x02, 0xc0, 0xf1, 0x49, 0x83, 0x41,
  0x01, 0x56, 0x3b, 0x4f, 0xd1, 0x18, 0x42, 0xfa, 0x7c, 0x9e, 0x97, 0x64,
  0x3f, 0x3a, 0x9d, 0x8c, 0xa4, 0x18, 0x9e, 0x6f, 0x53, 0xbf, 0xd9, 0xe6,
  0xab, 0x98, 0xb5, 0x23, 0xa4, 0x90, 0xb8, 0xd7, 0x2f, 0x2f, 0x81, 0x3a,
  0x0f, 0x86, 0x85, 0xaa, 0x00, 0x19, 0xf3, 0xcc, 0x3c, 0xa5, 0xa3, 0xd6,
  0x86, 0x29, 0xa1, 0x4f, 0x5f, 0xd2, 0x6f, 0x56, 0xc4, 0x76, 0xc8, 0x92,
  0x8e, 0x7c, 0x15, 0xde, 0xc6, 0x75, 0x03, 0xb6, 0x36, 0x11, 0x79, 0x36,
  0x37, 0x92, 0x49, 0x08, 0xdf, 0x61, 0xd6, 0xa0, 0x72, 0x14, 0x38, 0x73,
  0x20, 0xd0, 0x6f, 0x0e, 0xda, 0xd2, 0xea, 0xcf, 0xef, 0x8e, 0xda, 0xcb,
  0xae, 0x78, 0x54, 0x95, 0x05, 0x25, 0x6d, 0xb7, 0x68, 0xb9, 0x99, 0x03,
  0x20, 0x4d, 0xd8, 0xc2, 0x68, 0x27, 0xe5, 0x85, 0x03, 0x9b, 0x85, 0xf4,
  0x54, 0xaa, 0x7b, 0x33, 0xeb, 0xfc, 0xd9, 0x44, 0x0f, 0x2b, 0xda, 0x3d,
  0x28, 0x43, 0xa4, 0x1e, 0xa7, 0x0a, 0x03
};

uint8_t sendbuf1[] =
{
  0x00, 0x52, 0x00, 0x00, 0xcc, 0x00, 0xb2, 0x69, 0xeb, 0xb0, 0xaa, 0x2f,
  0x29, 0x20, 0x5b, 0x6d, 0xb7, 0xb6, 0x76, 0x98, 0xfc, 0xaa, 0xc8, 0xf4,
  0xde, 0x67, 0x54, 0x4b, 0x28, 0x5e, 0x2e, 0xcc, 0xad, 0xb8, 0x22, 0x1c,
  0xec, 0x64, 0xca, 0x28, 0x78, 0x4b, 0x0c, 0x4d, 0x9d, 0x2f, 0x02, 0x1c,
  0xe4, 0x27, 0xc3, 0xed, 0x54, 0xf2, 0xa3, 0x70, 0x51, 0xce, 0xf9, 0xbd,
  0x07, 0x26, 0x77, 0x4d, 0x29, 0xdc, 0x4f, 0x6d, 0x35, 0x80, 0xa9, 0xab,
  0x14, 0x9e, 0x4f, 0x90, 0x53, 0xab, 0xfc, 0x57, 0x53, 0x6a, 0x61, 0x1b,
  0x4b, 0xea, 0xa2, 0x90, 0xa3, 0xb2, 0x6f, 0x96, 0x34, 0x0b, 0x1a, 0x91,
  0x0c, 0x30, 0x09, 0xc7, 0x0c, 0x8b, 0xd1, 0x7b, 0x9e, 0x46, 0x78, 0x90,
  0x58, 0xbf, 0x78, 0x9c, 0x6d, 0x94, 0xe3, 0x68, 0x5e, 0x2a, 0xd0, 0xfc,
  0xd5, 0xf0, 0x65, 0x4c, 0x5c, 0x6e, 0x4b, 0x91, 0x25, 0x49, 0x8f, 0x8b,
  0xf9, 0x35, 0x36, 0xa3, 0xe9, 0xa7, 0xeb, 0x55, 0x4e, 0xa0, 0xb9, 0xe8,
  0x4b, 0xe6, 0x12, 0x9d, 0x41, 0x0b, 0xbc, 0x5d, 0xa2, 0x8d, 0x0f, 0x0c,
  0xa5, 0xc5, 0x58, 0x65, 0x35, 0xd5, 0x77, 0x48, 0x60, 0x5e, 0x83, 0x7e,
  0x5d, 0x99, 0xd1, 0x34, 0x95, 0x59, 0x13, 0x7d, 0x3e, 0xab, 0x80, 0x53,
  0x9e, 0xb6, 0x6a, 0xc7, 0xe2, 0x44, 0xb2, 0x7f, 0xd3, 0x59, 0x54, 0x14,
  0x89, 0xaf, 0xde, 0xfe, 0xbd, 0xe7, 0xee, 0xa1, 0x93, 0x46, 0x37, 0x47,
  0xe8, 0xfb, 0x8a, 0x4e, 0x58
};
void do_smart_card_test(void)
{
    uint8_t send[512] = {0};
    uint8_t reply[512] = {0};
    uint16_t sendlen = 0;
	uint16_t replylen = 0;
	static uint8_t firstIn = 1;
	if(firstIn)
	{
		if(CDSTBCA_SCReset(reply,(uint8_t *)&replylen))
		{
		CAS_PORTING_DEBUG("reset card sucess!\n");
		}
		firstIn = 0;
	}
	memset(send,0,512);
	memset(reply,0,512);
	sendlen = 223;
	if(app_porting_ca_smart_sc_apdu(sendbuf0,sendlen,reply,&replylen))
	{
		CAS_PORTING_DEBUG("send sucess reply=%d\n",replylen);
		GxCore_ThreadDelay(300);
	}
	else
	{
		CAS_PORTING_DEBUG("send failed\n");
	}
	
	while(1)
	{
		memset(reply,0,512);
		sendlen = 209;
		if(app_porting_ca_smart_sc_apdu(sendbuf1,sendlen,reply,&replylen))
		{
			CAS_PORTING_DEBUG("send sucess reply=%d\n",replylen);
			GxCore_ThreadDelay(300);
		}
		else
		{
			CAS_PORTING_DEBUG("send failed\n");
			//break;
			if(app_cd_cas30_api_smart_reset(reply,(uint8_t *)&replylen))
			{
				CAS_PORTING_DEBUG("reset card sucess!\n");
			}
		}
	}

}
void smart_card_test(void)
{
	//CDSTBCA_RegisterTask("card test",10,do_smart_card_test,NULL,10240);
}
#endif

/* ֪ͨ��Ȩ�仯 */
void CDSTBCA_EntitleChanged( CDCA_U16 wTvsID )
{
	CAS_PORTING_DEBUG("CDSTBCA_EntitleChanged\n");
	app_cas_api_on_event(DVB_CA_ENTITLE_INFO,CAS_NAME, NULL, 0);
	return ;
}

/* ����Ȩȷ����֪ͨ */
void CDSTBCA_DetitleReceived( CDCA_U8 bstatus )
{
	detitleflag.wStatus = bstatus;
	app_cas_api_on_event(DVB_CA_DETITLE_INFO,CAS_NAME, &detitleflag,sizeof(cd_cas30_detitle_st));	
	return ;
}

/* ��ȡ������Ψһ��� */
void CDSTBCA_GetSTBID( CDCA_U16* pwPlatformID,
                              CDCA_U32* pdwUniqueID)
{
	app_cd_cas30_api_get_uniqueid((uint32_t*)pdwUniqueID);
	*pwPlatformID = CDCASTB_GetPlatformID();
	CAS_PORTING_DEBUG("PlatformID=%x,uniqueID=%x\n",*pwPlatformID,(uint32_t )(*pdwUniqueID));
	return;
}

/* ��ȫоƬ�ӿ� */
CDCA_U16 CDSTBCA_SCFunction( CDCA_U8* pData)
{
	pData[0]=0x91;
	pData[1]=0x00;
	return 0X9100;
}



/* IPPV��Ŀ֪ͨ */
void CDSTBCA_StartIppvBuyDlg( CDCA_U8                 byMessageType,
                                     CDCA_U16                wEcmPid,
                                     const SCDCAIppvBuyInfo* pIppvProgram  )
{
	play_scramble_para_t playpara = {0};
	app_play_get_playing_para(&playpara);

	CAS_PORTING_DEBUG(" CDSTBCA_StartIppvBuyDlg wEcmPid=0x%x\n",wEcmPid);

	if (CDCA_IPPV_FREEVIEWED_SEGMENT == byMessageType)
	{
		CAS_PORTING_DEBUG("CDCA_IPPV_FREEVIEWED_SEGMENT byMessageType=%d wEcmPid=0x%x\n",
			byMessageType,wEcmPid);
	}
	else if (CDCA_IPPV_PAYVIEWED_SEGMENT == byMessageType)
	{
		CAS_PORTING_DEBUG("CDCA_IPPV_PAYVIEWED_SEGMENT byMessageType=%d wEcmPid=0x%x\n",
			byMessageType,wEcmPid);
	}
	else if (CDCA_IPPT_PAYVIEWED_SEGMENT == byMessageType)
	{
		CAS_PORTING_DEBUG("CDCA_IPPT_PAYVIEWED_SEGMENT byMessageType=%d wEcmPid=0x%x\n",
			byMessageType,wEcmPid);
	}

	if ((wEcmPid != playpara.p_ecm_pid)&&(wEcmPid != playpara.p_ecm_pid_video)
		&&(wEcmPid!= playpara.p_ecm_pid_audio))
	{
		return;
	}

	ippvbuy.wEcmPid = wEcmPid;
	ippvbuy.wStatus = TRUE;
	ippvbuy.byMessageType = byMessageType;
	memcpy(&ippvbuy.ippvBuyInfo,pIppvProgram,sizeof(SCDCAIppvBuyInfo));
	app_cas_api_on_event(DVB_CA_IPPV_POP_INFO,CAS_NAME, &ippvbuy, sizeof(cd_cas30_ippv_buy_st));	

	return;
}

/* ����IPPV�Ի��� */
void CDSTBCA_HideIPPVDlg(CDCA_U16 wEcmPid)
{
	CAS_PORTING_DEBUG(" CDSTBCA_HideIPPVDlg wEcmPid=0x%x\n",wEcmPid);
	ippvbuy.wStatus = FALSE;
	app_cas_api_on_event(DVB_CA_IPPV_POP_INFO, CAS_NAME, &ippvbuy, sizeof(cd_cas30_ippv_buy_st));			
}

/* �ʼ�֪ͨ */
void CDSTBCA_EmailNotifyIcon( CDCA_U8 byShow, CDCA_U32 dwEmailID )
{
	switch(byShow)
	{
		case CDCA_Email_IconHide:
			emailflag.wStatus = DVB_CA_EMAIL_FLAG_HIDE;
			CAS_PORTING_DEBUG("CDSTBCA_EmailNotifyIcon byShow=%d Ҫ�������ʼ�ͼ��\n ",byShow);
			break;
		case CDCA_Email_New:
			emailflag.wStatus = DVB_CA_EMAIL_NEW;
			CAS_PORTING_DEBUG("CDSTBCA_EmailNotifyIcon byShow=%d Ҫ����ʾ���ʼ�ͼ��\n ",byShow);				
			break;
		case CDCA_Email_SpaceExhaust:
			emailflag.wStatus = DVB_CA_EMAIL_EXHAUST;				
			CAS_PORTING_DEBUG("CDSTBCA_EmailNotifyIcon byShow=%d Ҫ����ʾ�ʼ�ͼ����˸\n ",byShow);					
			break;
		default:
			break;
	}

	emailflag.wStatus = byShow;
	emailflag.emailID = dwEmailID;
	app_cas_api_on_event(DVB_CA_EMAIL_INFO,CAS_NAME, &emailflag, sizeof(cd_cas30_email_st));
	
}

/* ��ʾOSD��Ϣ */
void CDSTBCA_ShowOSDMessage( CDCA_U8     byStyle,
                                    const char* szMessage )
{
	int i = 0;
	int j=0;
	CAS_PORTING_DEBUG(" CDSTBCA_ShowOSDMessage byStyle=%d,szMessage=%s\n",
		byStyle,szMessage);

	if (NULL == szMessage)
	{
		return;
	}

	if ((byStyle < CDCA_OSD_TOP)||(byStyle >CDCA_OSD_HALFSCREEN))
	{
		return;
	}

	memset(&rollingmsg,0,sizeof(cd_cas30_rolling_message_st))	;
	rollingmsg.byStyle = byStyle;



	for (i = 0; i< strlen(szMessage);i++)
	{
		if ((0x0d !=szMessage[i] )&&(0x0a != szMessage[i]))
		{
			rollingmsg.content[j++]=	szMessage[i];
		}
		else
		{
			/*�س����лᱻ����������*/
			CAS_PORTING_DEBUG("szMessage[%d]=0x%x\n",i,szMessage[i]);
		}

	}
 
	rollingmsg.wStatus = TRUE;
	app_cas_api_on_event(DVB_CA_ROLLING_INFO,CAS_NAME, &rollingmsg, sizeof(cd_cas30_rolling_message_st));


}

/* ����OSD��Ϣ*/
void CDSTBCA_HideOSDMessage( CDCA_U8 byStyle )
{
	CAS_PORTING_DEBUG(" CDSTBCA_HideOSDMessage byStyle=%d\n",	byStyle);
	
	if ((byStyle < CDCA_OSD_TOP)||(byStyle >CDCA_OSD_HALFSCREEN))
	{
		return;
	}

	switch(byStyle)
	{
		case CDCA_OSD_TOP:
			break;
		case CDCA_OSD_BOTTOM:
			break;
		case CDCA_OSD_FULLSCREEN:
			break;
		case CDCA_OSD_HALFSCREEN:
			break;
		default:
			break;

	}

	rollingmsg.byStyle = byStyle;
	rollingmsg.wStatus = FALSE;
	app_cas_api_on_event(DVB_CA_ROLLING_INFO,CAS_NAME, &rollingmsg, sizeof(cd_cas30_rolling_message_st));
	
	return ;

}

/* ������ʾ��ȡι�����ݽ�� */
void  CDSTBCA_RequestFeeding( CDCA_BOOL bReadStatus )
{

	if (CDCA_TRUE == bReadStatus)
	{
		CAS_PORTING_DEBUG("������ӿ�\n");
	}
	else
	{
		CAS_PORTING_DEBUG("��ȡĸ������ʧ��\n");
	}
	feed.bReadStatus = bReadStatus;
	
	app_cas_api_on_event(DVB_CA_MOTHER_CARD_INFO,CAS_NAME, &feed, sizeof(cd_cas30_feed_st));
}


/* Ƶ������ */
void CDSTBCA_LockService( const SCDCALockService* pLockService )
{
	app_cd_cas30_api_lock_service(pLockService);	
}

/* ���Ƶ������ */
void CDSTBCA_UNLockService( void )
{
	CAS_PORTING_DEBUG(" CDSTBCA_UNLockService \n");
	app_cd_cas30_api_set_lock_status(FALSE);
	return;
}

/* ���������տ���Ŀ����ʾ */
/*wEcmPID==0��ʾ��wEcmPID�޹ص���Ϣ���Ҳ��ܱ�������Ϣ����*/
void CDSTBCA_ShowBuyMessage( CDCA_U16 wEcmPID,
                                    CDCA_U8  byMessageType )
{

	play_scramble_para_t playpara = {0};
	app_play_get_playing_para(&playpara);

	CAS_PORTING_DEBUG(" CDSTBCA_ShowBuyMessage wEcmPID=0x%x,byMessageType=%d\n",wEcmPID,byMessageType);

	if (( 0 == wEcmPID)||(CDCA_MESSAGE_CANCEL_TYPE == byMessageType))
	{
		;
	}
	else
	{
		if ((wEcmPID != playpara.p_ecm_pid)&&(wEcmPID != playpara.p_ecm_pid_video)
			&&(wEcmPID!= playpara.p_ecm_pid_audio))
		{
			return;
		}
	}

	if (MSG_POP_COMMON_END+byMessageType+1 >=64)
		return ;

	if ( TRUE != app_play_get_msg_pop_type_state(MSG_POP_COMMON_END+byMessageType+1))
	{
		app_play_clear_ca_msg();
		app_play_set_msg_pop_type(MSG_POP_COMMON_END+byMessageType+1);
	}
	

	switch(byMessageType)
	{
		case CDCA_MESSAGE_CANCEL_TYPE:
			CAS_PORTING_DEBUG(" ȡ����ǰ����ʾ\n");
			break;
		case CDCA_MESSAGE_BADCARD_TYPE:
			CAS_PORTING_DEBUG(" �޷�ʶ��\n");
			break;
		case CDCA_MESSAGE_EXPICARD_TYPE:
			CAS_PORTING_DEBUG(" ���ܿ����ڣ�������¿�\n");
			break;
		case CDCA_MESSAGE_INSERTCARD_TYPE:
			CAS_PORTING_DEBUG(" ���Ž�Ŀ����������ܿ�\n");
			break;
		case CDCA_MESSAGE_NOOPER_TYPE:
			CAS_PORTING_DEBUG(" ���в����ڽ�Ŀ��Ӫ��\n");
			break;
		case CDCA_MESSAGE_BLACKOUT_TYPE:
			CAS_PORTING_DEBUG(" ��������\n");
			break;
		case CDCA_MESSAGE_OUTWORKTIME_TYPE:
			CAS_PORTING_DEBUG(" ��ǰʱ�α��趨Ϊ���ܹۿ�\n");
			break;
		case CDCA_MESSAGE_WATCHLEVEL_TYPE:
			CAS_PORTING_DEBUG(" ��Ŀ��������趨�Ĺۿ�����\n");
			break;
		case CDCA_MESSAGE_PAIRING_TYPE:
			CAS_PORTING_DEBUG(" ���ܿ��뱾�����в���Ӧ\n");
			break;
		case CDCA_MESSAGE_NOENTITLE_TYPE:
			CAS_PORTING_DEBUG(" û����Ȩ\n");
			break;
		case CDCA_MESSAGE_DECRYPTFAIL_TYPE:
			CAS_PORTING_DEBUG(" ��Ŀ����ʧ��\n");
			break;
		case CDCA_MESSAGE_NOMONEY_TYPE:
			CAS_PORTING_DEBUG(" ���ڽ���\n");
			break;
		case CDCA_MESSAGE_ERRREGION_TYPE:
			CAS_PORTING_DEBUG(" ������ȷ\n");
			break;
		case CDCA_MESSAGE_NEEDFEED_TYPE:
			CAS_PORTING_DEBUG(" �ӿ���Ҫ��ĸ����Ӧ�������ĸ��\n");
			break;
		case CDCA_MESSAGE_ERRCARD_TYPE:
			CAS_PORTING_DEBUG(" ���ܿ�У��ʧ�ܣ�����ϵ��Ӫ��\n");
			break;
		case CDCA_MESSAGE_UPDATE_TYPE:
			CAS_PORTING_DEBUG(" ���ܿ������У��벻Ҫ�ο����߹ػ�\n");
			break;
		case CDCA_MESSAGE_LOWCARDVER_TYPE:
			CAS_PORTING_DEBUG(" ���������ܿ�\n");
			break;
		case CDCA_MESSAGE_VIEWLOCK_TYPE:
			CAS_PORTING_DEBUG(" ����Ƶ���л�Ƶ��\n");
			break;
		case CDCA_MESSAGE_MAXRESTART_TYPE:
			CAS_PORTING_DEBUG(" ���ܿ���ʱ���ߣ���5���Ӻ����¿��� \n");
			break;
		case CDCA_MESSAGE_FREEZE_TYPE:
			CAS_PORTING_DEBUG(" ���ܿ��Ѷ��ᣬ����ϵ��Ӫ��\n");
			break;
		case CDCA_MESSAGE_CALLBACK_TYPE:
			CAS_PORTING_DEBUG(" ���ܿ�����ͣ����ش����Ӽ�¼����Ӫ��\n");
			break;
		case CDCA_MESSAGE_CURTAIN_TYPE:
			CAS_PORTING_DEBUG(" �߼�Ԥ����Ŀ���ý׶β�����ѹۿ�\n");
			break;
		case CDCA_MESSAGE_CARDTESTSTART_TYPE:
			CAS_PORTING_DEBUG(" �������Կ�������...\n");
			break;
		case CDCA_MESSAGE_CARDTESTFAILD_TYPE:
			CAS_PORTING_DEBUG(" �������Կ�����ʧ�ܣ��������ͨѶģ��\n");
			break;
		case CDCA_MESSAGE_CARDTESTSUCC_TYPE:
			CAS_PORTING_DEBUG(" �������Կ����Գɹ�\n");
			break;
		case CDCA_MESSAGE_NOCALIBOPER_TYPE:
			CAS_PORTING_DEBUG(" ���в�������ֲ�ⶨ����Ӫ��\n");
			break;
		case CDCA_MESSAGE_STBLOCKED_TYPE:
			CAS_PORTING_DEBUG(" ������������\n");
			break;
		case CDCA_MESSAGE_STBFREEZE_TYPE:
			CAS_PORTING_DEBUG(" �����б�����\n");
			break;
		default:
			break;
	}
	if(CDCA_MESSAGE_CARDTESTSUCC_TYPE == byMessageType\
		||CDCA_MESSAGE_CARDTESTFAILD_TYPE==byMessageType)
	{
		GxCore_ThreadDelay(1000);
	}
	return;

}

/* ָ����ʾ */
void CDSTBCA_ShowFingerMessage( CDCA_U16 wEcmPID,
                                       CDCA_U32 dwCardID )


{
	
	fingerdata.dwCardID = dwCardID;
	fingerdata.wEcmPid = wEcmPID;
	if (0 == dwCardID)
	{
		fingerdata.wStatus = 0;				
		/*֪ͨ�ر�ָ�ƴ���*/
	}
	else
	{
		fingerdata.wStatus = TRUE;							
	}

	app_cas_api_on_event(DVB_CA_FINGER_INFO,CAS_NAME, &fingerdata, sizeof(cd_cas30_finger_data_st));

	return;


}
void cdcas_redisplay_finger(void)
{
	app_cas_api_on_event(DVB_CA_FINGER_INFO,CAS_NAME, &fingerdata, sizeof(cd_cas30_finger_data_st));
}
extern App_CaCurtainNotify cdcasCurtainInfo;

/* �߼�Ԥ����ʾ*/
/* ֪ͨ��������ʾ��رո߼�Ԥ��*/
void  CDSTBCA_ShowCurtainNotify( CDCA_U16 wEcmPID,
                                    CDCA_U16  wCurtainCode)
{
	play_scramble_para_t playpara = {0};
	app_play_get_playing_para(&playpara);

	if ((wEcmPID != playpara.p_ecm_pid)&&(wEcmPID != playpara.p_ecm_pid_video)
		&&(wEcmPID!= playpara.p_ecm_pid_audio))
	{
		return;
	}
	cdcasCurtainInfo.wCurtainCode = wCurtainCode;		

	switch(wCurtainCode)
	{
		case CDCA_CURTAIN_CANCLE:
			cdcasCurtainInfo.wStatus = 0;		
			  CAS_PORTING_DEBUG(" ȡ���߼�Ԥ����ʾ\n");
			  break;
		case CDCA_CURTAIN_OK:
			cdcasCurtainInfo.wStatus = 1;	
			cdcasCurtainInfo.wShowStatus = 0;
			  CAS_PORTING_DEBUG("�߼�Ԥ����Ŀ��������\n");
			  break;				
		case CDCA_CURTAIN_TOTTIME_ERROR:
			cdcasCurtainInfo.wStatus= 1;	
			cdcasCurtainInfo.wShowStatus = 0;
			  CAS_PORTING_DEBUG("�߼�Ԥ����Ŀ��ֹ���ܣ��Ѿ��ﵽ�ܹۿ�ʱ��\n");
			  break;
		case CDCA_CURTAIN_WATCHTIME_ERROR:
			cdcasCurtainInfo.wStatus= 1;	
			cdcasCurtainInfo.wShowStatus = 0;
			  CAS_PORTING_DEBUG("�߼�Ԥ����Ŀ��ֹ���ܣ��Ѿ��ﵽWatchTime����\n");
			  break;	
		case CDCA_CURTAIN_TOTCNT_ERROR:
			cdcasCurtainInfo.wStatus= 1;	
			cdcasCurtainInfo.wShowStatus = 0;
			  CAS_PORTING_DEBUG(" �߼�Ԥ����Ŀ��ֹ���ܣ��Ѿ��ﵽ�������ۿ�����\n");
			  break;
		case CDCA_CURTAIN_ROOM_ERROR:
			cdcasCurtainInfo.wStatus= 1;	
			cdcasCurtainInfo.wShowStatus = 0;
			  CAS_PORTING_DEBUG("�߼�Ԥ����Ŀ��ֹ���ܣ��߼�Ԥ����Ŀ��¼�ռ䲻��\n");
			  break;				
		case CDCA_CURTAIN_PARAM_ERROR:
			cdcasCurtainInfo.wStatus= 1;	
			cdcasCurtainInfo.wShowStatus = 0;
			  CAS_PORTING_DEBUG("�߼�Ԥ����Ŀ��ֹ���ܣ���Ŀ��������\n");
			  break;
		case CDCA_CURTAIN_TIME_ERROR:
			cdcasCurtainInfo.wStatus= 1;	
			cdcasCurtainInfo.wShowStatus = 0;
			  CAS_PORTING_DEBUG("�߼�Ԥ����Ŀ��ֹ���ܣ����ݴ���\n");
			  break;	
		default:
			break;
			
}
			
	
	return;
}


/* ������ʾ */
void CDSTBCA_ShowProgressStrip( CDCA_U8 byProgress,
                                       CDCA_U8 byMark )
{
	if (CDCA_SCALE_PATCHING == byMark)
	{
		CAS_PORTING_DEBUG("CDSTBCA_ShowProgressStrip ���ܿ�������byMark=%d,byProgress=%d\n",byMark,byProgress);
	}
	else if (CDCA_SCALE_RECEIVEPATCH == byMark)
	{
		CAS_PORTING_DEBUG("CDSTBCA_ShowProgressStrip �������ݽ�����byMark=%d,byProgress=%d\n",byMark,byProgress);
	}


	card_update.byMark = byMark;
	card_update.byProgress = byProgress;
	app_cas_api_on_event(DVB_CA_CARD_UPDATE_INFO,CAS_NAME, &card_update, sizeof(cd_cas30_card_update_st));
	return;
}

/* ������֪ͨ */
void  CDSTBCA_ActionRequest( CDCA_U16 wTVSID,
                                    CDCA_U8  byActionType )
{
	/*ĿǰCA_LIB��Ҫ�������ʵ��*/
	return;
}

/* ��ȡ�ַ������� */
CDCA_U16 CDSTBCA_Strlen(const char* pString )
{
	CDCA_U16 len = strlen(pString);
	return len;
}



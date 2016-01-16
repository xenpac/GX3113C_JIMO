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
//#include "BYCAstb_ca.h"
//#include "BYCAca_stb.h"
//#include "BYCApubtype.h"   
#include "stb_ca2app.h"
#include "stb_app2ca.h"
#include "app_common_porting_ca_flash.h"
#include "app_common_porting_ca_demux.h"
#include "app_common_porting_ca_os.h"
#include "app_common_porting_ca_smart.h"
#include "app_common_table_nit.h"
#include "app_common_search.h"
#include "app_common_play.h"
#include "app_common_porting_stb_api.h"
#include "app_qilian_cas_api_smart.h"
#include "app_common_porting_ca_descramble.h"
#include "app_common_prog.h"
#include "app_common_lcn.h"
#include "app_qilian_cas_api_pop.h"
#include "app_qilian_cas_api_demux.h"
#include "app_qilian_cas_api_email.h"
#include "app_qilian_cas_api_lock_service.h"
#include "app_qilian_cas_api_demux.h"

static qilian_ca_rolling_message_st  rollingmsg = {0};
static qilian_ca_finger_data_st  fingerdata = {0};
static qilian_cas_email_st emailflag = {0};
extern uint8_t bat_recieve_flag ;
#define ONE_SECTOR_SIZE (64*1024)



/*++
���ܣ��������ܿ���ǰ״̬��
������pbyStatus��	�������ܿ�״̬��ΪBYCAS_SC_OUT��BYCAS_SC_IN����֮һ��
--*/
//BVOID BYSTBCA_GetSCStatus(BU8 * pbyStatus)
handle_t  queueId1= 0;
handle_t queueId2=0;
BU8 STBCA_MSGQUENE_Init(BU8 num)
{
	handle_t  queuedata = 0;
	if(num!=2)
	{
		return 0;
	}
 	if(GXCORE_SUCCESS==GxCore_QueueCreate(&queuedata,/*maxQueueLength*/20,sizeof(CA_MSG)))
	{
		queueId1=queuedata;
	}
	else
	{
		CAS_Dbg("STBCA_MSGQUENE_Init failed !\n");
	}
 	if(GXCORE_SUCCESS==GxCore_QueueCreate(&queuedata,/*maxQueueLength*/20,sizeof(CA_MSG)))
	{
		queueId2=queuedata;
	}
	else
	{
		CAS_Dbg("STBCA_MSGQUENE_Init failed !\n");
	}
	return 1;
}
/*++
���ܣ��ӵ�NO����Ϣ�����л�ȡͷ����Ϣ���������͡�
�������������Ϊ�գ���  ����msg Ϊ��
	CA_MSG *msg1= NULL;
	STBCA_GETCAMSG(0,msg1);
	if(msg1 != NULL )
	{
		//�ӵ�һ����Ϣ�����л�ȡ��  ������Ϣ
	}
	CA_MSG *msg2= NULL;
	STBCA_GETCAMSG(1,msg2);
	if(msg2 != NULL )
	{
		//�ӵڶ�����Ϣ�����л�ȡ��  ������Ϣ
	}
--*/
//void STBCA_GETCAMSG(BU8 NO,CA_MSG* msg);
CA_MSG ca_msg1,ca_msg2;
CA_MSG* STBCA_GETCAMSG(BU8 NO)
{
	uint32_t    sz=0;
	int32_t     timeout;
	int         ret;

#if defined(ECOS_OS)
	timeout = -1;
#elif defined(LINUX_OS)
	timeout = 0;
#endif
	if(NO==0)
	{
		ret = GxCore_QueueGet(queueId1, &ca_msg1, sizeof(CA_MSG), &sz,timeout);
		if (ret == GXCORE_SUCCESS)
		{
			if (0 == sz )
			{
				CAS_Dbg("STBCA_GETCAMSG sz = 0...\n");
				return NULL;
			}
			
			return &ca_msg1;
		}
		else
		{
			CAS_Dbg("STBCA_GETCAMSG Return value is error...\n");
			return NULL;
		}
	}
	else
	{
		ret = GxCore_QueueGet(queueId2, &ca_msg2, sizeof(CA_MSG), &sz,timeout);
		if (ret == GXCORE_SUCCESS)
		{
			if (0 == sz )
			{
				CAS_Dbg("STBCA_GETCAMSG sz = 0...\n");
				return NULL;
			}
			
			return &ca_msg2;
		}
		else
		{
			CAS_Dbg("STBCA_GETCAMSG Return value is error...\n");
			return NULL;
		}
	}
}
/*++
���ܣ��ڵ�NO����Ϣ����������һ����Ϣ�������������ɾ�����е���Ϣ��������Ϣ��
������
	static CA_MSG msg1;
	msg1.msgtype = 1;
	msg1.msgparm1 = 0x33;
	msg1.msgparm2 = 0x44;
	
	STBCA_SENDCAMSG(0,&msg1);
	STBCA_SENDCAMSG(1,&msg1);
--*/
void STBCA_SENDCAMSG(BU8 NO,CA_MSG* msg)
{
	int   ret ;
	
	if(msg == NULL)
	{
		CAS_Dbg("XinShiMao_OSPQueueSendMessage Parameter is NULL\n");
		return;
	}
	handle_t queue_id;
	if(NO==0)
	{
		 queue_id=queueId1;
	}
	else
	{
		 queue_id=queueId2;
	}	
	ret = GxCore_QueuePut(queue_id, msg, sizeof(CA_MSG),0);

	if(ret == GXCORE_SUCCESS )
	{
		
	}
	else
	{
		CAS_Dbg("STBCA_SENDCAMSG pipeID=0x%x Error\n", (unsigned int)queue_id);

	}

}

void STBCA_ReleaseCAMSG(BU8 NO,CA_MSG* msg)
{
	CAS_Dbg("STBCA_ReleaseCAMSG NO=0x%x Error\n", NO);
}

BU8 STBCA_GetSCStatus(void )
{


	if (TRUE == app_porting_ca_smart_status())
		//*pbyStatus = BYCAS_SC_IN;
		return 1;
	else
		//*pbyStatus = BYCAS_SC_OUT;
		return  0;
}

/*++
���ܣ���û����з����CAS�Ĵ洢�ռ������ַ�ʹ�С�����ֽ�Ϊ��λ����
������
	ppStartAddr:			�����з����CAS�Ĵ洢�ռ�Ŀ�ʼ��ַ��
	lSize:					��������з����CAS�Ĵ���ռ�Ĵ�С��
--*/
//BU8 BYSTBCA_GetDataBufferAddr(BU32* lSize,BU32 * ppStartAddr)
void STBCA_GetDataBufferAddr(BU32* lSize, BU32* ppStartAddr)
{
	if ((NULL == lSize)||(NULL ==ppStartAddr ))
		{
		  	CAS_Dbg("BYSTBCA_GetDataBufferAddr lSize=0x%x ppStartAddr=0x%x\n",(unsigned int)lSize,(unsigned int)ppStartAddr);		
			//return 0;
		}

	
    *ppStartAddr = ONE_SECTOR_SIZE;
	*lSize = ONE_SECTOR_SIZE;
	//return 1;
}

/*++
���ܣ���ȡ�����ڻ������е���Ϣ��
������
	pStartAddr:				Ҫ��ȡ�Ĵ洢�ռ�Ŀ�ʼ��ַ��
	plDataLen:				����ΪҪ��ȡ�������ֵ�����Ϊʵ�ʶ�ȡ�Ĵ�С��
	pData:					���������ݡ�
--*/
//BU8 BYSTBCA_ReadDataBuffer(BU32 pStartAddr,BU32* plDataLen,BU8* pData)
BU8 STBCA_ReadDataBuffer(BU32* pStartAddr, BU32* plDataLen, BYTE* pData)
{
	uint32_t  Offset = *pStartAddr-ONE_SECTOR_SIZE;
	
       if ((NULL ==plDataLen )||(NULL == pData))
       	{
		  	CAS_Dbg("STBCA_ReadDataBuffer plDataLen=0x%x pData=0x%x\n",(unsigned int)plDataLen,(unsigned int)pData);		       	
	   		return 0;
       	}
	   
	if (Offset + *plDataLen> ONE_SECTOR_SIZE)
		{
		  	CAS_Dbg("BYSTBCA_ReadDataBuffer Offset=0x%x *plDataLen=0x%x\n",(unsigned int)Offset,(unsigned int)(*plDataLen));		       	
			return 0;
		}
	
	return app_porting_ca_flash_read_data(Offset,(uint8_t *)pData,(uint32_t *)plDataLen);
}

/*++
���ܣ�������еĴ洢�ռ�д��Ϣ��
������
	lStartAddr:				Ҫд�Ĵ洢�ռ�Ŀ�ʼ��ַ��
	plDataLen:				����ΪҪд�����ݵĳ��ȣ����Ϊд���ʵ�ʳ��ȡ�
	pData:					Ҫд�����ݡ�
--*/
//BU8 BYSTBCA_WriteDataBuffer(BU32 pStartAddr,BU32 DataLen,BU8* pData)
BU8 STBCA_WriteDataBuffer(BU32 pStartAddr, BU32 plDataLen, const BYTE* pData)
{
	uint32_t  Offset = pStartAddr-ONE_SECTOR_SIZE;

	if (NULL == pData)
		{
			CAS_Dbg("BYSTBCA_WriteDataBuffer pData=0x%x \n",(unsigned int)pData);		       	
			return 0;
		}
	
	if (Offset + plDataLen> ONE_SECTOR_SIZE)
		{
		  	CAS_Dbg("BYSTBCA_WriteDataBuffer Offset=0x%x DataLen=0x%x\n",(unsigned int)Offset,(unsigned int)plDataLen);		       	
			return 0;
		}
	
	return	app_porting_ca_flash_write_data(Offset,(uint8_t *)pData,plDataLen);
	
}


/*++
���ܣ�����ǰ�̡߳�
������
	dwmsec:			���롣
--*/
//BU8 BYSTBCA_Sleep(BU32 dwmsec)
void STBCA_Sleep( int dwMicroseconds )
{

	app_porting_ca_os_sleep(dwMicroseconds);
	//return 1;
}

/*++
���ܣ���ʼ���ź���,��ʼ�����ź���û���źš�
������pSemaphore:				ָ���ź�����ָ�롣
	    flag:						  ��ʼ���ź���ֵ
--*/
//BU8 BYSTBCA_SemaphoreInit(BY_Semaphore *pSemaphore,BU8 flag)
BU8 STBCA_SemaphoreInit( CA_Semaphore *pSemaphore ,BU8 flag)
{
	handle_t semaphore = 0;	
	if (NULL == pSemaphore)
		{
			CAS_Dbg("BYSTBCA_SemaphoreInit pSemaphore=0x%x \n",(unsigned int)pSemaphore);		       	
			return 0;
		}
	
    	  app_porting_ca_os_sem_create(&semaphore,flag);
	*pSemaphore = (handle_t)semaphore;
	return 1;
}
#if 0
/*++
���ܣ��ͷ�һ���ź�����
������pSemaphore: 			ָ���ź�����ָ�롣
--*/
BU8 BYSTBCA_SemaphoreDestory(BY_Semaphore *pSemaphore )
{
	if (NULL == pSemaphore)
		{
			CAS_Dbg("BYSTBCA_SemaphoreDestory pSemaphore=0x%x \n",(unsigned int)pSemaphore);		       	
			return 0;
		}

	app_porting_ca_os_sem_delete((handle_t)*pSemaphore);
	return 1;
}
#endif
/*++
���ܣ����ź������źš�
������pSemaphore: 			ָ���ź�����ָ�롣
--*/
//BU8 BYSTBCA_SemaphoreSignal(BY_Semaphore *pSemaphore )
void STBCA_SemaphoreSignal( CA_Semaphore *pSemaphore )
{
	if (NULL == pSemaphore)
		{
			CAS_Dbg("BYSTBCA_SemaphoreSignal pSemaphore=0x%x \n",(unsigned int)pSemaphore);		       	
			return ;
		}
	
	app_porting_ca_os_sem_signal((handle_t)*pSemaphore);
	return ;
}

/*++
���ܣ��ȴ��ź���,�ȴ��ɹ�֮��,�ź���Ϊ���źš�
������pSemaphore: 			ָ���ź�����ָ�롣
--*/
void STBCA_SemaphoreWait( CA_Semaphore *pSemaphore )
//BU8 BYSTBCA_SemaphoreWait(BY_Semaphore *pSemaphore )
{
	if (NULL == pSemaphore)
		{
			CAS_Dbg("BYSTBCA_SemaphoreWait pSemaphore=0x%x \n",(unsigned int)pSemaphore);		       	
			return ;
		}
	
	app_porting_ca_os_sem_wait((handle_t)*pSemaphore);
	return ;
}

/*++
���ܣ�CASģ���������ע���̡߳�
������
	szName:					ע����߳����ơ�
	pTaskFun:				Ҫע����̺߳�����
--*/
//BU8 BYSTBCA_RegisterTask(const BS8* szName,pThreadFunc pTaskFun)
BU8	STBCA_RegisterTask(const char* szName, pThreadFunc pTaskFun)
{
    int         ret;
    handle_t    handle;
    uint32_t priority = GXOS_DEFAULT_PRIORITY;

	if ((NULL == szName)||(NULL == pTaskFun))
	{
		CAS_Dbg("BYSTBCA_RegisterTask szName=%s  pTaskFun=0x%x\n",szName,(unsigned int)pTaskFun);		       	
		return 0;
	}

	printf("BYSTBCA_RegisterTask szName=%s\n",szName);

           	ret = app_porting_ca_os_create_task(szName, &handle, (void*)pTaskFun,
                              NULL, 1024*10, priority);

	return 1;
}

/*++
���ܣ����ù���������CAS˽�����ݡ�
������
	byReqID:				�����ձ�������š�������Ӧ�ñ�������ݣ����յ�CAS˽�����ݺ����BYCASTB_StreamGuardDataGot()ʱӦ�ý������ݷ��ء�
	wEcmPID:				��Ҫ���˵�����PID��
	szFilter:				��������ֵ��Ϊһ��8���ֽڵ����飬�൱��8*8�Ĺ�������
	szMask:					�����������룬Ϊһ��8���ֽڵ����飬��8*8�Ĺ�������Ӧ����szMask��ĳһbitλΪ0ʱ��ʾҪ���˵ı���Ӧ��bitλ����Ҫ��szFilter���Ӧ��bitλ��ͬ����szMaskĳһλΪ1ʱ��ʾҪ���˵ı���Ӧ��bitλһ��Ҫ��szFilter���Ӧ��bitλ��ͬ��
	byLen:					�������ĳ��ȣ�Ϊ8��
	nWaitSecs:			�մ˱���ĵȴ�ʱ�䣬���Ϊ0�����޵ȴ�����λ�롣
--*/
//BU8 BYSTBCA_SetStreamGuardFilter(BU8 byReqID,BU16 wPID,BU8* szFilter,BU8* szMask,BU8 byLen,BU16 nWaitSecs)
BU8 STBCA_SetStreamGuardFilter(BYTE byReqID, WORD wPID, const BYTE* szFilter, const BYTE* szMask,BYTE byLen, int nWaitSecs)
{

	uint16_t            filterID;
	ca_filter_t* sfilter = NULL;
	ca_filter_t filter = {0};
	bool repeatFlag = TRUE;
	uint8_t     match[18] = {0,};
	uint8_t     mask[18] = {0,};
	BU8* pbyFilter = szFilter;
	BU8* pbyMask = szMask;
	uint16_t	 i=0;


	if(pbyFilter == NULL || pbyMask == NULL )
	{
		CAS_Dbg("BYSTBCA_SetStreamGuardFilter pbyFilter=0x%x  pbyMask=0x%x\n",(unsigned int)pbyFilter,(unsigned int)pbyMask);		       	
		return 0;
	}

/*	if (0x80 ==( 0x80&byReqID))
	{
		repeatFlag = FALSE;
	}*/

 	CAS_Dbg("STBCA_SetStreamGuardFilter byReqID=0x%x,wPID=0x%x byLen=0x%x,nWaitSecs=%d\n",byReqID,wPID,byLen,nWaitSecs);

//	CAS_DUMP("BYSTBCA_SetStreamGuardFilter pbyFilter", pbyFilter , byLen);
//	CAS_DUMP("BYSTBCA_SetStreamGuardFilter pbyMask", pbyMask , byLen);


	for (i = 0; i< byLen; i++)
	{
		if (0 == i)
		{
			match[i]	 = pbyFilter[i];
			mask[i] = pbyMask[i];
		}
		else
		{
			match[i+2]	 = pbyFilter[i];
			mask[i+2] = pbyMask[i];
		}
	}



	for (filterID = 0; filterID< MAX_FILTER_COUNT; filterID++)
	{
	      sfilter = app_porting_ca_demux_get_by_filter_id(filterID,&filter);
		if (( 0 !=filter.usedStatus)&&(wPID == filter.pid)
			&&(0 !=filter.channelhandle)&&(byReqID == filter.byReqID))
		{
			app_porting_ca_demux_release_filter(filterID, TRUE);
			break;
		}
	}
	

	memset(&filter,0,sizeof(ca_filter_t));
	filter.byReqID = byReqID;
//	filter.crcFlag = FALSE;
	filter.crcFlag = TRUE;
	filter.filterLen = byLen;
	memcpy(filter.match,match,byLen+2);
	memcpy(filter.mask,mask,byLen+2);
	filter.nWaitSeconds = nWaitSecs;
	filter.pid = wPID;
	filter.equalFlag = TRUE,
	filter.repeatFlag = repeatFlag;
	filter.Callback = app_qilian_cas_filter_notify;
	filter.timeOutCallback = app_qilian_cas_filter_timeout_notify;
	return app_porting_ca_demux_start_filter(&filter);

}


/*++
���ܣ�CA�����ô˺������ý�����������ǰ���ڼ���һ���ڵ�CW�͸���������
������
	wEcmPID:				CW������ECMPID��
	szOddKey:				��CW�����ݡ�
	szEvenKey:				żCW�����ݡ�
	byKeyLen:				CW�ĳ��ȡ�
	bTaingControl:			true������¼��,false��������¼��
--*/
//BU8 BYSTBCA_SetDescrCW(BU16 wEcmPid,BU8 byKeyLen,const BU8* szOddKey,const BU8* szEvenKey,BU8 bTaingControl)
void STBCA_ScrSetCW( BU16  wEcmPid, const BU8* szOddKey, const BU8* szEvenKey,BU8 byKeyLen)
{

	app_porting_ca_descramble_set_cw(wEcmPid,szOddKey,szEvenKey,byKeyLen,0);

	//return 1;
}

/*++
���ܣ���ӡ������Ϣ��
������Param1,Param2,pszMsg:					������Ϣ���ݡ�
--*/
//void BYSTBCA_AddDebugMsg(BU32 Param1,BU32 Param2,const BS8 *pszMsg)
void STBCA_AddDebugMsg(const char *pszMsg)
{
	if (NULL != pszMsg)
		//printf("[0x%x][0x%x] %s \n",(unsigned int)Param1,(unsigned int)Param2,pszMsg);
	//else
		//printf("[0x%x][0x%x] \n",(unsigned int)Param1,(unsigned int)Param2);	
		printf("%s \n",pszMsg);
}


/*++
���ܣ����û��忨ʱ,�ȵ��øú�����λ��
����:     true  �ɹ���falseʧ��
������pATR ���64 �ֽ�
--*/
void STBCA_SMARTCARD_ReSet(void)
//BU8 BYCASTB_SCReset(BU8 *pATR)
{

  	    uint8_t                     len;
	    uint8_t               atr[256] = {0};
	int nRetValue = FALSE;

  	CAS_Dbg("[SC] BYCASTB_SCReset!\n");

        nRetValue = app_qilian_cas_api_smart_reset(atr,&len);

	if (TRUE == nRetValue)
    	{
    		//memcpy(pATR,atr,len);
    		return ;
    	}
    else
    	{
     		return ;
    	}
}

/*++
���ܣ�ʵ�������ܿ�֮���ͨѶ������7816��׼��
������
	byReaderNo:				��Ӧ�Ķ�������š�
	pbyLen:					����Ϊ�����������ֽڵĳ���;���Ϊ�����ֽڳ��ȡ�
	byszCommand:			�����͵�һ�������ֽڡ�
	szReply:				���ص����ݣ��ռ䳤�Ⱥ�Ϊ256�ֽڡ�
--*/
//BU8 BYSTBCA_SCAPDU(BU8 byReaderNo,const BU8* byszCommand,BU16* pbyLen,BU8* byszReply)
BU8 STBCA_SCAPDU(BU8 num, BYTE* byszCommand,BU32* bReplyLen, BYTE* byszReply)
{
    uint8_t reply[1024] = {0};
    uint8_t sc_result;
    uint16_t s_byLen=*bReplyLen&0XFFFF;
    uint16_t r_byLen=0;
    sc_result =  app_porting_ca_smart_sc_apdu(byszCommand,s_byLen,reply,&r_byLen);
    if (TRUE == sc_result)
    	{
    		*bReplyLen=r_byLen;
    		memcpy(byszReply, reply, r_byLen);	
//	       CAS_DUMP("[SC] BYSTBCA_SCAPDU success ", byszReply, *pbyLen);
    	}
   return sc_result;

}

/*------------ ����1�Ľ��棺�������û�ͨ��ң����ȡ����ʾ�Ľ��� -----------------------*/
/*
���ܣ���ʾ�û����ܹۿ���Ŀ����ʾ��Ϣ����������������Ӧʹ�á�
������	
	byMesageNo:				Ҫ��ʾ����Ϣ��š�
--*/
//BVOID   BYSTBCA_ShowPromptMessage(BU8 byMesageNo)
void   STBCA_ShowOSDMessage(BYTE byMesageNo)
{
	#if 0
	if (MSG_POP_COMMON_END+byMesageNo+1 >=64)
		return ;

	if ( TRUE != app_play_get_msg_pop_type_state(MSG_POP_COMMON_END+byMesageNo+1))
		{
			app_play_clear_ca_msg();
			app_play_set_msg_pop_type(MSG_POP_COMMON_END+byMesageNo+1);
		}
	#endif
	switch( byMesageNo)
	{
		case STBCA_NO_ERROR:
		case STATUE_CA_OSD_CLS:
			app_play_clear_ca_msg();
			break;
		case STBCA_ERROR_InitCardCommand	: //							1   //���ܿ���ʼ������
		case STBCA_ERROR_ReadCardCommand	: //								2	// ���ܿ��޷�ʶ��
		case STBCA_ERROR_NO_CARD			: //										3	//�������ܿ�
		case STBCA_ERROR_EMM_RET				://								4  // ��Ч��EMM ����
		case STBCA_ERROR_ECM_RET				: //									5	//��Ч��ECM����
		case STBCA_ECM_RET_READCOMM_ERROR		: //							6
		case STBCA_EMMECM_RET_P1P2_ERROR		: //							7    //��Чָ��
		case STBCA_EMMECM_RET_P3_ERROR		: //								8	// ���ݸ�ʽ��Ч
		case STBCA_EMMECM_RET_DES_ERROR		: //								9
		case STBCA_ECM_RET_NOENTITLE_ERROR		: //						10			//��ǰ����û����Ȩ
		case STBCA_EMMECM_RET_STORE_ERROR		: //							11
		case STBCA_EMMECM_RET_CHECK_ERROR		: //							12			// CRC   ����
		case STBCA_EMM_NOKEY_OR_NOFILE_ERROR	: //						13
		case STBCA_ECM_OUTDATE_ERROR			: //								14
		case STBCA_EMMECM_RET_UNKNOW_ERROR	: //				  		15
		case STBCA_NO_ECM_INFO				: //									16
		case STBCA_ZONE_FORBID_ERROR			: //								17  // �����޲���Ч
		case STBCA_UserCdn_Limit_Ctrl_Enable		: //								18			// ������ֹ����
		case STBCA_UserCdn_Limit_Ctrl_Disable		: //								19			// ����������Ч
		case STBCA_ZoneCdn_Limit_Ctrl_Enable		: //								20			// ������ֹ����
		case STBCA_ZoneCdn_Limit_Ctrl_Disable		: //							21			// ����������Ч
		//�������
		case STBCA_CARD_NEED_PAIRING			: //								22   // û�л������
		case STATUE_CA_SET_PAIR					: //								23	//  is pairing   �������������Ϣ����ȴ�
		case STBCA_CARD_PAIRING_OK				: //								24	// ������Գɹ������31��16  24 25����Ϣ
		case STBCA_PAIRED_OtherCARD_ERROR		: //								25 /*�û��������������*/
		case STBCA_PAIRED_OtherMachine_ERROR		: //							26 /*�ÿ���˻��������*/

		//��ĸ�����STATUE_CA_TIME_VAILD
		case	STATUE_CA_CHILD_SC				: //						27 //��ĸ���ȴ����
		case STATUE_CA_TIME_VAILD                               : //	          			28// ��ĸ�����ʱ���Ѹ���
		case STATUE_CA_NEED_PAIR				: //						29  //"�ѹ���Ч��,��ѿ������������"
		//����
		case STATUE_CA_CARD_ZONE_INVALID		: //						30		//�������ܿ����ٷ�����
		case  STATUE_CA_CARD_ZONE_CHECK_ENTER     : //	            			31    /* ����Ѱ�����磬��ȴ�*/
		case  STATUE_CA_CARD_ZONE_CHEKC_OK           : //	            			32         // ��stb�õ�����Ϣ����������ϣ�
			if ( TRUE != app_play_get_msg_pop_type_state(MSG_POP_COMMON_END+byMesageNo+1))
			{
				app_play_clear_ca_msg();
				app_play_set_msg_pop_type(MSG_POP_COMMON_END+byMesageNo+1);
			}
			break;
		default:
			break;
	}
}
#if 0
BVOID   BYSTBCA_HidePromptMessage(BVOID)
{
	app_play_clear_ca_msg();
}
#endif
/*
���ܣ���ʾָ����Ϣ��
������
	wEcmPid					ECM PID
	dwCardID:				���š�
	wDuration:				����������
--*/
/*++
���ܣ���ʾָ����Ϣ����ͼ�귽ʽ��ʾָ��,��ʾλ��һ����ʼ�����ͼ�겻�ص�
������szOSD == NULL ʱ�����Ļ����ʾ����Ϣ��
--*/
static char *finger=NULL;
void STBCA_FingerSHOW(const char* szOSD)
{
	//if ((dwCardID == fingerdata.dwCardID)&&(wEcmPid == fingerdata.wEcmPid)
	//	&&(0x1fff == wEcmPid)&&(0xffffffff == dwCardID))
	//	return ;

	//printf("BYSTBCA_ShowFingerPrinting wEcmPid=0x%x,dwCardID=0x%x,wDuration=0x%x\n",
	//	(unsigned int)wEcmPid,(unsigned int)dwCardID,(unsigned int)wDuration);


	//fingerdata.dwCardID = dwCardID;
	//fingerdata.wDuration = wDuration;
	//fingerdata.wEcmPid = wEcmPid;
		finger=szOSD;
		 if(szOSD==NULL)
		{
			fingerdata.wStatus = 0;
			fingerdata.data=NULL;
			
		}
		 else
		 {
			fingerdata.wStatus = 1;	
			fingerdata.data=szOSD;
		 }

	app_cas_api_on_event(DVB_CA_FINGER_INFO,CAS_NAME, &fingerdata, sizeof(qilian_ca_finger_data_st));
//	GxCore_ThreadDelay(20); 
}
#if 0
BVOID	BYSTBCA_ShowFingerPrinting(BU16 wEcmPid,BU32 dwCardID,BU32 wDuration)
{
	if ((dwCardID == fingerdata.dwCardID)&&(wEcmPid == fingerdata.wEcmPid)
		&&(0x1fff == wEcmPid)&&(0xffffffff == dwCardID))
		return ;

	printf("BYSTBCA_ShowFingerPrinting wEcmPid=0x%x,dwCardID=0x%x,wDuration=0x%x\n",
		(unsigned int)wEcmPid,(unsigned int)dwCardID,(unsigned int)wDuration);


	fingerdata.dwCardID = dwCardID;
	fingerdata.wDuration = wDuration;
	fingerdata.wEcmPid = wEcmPid;

	if((wEcmPid != 0x1fff) && (dwCardID != 0xffffffff))
		{
			fingerdata.wStatus = 2;
		}
	else if((wEcmPid == 0x1fff) && (dwCardID != 0xffffffff))
		{
			fingerdata.wStatus = 1;		
		}
	else if((wEcmPid == 0x1fff) && (dwCardID == 0xffffffff))
		{
			fingerdata.wStatus = 0;				
		}

	app_cas_api_on_event(DVB_CA_FINGER_INFO,CAS_NAME, &fingerdata, sizeof(qilian_ca_finger_data_st));
//	GxCore_ThreadDelay(20); 
}
#endif
/*--------------------------- ����2�Ľ��棺�û�����ȡ����ʾ�Ľ��� -----------------------*/
/*
���ܣ��������Ļ�ķ�ʽ��ʾOSD��Ϣ��������ͬ����ʾ��Ҳ�������첽��ʾ��
����:	
	szOSD:					������ʾ��OSD��Ϣ��
	wDuration:				0:��ʾһ�κ���������;����ֵΪ��ʾ�ľ������������
˵����
	�û�����ͨ��ң����ȡ����ǰOSD��ʾ��
--*/
char buf_osd_msg0[200]={0};
void   STBCA_ShowOSDMsg(const char* szOSD, WORD wDuration)

//BVOID	BYSTBCA_ShowOSDMsg(const BS8* szTitle,const BS8* szOSD,BU16 wDuration)
{
	if((wDuration==0 )&&( szOSD!=NULL))
	{
		memset(buf_osd_msg0,0,100);
		if(strlen(szOSD)>100)
		{
			memcpy(buf_osd_msg0,szOSD,99);
		}
		else
		{
			memcpy(buf_osd_msg0,szOSD,strlen(szOSD));
		}
		#if 1
		app_play_clear_ca_msg();
		app_cas_api_on_event(DVB_CA_QILIAN_POP_MSG,CAS_NAME, "qilian_cas", strlen("qilian_cas"));
		#else
		if ( TRUE != app_play_get_msg_pop_type_state(MSG_POP_COMMON_END+33+1))
		{
			app_play_clear_ca_msg();
			app_play_set_msg_pop_type(MSG_POP_COMMON_END+33+1);
		}
		#endif
		return;
	}
	int i = 0;
	int j=0;

	printf("BYSTBCA_ShowOSDMsg szOSD=%s\n",szOSD);

	memset(&rollingmsg,0,sizeof(qilian_ca_rolling_message_st))	;
	rollingmsg.wDuration = wDuration;


	//if ((NULL == szTitle)||(NULL == szOSD))
	if ((NULL == szOSD))
		{
			return;
		}
#if 0
	for (i = 0; i< strlen(szTitle);i++)
		{
			if (i >= ROLL_TITLE_MAX)
				break;
			if ((0x0d !=szTitle[i] )&&(0x0a != szTitle[i]))
				{
					rollingmsg.title[j++]=	szTitle[i];
				}
			else
				{
					/*�س����лᱻ����������*/
					printf("szTitle[%d]=0x%x\n",i,szTitle[i]);
				}

		}
#endif
	i = 0;
	j=0;

		for (i = 0; i< strlen(szOSD);i++)
		{
			if (i >= ROLL_CONTENT_MAX)
				break;
			if ((0x0d !=szOSD[i] )&&(0x0a != szOSD[i]))
				{
					rollingmsg.content[j++]=	szOSD[i];
				}
			else
				{
					/*�س����лᱻ����������*/
					printf("szOSD[%d]=0x%x\n",i,szOSD[i]);
				}

		}
	rollingmsg.wStatus = TRUE;
	app_cas_api_on_event(DVB_CA_ROLLING_INFO,CAS_NAME, &rollingmsg, sizeof(qilian_ca_rolling_message_st));
//	GxCore_ThreadDelay(20); 
}

/*
����: �ṩ�������
����: blen ����pbBuf ����blen�������
*/

BU8 STBCA_RAND_GET( void )
{
	static BU32 seed=1;
	srand(seed);
	seed++;
	BU8 re_rand=rand();
	printf("rand=0x%x",re_rand);
	return re_rand;
}

/*
���ܣ�֪ͨAPP����ĳ��Ƶ���źţ��ڸ��ض���Ƶ��Ѱ��������Ϣ��
����:	KHZ;
����:  1����ʾƵ��������������δ������Ƶ�㡣
--*/
//BU8 BYCA_SetZoneFreq( BU32 Freq )
BU8 STBCA_SetZoneFreq( BU32 Freq )
{
	uint32_t symbol_rate = 0;
	uint32_t qam = 0;
	uint32_t freq = Freq;///1000;

	//if (TRUE == bat_recieve_flag)
	//	return 1;

	symbol_rate = app_flash_get_config_center_freq_symbol_rate();
	qam = app_flash_get_config_center_freq_qam();
	printf("%s Freq=%d",__FUNCTION__,Freq);
	if (0 == app_search_lock_tp(freq, symbol_rate,INVERSION_OFF, qam,1000))
	{
		printf("STBCA_SetZoneFreq lock\n");
		return 1;//app_qilian_cas_api_bat_filter_open();
	}
	else
	{
		printf("STBCA_SetZoneFreq unlock\n");
		return 0;
	}
	return 1;
}

/*++
���ܣ���ʾ���ʼ��ı�־��
������
	byShow:					��־���͡��������£�
							BYCAS_NEW_EAMIL						���ʼ�֪ͨ��
							BYCAS_NEW_EMAIL_NO_ROOM		�����ʼ�����Email�ռ䲻����
							BYCAS_EMAIL_NONE					û�����ʼ���
--*/
/*++
	����: ֪ͨ�˵�����ʾ�ʼ�ͼ��
	 ����
	 0,��ʾ��ʾ���ʼ�ͼ��
	 1����ʾ��ʾ��������
	 2, ��ʾû�����ʼ�ͼ��
*/
#if 0
typedef enum
{
	DVB_CA_EMAIL_FLAG_HIDE=0,		       /*hide email flag */
	DVB_CA_EMAIL_NEW,		/*new email flag show*/		
	DVB_CA_EMAIL_EXHAUST			/*email space exhaust*/
}dvb_ca_email_flag_type_t;
#endif
#define	BYCAS_NEW_EAMIL						0/*���ʼ�֪ͨ��*/
#define     BYCAS_NEW_EMAIL_NO_ROOM		1/*�����ʼ�����Email�ռ䲻����*/
#define	BYCAS_EMAIL_NONE					2/*û�����ʼ���*/
void STBCA_EmailNotify(BU8 byShow)
//BVOID BYSTBCA_EmailNotify(BU8 byShow)
{
#if 1
	if ((BYCAS_EMAIL_NONE == byShow)&&(0 == emailflag.wStatus))
		return ;
	
	switch(byShow)
		{
			case BYCAS_EMAIL_NONE:
				emailflag.wStatus = DVB_CA_EMAIL_FLAG_HIDE;
//				printf("BYSTBCA_EmailNotify byShow=%d Ҫ�������ʼ�ͼ��\n ",byShow);
				break;
			case BYCAS_NEW_EAMIL:
				emailflag.wStatus = DVB_CA_EMAIL_NEW;
//				printf("BYSTBCA_EmailNotify byShow=%d Ҫ����ʾ���ʼ�ͼ��\n ",byShow);				
				break;
			case BYCAS_NEW_EMAIL_NO_ROOM:
				emailflag.wStatus = DVB_CA_EMAIL_EXHAUST;
//				printf("BYSTBCA_EmailNotify byShow=%d Ҫ����ʾ�ʼ�ͼ����˸\n ",byShow);					
				break;
			default:
				break;
		}

	app_cas_api_on_event(DVB_CA_EMAIL_INFO,CAS_NAME, &emailflag, sizeof(qilian_cas_email_st));
//	GxCore_ThreadDelay(20); 
	#endif
	return;
}

/*--------------------------- Ӧ���㲥 -----------------------*/
/*++
���ܣ�Ӧ���㲥, �л���ָ��Ƶ����
������
	wOriNetID:				ԭʼ��?�ID��
	wTSID:					������ID��
	wServiceID:				ҵ��ID��
	pUTCTime--5 bytes:				UTCʱ�䡣
--*/
#if 0
BVOID BYCASTBCA_UrgencyBroad(BU16 wOriNetID,BU16 wTSID,BU16 wServiceID,BU8 *pUTCTime)
{
	printf(" BYCASTBCA_UrgencyBroad \n");
	return app_qilian_cas_api_lock_service(wOriNetID,wTSID,wServiceID,pUTCTime);
}

/*++
���ܣ�ȡ��Ӧ���㲥���л���Ӧ���㲥ǰ�û��ۿ���Ƶ����
�������ޡ�
--*/
BVOID BYCASTBCA_CancelUrgencyBroad(BVOID)
{
	printf(" BYCASTBCA_CancelUrgencyBroad \n");  
	app_play_recall_prog();
	app_play_switch_prog_clear_msg();	
	app_play_reset_play_timer(0);
	app_qilian_cas_api_set_lock_status(FALSE);
	
	return;
}
#endif
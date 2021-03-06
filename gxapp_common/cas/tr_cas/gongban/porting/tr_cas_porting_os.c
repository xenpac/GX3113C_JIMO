
/*****************************************************************************
* 						   CONFIDENTIAL
*        Hangzhou GuoXin Science and Technology Co., Ltd.
*                      (C)2012, All right reserved
******************************************************************************

******************************************************************************
* File Name :	tr_cas_porting_os.c
* Author    : 	xxxxx
* Project   :	goxceed dvbc
* Type      :
******************************************************************************
* Purpose   :	ģ��ͷ�ļ�
******************************************************************************
* Release History:
VERSION	Date			  AUTHOR         Description
1.0  	2012.12.02		  xxxxx 	 			creation
*****************************************************************************/

#include <gxtype.h>
#include "gxmsg.h"
#include "gxapp_sys_config.h"
#include "app_common_play.h"
#include "app_common_table_pmt.h"
#include "app_common_porting_stb_api.h"
#include "app_common_porting_ca_flash.h"
#include "app_common_porting_ca_demux.h"
#include "app_common_porting_ca_descramble.h"
#include "app_common_porting_ca_smart.h"
#include "app_common_porting_ca_os.h"
#include "Tr_Cas.h"


#define MSG_CA_MEQUEUE_MAX_ITEM     (30)
#define MSG_CA_MEQUEUE_MAX_NUM	(10)

typedef struct stQueTask_s
{
	handle_t hTask;
	handle_t hQueue;
	CAS_OS_MESSAGE stMsg;
}stQueTask_t;

/*wangjian add on 20150112*/
TRCAS_SC_ATR_NOTIFY g_trcasScNotifyBakeup = NULL;

static int TaskCnt = 0;
static stQueTask_t hQueTask[MSG_CA_MEQUEUE_MAX_NUM] = {{0,0},};


PVOID TRDRV_OS_AllocateMemory(U32 ulSize)
{
	if (0 == ulSize)
	{
		return NULL;
	}

	return GxCore_Malloc(ulSize);
}

void TRDRV_OS_FreeMemory(IN PVOID pvMemory)
{
	if (pvMemory != NULL)
	{
		GxCore_Free(pvMemory);
		pvMemory = NULL;
	}
}


U32 TRDRV_OS_CreateTask(IN void(*task)(void *arg), S16 iPriority, U32 ulStackSize)
{
	handle_t thread_id = 0;
	handle_t queue_id = 0;
	
	if (15 == iPriority)
	{
		iPriority = GXOS_DEFAULT_PRIORITY+1;
	}
	else //if ((iPriority < 15) && (iPriority > 10))
	{
    	iPriority = GXOS_DEFAULT_PRIORITY+2;
	}
	
	GxCore_ThreadCreate("trcas-xxx", &thread_id, task, NULL, ulStackSize*2, iPriority);
	GxCore_QueueCreate(&queue_id, MSG_CA_MEQUEUE_MAX_ITEM, sizeof(CAS_OS_MESSAGE));
	
	hQueTask[TaskCnt].hTask = thread_id;
	hQueTask[TaskCnt].hQueue = queue_id;
	memset(&(hQueTask[TaskCnt].stMsg), 0x00, sizeof(CAS_OS_MESSAGE));
	TaskCnt++;
	
	return thread_id;
}

void  TRDRV_OS_DelayTask(U32 ulDelayTime)
{
	GxCore_ThreadDelay(ulDelayTime);
}

U32   TRDRV_OS_GetSysMsTick(void)
{
	GxTime stTim;
	U32 ms = 0;
	
	GxCore_GetTickTime(&stTim);
	ms = stTim.seconds*1000 + stTim.microsecs/1000;
	return ms;
}

S16   TRDRV_OS_SendMessage(U32 tTaskId, IN CAS_OS_MESSAGE *psMsg)
{
	uint8_t i;
	int32_t chErr = 1;	
	
	for (i = 0; i < MSG_CA_MEQUEUE_MAX_NUM; i++)
	{
		if (tTaskId == hQueTask[i].hTask)
		{
			chErr = GxCore_QueuePut(hQueTask[i].hQueue,\
									(PVOID)psMsg,\
									sizeof(CAS_OS_MESSAGE),\
									-1);
			break;
		}
	}
	
	if (GXCORE_SUCCESS == chErr)
	{
		return 0;
	}
	else
	{
		return 1;
	}	
}

CAS_OS_MESSAGE* TRDRV_OS_ReceiveMessage(U32 tTaskId)
{
	uint8_t i;
	int32_t chErr = 1;
	uint32_t cpSize = 0;
	int32_t timeout = -1;

	for (i = 0; i < MSG_CA_MEQUEUE_MAX_NUM; i++)
	{
		if (tTaskId == hQueTask[i].hTask)
		{		  
			chErr = GxCore_QueueGet(hQueTask[i].hQueue,\
				   					(PVOID)&(hQueTask[i].stMsg),\
				   					sizeof(CAS_OS_MESSAGE),\
				   					&cpSize, timeout);
			break;
		}
	}
	
	if (GXCORE_SUCCESS == chErr)
	{
		if (0 == cpSize)
		{
			return NULL;
		}
		else
		{
			return &(hQueTask[i].stMsg);
			
		}
	}
	else
	{	
		return NULL;
	}	
}

U32   TRDRV_OS_CreateSemaphore(U32 ulInitialCount)
{
	handle_t hSema = 0;
	
	GxCore_SemCreate(&hSema, ulInitialCount);
	
	return (U32)hSema;
}

void  TRDRV_OS_SignalSemaphore(U32 ulSemaphore)
{
	GxCore_SemPost(ulSemaphore);
	return;
}

void  TRDRV_OS_WaitSemaphore(U32 ulSemaphore)
{	
	GxCore_SemWait(ulSemaphore);
	return;
}

void  MC_Printf(char *format, ...)
{
	static char pucDestBuffer[1024];
	va_list args;
	int i;
	
	memset(pucDestBuffer, 0x00, 1024);
	
	va_start(args, format);
	i = Vsnprintf(pucDestBuffer, 1024, format, args);
	va_end(args);
	printf("[MC_Printf](%s)#\n", pucDestBuffer);
	
	return;
}

void __assert_fail(int x)
{
	printf("\n__assert_fail %d\n", x);
}



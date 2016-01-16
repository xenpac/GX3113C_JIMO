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
#include "app_win_interface.h"
#include "win_divitone_cas_email.h"
#include "app_divitone_cas_api_email.h"

static ca_get_count_t get_count = {0};	

void app_divitone_cas_email_flag_img_show(uint8_t showFlag)
{
	switch(showFlag)
		{
			case DVB_CA_EMAIL_PROMTP_HIDE:
				GUI_SetProperty("full_screen_img_mail","state","hide");
				break;
			case DVB_CA_EMAIL_PROMTP_SHOW:
				GUI_SetProperty("full_screen_img_mail","state","show");
//				GUI_SetProperty("full_screen_img_mail", "draw_now", NULL);				
				break;
			case DVB_CA_EMAIL_PROMTP_TRANS_HIDE:
				GUI_SetProperty("full_screen_img_mail","state","osd_trans_hide");
//				GUI_SetProperty("full_screen_img_mail", "draw_now", NULL);				
				break;
			default:
				break;
		}
}


SIGNAL_HANDLER  int app_divitone_cas_email_create(const char* widgetname, void *usrdata)
{

	char	 config[10];
	memset(config, 0, 10);
//	printf("app_divitone_cas_email_create get_count.totalnum=%d, get_count.newnum=%d\n",get_count.totalnum,get_count.newnum);
	sprintf(config, "%d", get_count.totalnum);
	GUI_SetProperty("win_divitone_cas_email_text_count", "string", (void *)config);
	sprintf(config, "%d", get_count.newnum);
	GUI_SetProperty("win_divitone_cas_email_text_unread_count", "string", (void *)config);

	return 0;
}

SIGNAL_HANDLER  int app_divitone_cas_email_destroy(const char* widgetname, void *usrdata)
{
	return 0;
}

SIGNAL_HANDLER  int app_divitone_cas_email_listview_key_press(const char* widgetname, void *usrdata)
{
	GUI_Event *event = NULL;
	event = (GUI_Event *)usrdata;

	if(event->type == GUI_KEYDOWN)
	{
		switch(event->key.sym)
		{
		case KEY_MENU:
			event->key.sym = KEY_EXIT;
			return EVENT_TRANSFER_KEEPON;
			break;
		case KEY_POWER:
			return EVENT_TRANSFER_KEEPON;
		default:
			return EVENT_TRANSFER_KEEPON;
		}
	}

	return EVENT_TRANSFER_KEEPON;
}

SIGNAL_HANDLER  int app_divitone_cas_email_keypress(const char* widgetname, void *usrdata)
{

	GUI_Event *event = NULL;
	uint32_t nListViewSel = 0;
	uint32_t deleteSel;
	ca_delete_data_t delete_data = {0};
	ca_get_date_t get_data = {0};
	char	 config[10];
	uint32_t gMail_sel = 0;
	popmsg_ret ret_pop = POPMSG_RET_YES;

	event = (GUI_Event *)usrdata;

	switch(event->type)
	{
	case GUI_MOUSEBUTTONDOWN:
		break;

	case GUI_KEYDOWN:
		switch(event->key.sym)
		{
		case KEY_RED:
			GUI_GetProperty("win_divitone_cas_email_listview", "select", &nListViewSel);
			if (get_count.totalnum>0)
			{
				ret_pop = app_popmsg(210, 200, "Do you want to delete the mail?", POPMSG_TYPE_YESNO);
				if(ret_pop == POPMSG_RET_YES)
				{
					deleteSel = nListViewSel;
					if(nListViewSel >=	get_count.totalnum)
					{
						nListViewSel = get_count.totalnum - 1;
					}
					delete_data.date_type = DVB_CA_EMAIL_INFO;
					delete_data.pos = deleteSel;
					app_cas_api_delete(&delete_data);
					get_count.date_type = DVB_CA_EMAIL_INFO;
					app_cas_api_get_count(&get_count);
					GUI_SetProperty("win_divitone_cas_email_listview", "update_all", NULL);
					GUI_SetProperty("win_divitone_cas_email_listview","select",(void*)&nListViewSel);
					sprintf(config, "%d", get_count.totalnum);
					GUI_SetProperty("win_divitone_cas_email_text_count", "string", (void *)config);
					sprintf(config, "%d", get_count.newnum);
					GUI_SetProperty("win_divitone_cas_email_text_unread_count", "string", (void *)config);
					GUI_EndDialog("win_divitone_cas_email");
				}
				else
				{

				}
			}
			else
			{
				app_popmsg(210, 200,"No mail",POPMSG_TYPE_OK);
			}
			break;
		case KEY_YELLOW:
			if (get_count.totalnum >0)
			{
				ret_pop = app_popmsg(210, 200, "Do you want to delete all mail?", POPMSG_TYPE_YESNO);
				if(ret_pop == POPMSG_RET_YES)
				{
					delete_data.date_type = DVB_CA_EMAIL_INFO;
					app_cas_api_delete_all(&delete_data);
					get_count.date_type = DVB_CA_EMAIL_INFO;
					app_cas_api_get_count(&get_count);

					GUI_SetProperty("win_divitone_cas_email_listview", "update_all", NULL);
					sprintf(config, "%d", get_count.totalnum);
					GUI_SetProperty("win_divitone_cas_email_text_count", "string", (void *)config);
					sprintf(config, "%d", get_count.newnum);
					GUI_SetProperty("win_divitone_cas_email_text_unread_count", "string", (void *)config);
					GUI_EndDialog("win_divitone_cas_email");
				}
				else
				{

				}
			}
			else
			{
				app_popmsg(210, 200,"No mail",POPMSG_TYPE_OK);
			}
			break;
		case KEY_MENU:
		case KEY_EXIT:
		case KEY_RECALL:
			GUI_EndDialog("win_divitone_cas_email");
			return EVENT_TRANSFER_STOP;
		case KEY_F1:
			return EVENT_TRANSFER_STOP;
		case KEY_OK:
			GUI_GetProperty("win_divitone_cas_email_listview","select",(void*)&gMail_sel);
			if ( 0 == get_count.totalnum)
			{
				app_popmsg(210, 200,"No mail",POPMSG_TYPE_OK);
			}
			else
			{	
				get_data.date_type = DVB_CA_EMAIL_INFO;
				get_data.pos = gMail_sel; // ��
				get_data.ID = DIVI_EMAIL_CONTENT_ID;
				if (NULL != app_cas_api_get_data(&get_data))
					{
						GUI_CreateDialog("win_divitone_cas_emailcontent");
					}
				else
					{
						app_popmsg(210, 200,"No mail",POPMSG_TYPE_OK);
					}
			}
			return EVENT_TRANSFER_STOP;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return EVENT_TRANSFER_KEEPON;

}

SIGNAL_HANDLER  int app_divitone_cas_email_get_count(const char* widgetname, void *usrdata)
{

	int use = 0;
	char	 strmailNum[10]={0};
	char	 strnewNum[10]={0};

	get_count.date_type = DVB_CA_EMAIL_INFO;
	app_cas_api_get_count(&get_count);


	sprintf(strmailNum, "%d", get_count.totalnum);
	GUI_SetProperty("win_divitone_cas_email_text_count", "string", (void *)strmailNum);
	sprintf(strnewNum, "%d", get_count.newnum);
	GUI_SetProperty("win_divitone_cas_email_text_unread_count", "string", (void *)strnewNum);
	use = get_count.totalnum;
	return use;
}

SIGNAL_HANDLER  int app_divitone_cas_email_get_data(const char* widgetname, void *usrdata)
{
	ca_get_date_t get_data = {0};
       unsigned int      Row    = 0;
       unsigned int      ID    = 0;
	ListItemPara *item_para =NULL;
	if(NULL == widgetname || NULL == usrdata )
	{
		return (1);
	}
	item_para = (ListItemPara *)(usrdata);
	if(NULL == item_para) 
		return GXCORE_ERROR;


	Row = item_para->sel;

	get_data.date_type = DVB_CA_EMAIL_INFO;
	get_data.pos = Row; // ��


	for (ID = DIVI_EMAIL_FLAG_ID;ID<=DIVI_EMAIL_TIME_ID;ID++)
		{
			get_data.ID = ID;
			item_para->string = app_cas_api_get_data(&get_data);

			if (ID < DIVI_EMAIL_TIME_ID)
				{
					/*
					* �������һ��
					*/
					item_para= item_para->next;
					if(NULL == item_para) 
						return GXCORE_ERROR;
				}
		}

	return 0;
}


SIGNAL_HANDLER  int app_divitone_cas_email_content_create(const char* widgetname, void *usrdata)
{
	ca_get_date_t get_data = {0};
	char* str = NULL;
	uint32_t nListViewSel = 0;
	GUI_GetProperty("win_divitone_cas_email_listview", "select", &nListViewSel);		

	get_data.date_type = DVB_CA_EMAIL_INFO;
	get_data.pos = nListViewSel; // ��
	get_data.ID = DIVI_EMAIL_TITLE_ID;
	str = app_cas_api_get_data(&get_data);
	if (NULL != str)
	{
		GUI_SetProperty("win_divitone_cas_emailcontent_emailtitle","string", str);
	}
	get_data.ID = DIVI_EMAIL_CONTENT_ID;
	str = app_cas_api_get_data(&get_data);
	if (NULL != str)
	{
		GUI_SetProperty("win_divitone_cas_emailcontent_content","string", str);
	}

	return 0;
}

SIGNAL_HANDLER  int  app_divitone_cas_email_content_destroy(const char* widgetname, void *usrdata)
{
	if(get_count.newnum == 0)
		app_divitone_cas_email_flag_img_show(DVB_CA_EMAIL_PROMTP_HIDE);
	return 0;
}


SIGNAL_HANDLER  int app_divitone_cas_email_content_keypress(const char* widgetname, void *usrdata)
{
	GUI_Event *event = NULL;
	event = (GUI_Event *)usrdata;
	switch(event->type)
	{
		case GUI_MOUSEBUTTONDOWN:
			break;
		case GUI_KEYDOWN:
			switch(event->key.sym)
			{
				case KEY_EXIT:
					break;
					return EVENT_TRANSFER_STOP;
				case KEY_MENU:
					break;
				case KEY_RECALL: // zhou add at 20110407
					get_count.date_type = DVB_CA_EMAIL_INFO;
	    				app_cas_api_get_count(&get_count);
					GUI_EndDialog("win_divitone_cas_emailcontent");
				 	return EVENT_TRANSFER_STOP;
				case KEY_UP:
					GUI_SetProperty("win_divitone_cas_emailcontent_content", "page_up", NULL);
					return EVENT_TRANSFER_STOP;
				case KEY_DOWN:
					GUI_SetProperty("win_divitone_cas_emailcontent_content", "page_down", NULL);
					return EVENT_TRANSFER_STOP;						
				case KEY_F1:
					return EVENT_TRANSFER_STOP;
				case KEY_OK:
					return EVENT_TRANSFER_STOP;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return EVENT_TRANSFER_KEEPON;
}

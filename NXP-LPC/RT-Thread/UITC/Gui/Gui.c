/****************************************Copyright (c)**************************************************
**                                      
**                                      
**                                      
**
**                           
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名:  
**创   建   人:  
**最后修改日期: 
**描        述:  
**
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人:  
** 版  本:  
** 日　期:  
** 描　述: 
**
**--------------当前版本修订------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 描　述:  
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "applib.h"
#include "GuiList.h"
#include "keydrv.h"

#include "ScreenBase.h"
#include "guisystem.h"
#include "GuiEvent.h"
#include "ExtScreenDef.h"

#include "versionScr.h"
#include "devicecfgscreen.h"
#include "lcddriver.h"

//界面管理
struct SCREEN_MGR
{
	struct GuiListNode  ScrHeadNode;  // 界面指针数组
	INT16U 	    ScreensCnt;	 // 界面总数
	INT8U       ActiveScrID; //当前激活的ID

//	CScreenBase *ScreenArray[MAX_SCREEN_ID];   // 界面指针数组
};

typedef struct SCREEN_MGR CScreenMgr;

static CScreenMgr g_ScreenLib;

 
/*********************************************************************************************************
** 函数名称: GetCurrentScreenPtr
** 函数名称: GetCurrentScreenPtr
**
** 功能描述：  得到当前屏幕的指针
**
** 输　入:  CScreenMgr * pMgr
**          
** 输　出:   CScreenBase*
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年11月12日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
CScreenBase* GetCurrentScreenPtr(CScreenMgr *pMgr)
{
	CScreenBase *pScr = NULL ;
	struct GuiListNode *pNode = NULL;
	if(pMgr && GuiListIsEmpty(& pMgr->ScrHeadNode ) )
	{
		ASSERT(pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID);
		if ( pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID )
		{//循环遍历
			GuiListForEach ( pNode,  & pMgr->ScrHeadNode)
		//	for ( n = pMgr->ScrHeadNode.pNext ; n != & pMgr->ScrHeadNode; n = n->pNext )
			{
				pScr = CONTAINING_RECORD(pNode, CScreenBase,List);
				ASSERT(pScr);
				if (pScr && pScr->CurrentID == pMgr->ActiveScrID )
				{
					return pScr;
				}
			}
		}
	}
 	return NULL;
}  
// 得到指向序号ScreenID屏幕的指针
CScreenBase* GetScreenPtr(CScreenMgr *pMgr ,INT8U nScreenID)
{
	CScreenBase *pScr = NULL ;
	struct GuiListNode *pNode = NULL;
	if(pMgr && GuiListIsEmpty(& pMgr->ScrHeadNode ) )
	{
		ASSERT(pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID);
		if ( pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID )
		{//循环遍历
			GuiListForEach ( pNode,  & pMgr->ScrHeadNode)
		//	for ( n = pMgr->ScrHeadNode.pNext ; n != & pMgr->ScrHeadNode; n = n->pNext )
			{
				pScr = CONTAINING_RECORD(pNode, CScreenBase,List);
				ASSERT(pScr);
				if (pScr && pScr->CurrentID == nScreenID )
				{
					return pScr;
				}
			}
		}
	}
	return NULL;
}
/*********************************************************************************************************
** 函数名称: SwitchScreen
** 函数名称: SwitchScreen
**
** 功能描述： 切换到序号ScreenID屏幕 
**
** 输　入:  INT8U nScreenID
**          
** 输　出:   void
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年11月12日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SwitchScreen(INT8U nScreenID)
{
	CScreenBase * pScreen = NULL ;
	CScreenMgr *pMgr = &g_ScreenLib;

 	pScreen=GetCurrentScreenPtr(pMgr);

	//首先销毁原窗口
//	if(pScreen && pScreen->pfnDestory)
//	{
//		pScreen->pfnDestory(pScreen);
//	}

	//切换到下一窗口
 	pScreen=GetScreenPtr(pMgr,nScreenID);

	if(pScreen == NULL)
		return;

 	//如果切换到密码输入框保存密码输入框返回窗口
 //	if(nScreenID == ID_PASSWORD || nScreenID == ID_MODALDIALOG)
 //		SetFatherID(& pScreen->Base,GetActiveWinID());

// 	SetActiveWinID(nScreenID);

 	//清除屏幕,模式对话框因为要保存上个界面的图形所有不进行清屏
 //	if(nScreenID != ID_MODALDIALOG)
 //		ClearScreen();
//	if(pScreen != NULL && pScreen->pfnInit)
 //		pScreen->pfnInit(pScreen,0,0);// 界面默认初始化代码，比如建立资源

}
/*********************************************************************************************************
** 函数名称: InitScreenLib
** 函数名称: InitScreenLib
**
** 功能描述：  初始化所有的屏幕
**
**
** 输　出:
**
** 全局变量:
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年11月11日
** 备  注:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void InitScreenLib( )
{
	INT8U i = 0;
	CScreenBase *pScreen = NULL;

	//初始化链表先
	GuiListInit(&(g_ScreenLib.ScrHeadNode));

	//创建LOGO SCREEN
	//pScreen = ( );

	pScreen = InitVerScreen();

	//添加到链表中
	GuiListAppend(&(g_ScreenLib.ScrHeadNode),&(pScreen->List));
	g_ScreenLib.ScreensCnt ++;

	pScreen = InitDevCfgScreen();
	GuiListAppend(&(g_ScreenLib.ScrHeadNode),&(pScreen->List));
	g_ScreenLib.ScreensCnt ++;


//	InitScreenMgr(&g_ScreeLib);
//	InitLogoScreen( &LogoScreen );
// 	InitDefaultScreen(&DefScreen);
//	InitMainMenuScreen(&MainMenuScreen);
//
//	InitRealTimeValScreen(&RealTimeValScr);
//
//	for ( i=0;i<sizeof(screens)/sizeof(CScreenBase * );i++)
//	{
//		AppendScreen(&g_ScreeLib, screens[i]);
//	}
//	//进入默认画面
	SwitchScreen( ID_START_SCREEN);
} 
/*********************************************************************************************************
** 函数名称: SendEventN
** 函数名称: SendEventN
**
** 功能描述：  匿名发送，送给当前活动的窗口
**
** 输　入:  INT32U msg
** 输　入:  INT32U param
**          
** 输　出:   INT8U
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年11月12日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U SendEventN(INT32U msg,INT32U param,INT32U lParam)
{
	CScreenBase *pScreen = NULL;
	CScreenMgr *pMgr = &g_ScreenLib;

	pScreen = GetCurrentScreenPtr(pMgr);

	if (pScreen == NULL)
		return FALSE;

	return SendScreenEvnent( pScreen->Handle ,msg,param ,lParam);
}
//匿名寄送，送给当前活动的窗口
static INT8U PostEventN(INT32U msg,INT32U param)
{
	CScreenBase *pScreen = NULL;
	CScreenMgr *pMgr = &g_ScreenLib;

	pScreen = GetCurrentScreenPtr(pMgr);

	if (pScreen == NULL)
		return FALSE;

	return PostEvnent( pScreen->Handle ,msg,param,NULL,TRUE);
}

static void HandleCurScrEvent(void)
{
	CScreenBase *pScreen = NULL;
	CScreenMgr *pMgr = &g_ScreenLib;

	pScreen = GetCurrentScreenPtr(pMgr);

	if (pScreen == NULL)
		return;

	HandleScreenEvent(  pScreen  )	;
}

#define  ID_CLOSE_LCD  100
INT8U OnTaskTimer(INT32U nEventID,INT32U Param)
{
	if (nEventID == ID_CLOSE_LCD)
	{
		TurnOffLcd();
		KillGuiTimer (NULL,ID_CLOSE_LCD);
		return TRUE;
	}

	return FALSE;
}


static void GuiTask(void *pdata)
{
	INT16U  key = 0;
	INT8U  bRet = FALSE;
//	INT32U  nTimerID = 0;
	GuiEvent TaskEvent;

	pdata = pdata;

	//点亮液晶
	TurnOnLcd();
	//5秒后关闭液晶
//	nTimerID = SetTimer(nTimerID,5000,NULL,NULL);
	SetGuiTimer(NULL,ID_CLOSE_LCD,5000);

	while(TRUE)
	{
		HandleCurScrEvent( );
		//获取按键
		key = 0;
		if (KeyHit())
		{
			//TODO: 长按解决办法就是重构 GetKey 接口,从中获取多个一样的值,
			key = GetKey( 30 );
			if (key != KEY_NONE)
			{//有按键，点亮LCD的灯
				TurnOnLcd();
				SetGuiTimer(NULL,ID_CLOSE_LCD,5000);

				//1.看按键是否是重启等功能键

				//2.按键消息
				SendEventN(GUI_EVENT_KEYDOWN,NULL,NULL);
			 	//PostEventN(GUI_EVENT_KEYDOWN, key);

			}
			else
			{//没有按键
				//关闭灯

			}
		}
		//看看是否有其他任务发送过来的消息
		bRet = GuiTaskEventRecv( &TaskEvent );
		if(bRet)
		{
			HandleTaskEvent(&TaskEvent);
		}

	}

}

//定义各任务的堆栈长度
#define  GUI_TASK_STK_SIZE      512
#define  PRIO_GUI_TASK          30

static unsigned char  GuiTaskStk [GUI_TASK_STK_SIZE];
struct rt_thread Gui_Thread;

void InitGuiTask( void  )
{
	InitLcd();
	//初始化窗口及任务消息队列
	InitGuiEventQueue();

	InitGuiTimerMgr();
	// 界面初始化
	InitScreenLib();
	//启动任务
	rt_thread_init(&Gui_Thread,"Gui_Thread",GuiTask, RT_NULL, &GuiTaskStk[0], sizeof(GuiTaskStk),
			PRIO_GUI_TASK, 10);

	rt_thread_startup(&Gui_Thread);
}

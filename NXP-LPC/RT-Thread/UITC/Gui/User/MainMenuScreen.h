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
#pragma  once

#ifndef MAIN_MENU_H
#define	MAIN_MENU_H

#include "ListMenu.h"

//	描    述 : 显示主菜单
struct MAIN_SCR 
{
	CScreenBase  Base;
	CGuiListMenu  Menu;

 
	 
};

typedef struct MAIN_SCR  CMainMenuScreen;

//
 CScreenBase * InitMainMenuScreen(void);

 
#endif

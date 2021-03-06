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
#ifndef CTRL_BASE_H
#define	CTRL_BASE_H 
#include "GuiDef.h"
#include "CtrlBase.h"


//定义菜单链接
struct  LM_ITEM 
{
	INT16U		nMenuID;          //菜单ID号
	INT16U		nResourceID;      //菜单项名字
	INT32U		nItemData;		  //菜单附加项
};

typedef struct LM_ITEM CListMenuItem;


struct LIST_MENU
{
	CTRL_BASE_DEF
	INT16U     ItemCount;

	INT16U     CurItem;

	INT16U      MaxShowChars;           //该控件窗口中能显示的字符数
	INT16U      MaxShowLines;           //该控件窗口中能显示的行数

	/*动态滚动条*/
	CGuiRect ScrollBarRect;		//滚动条位置
	INT8U    ShowScrollBar;		//是否显示滚动条
	INT8U    ItmeHeight;        //每行高


};
typedef struct LIST_MENU CGuiListMenu;

//静态创建
INT8U InitListMenu(CGuiListMenu *pMenu, INT32U ResID, CGuiRect *pRc );
//动态创建
void CreateListMenu( );


void AddItem(void);

#endif

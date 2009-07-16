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
#ifndef _RAM_H
#define	_RAM_H
 
#include "MemData.h"
#include "FileData.h"

typedef struct DATE_TIME
{
	INT8U	y;		//年  从2000年开始
	INT8U	mon;	//月  1-12
	INT8U	d;		//日  1-31
	INT8U	h;		//时  0-23
	INT8U	min;	//分  0-59
	INT8U	s;		//秒  0-59
	INT16U	ms;		//毫秒 0-999
}CDateTime; 

typedef struct DEVICE_VER
{
	INT16U	MajorVer; //主版本号  
					   //具有相同名称但不同主版本号的程序集不可互换。
	                   //例如，这适用于对产品的大量重写，这些重写使得无法实现向后兼容性。
					   //如：主版本号和应用程序有关 
	INT16U  MinorVer; //从版本号，如果两个程序集的名称和主版本号相同，
	                   //而次版本号不同，这指示显著增强，但照顾到了向后兼容性。
	                   //例如，这适用于产品的修正版或完全向后兼容的新版本。
	
	INT16U Build;      //内部版本号的不同表示对相同源所作的重新编译。这适合于更改处理器、平台或编译器的情况。

	INT16U RevisionVer ;//名称、主版本号和次版本号都相同但修订号不同的程序集应是完全可互换的。
	                    //这适用于修复以前发布的程序集中的安全漏洞。
}DEVICE_VER;

#define  NUM_MSTIMERS  32

/*========================================================================
//	一些主要的Ram存储结构
==========================================================================*/
typedef struct RAM
{ 
//	volatile INT32U	MsTimer[NUM_MSTIMERS];					//通用毫秒计数器

	//增量型编码器计数脉冲
//	INT32U	Abz_Pulse;
  	/****运行态/调试态切换标志*****/
//	INT16U DeviceStatusChange;			//STATUS_DEBUG-切换到调试态 STATUS_NORMAL 切换到运行态
 
	/*** 系统当前时间 ****/
	CDateTime now;

	DEVICE_VER   Version;
	/*** 软件加载时间 ****/
	CDateTime dtLoadTime;						//软件加载时间（烧录FLASH时间）


	//编码器接口类型，根据硬件自动识别
//	INT16U	EncoderType;	 



	//文件控制块
	FCB  Fcb;
	//
	BIN_DATA BinData;	
}CRamMain;		// BYTE
 
extern CRamMain Ram;
 
#if 0
//闸门的计算方式
//extern INT8U GetGatageCalcMethod() ;
#define GetGatageCalcMethod(ignore)  Ram.BinData.GatageCfg.CalcMethod 

//编码器旋转方向
//extern INT8U GetEncoderDirection() ;
#define GetEncoderDirection(ignore) Ram.BinData.GatageCfg.Direction

#define GetFRamMDCnt(ignore)   Ram.BinData.HdCfg.CpuCfg.MDCnt
#define GetFRamMWCnt(ignore)  Ram.BinData.HdCfg.CpuCfg.MWCnt
#endif

extern __inline  INT8U GetGatageCalcMethod() 
{
	return Ram.BinData.GatageCfg.CalcMethod ;
};

extern __inline  INT8U GetEncoderDirection( ) 
{
	return Ram.BinData.GatageCfg.Direction	;
}
extern __inline INT32U GetFRamMDCnt( )
{
	return 	Ram.BinData.HdCfg.CpuCfg.MDCnt;
}

extern __inline INT32U GetFRamMWCnt( ) 
{
	return Ram.BinData.HdCfg.CpuCfg.MWCnt;
}


#endif

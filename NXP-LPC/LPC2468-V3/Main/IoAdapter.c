/****************************************Copyright (c)**************************************************
**                                开入、开出、模入、模出、传感器等输入输出接口模块
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
#include "includes.h" 
#include "hd_drive.h"
#include "IoAdapter.h" 
 

#define  MAX_AIN_CH 2 //最多2个模拟量通道

//模拟量采样码值
static INT16U	ADcode[MAX_AIN_CH];

/*********************************************************************************************************
** 函数名称: GetAinRawVal
** 函数名称: GetAinRawVal
**
** 功能描述： 
**
** 输　入:  INT16U nChNo 从1开始
** 输　入:  INT16U * pRawVal
**          
** 输　出:  INT8U
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2008年9月6日
** 备  注: 
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U GetAinRawVal( INT16U nChNo,INT16U *pRawVal)
{
	if (nChNo == 1)
	{
		*pRawVal = ADcode[0];
		return TRUE;
	}
	else if ( nChNo == 2 )
	{
		*pRawVal = ADcode[1];
		return TRUE;
	}
	else
	{

	}
	return FALSE;
}

INT8U CpuGetAinVal(   )
{
	INT8U ad_high,ad_low,dummy;

	INT32U ChCnt = 0;
	INT32U i = 0;
	
	if ( ChCnt > 0 && ChCnt <= MAX_AIN_CH )
	{
		for ( i = 0; i < ChCnt ; i++)
		{
			if (i == 0)
			{
				OPCODE_AD(0x48);
				dummy = OPCODE_AD(0x00);          //丢掉一个字节，此处有疑问
				ad_high = OPCODE_AD(0x00);
				ad_low = OPCODE_AD(0x00);
				ADcode[0] = (ad_high<<8)|ad_low;
			}
			else if ( i == 1 )
			{
				OPCODE_AD(0x4a);
				dummy=OPCODE_AD(0x00);          //丢掉一个字节，此处有疑问
				ad_high=OPCODE_AD(0x00);
				ad_low=OPCODE_AD(0x00);
				ADcode[1] = (ad_high<<8)|ad_low;
			}			 
		}
	}
}

/*********************************************************************************************************
** 函数名称: SetLed
** 函数名称: SetLed
**
** 功能描述： 点（灭）LED灯
**
** 输　入:  INT8U uLedID
** 输　入:  INT8U bState
**          
** 输　出:  void
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2008年9月22日
** 备  注: 
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SetLed( INT8U uLedID,INT8U bState)
{
	if (bState)
	{
		hd_SetOneLED(uLedID);
	}
	else
	{
		hd_ClearOneLED(uLedID);
	}
}

extern void HotReset(INT16U reset_type)
{
//	INT8U tmpdata = 0xEE;

	//	DisableVICIRQ(VIC_UART0);
	// 	DisableVICIRQ(VIC_UART3);

//	RamCheck1.reset_type=RamCheck2.reset_type=reset_type;
//	RamCheck1.cpuflag=RamCheck2.cpuflag=START_HOT;

//	FRam_WriteByte(FRAM3164, CFG_HOTRESETFLAG, &tmpdata, 1);//置保存在铁电中的热重启标志,主要是给增量型
	//点亮所有灯，通知装置重启了
	//	Ram.uLed = 0x0FFF;
	//	do_LedOut();
	DelayNS(200);

	//将全部FRAM数据都写完再复归
	//	ClearMs(ONE_MSTIMER);
	//复归最大等待时间为1S ，并且复归至少等待200ms
	/*	while( (GetMs(ONE_MSTIMER)<=1000 && hd_I2C2_HaveOperator())|| (GetMs(ONE_MSTIMER)< 200))
	{
	//FRAM写操作信号量
	//保存数据
	FRam_SaveValue(&g_MemReg.RData);

	//清狗
	hd_ClearWatchDog();

	Ram.uLed = 0x0FFF;
	do_LedOut();
	}
	*/
	Reset();
	//	__main();
}

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
**备        注 :   
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
 

#define  MAX_LED_CNT 12


struct LED_STATUS
{
	rt_uint8_t  AutoToggle; //一直自动翻转
	rt_uint8_t  DlyTime; //  
	rt_uint8_t  Value;
};

static struct LED_STATUS g_LedStatus[MAX_LED_CNT];
static OS_TMR *pBlinkyTmr;

void SetLedBlinking( rt_uint8_t nLedNo ,rt_uint8_t ms100 ,rt_uint8_t Toggle)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	
	if (nLedNo < MAX_LED_CNT)
	{
		OS_ENTER_CRITICAL();	
		g_LedStatus[nLedNo].DlyTime= ms100;
		g_LedStatus[nLedNo].AutoToggle= Toggle;
		OS_EXIT_CRITICAL();
		LED_On(nLedNo);
	}
}

static void LedHandler( void *ptmr, void *parg )
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	rt_uint8_t i = 0;
	parg = parg;
	if (ptmr && ptmr == pBlinkyTmr)
	{
		OS_ENTER_CRITICAL();	
		for ( i = 0; i < MAX_LED_CNT ; i++)
		{
			if (g_LedStatus[i].DlyTime)
			{			 
				g_LedStatus[i].DlyTime --;
				if (g_LedStatus[i].DlyTime == 0 )
				{					
					if (g_LedStatus[i].AutoToggle)
					{
						g_LedStatus[i].DlyTime = g_LedStatus[i].AutoToggle;
						if (g_LedStatus[i].Value)
						{
							LED_On(i);
						}
						else
						{
							LED_Off(i);
						}
						g_LedStatus[i].Value = !g_LedStatus[i].Value;
					}
					else
					{
						//灭LED
						LED_Off(i);
					}
				}
			}
		}
		OS_EXIT_CRITICAL();
	}
}

void InitLed( void )
{
	rt_uint8_t i = 0;
	rt_uint8_t err = 0;
	for (i = 0; i < MAX_LED_CNT; i++)
	{
		g_LedStatus[i].AutoToggle = 0;
		g_LedStatus[i].DlyTime = 0;
		g_LedStatus[i].Value = 0;
		LED_On(i);
	}
	for (i = 0; i < MAX_LED_CNT; i++)
	{ 
		LED_Off(i);
	}
	pBlinkyTmr = OSTmrCreate( 1,1,OS_TMR_OPT_PERIODIC,LedHandler,NULL,(rt_uint8_t *)0,&err);
	OSTmrStart(pBlinkyTmr,&err);
}

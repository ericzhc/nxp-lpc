/***********************************************Copyright (c)*********************************************
**                                Guangzou ZLG-MCU Development Co.,LTD.
**                                     
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    IICPrivate.h
** Last modified Date:      2007-10-15
** Last Version:		    1.0
** Descriptions:		    IIC私有头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    lixiaocheng
** Created date:		    2007-10-15
** Version:				    1.0
** Descriptions:		    该头文件只要在I2C.c中包括就好了，在CONFIG.h中不要包括
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			    
** Modified Date:		    
** Version:				    
** Descriptions:		    
**
*********************************************************************************************************/
#ifndef __I2CPRIVATE_H
#define __I2CPRIVATE_H

/*********************************************************************************************************
   I2C器件信息结构结构体
*********************************************************************************************************/
struct __i2cinfo
{
                INT32U      uiID;                                       /*  标识该结构体是那个部件      */
                INT32U      uiOffBase;                                  /*  I2C寄存器间隔= 1 << OffBase */                         
    volatile    INT8U      *pucAddrBase;                                /*  I2C寄存器基地址             */            
    volatile    INT8U       ucIICflag;			                        /*  I2C_IDLE		:   空闲    */
							                                            /*  I2C_ERR    	:   读写错误    */
							                                            /*  I2C_BUSY	    :   忙      */		
        						 	                                    /*  I2C_WRITE_END  :   写完成   */
         							                                    /*  I2C_READ_END   :   读完成   */
                INT8U       ucSlave;                                    /*  是否是从机标志              */
   	            INT8U 	    ucSLAddr;		                            /*  需要访问的从机地址          */
	            INT16U		usSubAddr;		                            /*  从机内部子地址              */ 
	            INT8U 		ucSubAddrNum;	                            /*  从机内部子地址字节数        */	
	            INT8U      	ucI2CSubAddrCtl;                            /*  子地址控制。                */
									                                    /*  0--子地址已经处理-->        */
									                                    /*  -->或者不需要子地址         */
									                                    /*  1--读取操作                 */
									                                    /*  2--写操作                   */
	volatile    INT8U	   *pucDataBuf;
	volatile    INT16U		usDataNum;		                            /*  待处理的数据个数            */     	
}; 

typedef struct __i2cinfo    __I2C_INFO;                                 /*  定义类型                    */
typedef __I2C_INFO         *__PI2C_INFO;                                /*  定义指针                    */

/*********************************************************************************************************
   宏定义报错系统
*********************************************************************************************************/
#ifndef OPERATE_FAIL
#define OPERATE_FAIL        I2C_NOK
#endif

#ifndef OPERATE_SUCCESS
#define OPERATE_SUCCESS     I2C_OK
#endif

/*********************************************************************************************************
   定义I2C器件数目
*********************************************************************************************************/
#define __IIC_MAX_NUM                 3

/*********************************************************************************************************
   I2c作为主机或从机定义
*********************************************************************************************************/
#define __IIC_MASTER                  1                                 /*  标识IIC为主机               */
#define __IIC_SLAVER                  0                                 /*  标识IIC为从机               */

/*********************************************************************************************************
   自地址控制宏定义
*********************************************************************************************************/
#define __IIC_SUB_W                   2                                 /*  写操作标识符                */
#define __IIC_SUB_R                   1                                 /*  读操作标识符                */
#define __IIC_SUB_NONE                0                                 /*  子地址已处理或无子地址      */

/*********************************************************************************************************
  定义使用到的寄存器偏移地址
*********************************************************************************************************/
#define __B_IIC_SET                   0                                 /*  I20CONSET                   */
#define __B_IIC_STAT                  1                                 /*  I20STAT                     */
#define __B_IIC_DAT                   2                                 /*  I20DAT                      */
#define __B_IIC_ADR                   3                                 /*  I20ADR                      */
#define __B_IIC_SCLH                  4                                 /*  I20SCLH                     */
#define __B_IIC_SCLL                  5                                 /*  I20SCLL                     */
#define __B_IIC_CLR                   6                                 /*  I20CONCLR                   */

/*********************************************************************************************************
  中断状态宏定义
*********************************************************************************************************/
#define __SEND_START                  0x08                              /*  发送起始信号                */
#define __SEND_RESTART                0x10                              /*  发送重起信号                */
#define __SEND_SLA_W_ACK              0x18                              /*  发送SLA+W 收到ACK           */
#define __SEND_DATA_ACK               0x28                              /*  发送数据 收到ACK            */
#define __SEND_SLA_W_NOACK            0x20                              /*  发送SLA+W 收到非ACK         */
#define __SEND_DATA_NOACK             0x30                              /*  发送数据 收到非ACK          */
#define __LOSS_BUS                    0x38                              /*  丢失总线仲裁                */
#define __SEND_SLA_R_NOACK            0x48                              /*  发送SLA+R 收到非ACK         */
#define __SEND_SLA_R_ACK              0x40                              /*  发送SLA+R 收到ACK           */
#define __RECV_DATA_ACK               0x50                              /*  接收数据字节，返回ACK       */
#define __RECV_DATA_NOACK             0x58                              /*  接收数据字节，返回非ACK     */

/*********************************************************************************************************
  定义一些与操作系统相关的操作宏，移植不需要关系
*********************************************************************************************************/

                                                                        /*  给I2C上锁                   */
#define __I2C_LOCK(nblock)  do {                                        \
                                INT8U   ucErr;                          \
                                OSSemPend(nblock, 0, &ucErr);           \
                                if (ucErr != OS_NO_ERR) {               \
                                    return  (OPERATE_FAIL);             \
                                }                                       \
                            } while (0)

                                                                        /*  给I2C解锁                   */
#define __I2C_UNLOCK(nblock) do {                                       \
                                OSSemPost(nblock);                      \
                             } while(0)
                             
#define __OS_ENTER_CIRCT()              OS_ENTER_CRITICAL()             /*  关中断                      */
#define __OS_EXIT_CIRCT()               OS_EXIT_CRITICAL()              /*  开中断                      */

#endif                                                                  /*  __I2CPRIVATE_H              */
/*********************************************************************************************************
   END FILE
*********************************************************************************************************/

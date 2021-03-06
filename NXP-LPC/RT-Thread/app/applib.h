


#pragma  once
#include "ExtLib.h"
#include "rthw.h"

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define  DEF_BIT_NONE                                   0x00

#define  DEF_BIT_00                                     0x01
#define  DEF_BIT_01                                     0x02
#define  DEF_BIT_02                                     0x04
#define  DEF_BIT_03                                     0x08
#define  DEF_BIT_04                                     0x10
#define  DEF_BIT_05                                     0x20
#define  DEF_BIT_06                                     0x40
#define  DEF_BIT_07                                     0x80

#define  DEF_BIT_08                                   0x0100
#define  DEF_BIT_09                                   0x0200
#define  DEF_BIT_10                                   0x0400
#define  DEF_BIT_11                                   0x0800
#define  DEF_BIT_12                                   0x1000
#define  DEF_BIT_13                                   0x2000
#define  DEF_BIT_14                                   0x4000
#define  DEF_BIT_15                                   0x8000

#define  DEF_BIT_16                               0x00010000
#define  DEF_BIT_17                               0x00020000
#define  DEF_BIT_18                               0x00040000
#define  DEF_BIT_19                               0x00080000
#define  DEF_BIT_20                               0x00100000
#define  DEF_BIT_21                               0x00200000
#define  DEF_BIT_22                               0x00400000
#define  DEF_BIT_23                               0x00800000

#define  DEF_BIT_24                               0x01000000
#define  DEF_BIT_25                               0x02000000
#define  DEF_BIT_26                               0x04000000
#define  DEF_BIT_27                               0x08000000
#define  DEF_BIT_28                               0x10000000
#define  DEF_BIT_29                               0x20000000
#define  DEF_BIT_30                               0x40000000
#define  DEF_BIT_31                               0x80000000
 

#ifndef BOOLEAN
typedef unsigned char  BOOLEAN;
#endif

#ifndef INT8U
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
#endif

#ifndef INT8S
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
#endif

#ifndef INT16U
typedef unsigned short   INT16U;                   /* Unsigned 16 bit quantity                           */
#endif

#ifndef INT16S
typedef signed   short   INT16S;                   /* Signed   16 bit quantity                           */
#endif

#ifndef INT32U
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
#endif

#ifndef INT32S
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
#endif

#ifndef FP32
typedef float          FP32;                     /* Single precision floating point                    */
#endif

#ifndef FP64
typedef double         FP64;                     /* Double precision floating point                    */
#endif


#ifndef OS_CPU_SR
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */
#endif
 
#ifndef OS_ENTER_CRITICAL
#define  OS_ENTER_CRITICAL()  {cpu_sr = rt_hw_interrupt_disable();}
#endif

#ifndef OS_EXIT_CRITICAL
#define  OS_EXIT_CRITICAL()   {rt_hw_interrupt_enable(cpu_sr);}
#endif

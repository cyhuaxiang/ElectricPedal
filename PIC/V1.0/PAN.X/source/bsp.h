/* 
 * File:   bsp.h
 * Author: Administrator
 *
 * Created on 2017年7月11日, 下午4:47
 */

#ifndef BSP_H
#define	BSP_H


#ifdef	__cplusplus
extern "C" {
#endif

 //头文件定义
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

   
/* 开关中断的宏 */
#define ENABLE_INT()	INTCONbits.GIE = 1;INTCONbits.PEIE = 1;	/* 使能全局中断,高、低优先级 */
#define DISABLE_INT()	INTCONbits.GIE = 0;INTCONbits.PEIE = 0;	/* 禁止全局中断,高、低优先级 */
/* 开关中断优先级的宏 */
#define ENABLE_IP()     RCONbits.IPEN = 1;	/* 使能中断优先级 */
#define DISABLE_IP()	RCONbits.IPEN = 0;	/* 禁止中断优先级 */
/* 这个宏仅用于调试阶段排错 */
//#define BSP_Printf		printf
//#define BSP_Printf(...)    
    
////*******************************************************************************
//#define DEBUG_SWITCH  1    // 0-关闭调试信息，1-打开调试信息
//
//
//#if DEBUG_SWITCH 
//    #define DBG_PRT(fmt,args...) printf(fmt, ##args)
//#else
//    #define DBG_PRT(fmt,args...) /*do nothing */
//#endif

#define _XTAL_FREQ  32000000UL
#define SYS_FREQ  32000000UL
#define WAKEUP_US_DELAY 150
#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif
  
#define ENABLE   1
#define DISABLE  0

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0
/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                (0x01u)
#define BIT1                (0x02u)
#define BIT2                (0x04u)
#define BIT3                (0x08u)
#define BIT4                (0x10u)
#define BIT5                (0x20u)
#define BIT6                (0x40u)
#define BIT7                (0x80u)

//// get/set POT_CHANNEL aliases
//#define POT_CHANNEL_TRIS               TRISA0
//#define POT_CHANNEL_LAT                LATA0
//#define POT_CHANNEL_PORT               RA0
//#define POT_CHANNEL_WPU                WPUA0
//#define POT_CHANNEL_ANS                ANSA0
//#define POT_CHANNEL_SetHigh()    do { LATA0 = 1; } while(0)
//#define POT_CHANNEL_SetLow()   do { LATA0 = 0; } while(0)
//#define POT_CHANNEL_Toggle()   do { LATA0 = ~LATA0; } while(0)
//#define POT_CHANNEL_GetValue()         RA0
//#define POT_CHANNEL_SetDigitalInput()    do { TRISA0 = 1; } while(0)
//#define POT_CHANNEL_SetDigitalOutput()   do { TRISA0 = 0; } while(0)
//
//#define POT_CHANNEL_SetPullup()    do { WPUA0 = 1; } while(0)
//#define POT_CHANNEL_ResetPullup()   do { WPUA0 = 0; } while(0)
//#define POT_CHANNEL_SetAnalogMode()   do { ANSA0 = 1; } while(0)
//#define POT_CHANNEL_SetDigitalMode()   do { ANSA0 = 0; } while(0)
//// get/set LCD_CHIP_SELECT aliases
//#define LCD_CHIP_SELECT_TRIS               TRISA2
//#define LCD_CHIP_SELECT_LAT                LATA2
//#define LCD_CHIP_SELECT_PORT               RA2
//#define LCD_CHIP_SELECT_WPU                WPUA2
//#define LCD_CHIP_SELECT_ANS                ANSA2
//#define LCD_CHIP_SELECT_SetHigh()    do { LATA2 = 1; } while(0)
//#define LCD_CHIP_SELECT_SetLow()   do { LATA2 = 0; } while(0)
//#define LCD_CHIP_SELECT_Toggle()   do { LATA2 = ~LATA2; } while(0)
//#define LCD_CHIP_SELECT_GetValue()         RA2
//#define LCD_CHIP_SELECT_SetDigitalInput()    do { TRISA2 = 1; } while(0)
//#define LCD_CHIP_SELECT_SetDigitalOutput()   do { TRISA2 = 0; } while(0)
//
//#define LCD_CHIP_SELECT_SetPullup()    do { WPUA2 = 1; } while(0)
//#define LCD_CHIP_SELECT_ResetPullup()   do { WPUA2 = 0; } while(0)
//#define LCD_CHIP_SELECT_SetAnalogMode()   do { ANSA2 = 1; } while(0)
//#define LCD_CHIP_SELECT_SetDigitalMode()   do { ANSA2 = 0; } while(0)
//// get/set SWITCH_S2 aliases
//#define SWITCH_S2_TRIS               TRISA5
//#define SWITCH_S2_LAT                LATA5
//#define SWITCH_S2_PORT               RA5
//#define SWITCH_S2_WPU                WPUA5
//#define SWITCH_S2_ANS                ANSA5
//#define SWITCH_S2_SetHigh()    do { LATA5 = 1; } while(0)
//#define SWITCH_S2_SetLow()   do { LATA5 = 0; } while(0)
//#define SWITCH_S2_Toggle()   do { LATA5 = ~LATA5; } while(0)
//#define SWITCH_S2_GetValue()         RA5
//#define SWITCH_S2_SetDigitalInput()    do { TRISA5 = 1; } while(0)
//#define SWITCH_S2_SetDigitalOutput()   do { TRISA5 = 0; } while(0)
//
//#define SWITCH_S2_SetPullup()    do { WPUA5 = 1; } while(0)
//#define SWITCH_S2_ResetPullup()   do { WPUA5 = 0; } while(0)
//#define SWITCH_S2_SetAnalogMode()   do { ANSA5 = 1; } while(0)
//#define SWITCH_S2_SetDigitalMode()   do { ANSA5 = 0; } while(0)
//// get/set SWITCH_S1 aliases
//#define SWITCH_S1_TRIS               TRISB0
//#define SWITCH_S1_LAT                LATB0
//#define SWITCH_S1_PORT               RB0
//#define SWITCH_S1_WPU                WPUB0
//#define SWITCH_S1_ANS                ANSB0
//#define SWITCH_S1_SetHigh()    do { LATB0 = 1; } while(0)
//#define SWITCH_S1_SetLow()   do { LATB0 = 0; } while(0)
//#define SWITCH_S1_Toggle()   do { LATB0 = ~LATB0; } while(0)
//#define SWITCH_S1_GetValue()         RB0
//#define SWITCH_S1_SetDigitalInput()    do { TRISB0 = 1; } while(0)
//#define SWITCH_S1_SetDigitalOutput()   do { TRISB0 = 0; } while(0)
//
//#define SWITCH_S1_SetPullup()    do { WPUB0 = 1; } while(0)
//#define SWITCH_S1_ResetPullup()   do { WPUB0 = 0; } while(0)
//#define SWITCH_S1_SetAnalogMode()   do { ANSB0 = 1; } while(0)
//#define SWITCH_S1_SetDigitalMode()   do { ANSB0 = 0; } while(0)
//// get/set COG1B aliases
//#define COG1B_TRIS               TRISB1
//#define COG1B_LAT                LATB1
//#define COG1B_PORT               RB1
//#define COG1B_WPU                WPUB1
//#define COG1B_ANS                ANSB1
//#define COG1B_SetHigh()    do { LATB1 = 1; } while(0)
//#define COG1B_SetLow()   do { LATB1 = 0; } while(0)
//#define COG1B_Toggle()   do { LATB1 = ~LATB1; } while(0)
//#define COG1B_GetValue()         RB1
//#define COG1B_SetDigitalInput()    do { TRISB1 = 1; } while(0)
//#define COG1B_SetDigitalOutput()   do { TRISB1 = 0; } while(0)
//
//#define COG1B_SetPullup()    do { WPUB1 = 1; } while(0)
//#define COG1B_ResetPullup()   do { WPUB1 = 0; } while(0)
//#define COG1B_SetAnalogMode()   do { ANSB1 = 1; } while(0)
//#define COG1B_SetDigitalMode()   do { ANSB1 = 0; } while(0)
//// get/set COG1C aliases
//#define COG1C_TRIS               TRISB2
//#define COG1C_LAT                LATB2
//#define COG1C_PORT               RB2
//#define COG1C_WPU                WPUB2
//#define COG1C_ANS                ANSB2
//#define COG1C_SetHigh()    do { LATB2 = 1; } while(0)
//#define COG1C_SetLow()   do { LATB2 = 0; } while(0)
//#define COG1C_Toggle()   do { LATB2 = ~LATB2; } while(0)
//#define COG1C_GetValue()         RB2
//#define COG1C_SetDigitalInput()    do { TRISB2 = 1; } while(0)
//#define COG1C_SetDigitalOutput()   do { TRISB2 = 0; } while(0)
//
//#define COG1C_SetPullup()    do { WPUB2 = 1; } while(0)
//#define COG1C_ResetPullup()   do { WPUB2 = 0; } while(0)
//#define COG1C_SetAnalogMode()   do { ANSB2 = 1; } while(0)
//#define COG1C_SetDigitalMode()   do { ANSB2 = 0; } while(0)
//// get/set COG1D aliases
//#define COG1D_TRIS               TRISB3
//#define COG1D_LAT                LATB3
//#define COG1D_PORT               RB3
//#define COG1D_WPU                WPUB3
//#define COG1D_ANS                ANSB3
//#define COG1D_SetHigh()    do { LATB3 = 1; } while(0)
//#define COG1D_SetLow()   do { LATB3 = 0; } while(0)
//#define COG1D_Toggle()   do { LATB3 = ~LATB3; } while(0)
//#define COG1D_GetValue()         RB3
//#define COG1D_SetDigitalInput()    do { TRISB3 = 1; } while(0)
//#define COG1D_SetDigitalOutput()   do { TRISB3 = 0; } while(0)
//
//#define COG1D_SetPullup()    do { WPUB3 = 1; } while(0)
//#define COG1D_ResetPullup()   do { WPUB3 = 0; } while(0)
//#define COG1D_SetAnalogMode()   do { ANSB3 = 1; } while(0)
//#define COG1D_SetDigitalMode()   do { ANSB3 = 0; } while(0)
//// get/set SCK aliases
//#define SCK_TRIS               TRISC3
//#define SCK_LAT                LATC3
//#define SCK_PORT               RC3
//#define SCK_WPU                WPUC3
//#define SCK_ANS                ANSC3
//#define SCK_SetHigh()    do { LATC3 = 1; } while(0)
//#define SCK_SetLow()   do { LATC3 = 0; } while(0)
//#define SCK_Toggle()   do { LATC3 = ~LATC3; } while(0)
//#define SCK_GetValue()         RC3
//#define SCK_SetDigitalInput()    do { TRISC3 = 1; } while(0)
//#define SCK_SetDigitalOutput()   do { TRISC3 = 0; } while(0)
//
//#define SCK_SetPullup()    do { WPUC3 = 1; } while(0)
//#define SCK_ResetPullup()   do { WPUC3 = 0; } while(0)
//#define SCK_SetAnalogMode()   do { ANSC3 = 1; } while(0)
//#define SCK_SetDigitalMode()   do { ANSC3 = 0; } while(0)
//// get/set SDI aliases
//#define SDI_TRIS               TRISC4
//#define SDI_LAT                LATC4
//#define SDI_PORT               RC4
//#define SDI_WPU                WPUC4
//#define SDI_ANS                ANSC4
//#define SDI_SetHigh()    do { LATC4 = 1; } while(0)
//#define SDI_SetLow()   do { LATC4 = 0; } while(0)
//#define SDI_Toggle()   do { LATC4 = ~LATC4; } while(0)
//#define SDI_GetValue()         RC4
//#define SDI_SetDigitalInput()    do { TRISC4 = 1; } while(0)
//#define SDI_SetDigitalOutput()   do { TRISC4 = 0; } while(0)
//
//#define SDI_SetPullup()    do { WPUC4 = 1; } while(0)
//#define SDI_ResetPullup()   do { WPUC4 = 0; } while(0)
//#define SDI_SetAnalogMode()   do { ANSC4 = 1; } while(0)
//#define SDI_SetDigitalMode()   do { ANSC4 = 0; } while(0)
//// get/set SDO aliases
//#define SDO_TRIS               TRISC5
//#define SDO_LAT                LATC5
//#define SDO_PORT               RC5
//#define SDO_WPU                WPUC5
//#define SDO_ANS                ANSC5
//#define SDO_SetHigh()    do { LATC5 = 1; } while(0)
//#define SDO_SetLow()   do { LATC5 = 0; } while(0)
//#define SDO_Toggle()   do { LATC5 = ~LATC5; } while(0)
//#define SDO_GetValue()         RC5
//#define SDO_SetDigitalInput()    do { TRISC5 = 1; } while(0)
//#define SDO_SetDigitalOutput()   do { TRISC5 = 0; } while(0)
//
//#define SDO_SetPullup()    do { WPUC5 = 1; } while(0)
//#define SDO_ResetPullup()   do { WPUC5 = 0; } while(0)
//#define SDO_SetAnalogMode()   do { ANSC5 = 1; } while(0)
//#define SDO_SetDigitalMode()   do { ANSC5 = 0; } while(0)
//// get/set TX aliases
//#define TX_TRIS               TRISC6
//#define TX_LAT                LATC6
//#define TX_PORT               RC6
//#define TX_WPU                WPUC6
//#define TX_ANS                ANSC6
//#define TX_SetHigh()    do { LATC6 = 1; } while(0)
//#define TX_SetLow()   do { LATC6 = 0; } while(0)
//#define TX_Toggle()   do { LATC6 = ~LATC6; } while(0)
//#define TX_GetValue()         RC6
//#define TX_SetDigitalInput()    do { TRISC6 = 1; } while(0)
//#define TX_SetDigitalOutput()   do { TRISC6 = 0; } while(0)
//
//#define TX_SetPullup()    do { WPUC6 = 1; } while(0)
//#define TX_ResetPullup()   do { WPUC6 = 0; } while(0)
//#define TX_SetAnalogMode()   do { ANSC6 = 1; } while(0)
//#define TX_SetDigitalMode()   do { ANSC6 = 0; } while(0)
//// get/set LED_D0 aliases
//#define LED_D0_TRIS               TRISD0
//#define LED_D0_LAT                LATD0
//#define LED_D0_PORT               RD0
//#define LED_D0_WPU                WPUD0
//#define LED_D0_ANS                ANSD0
//#define LED_D0_SetHigh()    do { LATD0 = 1; } while(0)
//#define LED_D0_SetLow()   do { LATD0 = 0; } while(0)
//#define LED_D0_Toggle()   do { LATD0 = ~LATD0; } while(0)
//#define LED_D0_GetValue()         RD0
//#define LED_D0_SetDigitalInput()    do { TRISD0 = 1; } while(0)
//#define LED_D0_SetDigitalOutput()   do { TRISD0 = 0; } while(0)
//
//#define LED_D0_SetPullup()    do { WPUD0 = 1; } while(0)
//#define LED_D0_ResetPullup()   do { WPUD0 = 0; } while(0)
//#define LED_D0_SetAnalogMode()   do { ANSD0 = 1; } while(0)
//#define LED_D0_SetDigitalMode()   do { ANSD0 = 0; } while(0)
// get/set RLY_L1 aliases
#define RLY_L1_TRIS               TRISC1
#define RLY_L1_LAT                LATC1
#define RLY_L1_PORT               RC1
#define RLY_L1_WPU                WPUC1
#define RLY_L1_ANS                ANSC1
#define RLY_L1_SetHigh()    do { LATC1 = 1; } while(0)
#define RLY_L1_SetLow()   do { LATC1 = 0; } while(0)
#define RLY_L1_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define RLY_L1_GetValue()         RD1
#define RLY_L1_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define RLY_L1_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

#define RLY_L1_SetPullup()    do { WPUC1 = 1; } while(0)
#define RLY_L1_ResetPullup()   do { WPUC1 = 0; } while(0)
#define RLY_L1_SetAnalogMode()   do { ANSC1 = 1; } while(0)
#define RLY_L1_SetDigitalMode()   do { ANSC1 = 0; } while(0)
// get/set RLY_L1 aliases
#define RLY_L1_TRIS               TRISC1
#define RLY_L1_LAT                LATC1
#define RLY_L1_PORT               RC1
#define RLY_L1_WPU                WPUC1
#define RLY_L1_ANS                ANSC1
#define RLY_L1_SetHigh()    do { LATC1 = 1; } while(0)
#define RLY_L1_SetLow()   do { LATC1 = 0; } while(0)
#define RLY_L1_Toggle()   do { LATC1 = ~LATC1; } while(0)
//#define RLY_L1_GetValue()         RC1
#define RLY_L1_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define RLY_L1_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

#define RLY_L1_SetPullup()    do { WPUC1 = 1; } while(0)
#define RLY_L1_ResetPullup()   do { WPUC1 = 0; } while(0)
#define RLY_L1_SetAnalogMode()   do { ANSC1 = 1; } while(0)
#define RLY_L1_SetDigitalMode()   do { ANSC1 = 0; } while(0)
// get/set RLY_L2 aliases
#define RLY_L2_TRIS               TRISC0
#define RLY_L2_LAT                LATC0
#define RLY_L2_PORT               RC0
#define RLY_L2_WPU                WPUC0
#define RLY_L2_ANS                ANSC0
#define RLY_L2_SetHigh()    do { LATC0 = 1; } while(0)
#define RLY_L2_SetLow()   do { LATC0 = 0; } while(0)
#define RLY_L2_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define RLY_L2_GetValue()         RC0
#define RLY_L2_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define RLY_L2_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

#define RLY_L2_SetPullup()    do { WPUC0 = 1; } while(0)
#define RLY_L2_ResetPullup()   do { WPUC0 = 0; } while(0)
#define RLY_L2_SetAnalogMode()   do { ANSC0 = 1; } while(0)
#define RLY_L2_SetDigitalMode()   do { ANSC0 = 0; } while(0)
// get/set RLY_R1 aliases
#define RLY_R1_TRIS               TRISC7
#define RLY_R1_LAT                LATC7
#define RLY_R1_PORT               RC7
#define RLY_R1_WPU                WPUC7
#define RLY_R1_ANS                ANSC7
#define RLY_R1_SetHigh()    do { LATC7 = 1; } while(0)
#define RLY_R1_SetLow()   do { LATC7 = 0; } while(0)
#define RLY_R1_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RLY_R1_GetValue()         RC7
#define RLY_R1_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RLY_R1_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RLY_R1_SetPullup()    do { WPUC7 = 1; } while(0)
#define RLY_R1_ResetPullup()   do { WPUC7 = 0; } while(0)
#define RLY_R1_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RLY_R1_SetDigitalMode()   do { ANSC7 = 0; } while(0)
// get/set RLY_R2 aliases
#define RLY_R2_TRIS               TRISC4
#define RLY_R2_LAT                LATC4
#define RLY_R2_PORT               RC4
#define RLY_R2_WPU                WPUC4
#define RLY_R2_ANS                ANSC4
#define RLY_R2_SetHigh()    do { LATC4 = 1; } while(0)
#define RLY_R2_SetLow()   do { LATC4 = 0; } while(0)
#define RLY_R2_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define RLY_R2_GetValue()         RC4
#define RLY_R2_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define RLY_R2_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define RLY_R2_SetPullup()    do { WPUC4 = 1; } while(0)
#define RLY_R2_ResetPullup()   do { WPUC4 = 0; } while(0)
#define RLY_R2_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define RLY_R2_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set CAN_STB aliases
#define CAN_STB_TRIS               TRISB5
#define CAN_STB_LAT                LATB5
#define CAN_STB_PORT               RB5
#define CAN_STB_WPU                WPUB5
#define CAN_STB_ANS                ANSB5
#define CAN_STB_SetHigh()    do { LATB5 = 1; } while(0)
#define CAN_STB_SetLow()   do { LATB5 = 0; } while(0)
#define CAN_STB_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define CAN_STB_GetValue()         RB5
#define CAN_STB_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define CAN_STB_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define CAN_STB_SetPullup()    do { WPUB5 = 1; } while(0)
#define CAN_STB_ResetPullup()   do { WPUB5 = 0; } while(0)
#define CAN_STB_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define CAN_STB_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set CAN_RX aliases
#define CAN_RX_TRIS               TRISB3
#define CAN_RX_LAT                LATB3
#define CAN_RX_PORT               RB3
#define CAN_RX_WPU                WPUB3
#define CAN_RX_ANS                ANSB3
#define CAN_RX_SetHigh()    do { LATB3 = 1; } while(0)
#define CAN_RX_SetLow()   do { LATB3 = 0; } while(0)
#define CAN_RX_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define CAN_RX_GetValue()         RB3
#define CAN_RX_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define CAN_RX_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define CAN_RX_SetPullup()    do { WPUB3 = 1; } while(0)
#define CAN_RX_ResetPullup()   do { WPUB3 = 0; } while(0)
#define CAN_RX_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define CAN_RX_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set CAN_TX aliases
#define CAN_TX_TRIS               TRISB2
#define CAN_TX_LAT                LATB2
#define CAN_TX_PORT               RB2
#define CAN_TX_WPU                WPUB2
#define CAN_TX_ANS                ANSB2
#define CAN_TX_SetHigh()    do { LATB2 = 1; } while(0)
#define CAN_TX_SetLow()   do { LATB2 = 0; } while(0)
#define CAN_TX_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define CAN_TX_GetValue()         RB2
#define CAN_TX_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define CAN_TX_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define CAN_TX_SetPullup()    do { WPUB2 = 1; } while(0)
#define CAN_TX_ResetPullup()   do { WPUB2 = 0; } while(0)
#define CAN_TX_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define CAN_TX_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set VHALL_SEN_EN aliases
#define VHALL_SEN_EN_TRIS               TRISB7
#define VHALL_SEN_EN_LAT                LATB7
#define VHALL_SEN_EN_PORT               RB7
#define VHALL_SEN_EN_WPU                WPUB7
#define VHALL_SEN_EN_ANS                ANSB7
#define VHALL_SEN_EN_SetHigh()    do { LATB7 = 1; } while(0)
#define VHALL_SEN_EN_SetLow()   do { LATB7 = 0; } while(0)
#define VHALL_SEN_EN_Toggle()   do { LATB7 = ~LATB7; } while(0)
#define VHALL_SEN_EN_GetValue()         RB7
#define VHALL_SEN_EN_SetDigitalInput()    do { TRISB7 = 1; } while(0)
#define VHALL_SEN_EN_SetDigitalOutput()   do { TRISB7 = 0; } while(0)

#define VHALL_SEN_EN_SetPullup()    do { WPUB7 = 1; } while(0)
#define VHALL_SEN_EN_ResetPullup()   do { WPUB7 = 0; } while(0)
#define VHALL_SEN_EN_SetAnalogMode()   do { ANSB7 = 1; } while(0)
#define VHALL_SEN_EN_SetDigitalMode()   do { ANSB7 = 0; } while(0)
// get/set VBAT_SEN_EN aliases
#define VBAT_SEN_EN_TRIS               TRISB6
#define VBAT_SEN_EN_LAT                LATB6
#define VBAT_SEN_EN_PORT               RB6
#define VBAT_SEN_EN_WPU                WPUB6
#define VBAT_SEN_EN_ANS                ANSB6
#define VBAT_SEN_EN_SetHigh()    do { LATB6 = 1; } while(0)
#define VBAT_SEN_EN_SetLow()   do { LATB6 = 0; } while(0)
#define VBAT_SEN_EN_Toggle()   do { LATB6 = ~LATB6; } while(0)
#define VBAT_SEN_EN_GetValue()         RB6
#define VBAT_SEN_EN_SetDigitalInput()    do { TRISB6 = 1; } while(0)
#define VBAT_SEN_EN_SetDigitalOutput()   do { TRISB6 = 0; } while(0)

#define VBAT_SEN_EN_SetPullup()    do { WPUB6 = 1; } while(0)
#define VBAT_SEN_EN_ResetPullup()   do { WPUB6 = 0; } while(0)
#define VBAT_SEN_EN_SetAnalogMode()   do { ANSB6 = 1; } while(0)
#define VBAT_SEN_EN_SetDigitalMode()   do { ANSB6 = 0; } while(0)
// get/set PULL aliases
#define PULL_TRIS               TRISB0
#define PULL_LAT                LATB0
#define PULL_PORT               RB0
#define PULL_WPU                WPUB0
#define PULL_ANS                ANSB0
#define PULL_SetHigh()    do { LATB0 = 1; } while(0)
#define PULL_SetLow()   do { LATB0 = 0; } while(0)
#define PULL_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define PULL_GetValue()         RB0
#define PULL_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define PULL_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define PULL_SetPullup()    do { WPUB0 = 1; } while(0)
#define PULL_ResetPullup()   do { WPUB0 = 0; } while(0)
#define PULL_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define PULL_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set PULR aliases
#define PULR_TRIS               TRISB0
#define PULR_LAT                LATB0
#define PULR_PORT               RB0
#define PULR_WPU                WPUB0
#define PULR_ANS                ANSB0
#define PULR_SetHigh()    do { LATB0 = 1; } while(0)
#define PULR_SetLow()   do { LATB0 = 0; } while(0)
#define PULR_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define PULR_GetValue()         RB0
#define PULR_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define PULR_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define PULR_SetPullup()    do { WPUB0 = 1; } while(0)
#define PULR_ResetPullup()   do { WPUB0 = 0; } while(0)
#define PULR_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define PULR_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set RLY_SEN_L1 aliases
#define RLY_SEN_L1_TRIS               TRISC3
#define RLY_SEN_L1_LAT                LATC3
#define RLY_SEN_L1_PORT               RC3
#define RLY_SEN_L1_WPU                WPUC3
#define RLY_SEN_L1_ANS                ANSC3
#define RLY_SEN_L1_SetHigh()    do { LATC3 = 1; } while(0)
#define RLY_SEN_L1_SetLow()   do { LATC3 = 0; } while(0)
#define RLY_SEN_L1_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define RLY_SEN_L1_GetValue()         RC3
#define RLY_SEN_L1_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define RLY_SEN_L1_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define RLY_SEN_L1_SetPullup()    do { WPUC3 = 1; } while(0)
#define RLY_SEN_L1_ResetPullup()   do { WPUC3 = 0; } while(0)
#define RLY_SEN_L1_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define RLY_SEN_L1_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set RLY_SEN_L2 aliases
#define RLY_SEN_L2_TRIS               TRISC2
#define RLY_SEN_L2_LAT                LATC2
#define RLY_SEN_L2_PORT               RC2
#define RLY_SEN_L2_WPU                WPUC2
#define RLY_SEN_L2_ANS                ANSC2
#define RLY_SEN_L2_SetHigh()    do { LATC2 = 1; } while(0)
#define RLY_SEN_L2_SetLow()   do { LATC2 = 0; } while(0)
#define RLY_SEN_L2_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define RLY_SEN_L2_GetValue()         RC2
#define RLY_SEN_L2_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define RLY_SEN_L2_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define RLY_SEN_L2_SetPullup()    do { WPUC2 = 1; } while(0)
#define RLY_SEN_L2_ResetPullup()   do { WPUC2 = 0; } while(0)
#define RLY_SEN_L2_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define RLY_SEN_L2_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set RLY_SEN_R1 aliases
#define RLY_SEN_R1_TRIS               TRISC6
#define RLY_SEN_R1_LAT                LATC6
#define RLY_SEN_R1_PORT               RC6
#define RLY_SEN_R1_WPU                WPUC6
#define RLY_SEN_R1_ANS                ANSC6
#define RLY_SEN_R1_SetHigh()    do { LATC6 = 1; } while(0)
#define RLY_SEN_R1_SetLow()   do { LATC6 = 0; } while(0)
#define RLY_SEN_R1_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define RLY_SEN_R1_GetValue()         RC6
#define RLY_SEN_R1_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define RLY_SEN_R1_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define RLY_SEN_R1_SetPullup()    do { WPUC6 = 1; } while(0)
#define RLY_SEN_R1_ResetPullup()   do { WPUC6 = 0; } while(0)
#define RLY_SEN_R1_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define RLY_SEN_R1_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set RLY_SEN_L2 aliases
#define RLY_SEN_R2_TRIS               TRISC5
#define RLY_SEN_R2_LAT                LATC5
#define RLY_SEN_R2_PORT               RC5
#define RLY_SEN_R2_WPU                WPUC5
#define RLY_SEN_R2_ANS                ANSC5
#define RLY_SEN_R2_SetHigh()    do { LATC5 = 1; } while(0)
#define RLY_SEN_R2_SetLow()   do { LATC5 = 0; } while(0)
#define RLY_SEN_R2_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define RLY_SEN_R2_GetValue()         RC5
#define RLY_SEN_R2_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define RLY_SEN_R2_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define RLY_SEN_R2_SetPullup()    do { WPUC5 = 1; } while(0)
#define RLY_SEN_R2_ResetPullup()   do { WPUC5 = 0; } while(0)
#define RLY_SEN_R2_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define RLY_SEN_R2_SetDigitalMode()   do { ANSC5 = 0; } while(0)

#include "app.h"
#include "adc.h"
#include "timer.h"
#include "ecan.h"
#include "rly.h"
#ifdef	__cplusplus
}
#endif


#endif	/* BSP_H */


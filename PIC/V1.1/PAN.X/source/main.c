
/**********************************************************************
* 2017 FangcunApply Technology Inc.
*
* FileName:        
* Dependencies:    
* Processor:       PIC18F66K80 family
* Linker:          
* Compiler:        XC8
*
* 
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 曹宇.        2017-7-31     完善低功耗，加入电池亏电检测
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 曹宇.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ADDITIONAL NOTES:
* 
* 
* DESCRIPTION:
* 
* 
*********************************************************************/



#include "bsp.h"
/**************************************************/
//器件参数配置
#pragma config INTOSCSEL=LOW//休眠期间LF-INTOSC处于低功耗模式
#pragma config SOSCSEL=DIG //数字模式使能RC0,RC1端口功能
#pragma config XINST=OFF  //不使用扩展指令集
#pragma config RETEN=OFF  //禁止超低功耗稳压器
#pragma config IESO=OFF    // 禁止双速启动
#pragma config FOSC=HS1   //振荡器4-16MHZ
#pragma config FCMEN=OFF //禁止故障保护时钟
#pragma config PLLCFG=OFF  //直接试用晶振
#pragma config BOREN=OFF   //关闭欠压复位
#pragma config BORPWR=LOW  //低功耗级别
#pragma config BORV=3    //欠压复位电压1.8V
#pragma config PWRTEN=OFF //禁止上电延时复位
#pragma config WDTPS=256   //WDT后分频比为1:256约为1.024S
#pragma config WDTEN=OFF   //关闭看门狗
#pragma config CANMX=PORTB  //CAN TX RX为RB2 RB3
#pragma config MSSPMSK=MSK7  //7位地址掩码
#pragma config MCLRE=ON      // 使能MCLR复位引脚，禁止RE3IO功能
#pragma config STVREN=OFF     //堆栈下溢、满不会导致复位
#pragma config BBSIZ=BB2K   //引导区为2K
#pragma config CP0=OFF      //代码保护关闭
#pragma config CP1=OFF
#pragma config CP2=OFF
#pragma config CP3=OFF
#pragma config CPD=OFF
#pragma config CPB=OFF
#pragma config WRT0=OFF    //不写保护
#pragma config WRT1=OFF
#pragma config WRT2=OFF
#pragma config WRT3=OFF
#pragma config WRTB=OFF
#pragma config WRTC=OFF
#pragma config WRTD=OFF
#pragma config EBTR0=OFF
#pragma config EBTR1=OFF
#pragma config EBTR2=OFF
#pragma config EBTR3=OFF   //允许表读
#pragma config EBTRB=OFF

int main(void)
{
    App_System_Init();//系统应用初始化
    //系统进入休眠模式
    SysEnterSleep();
    App_System_Init();//唤醒后重新初始化
    while(1)    
    {
        //应用任务轮询处理
        AppTask_PollHandler();
    }
}

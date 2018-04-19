#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名: RLY_Init
*	功能说明: 继电器IO初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RLY_Init(void)
{
    RLY_L1_SetLow();
    RLY_L2_SetLow();
    RLY_R1_SetLow();
    RLY_R2_SetLow();
    RLY_L1_SetDigitalOutput();
    RLY_L2_SetDigitalOutput();
    RLY_R1_SetDigitalOutput();
    RLY_R2_SetDigitalOutput();
}
/*
*********************************************************************************************************
*	函 数 名: Pedal_Out
*	功能说明: 踏板伸出
*	形    参: dir : 踏板方向选择，范围 0,1
*	返 回 值: 无
*********************************************************************************************************
*/
void Pedal_Out(uint8_t dir)
{
     if(dir == PEDAL_LEFT)
    {
        RLY_L1_SetHigh();
        RLY_L2_SetLow();  //逆时针
    }
    else if(dir == PEDAL_RIGHT)
    {
        RLY_R1_SetLow();  //顺时针
        RLY_R2_SetHigh();
    }
}
/*
*********************************************************************************************************
*	函 数 名: Pedal_Back
*	功能说明: 踏板收回
*	形    参: dir : 踏板方向选择，范围 0,1
*	返 回 值: 无
*********************************************************************************************************
*/
void Pedal_Back(uint8_t dir)
{
     if(dir == PEDAL_LEFT)
    {
        RLY_L1_SetLow();
        RLY_L2_SetHigh();  //顺时针
    }
    else if(dir == PEDAL_RIGHT)
    {
        RLY_R1_SetHigh();
        RLY_R2_SetLow();  //逆时针
    }
}
/*
*********************************************************************************************************
*	函 数 名: Pedal_Stop
*	功能说明: 踏板停止
*	形    参: dir : 踏板方向选择，范围 0,1
*	返 回 值: 无
*********************************************************************************************************
*/
void Pedal_Stop(uint8_t dir)
{
     if(dir == PEDAL_LEFT)
    {
        RLY_L1_SetLow();
        RLY_L2_SetLow();
    }
    else if(dir == PEDAL_RIGHT)
    {
        RLY_R1_SetLow();
        RLY_R2_SetLow();
    }
}



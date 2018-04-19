#include "bsp.h"

/*
*********************************************************************************************************
*	�� �� ��: RLY_Init
*	����˵��: �̵���IO��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
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
*	�� �� ��: Pedal_Out
*	����˵��: ̤�����
*	��    ��: dir : ̤�巽��ѡ�񣬷�Χ 0,1
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Pedal_Out(uint8_t dir)
{
     if(dir == PEDAL_LEFT)
    {
        RLY_L1_SetHigh();
        RLY_L2_SetLow();  //��ʱ��
    }
    else if(dir == PEDAL_RIGHT)
    {
        RLY_R1_SetLow();  //˳ʱ��
        RLY_R2_SetHigh();
    }
}
/*
*********************************************************************************************************
*	�� �� ��: Pedal_Back
*	����˵��: ̤���ջ�
*	��    ��: dir : ̤�巽��ѡ�񣬷�Χ 0,1
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Pedal_Back(uint8_t dir)
{
     if(dir == PEDAL_LEFT)
    {
        RLY_L1_SetLow();
        RLY_L2_SetHigh();  //˳ʱ��
    }
    else if(dir == PEDAL_RIGHT)
    {
        RLY_R1_SetHigh();
        RLY_R2_SetLow();  //��ʱ��
    }
}
/*
*********************************************************************************************************
*	�� �� ��: Pedal_Stop
*	����˵��: ̤��ֹͣ
*	��    ��: dir : ̤�巽��ѡ�񣬷�Χ 0,1
*	�� �� ֵ: ��
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


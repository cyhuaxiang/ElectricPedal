#include "bsp.h"

KEY_T s_tBtn;

/*
*********************************************************************************************************
*	函 数 名: RemoteCtrl_Init
*	功能说明: 遥控初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RemoteCtrl_Init(void)
{
#if REMOTE_CTRL_MODE == 1
    ANCON1bits.ANSEL9 = 0;
    REMOTE_IN_SetDigitalInput();
    IOCBbits.IOCB4 = 1;//允许电平变化中断
    INTCONbits.RBIF = 0;//清除RB端口电平变化中断标志位
    INTCONbits.RBIE = 1;//允许RB端口电平变化中断
    INTCON2bits.RBIP = 1;//RB端口电平变化中断设为高优先级
    
    /* 对按键FIFO读写指针清零 */
    s_tBtn.LongTime = KEY_LONG_TIME;			/* 长按时间 0 表示不检测长按键事件 */
    s_tBtn.Count = KEY_FILTER_TIME / 2;		/* 计数器设置为滤波时间的一半 */
    s_tBtn.State = 0;							/* 按键缺省状态，0为未按下 */
    s_tBtn.RepeatSpeed = 0;						/* 按键连发的速度，0表示不支持连发 */
    s_tBtn.RepeatCount = 0;						/* 连发计数器 */
#endif
  
}

/*
*********************************************************************************************************
*	函 数 名: bsp_DetectKey
*	功能说明: 遥控检测，定时10ms扫描
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_DetectKey(void)
{
   
    KEY_T *pBtn;

	pBtn = &s_tBtn;
	if (REMOTE_IN_GetValue() == 0)
	{
		if (pBtn->Count < KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count < 2 * KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;

				/* 发送按钮按下的消息 */
				
			}

			if (pBtn->LongTime > 0)
			{
				if (pBtn->LongCount < pBtn->LongTime)
				{
					/* 发送按钮持续按下的消息 */
					if (++pBtn->LongCount == pBtn->LongTime)
					{
						/* 键值放入按键FIFO */
						
					}
				}
				else
				{
					if (pBtn->RepeatSpeed > 0)
					{
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount = 0;
							/* 常按键后，每隔10ms发送1个按键 */
							
						}
					}
				}
			}
		}
	}
	else
	{
		if(pBtn->Count > KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;
                if (pBtn->LongCount < pBtn->LongTime)
                {
                    if(SysRunData.RemoteCtrlSta == LOCK)
                    {
                        SysRunData.RemoteCtrlSta = UNLOCK;
                        LeftDoorOpen();
                        RightDoorOpen();
                    }
                    else
                    {
                        SysRunData.RemoteCtrlSta = LOCK;
                        LeftDoorClose();
                        RightDoorClose();
                    }
                    pBtn->LongCount = 0;
                }
                else
                {
                    pBtn->LongCount = 0;
                }    
			}
		}

//		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}
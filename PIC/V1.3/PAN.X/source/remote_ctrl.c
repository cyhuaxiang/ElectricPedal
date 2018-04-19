#include "bsp.h"

KEY_T s_tBtn;

/*
*********************************************************************************************************
*	�� �� ��: RemoteCtrl_Init
*	����˵��: ң�س�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void RemoteCtrl_Init(void)
{
#if REMOTE_CTRL_MODE == 1
    ANCON1bits.ANSEL9 = 0;
    REMOTE_IN_SetDigitalInput();
    IOCBbits.IOCB4 = 1;//�����ƽ�仯�ж�
    INTCONbits.RBIF = 0;//���RB�˿ڵ�ƽ�仯�жϱ�־λ
    INTCONbits.RBIE = 1;//����RB�˿ڵ�ƽ�仯�ж�
    INTCON2bits.RBIP = 1;//RB�˿ڵ�ƽ�仯�ж���Ϊ�����ȼ�
    
    /* �԰���FIFO��дָ������ */
    s_tBtn.LongTime = KEY_LONG_TIME;			/* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
    s_tBtn.Count = KEY_FILTER_TIME / 2;		/* ����������Ϊ�˲�ʱ���һ�� */
    s_tBtn.State = 0;							/* ����ȱʡ״̬��0Ϊδ���� */
    s_tBtn.RepeatSpeed = 0;						/* �����������ٶȣ�0��ʾ��֧������ */
    s_tBtn.RepeatCount = 0;						/* ���������� */
#endif
  
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_DetectKey
*	����˵��: ң�ؼ�⣬��ʱ10msɨ��
*	��    ��: ��
*	�� �� ֵ: ��
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

				/* ���Ͱ�ť���µ���Ϣ */
				
			}

			if (pBtn->LongTime > 0)
			{
				if (pBtn->LongCount < pBtn->LongTime)
				{
					/* ���Ͱ�ť�������µ���Ϣ */
					if (++pBtn->LongCount == pBtn->LongTime)
					{
						/* ��ֵ���밴��FIFO */
						
					}
				}
				else
				{
					if (pBtn->RepeatSpeed > 0)
					{
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount = 0;
							/* ��������ÿ��10ms����1������ */
							
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
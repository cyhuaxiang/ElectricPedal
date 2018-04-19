#include "bsp.h"

/*
********************************************************************************
*
*   ģ������ : Ӧ�ó������
*   �ļ����� : app.c
*   ��    �� : V1.2
*   ˵    �� : Ӧ�ò���ڣ�Ҳ��ϵͳ��ڣ���Ҫ��ʼ���������������ݣ�����LogicTask    
*              
*   �޸ļ�¼ :
*       �汾��  ����        ����     ˵��
*       V1.0    2017-08-01   cy  ��ʼ�汾
*       V1.1    2017-09-16   cy  �Ż�̤���߼����������������ʱ�����Ż�CAN����
*                                ��Ϣ�����Ժ�����µĳ��ͣ�ֻ��Ҫ��app.h�ļ���
*                                �ĺ궨�弴��
*       V1.2    2017-09-27   cy  ������ٿ�����̤�岻��ֹͣ������
*   Copyright (C), 2017-20xx, xxxxxx
*
********************************************************************************
*/

//*******************************************************************************
SYS_RUN_DATA_T SysRunData;
//*******************************************************************************
static void Pedal_Process(void);
static uint16_t GetADC(uint8_t channel);
static void SysVoltDetect(void);
static void SetSysClock(void);
static void SysNormalWaitSleep(void);
static void SysErrorWaitSleep(void);
static void PORT_Init(void);   
//*******************************************************************************

/*
*********************************************************************************************************
*	�� �� ��: App_System_Init
*	����˵��: ϵͳӦ�ó�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void App_System_Init(void)
{
    /* ʹ���ж����ȼ� */
    ENABLE_IP();
    /* ��ȫ���жϣ��ߡ������ȼ� */
    ENABLE_INT();
    /* ����ϵͳʱ�� */
    SetSysClock();
    /* Ӳ����ʼ�� */
    ADC_Init();
    ECAN_Init();
    RLY_Init();
    PORT_Init();
    /* ����ϵͳ���� */
    ConfigTimer0(1);
    //CAN�շ�������Ϊ����ģʽ
    CAN_SetMode(CAN_MODE_NORMAL);
    //ADC�ɼ�ʹ��
    ADC_Cmd(ADC_CHS_VHALL,ENABLE); 
    ADC_Cmd(ADC_CHS_VBAT,ENABLE); 
    /* ����ʱ��Ƭ */
    bsp_StartAutoTimer(TIMER_PEDAL,10);//10msʱ��Ƭ
    bsp_StartAutoTimer(TIMER_ADC,1);//1msʱ��Ƭ
}
/*
*********************************************************************************************************
*	�� �� ��: AppTask_PollHandler
*	����˵��: ϵͳӦ��������ѯ����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void AppTask_PollHandler(void)
{
    if (bsp_CheckTimer(TIMER_ADC))	/* 1ms��ʱ�� */
    {
        AdcPro();  
//        SysVoltDetect();//ϵͳ��ѹ���
//        CAN_TX_Test();
    } 
    if (bsp_CheckTimer(TIMER_PEDAL))	/* 10ms��ʱ�� */
    {
        if(SysRunData.SysSta == SYS_NORMAL)
        {
            Pedal_Process();  //̤���߼�����
        }
        else
        {
//            SysErrorWaitSleep();
        }
    }  
}
/*
*********************************************************************************************************
*	�� �� ��: Pedal_Process
*	����˵��: ̤���߼����ƽ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void Pedal_Process(void)
{
//    uint16_t StallCurrent = 0;
    /*���̤���߼�����*/
    
    if(LeftDoorIsOpen)//������Ŵ�
    {
        switch(SysRunData.PedalSta[PEDAL_LEFT])
        {
            case PEDAL_DOWN_LIMIT:
                if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//������������
                {
                    Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_OUT;
//                    if(++SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
//                    {
//                        Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
//                        SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_OUT;
//                    } 
//                    else//�����ϰ���
//                    {
//                        
//                    }
                } 
                break;
            case PEDAL_ERROR_FAST_BACK:
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_DOWN_LIMIT;
                break;
            case PEDAL_UP_LIMIT:
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Out(PEDAL_LEFT); 
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
//                    StallCurrent = GetADC(ADC_CHS_CURRENT_L);
                    if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//������������
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
                            {
                                Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_NORMAL_WAIT_BACK;
                            }
                            else  //�����ϰ���
                            {
                                Pedal_Stop(PEDAL_LEFT);
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_STALL_BACK; 
                                Pedal_Back(PEDAL_LEFT);   //̤�������ϰ�������
                                SysRunData.PedalWaitSleepCnt = 0;
                            }
                        }    
                    }
                }
                else//������ʱ
                {
                    Pedal_Stop(PEDAL_LEFT);//��̤��ֹͣ          
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_OUT_TIMEOUT;  
                }       
                break;
            case PEDAL_ERROR_STALL_BACK:
                //�������ϰ���ʱ������ʱ�ж�
                SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//������������
                    {
                        Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ
                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                        SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_STALL_BACK;
                    }
                }
                break;
            case PEDAL_STALL_WAIT_BACK:
                 //��ת�������������
                SysRunData.PedalWaitBackCnt[PEDAL_LEFT] = 0;
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_DOWN_LIMIT;  
                break;
            case PEDAL_ERROR_BACK_TIMEOUT:   
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Out(PEDAL_LEFT);
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//������ʱ
                {
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_OUT_TIMEOUT;    
                    Pedal_Stop(PEDAL_LEFT);//��̤�������ϰ���ֹͣ
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                }        
                break; 
            default:
                break;                    
        }
    }
    else//  ��ߵ���ȫ���ر�
    {
        switch(SysRunData.PedalSta[PEDAL_LEFT])
        {
            case PEDAL_NORMAL_WAIT_BACK:
                if(++SysRunData.PedalWaitBackCnt[PEDAL_LEFT] >= PEDAL_NORMAL_WAIT_BACK_TIME)   
                {
                    SysRunData.PedalWaitBackCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_DOWN_LIMIT;    
                }
                break;
            case PEDAL_UP_LIMIT:
                if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//������������
                {
                    Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_BACK;
//                    if(++SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
//                    {
//                        Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
//                        SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_BACK;
//                    }  
//                    else//�����ϰ���
//                    {
//                        
//                    }
                }    
                break;
            case PEDAL_ERROR_FAST_OUT:
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_UP_LIMIT;
                break;
            case PEDAL_DOWN_LIMIT:
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Back(PEDAL_LEFT);
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
//                    StallCurrent = GetADC(ADC_CHS_CURRENT_L);
                    if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//������������
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
                            {
                                Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                                SysRunData.PedalWaitSleepCnt = 0;
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_UP_LIMIT;
                            }
                            else//�����ϰ���
                            {
                                Pedal_Stop(PEDAL_LEFT);
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_STALL_OUT;  
                                Pedal_Out(PEDAL_LEFT);//̤������ʱ�����ϰ���̤�����
                            }
                        }   
                    }              
                }
                else//������ʱ
                {
                    Pedal_Stop(PEDAL_LEFT);//��̤�������ϰ���ֹͣ
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_BACK_TIMEOUT;    
                }     
                break;  
            case PEDAL_ERROR_STALL_OUT:
                 //�������ϰ���ʱ������ʱ�ж�
                SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//������������
                    {
                        //����һ�ζ�ת�������ȥ���ټ����ζ�ת
                        Pedal_Stop(PEDAL_LEFT);//��̤�嶯����λ  
                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                        SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_STALL_WAIT_BACK;
                    } 
                }
                break;  
            case PEDAL_STALL_WAIT_BACK:
                SysRunData.PedalWaitSleepCnt = 0;
                if(++SysRunData.PedalWaitBackCnt[PEDAL_LEFT] >= PEDAL_STALL_WAIT_BACK_TIME)
                {
                    SysRunData.PedalWaitBackCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_DOWN_LIMIT;  
                } 
                break;   
            case PEDAL_ERROR_STALL_BACK:
                //̤��״̬�л�������λ
                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_UP_LIMIT;
                break;   
            case PEDAL_ERROR_OUT_TIMEOUT:
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Back(PEDAL_LEFT);
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//������ʱ
                {
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_BACK_TIMEOUT;    
                    Pedal_Stop(PEDAL_LEFT);//��̤�������ϰ���ֹͣ
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                }        
                break;                      
            default:
                break;                             
        }
    }
    
    ////*****************************************************
    ////*****************************************************
    /*�ұ�̤���߼�����*/
    if(RightDoorIsOpen)//�ұ����Ŵ�
    {
        switch(SysRunData.PedalSta[PEDAL_RIGHT])
        {
            case PEDAL_DOWN_LIMIT:
                if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//������������
                {
                    Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_OUT;
//                    if(++SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
//                    {
//                        Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
//                        SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_OUT;
//                    } 
//                    else//�����ϰ���
//                    {
//                        
//                    }
                } 
                break;
            case PEDAL_ERROR_FAST_BACK:
                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_DOWN_LIMIT;
                break;
                break;
            case PEDAL_UP_LIMIT:
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Out(PEDAL_RIGHT); 
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                    if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//������������
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
                            {
                                Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_NORMAL_WAIT_BACK;
                            }
                            else //�����ϰ���
                            {
                                Pedal_Stop(PEDAL_RIGHT);
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_STALL_BACK; 
                                Pedal_Back(PEDAL_RIGHT);   //̤�������ϰ������� 
                                SysRunData.PedalWaitSleepCnt = 0;
                            }
                        }
                    }
                }
                else//������ʱ
                {
                    Pedal_Stop(PEDAL_RIGHT);//��̤��ֹͣ          
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_OUT_TIMEOUT;    
                }       
                break;
            case PEDAL_ERROR_STALL_BACK:
                //�������ϰ���ʱ������ʱ�ж�
                SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//������������
                    {
                        Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ
                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                        SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_STALL_BACK;
                    }   
                }
                break;
            case PEDAL_STALL_WAIT_BACK:
                 //��ת�������������
                SysRunData.PedalWaitBackCnt[PEDAL_RIGHT] = 0;
                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_DOWN_LIMIT;  
                break;
            case PEDAL_ERROR_BACK_TIMEOUT:   
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Out(PEDAL_RIGHT);
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//������ʱ
                {
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_OUT_TIMEOUT;    
                    Pedal_Stop(PEDAL_RIGHT);//��̤�������ϰ���ֹͣ
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                }        
                break; 
            default:
                break;                    
        }
    }
    else//  �ұߵ���ȫ���ر�
    {
        switch(SysRunData.PedalSta[PEDAL_RIGHT])
        {
            case PEDAL_NORMAL_WAIT_BACK:
                if(++SysRunData.PedalWaitBackCnt[PEDAL_RIGHT] >= PEDAL_NORMAL_WAIT_BACK_TIME)   
                {
                    SysRunData.PedalWaitBackCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_DOWN_LIMIT;    
                }
                break;
            case PEDAL_UP_LIMIT:
               if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//������������
                {
                    Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_BACK;
//                    if(++SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
//                    {
//                        Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
//                        SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_BACK;
//                    }  
//                    else//�����ϰ���
//                    {
//                        
//                    }
                }    
                break;
            case PEDAL_ERROR_FAST_OUT:
                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_UP_LIMIT;
                break;
                break;
            case PEDAL_DOWN_LIMIT:
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Back(PEDAL_RIGHT);
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
//                    StallCurrent = GetADC(ADC_CHS_CURRENT_R);
                    if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//������������
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //̤�嶯��ʱ������趨ֵ 
                            {
                                Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalWaitSleepCnt = 0;
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_UP_LIMIT;
                            }
                            else//�����ϰ���
                            {
                                Pedal_Stop(PEDAL_RIGHT);
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_STALL_OUT;
                                Pedal_Out(PEDAL_RIGHT);//̤������ʱ�����ϰ���̤�����
                                
                            }
                        }
                    }
                }
                else//������ʱ
                {
                    Pedal_Stop(PEDAL_RIGHT);//��̤�������ϰ���ֹͣ
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_BACK_TIMEOUT;    
                }     
                break;  
            case PEDAL_ERROR_STALL_OUT:
                 //�������ϰ���ʱ������ʱ�ж�
                SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//������������
                    {
                        //����һ�ζ�ת�������ȥ���ټ����ζ�ת
                        Pedal_Stop(PEDAL_RIGHT);//��̤�嶯����λ  
                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                        SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_STALL_WAIT_BACK;
                    }     
                }
                break;  
            case PEDAL_STALL_WAIT_BACK:
                SysRunData.PedalWaitSleepCnt = 0;
                if(++SysRunData.PedalWaitBackCnt[PEDAL_RIGHT] >= PEDAL_STALL_WAIT_BACK_TIME)
                {
                    SysRunData.PedalWaitBackCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_DOWN_LIMIT;  
                } 
                break;   
            case PEDAL_ERROR_STALL_BACK:
                //̤��״̬�л�������λ
                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_UP_LIMIT;
                break;   
            case PEDAL_ERROR_OUT_TIMEOUT:
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//����δ��ʱ
                {
                    Pedal_Back(PEDAL_RIGHT);
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//������ʱ
                {
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_BACK_TIMEOUT;    
                    Pedal_Stop(PEDAL_RIGHT);//��̤�������ϰ���ֹͣ
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                }        
                break;                      
            default:
                break;                             
        }
    }
    //���̤����ұ�̤�崦�ڶ�ת��ȴ�����״̬�����ߣ����غ��ٽ������ߣ�̤�嶯����ʱ������
    if((SysRunData.PedalSta[PEDAL_LEFT] != PEDAL_STALL_WAIT_BACK) || (SysRunData.PedalSta[PEDAL_RIGHT] != PEDAL_STALL_WAIT_BACK) && (SysRunData.PedalRunCnt[PEDAL_LEFT] == 0))
    {
        SysNormalWaitSleep();//ϵͳ�ȴ�����   
    }
    //̤���߼����ƽ���  
}
/*
*********************************************************************************************************
*	�� �� ��: SetSysClock
*	����˵��: ����ϵͳʱ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void SetSysClock(void)
{
    // Set the internal oscillator to 32MHz
    OSCTUNEbits.PLLEN = 1;//4��Ƶ HS = 8M, 8X4 = 32M
}

/*
*********************************************************************************************************
*	�� �� ��: SysNormalWaitSleep
*	����˵��: ϵͳ�����ȴ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void SysNormalWaitSleep(void)
{
    static uint8_t tempPedalRunFlag = 0xAA;  
    
    if(SysRunData.PedalRunFlag != tempPedalRunFlag)
    {
        tempPedalRunFlag = 0xAA;//��ʼ��̤�����б�־
        if(++SysRunData.PedalWaitSleepCnt > PEDAL_STOP_ENTER_SLEEP_TIME)
        {
            SysRunData.PedalWaitSleepCnt = 0;
            tempPedalRunFlag = SysRunData.PedalRunFlag;//����˴ε�̤���־
            SysEnterSleep();//ϵͳ����
            App_System_Init();//���Ѻ����³�ʼ��
        }
    }
    else
    {
        SysEnterSleep();//ϵͳ����
        App_System_Init();//���Ѻ����³�ʼ��
    } 
}
/*
*********************************************************************************************************
*	�� �� ��: SysEnterSleep
*	����˵��: ϵͳ��������ģʽ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 void SysEnterSleep(void)
{
    CAN_SetMode(CAN_MODE_STANDBY);//CAN�շ����������ģʽ
    ADC_Cmd(ADC_CHS_VHALL,DISABLE); 
    ADC_Cmd(ADC_CHS_VBAT,DISABLE); 
    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
    SysRunData.PedalWaitSleepCnt = 0;
    PIR5bits.WAKIF = 0;     //���CAN���߻�����жϱ�־
    PIE5bits.WAKIE = 1;     //����CAN���߻�����ж�
    IPR5bits.WAKIP = 1;     //CAN���߻�����ж�Ϊ�����ȼ�
    CANCON = 0x20;//��ֹ/����ģʽ  
    while(CANSTATbits.OPMODE !=0x01); 
    OSCCONbits.IDLEN = 0;//��������ģʽ
    Sleep();//��������ģʽ
    __delay_us(WAKEUP_US_DELAY);
}
/*
*********************************************************************************************************
*	�� �� ��: SysErrorWaitSleep
*	����˵��: ϵͳ����ȴ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
 static void SysErrorWaitSleep(void)
 {
    if(++SysRunData.PedalWaitSleepCnt > BAT_LOW_VOLT_TIME)
    {
        SysRunData.PedalWaitSleepCnt = 0;
        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
        SysRunData.PedalRunFlag = 0;
        CAN_TX_ErrorCode(ERROR_CODE_BAT_LOW_VOLT);
        SysEnterSleep();//ϵͳ����
        App_System_Init();//���Ѻ����³�ʼ��
    }
 }
/*
*********************************************************************************************************
*	�� �� ��: AdcPro
*	����˵��: ADC�˲�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void AdcPro(void)
{
	static uint16_t buf[ADC_SAMP_CNT][ADC_CHS_NUM];
	static uint8_t write;
    static uint8_t index = ADC_CHS_VBAT;
	uint16_t sum;
	uint8_t i;
    
    if(index == ADC_CHS_VBAT)//��ص�ѹ�ɼ�
    {
        buf[write][ADC_CHS_VBAT] = ADC_GetConversionValue();
        
        /* ������δ��������ƽ��ֵ�ķ��������˲�
            Ҳ���Ը����£�ѡ��ȥ����������2��ֵ��ʹ���ݸ��Ӿ�ȷ
        */
        sum = 0;
        for (i = 0; i < ADC_SAMP_CNT; i++)
        {
            sum += buf[i][ADC_CHS_VBAT];
        }
        SysRunData.ADC_Buf[ADC_CHS_VBAT] = sum / ADC_SAMP_CNT;	/* ADC����ֵ�����ɴβ���ֵƽ�� */
        index = ADC_CHS_CURRENT_R;
        ADC_StartConversion(ADC_CHS_CURRENT_R); /* ��������´�ADCת�� */
    } 
    else if(index == ADC_CHS_CURRENT_R)//�ұ�̤���ת�����ɼ�
    {
        buf[write][ADC_CHS_CURRENT_R] = ADC_GetConversionValue();

        /* ������δ��������ƽ��ֵ�ķ��������˲�
            Ҳ���Ը����£�ѡ��ȥ����������2��ֵ��ʹ���ݸ��Ӿ�ȷ
        */
        sum = 0;
        for (i = 0; i < ADC_SAMP_CNT; i++)
        {
            sum += buf[i][ADC_CHS_CURRENT_R];
        }
        SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] = sum / ADC_SAMP_CNT; /* ADC����ֵ�����ɴβ���ֵƽ�� */

        index = ADC_CHS_CURRENT_L;
        ADC_StartConversion(ADC_CHS_CURRENT_L);	/* ��������´�ADCת�� */
    }
    else if(index == ADC_CHS_CURRENT_L)//���̤���ת�����ɼ�
    {
        buf[write][ADC_CHS_CURRENT_L] = ADC_GetConversionValue();
        /* ������δ��������ƽ��ֵ�ķ��������˲�
            Ҳ���Ը����£�ѡ��ȥ����������2��ֵ��ʹ���ݸ��Ӿ�ȷ
        */
        sum = 0;
        for (i = 0; i < ADC_SAMP_CNT; i++)
        {
            sum += buf[i][ADC_CHS_CURRENT_L];
        }
        SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] = sum / ADC_SAMP_CNT; /* ADC����ֵ�����ɴβ���ֵƽ�� */
        if (++write >= ADC_SAMP_CNT)
        {
            write = 0;
        }                         
        index = ADC_CHS_VBAT;
        ADC_StartConversion(ADC_CHS_VBAT);	/* ��������´�ADCת�� */
    } 
}
/*
*********************************************************************************************************
*	�� �� ��: GetADC
*	����˵��: ϵͳ�������ģʽ
*	��    ��: channel,ADCͨ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static uint16_t GetADC(uint8_t channel)
{
	uint16_t ret;

	/* ��Ϊ	g_AdcValue ������systick�ж��и�д��Ϊ�˱��������������ʱ���жϳ�����ҵ������ݴ��������Ҫ
	�ر��жϽ��б��� */

//	/* �����ٽ����������ر��ж� */
	DISABLE_INT();  /* ���ж� */

	ret = SysRunData.ADC_Buf[channel];

	ENABLE_INT();  /* ���ж� */

	return ret;
}
/*
*********************************************************************************************************
*	�� �� ��: SysVoltDetect()
*	����˵��: ϵͳ�������ģʽ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void SysVoltDetect(void)
{
    //    ���ؼ��
    if(SysRunData.ADC_Buf[ADC_CHS_VBAT] < VBAT_UNDER_VOLT_VAL)       
    {
        SysRunData.SysSta = SYS_ERROR_UNDER_VOLT;
    }
    else
    {
        SysRunData.SysSta = SYS_NORMAL;  
    } 
}
/*
*********************************************************************************************************
*	�� �� ��: PORT_Init()
*	����˵��: ���ж˿ڳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void PORT_Init(void)   
{
    
}
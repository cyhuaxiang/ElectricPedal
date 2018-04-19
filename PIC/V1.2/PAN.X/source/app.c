#include "bsp.h"

/*
********************************************************************************
*
*   模块名称 : 应用程序入口
*   文件名称 : app.c
*   版    本 : V1.2
*   说    明 : 应用层入口，也是系统入口，主要初始化各类驱动、数据，建立LogicTask    
*              
*   修改记录 :
*       版本号  日期        作者     说明
*       V1.0    2017-08-01   cy  初始版本
*       V1.1    2017-09-16   cy  优化踏板逻辑控制任务的启动延时处理，优化CAN接收
*                                消息处理，以后添加新的车型，只需要在app.h文件修
*                                改宏定义即可
*       V1.2    2017-09-27   cy  解决快速开关门踏板不能停止的问题
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
*	函 数 名: App_System_Init
*	功能说明: 系统应用初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void App_System_Init(void)
{
    /* 使能中断优先级 */
    ENABLE_IP();
    /* 开全局中断，高、低优先级 */
    ENABLE_INT();
    /* 设置系统时钟 */
    SetSysClock();
    /* 硬件初始化 */
    ADC_Init();
    ECAN_Init();
    RLY_Init();
    PORT_Init();
    /* 配置系统节拍 */
    ConfigTimer0(1);
    //CAN收发器设置为正常模式
    CAN_SetMode(CAN_MODE_NORMAL);
    //ADC采集使能
    ADC_Cmd(ADC_CHS_VHALL,ENABLE); 
    ADC_Cmd(ADC_CHS_VBAT,ENABLE); 
    /* 分配时间片 */
    bsp_StartAutoTimer(TIMER_PEDAL,10);//10ms时间片
    bsp_StartAutoTimer(TIMER_ADC,1);//1ms时间片
}
/*
*********************************************************************************************************
*	函 数 名: AppTask_PollHandler
*	功能说明: 系统应用任务轮询处理
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void AppTask_PollHandler(void)
{
    if (bsp_CheckTimer(TIMER_ADC))	/* 1ms定时到 */
    {
        AdcPro();  
//        SysVoltDetect();//系统电压检测
//        CAN_TX_Test();
    } 
    if (bsp_CheckTimer(TIMER_PEDAL))	/* 10ms定时到 */
    {
        if(SysRunData.SysSta == SYS_NORMAL)
        {
            Pedal_Process();  //踏板逻辑处理
        }
        else
        {
//            SysErrorWaitSleep();
        }
    }  
}
/*
*********************************************************************************************************
*	函 数 名: Pedal_Process
*	功能说明: 踏板逻辑控制进程
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void Pedal_Process(void)
{
//    uint16_t StallCurrent = 0;
    /*左边踏板逻辑控制*/
    
    if(LeftDoorIsOpen)//左边有门打开
    {
        switch(SysRunData.PedalSta[PEDAL_LEFT])
        {
            case PEDAL_DOWN_LIMIT:
                if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                {
                    Pedal_Stop(PEDAL_LEFT);//左踏板动作到位
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_OUT;
//                    if(++SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
//                    {
//                        Pedal_Stop(PEDAL_LEFT);//左踏板动作到位
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
//                        SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_OUT;
//                    } 
//                    else//遇到障碍物
//                    {
//                        
//                    }
                } 
                break;
            case PEDAL_ERROR_FAST_BACK:
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_DOWN_LIMIT;
                break;
            case PEDAL_UP_LIMIT:
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Out(PEDAL_LEFT); 
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
//                    StallCurrent = GetADC(ADC_CHS_CURRENT_L);
                    if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
                            {
                                Pedal_Stop(PEDAL_LEFT);//左踏板动作到位
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_NORMAL_WAIT_BACK;
                            }
                            else  //遇到障碍物
                            {
                                Pedal_Stop(PEDAL_LEFT);
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_STALL_BACK; 
                                Pedal_Back(PEDAL_LEFT);   //踏板遇到障碍物缩回
                                SysRunData.PedalWaitSleepCnt = 0;
                            }
                        }    
                    }
                }
                else//动作超时
                {
                    Pedal_Stop(PEDAL_LEFT);//左踏板停止          
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_OUT_TIMEOUT;  
                }       
                break;
            case PEDAL_ERROR_STALL_BACK:
                //有遇到障碍物时不做超时判断
                SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                    {
                        Pedal_Stop(PEDAL_LEFT);//左踏板动作到位
                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                        SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_STALL_BACK;
                    }
                }
                break;
            case PEDAL_STALL_WAIT_BACK:
                 //堵转输出计数器清零
                SysRunData.PedalWaitBackCnt[PEDAL_LEFT] = 0;
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_DOWN_LIMIT;  
                break;
            case PEDAL_ERROR_BACK_TIMEOUT:   
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Out(PEDAL_LEFT);
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//动作超时
                {
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_OUT_TIMEOUT;    
                    Pedal_Stop(PEDAL_LEFT);//左踏板遇到障碍物停止
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                }        
                break; 
            default:
                break;                    
        }
    }
    else//  左边的门全部关闭
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
                if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                {
                    Pedal_Stop(PEDAL_LEFT);//左踏板动作到位
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_BACK;
//                    if(++SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
//                    {
//                        Pedal_Stop(PEDAL_LEFT);//左踏板动作到位
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
//                        SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_FAST_BACK;
//                    }  
//                    else//遇到障碍物
//                    {
//                        
//                    }
                }    
                break;
            case PEDAL_ERROR_FAST_OUT:
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_UP_LIMIT;
                break;
            case PEDAL_DOWN_LIMIT:
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Back(PEDAL_LEFT);
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
//                    StallCurrent = GetADC(ADC_CHS_CURRENT_L);
                    if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_LEFT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
                            {
                                Pedal_Stop(PEDAL_LEFT);//左踏板动作到位
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                                SysRunData.PedalWaitSleepCnt = 0;
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_UP_LIMIT;
                            }
                            else//遇到障碍物
                            {
                                Pedal_Stop(PEDAL_LEFT);
                                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0; 
                                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_STALL_OUT;  
                                Pedal_Out(PEDAL_LEFT);//踏板缩回时遇到障碍物踏板伸出
                            }
                        }   
                    }              
                }
                else//动作超时
                {
                    Pedal_Stop(PEDAL_LEFT);//左踏板遇到障碍物停止
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_BACK_TIMEOUT;    
                }     
                break;  
            case PEDAL_ERROR_STALL_OUT:
                 //有遇到障碍物时不做超时判断
                SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                    {
                        //遇到一次堵转反方向回去不再检测二次堵转
                        Pedal_Stop(PEDAL_LEFT);//左踏板动作到位  
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
                //踏板状态切换到上限位
                SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_UP_LIMIT;
                break;   
            case PEDAL_ERROR_OUT_TIMEOUT:
                if(SysRunData.PedalRunCnt[PEDAL_LEFT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Back(PEDAL_LEFT);
                    SysRunData.PedalRunCnt[PEDAL_LEFT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//动作超时
                {
                    SysRunData.PedalSta[PEDAL_LEFT] = PEDAL_ERROR_BACK_TIMEOUT;    
                    Pedal_Stop(PEDAL_LEFT);//左踏板遇到障碍物停止
                    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
                }        
                break;                      
            default:
                break;                             
        }
    }
    
    ////*****************************************************
    ////*****************************************************
    /*右边踏板逻辑控制*/
    if(RightDoorIsOpen)//右边有门打开
    {
        switch(SysRunData.PedalSta[PEDAL_RIGHT])
        {
            case PEDAL_DOWN_LIMIT:
                if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                {
                    Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_OUT;
//                    if(++SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
//                    {
//                        Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
//                        SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_OUT;
//                    } 
//                    else//遇到障碍物
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
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Out(PEDAL_RIGHT); 
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                    if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
                            {
                                Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_NORMAL_WAIT_BACK;
                            }
                            else //遇到障碍物
                            {
                                Pedal_Stop(PEDAL_RIGHT);
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_STALL_BACK; 
                                Pedal_Back(PEDAL_RIGHT);   //踏板遇到障碍物缩回 
                                SysRunData.PedalWaitSleepCnt = 0;
                            }
                        }
                    }
                }
                else//动作超时
                {
                    Pedal_Stop(PEDAL_RIGHT);//左踏板停止          
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_OUT_TIMEOUT;    
                }       
                break;
            case PEDAL_ERROR_STALL_BACK:
                //有遇到障碍物时不做超时判断
                SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                    {
                        Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位
                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                        SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_STALL_BACK;
                    }   
                }
                break;
            case PEDAL_STALL_WAIT_BACK:
                 //堵转输出计数器清零
                SysRunData.PedalWaitBackCnt[PEDAL_RIGHT] = 0;
                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_DOWN_LIMIT;  
                break;
            case PEDAL_ERROR_BACK_TIMEOUT:   
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Out(PEDAL_RIGHT);
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//动作超时
                {
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_OUT_TIMEOUT;    
                    Pedal_Stop(PEDAL_RIGHT);//左踏板遇到障碍物停止
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                }        
                break; 
            default:
                break;                    
        }
    }
    else//  右边的门全部关闭
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
               if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                {
                    Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                    SysRunData.PedalWaitSleepCnt = 0;
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_BACK;
//                    if(++SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
//                    {
//                        Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
//                        SysRunData.PedalWaitSleepCnt = 0;
//                        SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
//                        SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_FAST_BACK;
//                    }  
//                    else//遇到障碍物
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
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Back(PEDAL_RIGHT);
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
//                    StallCurrent = GetADC(ADC_CHS_CURRENT_R);
                    if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                    {
                        if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                        {
                            if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > PEDAL_RUN_NORMAL_TIME) //踏板动作时间大于设定值 
                            {
                                Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalWaitSleepCnt = 0;
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_UP_LIMIT;
                            }
                            else//遇到障碍物
                            {
                                Pedal_Stop(PEDAL_RIGHT);
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0; 
                                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_STALL_OUT;
                                Pedal_Out(PEDAL_RIGHT);//踏板缩回时遇到障碍物踏板伸出
                                
                            }
                        }
                    }
                }
                else//动作超时
                {
                    Pedal_Stop(PEDAL_RIGHT);//左踏板遇到障碍物停止
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_BACK_TIMEOUT;    
                }     
                break;  
            case PEDAL_ERROR_STALL_OUT:
                 //有遇到障碍物时不做超时判断
                SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] > CURRENT_SAMPLE_DELAY_TIME)
                {
                    if(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] > PEDAL_STALL_CURRENT_VAL)//电机产生大电流
                    {
                        //遇到一次堵转反方向回去不再检测二次堵转
                        Pedal_Stop(PEDAL_RIGHT);//左踏板动作到位  
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
                //踏板状态切换到上限位
                SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_UP_LIMIT;
                break;   
            case PEDAL_ERROR_OUT_TIMEOUT:
                if(SysRunData.PedalRunCnt[PEDAL_RIGHT] < PEDAL_RUN_TIMEOUT_TIME)//动作未超时
                {
                    Pedal_Back(PEDAL_RIGHT);
                    SysRunData.PedalRunCnt[PEDAL_RIGHT]++;
                    SysRunData.PedalWaitSleepCnt = 0;
                }
                else//动作超时
                {
                    SysRunData.PedalSta[PEDAL_RIGHT] = PEDAL_ERROR_BACK_TIMEOUT;    
                    Pedal_Stop(PEDAL_RIGHT);//左踏板遇到障碍物停止
                    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
                }        
                break;                      
            default:
                break;                             
        }
    }
    //左边踏板或右边踏板处于堵转后等待返回状态不休眠，返回后再进入休眠，踏板动作的时候不休眠
    if((SysRunData.PedalSta[PEDAL_LEFT] != PEDAL_STALL_WAIT_BACK) || (SysRunData.PedalSta[PEDAL_RIGHT] != PEDAL_STALL_WAIT_BACK) && (SysRunData.PedalRunCnt[PEDAL_LEFT] == 0))
    {
        SysNormalWaitSleep();//系统等待休眠   
    }
    //踏板逻辑控制结束  
}
/*
*********************************************************************************************************
*	函 数 名: SetSysClock
*	功能说明: 设置系统时钟
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void SetSysClock(void)
{
    // Set the internal oscillator to 32MHz
    OSCTUNEbits.PLLEN = 1;//4倍频 HS = 8M, 8X4 = 32M
}

/*
*********************************************************************************************************
*	函 数 名: SysNormalWaitSleep
*	功能说明: 系统正常等待休眠
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void SysNormalWaitSleep(void)
{
    static uint8_t tempPedalRunFlag = 0xAA;  
    
    if(SysRunData.PedalRunFlag != tempPedalRunFlag)
    {
        tempPedalRunFlag = 0xAA;//初始化踏板运行标志
        if(++SysRunData.PedalWaitSleepCnt > PEDAL_STOP_ENTER_SLEEP_TIME)
        {
            SysRunData.PedalWaitSleepCnt = 0;
            tempPedalRunFlag = SysRunData.PedalRunFlag;//保存此次的踏板标志
            SysEnterSleep();//系统休眠
            App_System_Init();//唤醒后重新初始化
        }
    }
    else
    {
        SysEnterSleep();//系统休眠
        App_System_Init();//唤醒后重新初始化
    } 
}
/*
*********************************************************************************************************
*	函 数 名: SysEnterSleep
*	功能说明: 系统进入休眠模式
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
 void SysEnterSleep(void)
{
    CAN_SetMode(CAN_MODE_STANDBY);//CAN收发器进入待机模式
    ADC_Cmd(ADC_CHS_VHALL,DISABLE); 
    ADC_Cmd(ADC_CHS_VBAT,DISABLE); 
    SysRunData.PedalRunCnt[PEDAL_LEFT] = 0;
    SysRunData.PedalRunCnt[PEDAL_RIGHT] = 0;
    SysRunData.PedalWaitSleepCnt = 0;
    PIR5bits.WAKIF = 0;     //清除CAN总线活动唤醒中断标志
    PIE5bits.WAKIE = 1;     //允许CAN总线活动唤醒中断
    IPR5bits.WAKIP = 1;     //CAN总线活动唤醒中断为高优先级
    CANCON = 0x20;//禁止/休眠模式  
    while(CANSTATbits.OPMODE !=0x01); 
    OSCCONbits.IDLEN = 0;//配置休眠模式
    Sleep();//进入休眠模式
    __delay_us(WAKEUP_US_DELAY);
}
/*
*********************************************************************************************************
*	函 数 名: SysErrorWaitSleep
*	功能说明: 系统错误等待休眠
*	形    参: 无
*	返 回 值: 无
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
        SysEnterSleep();//系统休眠
        App_System_Init();//唤醒后重新初始化
    }
 }
/*
*********************************************************************************************************
*	函 数 名: AdcPro
*	功能说明: ADC滤波处理
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void AdcPro(void)
{
	static uint16_t buf[ADC_SAMP_CNT][ADC_CHS_NUM];
	static uint8_t write;
    static uint8_t index = ADC_CHS_VBAT;
	uint16_t sum;
	uint8_t i;
    
    if(index == ADC_CHS_VBAT)//电池电压采集
    {
        buf[write][ADC_CHS_VBAT] = ADC_GetConversionValue();
        
        /* 下面这段代码采用求平均值的方法进行滤波
            也可以改善下，选择去掉最大和最下2个值，使数据更加精确
        */
        sum = 0;
        for (i = 0; i < ADC_SAMP_CNT; i++)
        {
            sum += buf[i][ADC_CHS_VBAT];
        }
        SysRunData.ADC_Buf[ADC_CHS_VBAT] = sum / ADC_SAMP_CNT;	/* ADC采样值由若干次采样值平均 */
        index = ADC_CHS_CURRENT_R;
        ADC_StartConversion(ADC_CHS_CURRENT_R); /* 软件启动下次ADC转换 */
    } 
    else if(index == ADC_CHS_CURRENT_R)//右边踏板堵转电流采集
    {
        buf[write][ADC_CHS_CURRENT_R] = ADC_GetConversionValue();

        /* 下面这段代码采用求平均值的方法进行滤波
            也可以改善下，选择去掉最大和最下2个值，使数据更加精确
        */
        sum = 0;
        for (i = 0; i < ADC_SAMP_CNT; i++)
        {
            sum += buf[i][ADC_CHS_CURRENT_R];
        }
        SysRunData.ADC_Buf[ADC_CHS_CURRENT_R] = sum / ADC_SAMP_CNT; /* ADC采样值由若干次采样值平均 */

        index = ADC_CHS_CURRENT_L;
        ADC_StartConversion(ADC_CHS_CURRENT_L);	/* 软件启动下次ADC转换 */
    }
    else if(index == ADC_CHS_CURRENT_L)//左边踏板堵转电流采集
    {
        buf[write][ADC_CHS_CURRENT_L] = ADC_GetConversionValue();
        /* 下面这段代码采用求平均值的方法进行滤波
            也可以改善下，选择去掉最大和最下2个值，使数据更加精确
        */
        sum = 0;
        for (i = 0; i < ADC_SAMP_CNT; i++)
        {
            sum += buf[i][ADC_CHS_CURRENT_L];
        }
        SysRunData.ADC_Buf[ADC_CHS_CURRENT_L] = sum / ADC_SAMP_CNT; /* ADC采样值由若干次采样值平均 */
        if (++write >= ADC_SAMP_CNT)
        {
            write = 0;
        }                         
        index = ADC_CHS_VBAT;
        ADC_StartConversion(ADC_CHS_VBAT);	/* 软件启动下次ADC转换 */
    } 
}
/*
*********************************************************************************************************
*	函 数 名: GetADC
*	功能说明: 系统进入空闲模式
*	形    参: channel,ADC通道
*	返 回 值: 无
*********************************************************************************************************
*/
static uint16_t GetADC(uint8_t channel)
{
	uint16_t ret;

	/* 因为	g_AdcValue 变量在systick中断中改写，为了避免主程序读变量时被中断程序打乱导致数据错误，因此需要
	关闭中断进行保护 */

//	/* 进行临界区保护，关闭中断 */
	DISABLE_INT();  /* 关中断 */

	ret = SysRunData.ADC_Buf[channel];

	ENABLE_INT();  /* 开中断 */

	return ret;
}
/*
*********************************************************************************************************
*	函 数 名: SysVoltDetect()
*	功能说明: 系统进入空闲模式
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void SysVoltDetect(void)
{
    //    蓄电池检测
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
*	函 数 名: PORT_Init()
*	功能说明: 空闲端口初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PORT_Init(void)   
{
    
}
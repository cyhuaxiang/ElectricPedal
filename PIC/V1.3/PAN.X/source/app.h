/* 
 * File:   app.h
 * Author: Administrator
 *
 * Created on 2017年7月11日, 下午4:33
 */

#ifndef APP_H
#define	APP_H

#ifdef	__cplusplus
extern "C" {
#endif
//*******************************************************************************

typedef enum
{
    SYS_NORMAL = 0,
    SYS_TEST,
    SYS_ERROR_UNDER_VOLT,
    SYS_ERROR_OVER_VOLT,
}SYS_STA_E;

typedef enum
{
    PEDAL_UP_LIMIT = 0,
    PEDAL_DOWN_LIMIT,
    PEDAL_NORMAL_WAIT_BACK,
    PEDAL_STALL_WAIT_BACK,
    PEDAL_ERROR_STALL_BACK,       
    PEDAL_ERROR_STALL_OUT,
    PEDAL_ERROR_FAST_BACK,
    PEDAL_ERROR_FAST_OUT,
    PEDAL_ERROR_OUT_TIMEOUT, 
    PEDAL_ERROR_BACK_TIMEOUT,  
}PEDAL_STA_E;

typedef enum 
{
    //遥控状态
    LOCK = 0,//上锁
    UNLOCK, //解锁       
       
} REMOTE_CTRL_E;
typedef struct
{
    PEDAL_STA_E PedalSta[2]; //踏板状态
    SYS_STA_E SysSta;//系统状态
    REMOTE_CTRL_E RemoteCtrlSta;//遥控状态
    
    uint16_t PedalRunCnt[2];//踏板运行计数
    uint16_t PedalWaitSleepCnt;//踏板等待休眠计数器 
    uint16_t PedalWaitBackCnt[2];//踏板等待缩回计数器 
    uint16_t UnlockWaitCnt;  //解锁等待计数器
    uint16_t ADC_Buf[4];//ADC滤波值
    uint8_t  PedalRunFlag;//电流采样状态
    
}SYS_RUN_DATA_T;//系统运行数据结构体

extern SYS_RUN_DATA_T SysRunData;

//*******************************************************************************
//汽车类型定义
#define	TRUMPCHI_GS8         6//广汽传祺GS8
#define	CADILLAC_ESCALADE    5//凯迪拉克凯雷德
#define	AUDI_Q5	             4//奥迪Q5
#define	AUDI_Q7	             3//奥迪Q7
#define RANGEROVER_16        2//路虎揽胜16款
#define RANGEROVER_17        1//路虎揽胜17款

#define CAR_TYPE  RANGEROVER_17 


#define PEDAL_LEFT    0//左踏板
#define PEDAL_RIGHT   1//右踏板

#define FRONT_LEFT    0//左前门
#define REAR_LEFT     1//左后门
#define FRONT_RIGHT   2//右前门
#define REAR_RIGHT    3//右后门


#define TIMER_ADC     0//ADC扫描定时器ID
#define TIMER_PEDAL   1//踏板运行时间定时器ID

#define LeftDoorIsOpen             (SysRunData.PedalRunFlag & BIT0) == BIT0
#define RightDoorIsOpen            (SysRunData.PedalRunFlag & BIT1) == BIT1

#define LeftDoorOpen()             SysRunData.PedalRunFlag |= (1<<0)
#define LeftDoorClose()            SysRunData.PedalRunFlag &= ~(1<<0)

#define RightDoorOpen()            SysRunData.PedalRunFlag |= (1<<1)
#define RightDoorClose()           SysRunData.PedalRunFlag &= ~(1<<1)

#define NORMAL_MODE          0
#define LISTEN_ONLY_MODE     1
#define LOOPBACK_MODE        2
#define ECAN_MODE            NORMAL_MODE //ECAN模式

#define REMOTE_CTRL_MODE          1  //遥控模式是否开启 0，开启 1，关闭
#define TEST_MODE                 1  //测试模式是否开启 0，开启 1，关闭，开启后向上位机反馈踏板动作状态信息

#define PEDAL_NORMAL_WAIT_BACK_TIME      0   //踏板缩回等待时间x*10ms
#define CURRENT_SAMPLE_DELAY_TIME        50  //电流采样延时500ms
#define PEDAL_FAST_RESPONSE_TIME         10  //踏板快速响应时间，大于此阈值被认为是快速开关门动作并给予响应
#define PEDAL_RUN_NORMAL_TIME            120 //踏板运行正常时间
#define PEDAL_RUN_ERROR_TIME             (CURRENT_SAMPLE_DELAY_TIME + 10) //踏板运行错误时间，用于检测踏板已经伸出或关闭执行开关门动作导致误判断为堵转情况
#define PEDAL_RUN_TIMEOUT_TIME           350 //踏板伸出超时时间
#define PEDAL_STOP_ENTER_SLEEP_TIME      1500//踏板停止系统休眠时间
#define PEDAL_STALL_WAIT_BACK_TIME       1500//踏板堵转等待返回时间
#define UNLOCK_NO_OPERATION_TIME         1500//遥控解锁后无操作时间
#define BAT_LOW_VOLT_TIME                1500//电瓶亏电时间


//K = 9.846
//1.3A  128    
//2.0A  197
//2.5A  246
//3.0A  295
//3.5A  345
//4.0A  394
//4.5A  443
//5.0A  492
//5.5A  542
//6.0A  591
//6.5A  640
//7.0A  689
//8.0A  788
//9.0A  886
//10.0A  985
#define PEDAL_STALL_CURRENT_VAL         985//踏板堵转电流ADC阈值
#define VBAT_UNDER_VOLT_VAL             1696//9V，电池电压ADC阈值
#define VBAT_OVER_VOLT_VAL              2000//电池过压ADC阈值
#define VHALL_OVER_VOLT_VAL             2000//

#if CAR_TYPE == RANGEROVER_17
    // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    0                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    1                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps

    #define CAR_TERRAIN_MODE_ID   0X000//  汽车地形模式帧ID
    #define CAR_REMOTE_KEY_ID     0X000//  汽车遥控钥匙ID
    #define CAR_DOOR_ID           0X110//  汽车门帧ID

    #define POS_LOGIC                  1
    #define NEG_LOGIC                  0 
    #define CTRL_LOGIC                 NEG_LOGIC//踏板控制逻辑 0，伸出 1，缩回

    #define FRONT_LEFT_CTRL_BYTE       5//左前门控制字节
    #define FRONT_LEFT_CTRL_BIT        BIT1//左前门控制字节的控制位

    #define REAR_LEFT_CTRL_BYTE        5
    #define REAR_LEFT_CTRL_BIT         BIT3

    #define FRONT_RIGHT_CTRL_BYTE      5
    #define FRONT_RIGHT_CTRL_BIT       BIT0

    #define REAR_RIGHT_CTRL_BYTE       5
    #define REAR_RIGHT_CTRL_BIT        BIT2
 

#elif CAR_TYPE == RANGEROVER_16
    // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    1                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    0                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps

    #define CAR_TERRAIN_MODE_ID   0X000//  汽车地形模式帧ID
    #define CAR_REMOTE_KEY_ID     0X000//  汽车遥控钥匙ID
    #define CAR_DOOR_ID           0X297//  汽车门帧ID
    
    #define POS_LOGIC                  1
    #define NEG_LOGIC                  0 
    #define CTRL_LOGIC                 NEG_LOGIC//踏板控制逻辑 0，伸出 1，缩回

    #define FRONT_LEFT_CTRL_BYTE       0//左前门控制字节
    #define FRONT_LEFT_CTRL_BIT        BIT0//左前门控制字节的控制位

    #define REAR_LEFT_CTRL_BYTE        0
    #define REAR_LEFT_CTRL_BIT         BIT0

    #define FRONT_RIGHT_CTRL_BYTE      0
    #define FRONT_RIGHT_CTRL_BIT       BIT0

    #define REAR_RIGHT_CTRL_BYTE       0
    #define REAR_RIGHT_CTRL_BIT        BIT0

    
#elif CAR_TYPE == TRUMPCHI_GS8
    // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    0                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    1                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps
    
    #define CAR_DOOR_ID   0X375//  汽车门帧ID

    #define POS_LOGIC                  1
    #define NEG_LOGIC                  0 
    #define CTRL_LOGIC                 POS_LOGIC//踏板控制逻辑 0，伸出 1，缩回

    #define FRONT_LEFT_CTRL_BYTE       2//左前门控制字节
    #define FRONT_LEFT_CTRL_BIT        BIT1//左前门控制字节的控制位

    #define REAR_LEFT_CTRL_BYTE        2
    #define REAR_LEFT_CTRL_BIT         BIT3

    #define FRONT_RIGHT_CTRL_BYTE      1
    #define FRONT_RIGHT_CTRL_BIT       BIT6

    #define REAR_RIGHT_CTRL_BYTE       2
    #define REAR_RIGHT_CTRL_BIT        BIT2

   

#elif CAR_TYPE == CADILLAC_ESCALADE
     // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    0                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    1                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps
    
    #define CAR_DOOR_ID   0X12A//  汽车门帧ID


#endif

//*******************************************************************************
void SysEnterSleep(void);
void App_System_Init(void);
void AppTask_PollHandler(void);
void AdcPro(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_H */


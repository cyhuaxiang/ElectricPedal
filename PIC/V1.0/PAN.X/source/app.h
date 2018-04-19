/* 
 * File:   app.h
 * Author: Administrator
 *
 * Created on 2017��7��11��, ����4:33
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
    PEDAL_ERROR_WAIT_SLEEP,        
    PEDAL_ERROR_STALL_OUT,
    PEDAL_ERROR_OUT_TIMEOUT, 
    PEDAL_ERROR_BACK_TIMEOUT,
}PEDAL_STA_E;

typedef enum 
{
    //ϵͳ�������
    ERROR_CODE_BAT_LOW_VOLT = 0X50,//������ƿ����
       
} ERROR_CODE_E;

typedef struct
{
    PEDAL_STA_E PedalSta[2]; //̤��״̬
    SYS_STA_E SysSta;//ϵͳ״̬
    uint16_t PedalRunCnt[2];//̤�����м���
    uint8_t  CurrentDelayAcqCnt[2];
    uint16_t PedalWaitSleepCnt;//̤��ȴ����߼����� 
    uint16_t PedalWaitBackCnt[2];//̤��ȴ����ؼ����� 
    uint16_t ADC_Buf[4];//ADC�˲�ֵ
    uint8_t  PedalRunFlag;//��������״̬
    uint8_t  CurrentAcqSta;//��������״̬
    
}SYS_RUN_DATA_T;//ϵͳ�������ݽṹ��

extern SYS_RUN_DATA_T SysRunData;

//*******************************************************************************
//�������Ͷ���
#define	TRUMPCHI_GS8         6//��������GS8
#define	CADILLAC_ESCALADE    5//�������˿��׵�
#define	AUDI_Q5	             4//�µ�Q5
#define	AUDI_Q7	             3//�µ�Q7
#define RANGEROVER_16        2//·����ʤ16��
#define RANGEROVER_17        1//·����ʤ17��

#define CAR_TYPE  RANGEROVER_17 


#define PEDAL_LEFT    0//��̤��
#define PEDAL_RIGHT   1//��̤��

#define FRONT_LEFT    0//��ǰ��
#define REAR_LEFT     1//�����
#define FRONT_RIGHT   2//��ǰ��
#define REAR_RIGHT    3//�Һ���


#define TIMER_ADC     0//ADCɨ��ID
#define TIMER_PEDAL   1//̤������ʱ��ID

#define LeftDoorIsOpen           ((SysRunData.PedalRunFlag & BIT0) == BIT0)
#define RighDoorIsOpen           ((SysRunData.PedalRunFlag & BIT1) == BIT1)

#define LeftCurrentAcqIsOpen     ((SysRunData.CurrentAcqSta & BIT0) == BIT0)
#define RightCurrentAcqIsOpen    ((SysRunData.CurrentAcqSta & BIT1) == BIT1)


#if CAR_TYPE == RANGEROVER_17
    // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    0                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    1                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps

    #define CAR_TERRAIN_MODE_ID   0X000//  ��������ģʽ֡ID
    #define CAR_REMOTE_KEY_ID     0X000//  ����ң��Կ��ID
    #define CAR_DOOR_ID           0X110//  ������֡ID

    #define CTRL_LOGIC                 0//̤������߼� 0����� 1������

    #define FRONT_LEFT_CTRL_BYTE       5//��ǰ�ſ����ֽ�
    #define FRONT_LEFT_CTRL_BIT        BIT1//��ǰ�ſ����ֽڵĿ���λ

    #define REAR_LEFT_CTRL_BYTE        5
    #define REAR_LEFT_CTRL_BIT         BIT3

    #define FRONT_RIGHT_CTRL_BYTE      5
    #define FRONT_RIGHT_CTRL_BIT       BIT0

    #define REAR_RIGHT_CTRL_BYTE       5
    #define REAR_RIGHT_CTRL_BIT        BIT2

    #define PEDAL_NORMAL_WAIT_BACK_TIME      250 //̤�����صȴ�ʱ��
    #define CURRENT_SAMPLE_DELAY_TIME        50  //����������ʱ500ms
    #define PEDAL_RUN_NORMAL_TIME            130 //̤����������ʱ��
    #define PEDAL_RUN_ERROR_TIME             (CURRENT_SAMPLE_DELAY_TIME + 10)
    #define PEDAL_RUN_TIMEOUT_TIME           350 //̤�������ʱʱ��
    #define PEDAL_STOP_ENTER_SLEEP_TIME      1500//̤��ֹͣϵͳ����ʱ��
    #define PEDAL_STALL_WAIT_BACK_TIME       1500//̤���ת�ȴ�����ʱ��
    #define BAT_LOW_VOLT_TIME                1500//��ƿ����ʱ��
      
         
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
    #define PEDAL_STALL_CURRENT_VAL         492//̤���ת����ADC��ֵ
    #define VBAT_UNDER_VOLT_VAL             1696//9V����ص�ѹADC��ֵ
    #define VBAT_OVER_VOLT_VAL              2000//��ع�ѹADC��ֵ
    #define VHALL_OVER_VOLT_VAL             2000//
#elif CAR_TYPE == RANGEROVER_16
    // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    1                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    0                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps

    #define CAR_TERRAIN_MODE_ID   0X000//  ��������ģʽ֡ID
    #define CAR_REMOTE_KEY_ID     0X000//  ����ң��Կ��ID
    #define CAR_DOOR_ID           0X297//  ������֡ID

    #define PEDAL_NORMAL_WAIT_BACK_TIME      250 //̤�����صȴ�ʱ��
    #define CURRENT_SAMPLE_DELAY_TIME        50  //����������ʱ500ms
    #define PEDAL_RUN_NORMAL_TIME            130 //̤����������ʱ��
    #define PEDAL_RUN_ERROR_TIME             (CURRENT_SAMPLE_DELAY_TIME + 10)
    #define PEDAL_RUN_TIMEOUT_TIME           350 //̤�������ʱʱ��
    #define PEDAL_STOP_ENTER_SLEEP_TIME      1500//̤��ֹͣϵͳ����ʱ��
    #define PEDAL_STALL_WAIT_BACK_TIME       1500//̤���ת�ȴ�����ʱ��
    #define BAT_LOW_VOLT_TIME                1500//��ƿ����ʱ��
      
         
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
    #define PEDAL_STALL_CURRENT_VAL         492//̤���ת����ADC��ֵ
    #define VBAT_UNDER_VOLT_VAL             1696//9V����ص�ѹADC��ֵ
    #define VBAT_OVER_VOLT_VAL              2000//��ع�ѹADC��ֵ
    #define VHALL_OVER_VOLT_VAL             2000//
#elif CAR_TYPE == TRUMPCHI_GS8
    // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    0                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    1                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps
    
    #define CAR_DOOR_ID   0X375//  ������֡ID

    #define PEDAL_NORMAL_WAIT_BACK_TIME      250 //̤�����صȴ�ʱ��
    #define CURRENT_SAMPLE_DELAY_TIME        50  //����������ʱ500ms
    #define PEDAL_RUN_NORMAL_TIME            130 //̤����������ʱ��
    #define PEDAL_RUN_TIMEOUT_TIME           350 //̤�������ʱʱ��
    #define PEDAL_STOP_ENTER_SLEEP_TIME      1500//̤��ֹͣϵͳ����ʱ��
    #define PEDAL_STALL_WAIT_BACK_TIME       1500//̤���ת�ȴ�����ʱ��
    #define BAT_LOW_VOLT_TIME                1500//��ƿ����ʱ��
      
         
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
    #define PEDAL_STALL_CURRENT_VAL         492//̤���ת����ADC��ֵ
    #define VBAT_UNDER_VOLT_VAL             1696//9V����ص�ѹADC��ֵ
    #define VBAT_OVER_VOLT_VAL              2000//��ع�ѹADC��ֵ
    #define VHALL_OVER_VOLT_VAL             2000//

#elif CAR_TYPE == CADILLAC_ESCALADE
     // ECAN bitrate define, only can choose one rate
    #define F_ECAN_100    0                 // 1 set ECAN module on 100Kbps
    #define F_ECAN_125    0                 // 1 set ECAN module on 125Kbps
    #define F_ECAN_500    1                 // 1 set ECAN module on 500Kbps
    #define F_ECAN_1000   0                 // 1 set ECAN module on 1Mbps
    
    #define CAR_DOOR_ID   0X12A//  ������֡ID

    #define PEDAL_NORMAL_WAIT_BACK_TIME      250 //̤�����صȴ�ʱ��
    #define CURRENT_SAMPLE_DELAY_TIME        50  //����������ʱ500ms
    #define PEDAL_RUN_NORMAL_TIME            130 //̤����������ʱ��
    #define PEDAL_RUN_TIMEOUT_TIME           350 //̤�������ʱʱ��
    #define PEDAL_STOP_ENTER_SLEEP_TIME      1500//̤��ֹͣϵͳ����ʱ��
    #define PEDAL_STALL_WAIT_BACK_TIME       1500//̤���ת�ȴ�����ʱ��
    #define BAT_LOW_VOLT_TIME                1500//��ƿ����ʱ��
      
         
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
    #define PEDAL_STALL_CURRENT_VAL         492//̤���ת����ADC��ֵ
    #define VBAT_UNDER_VOLT_VAL             1696//9V����ص�ѹADC��ֵ
    #define VBAT_OVER_VOLT_VAL              2000//��ع�ѹADC��ֵ
    #define VHALL_OVER_VOLT_VAL             2000//

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


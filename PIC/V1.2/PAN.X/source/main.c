
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
* ����.        2017-7-31     ���Ƶ͹��ģ������ؿ�����
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ����.
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
//������������
#pragma config INTOSCSEL=LOW//�����ڼ�LF-INTOSC���ڵ͹���ģʽ
#pragma config SOSCSEL=DIG //����ģʽʹ��RC0,RC1�˿ڹ���
#pragma config XINST=OFF  //��ʹ����չָ�
#pragma config RETEN=OFF  //��ֹ���͹�����ѹ��
#pragma config IESO=OFF    // ��ֹ˫������
#pragma config FOSC=HS1   //����4-16MHZ
#pragma config FCMEN=OFF //��ֹ���ϱ���ʱ��
#pragma config PLLCFG=OFF  //ֱ�����þ���
#pragma config BOREN=OFF   //�ر�Ƿѹ��λ
#pragma config BORPWR=LOW  //�͹��ļ���
#pragma config BORV=3    //Ƿѹ��λ��ѹ1.8V
#pragma config PWRTEN=OFF //��ֹ�ϵ���ʱ��λ
#pragma config WDTPS=256   //WDT���Ƶ��Ϊ1:256ԼΪ1.024S
#pragma config WDTEN=OFF   //�رտ��Ź�
#pragma config CANMX=PORTB  //CAN TX RXΪRB2 RB3
#pragma config MSSPMSK=MSK7  //7λ��ַ����
#pragma config MCLRE=ON      // ʹ��MCLR��λ���ţ���ֹRE3IO����
#pragma config STVREN=OFF     //��ջ���硢�����ᵼ�¸�λ
#pragma config BBSIZ=BB2K   //������Ϊ2K
#pragma config CP0=OFF      //���뱣���ر�
#pragma config CP1=OFF
#pragma config CP2=OFF
#pragma config CP3=OFF
#pragma config CPD=OFF
#pragma config CPB=OFF
#pragma config WRT0=OFF    //��д����
#pragma config WRT1=OFF
#pragma config WRT2=OFF
#pragma config WRT3=OFF
#pragma config WRTB=OFF
#pragma config WRTC=OFF
#pragma config WRTD=OFF
#pragma config EBTR0=OFF
#pragma config EBTR1=OFF
#pragma config EBTR2=OFF
#pragma config EBTR3=OFF   //������
#pragma config EBTRB=OFF

int main(void)
{
    App_System_Init();//ϵͳӦ�ó�ʼ��
    //ϵͳ��������ģʽ
    SysEnterSleep();
    App_System_Init();//���Ѻ����³�ʼ��
    while(1)    
    {
        //Ӧ��������ѯ����
        AppTask_PollHandler();
    }
}

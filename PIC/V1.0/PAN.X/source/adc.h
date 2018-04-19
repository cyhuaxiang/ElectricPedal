/* 
 * File:   adc.h
 * Author: Administrator
 *
 * Created on 2017��7��11��, ����4:33
 */

#ifndef ADC_H
#define	ADC_H


#ifdef	__cplusplus
extern "C" {
#endif
// ת��ͨ������
#define    ADC_CHS_NUM				4
#define    ADC_SAMP_CNT             5
    
#define    ACQ_US_DELAY             5//ADC�ɼ���ʱʱ��
#define    CHS_SWITCH_US_DELAY      5//ADC�ɼ���ʱʱ��

#define    ADC_CHS_VHALL            0x00//����������Դ��ѹ�ɼ�ͨ��
#define    ADC_CHS_VBAT             0x01//��ص�ѹ�ɼ�ͨ��
#define    ADC_CHS_CURRENT_R        0x02//�ұ߶�ת�����ɼ�ͨ��
#define    ADC_CHS_CURRENT_L        0x03//��߶�ת�����ɼ�ͨ��

void ADC_Init();
void ADC_Cmd(uint8_t channel, uint8_t sta);
uint16_t ADC_Read(uint8_t channel);
uint16_t ADC_GetConversionValue();
void ADC_StartConversion(uint8_t channel); 
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


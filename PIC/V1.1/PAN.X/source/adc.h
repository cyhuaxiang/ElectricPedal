/* 
 * File:   adc.h
 * Author: Administrator
 *
 * Created on 2017年7月11日, 下午4:33
 */

#ifndef ADC_H
#define	ADC_H


#ifdef	__cplusplus
extern "C" {
#endif
// 转换通道个数
#define    ADC_CHS_NUM				4
#define    ADC_SAMP_CNT             5
    
#define    ACQ_US_DELAY             5//ADC采集延时时间
#define    CHS_SWITCH_US_DELAY      5//ADC采集延时时间

#define    ADC_CHS_VHALL            0x00//传感器件电源电压采集通道
#define    ADC_CHS_VBAT             0x01//电池电压采集通道
#define    ADC_CHS_CURRENT_R        0x02//右边堵转电流采集通道
#define    ADC_CHS_CURRENT_L        0x03//左边堵转电流采集通道

void ADC_Init();
void ADC_Cmd(uint8_t channel, uint8_t sta);
uint16_t ADC_Read(uint8_t channel);
uint16_t ADC_GetConversionValue();
void ADC_StartConversion(uint8_t channel); 
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


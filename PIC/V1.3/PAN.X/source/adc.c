#include "bsp.h"

/*
*********************************************************************************************************
*	�� �� ��: ADC_Init
*	����˵��: ADC��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ADC_Init() 
{
    VBAT_SEN_EN_SetDigitalOutput();
    VHALL_SEN_EN_SetDigitalOutput();	 
    TRISAbits.TRISA0 = 1;//as input
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    ANCON0 = 0X0F; //��������Ϊģ��ͨ��
    
    ADCON1 = 0x00; // �ⲿ���ο���ѹ��AVddΪ����ѹ��ģ�ⷴ��ͨ��ΪAVss
    ADCON2 = 0xAA; // FOSC/32 as conversion clock, Result is right justified,Aquisition time of 12 TAD 
    ADRESH = 0;
    ADRESL = 0;
    ADC_StartConversion(ADC_CHS_VBAT);
}

/*
*********************************************************************************************************
*	�� �� ��: ADC_Read
*	����˵��: ADC��ȡ
*	��    ��: channel���ɼ�ͨ�� 
*	�� �� ֵ: ADCͨ���ɼ����
*********************************************************************************************************
*/
uint16_t ADC_Read(uint8_t channel) 
{
    uint16_t ADC_Result = 0;
    
    if (channel > 7) //If Invalid channel selected 
    {
        return 0; //Return 0
    }   
    ADCON0bits.CHS = channel;
    //__delay_us(ACQ_US_DELAY);// Acquisition time delay
    ADCON0bits.GO_NOT_DONE = 1; //Initializes A/D Conversion
    while (ADCON0bits.GO_NOT_DONE); //Wait for A/D Conversion to complete
    ADC_Result = (uint16_t)ADRESH << 8|(ADRESL&0xE0);
    
    return ADC_Result; //Returns Result
}
/*
*********************************************************************************************************
*	�� �� ��: ADC_GetConversionValue
*	����˵��: ADC��ȡ
*	��    ��: ��
*	�� �� ֵ: ADCͨ���ɼ����
*********************************************************************************************************
*/
uint16_t ADC_GetConversionValue()
{
    uint16_t ADC_Result = 0;

    // Conversion finished, return the result
    ADC_Result = (uint16_t)ADRESH << 8|(ADRESL&0xE0);

    return ADC_Result; //Returns Result
}
/*
*********************************************************************************************************
*	�� �� ��: ADC_StartConversion
*	����˵��: ADC����ת��
*	��    ��: channel���ɼ�ͨ�� 
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ADC_StartConversion(uint8_t channel) 
{
    // select the A/D channel
    ADCON0bits.CHS = channel;
    // Turn on the ADC module
    ADCON0bits.ADON = 1;
    // Acquisition time delay
    //__delay_us(ACQ_US_DELAY);

    // Start the conversion
    ADCON0bits.GO_NOT_DONE = 1;
}
/*
*********************************************************************************************************
*	�� �� ��: ADC_Cmd
*	����˵��: ADCͨ���ɼ�ʹ��
*	��    ��: channel��ͨ���� sta��״̬
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ADC_Cmd(uint8_t channel, uint8_t sta)
{
	if(sta != DISABLE)
    {
        if(channel == 1)
        {
            VBAT_SEN_EN_SetHigh();
        }
        else
        {
            VHALL_SEN_EN_SetHigh();
        }
    }
    else
    {
        if(channel == 1)
        {
            VBAT_SEN_EN_SetLow();
        }
        else
        {
            VHALL_SEN_EN_SetLow();
        }
    }
}
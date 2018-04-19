#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名: ADC_Init
*	功能说明: ADC初始化
*	形    参: 无
*	返 回 值: 无
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
    ANCON0 = 0X0F; //引脚配置为模拟通道
    
    ADCON1 = 0x00; // 外部正参考电压，AVdd为负电压，模拟反相通道为AVss
    ADCON2 = 0xAA; // FOSC/32 as conversion clock, Result is right justified,Aquisition time of 12 TAD 
    ADRESH = 0;
    ADRESL = 0;
    ADC_StartConversion(ADC_CHS_VBAT);
}

/*
*********************************************************************************************************
*	函 数 名: ADC_Read
*	功能说明: ADC读取
*	形    参: channel，采集通道 
*	返 回 值: ADC通道采集结果
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
*	函 数 名: ADC_GetConversionValue
*	功能说明: ADC读取
*	形    参: 无
*	返 回 值: ADC通道采集结果
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
*	函 数 名: ADC_StartConversion
*	功能说明: ADC启动转换
*	形    参: channel，采集通道 
*	返 回 值: 无
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
*	函 数 名: ADC_Cmd
*	功能说明: ADC通道采集使能
*	形    参: channel，通道数 sta，状态
*	返 回 值: 无
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
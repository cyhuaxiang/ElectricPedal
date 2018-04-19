
/*********************************************************************
*
*                            Includes 
*
*********************************************************************/
#include "bsp.h"

/*********************************************************************
*
*                             Defines 
*
*********************************************************************/


/*********************************************************************
*
*                            Global Variables 
*
*********************************************************************/
/* 定义全局变量 */
CanTxMsg g_tCanTxMsg;	/* 用于发送 */
CanRxMsg g_tCanRxMsg;	/* 用于接收 */


/*********************************************************************
*
*     Function: Initialize the CAN Module
*
*********************************************************************/
void ECAN_Init(void)
{
    CAN_STB_SetDigitalOutput();//CAN待机模式端配置为输出
    CAN_TX_SetDigitalOutput();
    CAN_RX_SetDigitalInput();
    // Place CAN module in configuration mode, see CANCON register data
    CANCON = 0x80;    //REQOP bits <2:0> = 0b100
//    while(!(CANSTATbits.OPMODE ==0x04));    //Wait for op-mode bits in the
    while(CANSTAT != 0X80);                  //CANSTAT register to = 0b100
                                            //to indicate config mode OK

    // Enter CAN module into Mode 0, standard legacy mode; see ECANCON register
    
    ECANCON = 0x00;
    
    // See Microchip application note AN754, Understanding Microchip's
    // CAN Module Bit Timing."  See also: Microchip Controller Area Network
    //(CAN) Bit Timing Calculator, available at Intrepid Control Systems:
    //www.intrepidcs.com/support/mbtime.htm.
    
    // Initialize CAN Bus bit rate timing. Assumes only four standard rates.  
    // Initialize CAN Timing  
    if (F_ECAN_100==1)
    {
        //  100 Kbps @ 32MHz  
        BRGCON1 = 0x13; //SJW=1TQ     BRP  19
        BRGCON2 = 0x90; //SEG2PHTS 1    sampled once  PS1=3TQ  PropagationT 1TQ  
        BRGCON3 = 0x02; //PS2  3TQ
    } 
    else if (F_ECAN_125==1)
    {
        //  125 Kbps @ 32MHz 
        BRGCON1 = 0x0F; //SJW=1TQ     BRP  15
        BRGCON2 = 0x90; //SEG2PHTS 1    sampled once  PS1=3TQ  PropagationT 1TQ  
        BRGCON3 = 0x02; //PS2  3TQ
    }
    else if (F_ECAN_500==1)
    {
       //  125 Kbps @ 32MHz 
        BRGCON1 = 0x03; //SJW=1TQ     BRP  3
        BRGCON2 = 0x90; //SEG2PHTS 1    sampled once  PS1=3TQ  PropagationT 1TQ  
        BRGCON3 = 0x02; //PS2  3TQ
    }
    else if (F_ECAN_1000==1)
    {
        //  1000 Kbps @ 32MHz 
        BRGCON1 = 0x01; //SJW=1TQ     BRP  1
        BRGCON2 = 0x90; //SEG2PHTS 1    sampled once  PS1=3TQ  PropagationT 1TQ  
        BRGCON3 = 0x02; //PS2  3TQ
    } 
    // Initialize Receive Masks, see registers RXMxEIDH, RXMxEIDL, etc...
    // Mask 0 (M0) will accept NO extended addresses, but any standard address
    RXM0EIDH = 0x00;    // Extended Address receive acceptance mask, high byte 
    RXM0EIDL = 0x00;    // Extended Address receive acceptance mask, low byte
    RXM0SIDH = 0xFF;    // Standard Address receive acceptance mask, high byte
    RXM0SIDL = 0xE0;    // Standard Address receive acceptance mask, low byte
    
    // Mode 0 allows use of receiver filters RXF0 through RXF5. Enable filters
    // RXF0 and RXF1, all others disabled. See register RXFCONn.
    //  Only using two filters
    RXFCON0 = 0x01;     //Enable Filter-0; disable others 
    RXFCON1 = 0x00;     //Disable Filters 8 through 15
#if CAR_TYPE == RANGEROVER_17   
    // Initialize Receive Filters
    //  Filter 0 = 0xxx
   
    RXF0EIDH = 0x00;    //Extended Address Filter-0 unused, set high byte to 0
    RXF0EIDL = 0x00;    //Extended Address Filter-0 unused, set low byte to 0
    RXF0SIDH = (uint8_t)(CAR_DOOR_ID>>3);    //Standard Address Filter-0 high byte set to 0xxx
    RXF0SIDL = (uint8_t)(CAR_DOOR_ID<<5)&0xE0;    //Standard Address Filter-0 low byte set to 0xxx
#elif CAR_TYPE == TRUMPCHI_GS8
    // Initialize Receive Filters
    //  Filter 0 = 0xxx
   
    RXF0EIDH = 0x00;    //Extended Address Filter-0 unused, set high byte to 0
    RXF0EIDL = 0x00;    //Extended Address Filter-0 unused, set low byte to 0
    RXF0SIDH = (uint8_t)(CAR_DOOR_ID>>3);    //Standard Address Filter-0 high byte set to 0xxx
    RXF0SIDL = (uint8_t)(CAR_DOOR_ID<<5)&0xE0;    //Standard Address Filter-0 low byte set to 0xxx
#elif CAR_TYPE == CADILLAC_ESCALADE
   
#endif	  
    TXB0CON=0X03;//TXB0为最高优先级3
    // After configuring CAN module with above settings, return it
    // to Normal mode
    CANCON = 0x00;
//    while(CANSTATbits.OPMODE!=0x00);        //Wait for op-mode bits in the
    while(CANSTAT != 0X00);                  //CANSTAT register to = 0b000
                                            //to indicate Normal mode OK
    
    RXB0CON = 0x20;//只接收有效的标准标识符信息
    /* 初始化CAN的中断，PIR5为CAN的外围中断标志寄存器 */  
    PIR5=0X00;               // 清所有CAN中断标志   
    PIE5bits.RXB0IE = 1;     //使能接收缓冲器0的接收中断
    IPR5bits.RXB0IP = 1;     // 接收缓冲器0的接收中断为高优先级   
//    PIR5bits.WAKIF = 0;     //清除CAN总线活动唤醒中断标志
//    PIE5bits.WAKIE = 1;      //允许CAN总线活动唤醒中断
//    IPR5bits.WAKIP = 1;     //CAN总线活动唤醒中断为高优先级
}

/*
*********************************************************************************************************
*	函 数 名: CAN_SetMode
*	功能说明: 配置CAN收发器模式
*	形    参：mode 0,正常模式 1，待机模式
*	返 回 值: 无
*********************************************************************************************************
*/
void CAN_SetMode(uint8_t mode)
{
    if(mode == 0)
    {
        CAN_STB_SetLow();
    }
    else
    {
        CAN_STB_SetHigh();
    }
}

/*********************************************************************
*
*     Function: Check the buffers to determine if they have messages
*               if so, transfer the info to the temporary-storage
*               variables. Note: Messages to receiver 0 or 1 get saved in
*               the same variables.  This id done for simplicity in
*               this example. You could save messages to separate
*               variables, or in separate arrays, if you wish. 
*
*********************************************************************/
void ECAN_Receive(CanRxMsg* RxMessage)
{    
    if (RXB0CONbits.RXFUL)      // Check RXB0CON bit RXFUL to see if RX Buffer 0
                                // has received a message, if so, get the
                                // associated data from the buffer and save it.
    {
        /* Get the Id */
        RxMessage->IDE = RXB0SIDLbits.EXID;
        if (RxMessage->IDE == CAN_Id_Standard)
        {
          RxMessage->StdId = (uint16_t)RXB0SIDH<<3 | (RXB0SIDL>>5);
        }
        else
        {
          
        }

        RxMessage->RTR = RXB0DLCbits.RXRTR;
        /* Get the DLC */
        RxMessage->DLC = RXB0DLC&0x0F;
        /* Get the FMI */
//        RxMessage->FMI = 0x00;
        /* Get the data field */
        RxMessage->Data[0] = RXB0D0;
        RxMessage->Data[1] = RXB0D1;
        RxMessage->Data[2] = RXB0D2;
        RxMessage->Data[3] = RXB0D3;
        RxMessage->Data[4] = RXB0D4;
        RxMessage->Data[5] = RXB0D5;
        RxMessage->Data[6] = RXB0D6;
        RxMessage->Data[7] = RXB0D7;
        RXB0CONbits.RXFUL = 0;      // Reset buffer-0-full bit to show "empty"
    }   
}



/*
*********************************************************************************************************
*	函 数 名: ECAN_Transmit
*	功能说明: CAN发送报文消息
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void ECAN_Transmit(CanTxMsg* TxMessage)
{
    TXB0CONbits.TXREQ = 0;       /* 关发送 ，该位发送成功则自动清零*/   
    if (TxMessage->IDE == CAN_Id_Standard)
    {
        TXB0SIDH = (uint8_t)(TxMessage->StdId>>3);
        TXB0SIDL = (uint8_t)(TxMessage->StdId<<5)&0xE0;
        TXB0SIDLbits.EXIDE = TxMessage->IDE;
        TXB0DLCbits.TXRTR = TxMessage->RTR;
    }
    else
    {
//        TXB0EIDH = TxMessage->ExtId>>8;
//        TXB0EIDL = TxMessage->ExtId;
    }
    TXB0DLC = TxMessage->DLC;
    TXB0D0 = TxMessage->Data[0];
    TXB0D1 = TxMessage->Data[1];
    TXB0D2 = TxMessage->Data[2];
    TXB0D3 = TxMessage->Data[3];
    TXB0D4 = TxMessage->Data[4];
    TXB0D5 = TxMessage->Data[5];
    TXB0D6 = TxMessage->Data[6];
    TXB0D7 = TxMessage->Data[7];
    
    TXB0CONbits.TXREQ = 1; //Set the buffer to transmit
    while(TXB0CONbits.TXREQ==1);           //等待发送 完成   
}
/*
*********************************************************************************************************
*	函 数 名: CAN_TX_Test
*	功能说明: CAN发送测试
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void CAN_TX_Test(void)
{
    /* 进行临界区保护，关闭中断 */
    //标准帧ID,0x375   
	g_tCanTxMsg.StdId = CAR_DOOR_ID;     //标准帧ID
	g_tCanTxMsg.RTR = CAN_RTR_DATA;//数据帧
	g_tCanTxMsg.IDE = CAN_ID_STD;  //标准帧
	
	g_tCanTxMsg.DLC = 0X08;				
	g_tCanTxMsg.Data[0] = ADCON0;
	g_tCanTxMsg.Data[1] = 0;	
    g_tCanTxMsg.Data[2] = (uint8_t)(SysRunData.ADC_Buf[ADC_CHS_VBAT]>>8);
	g_tCanTxMsg.Data[3] = (uint8_t)SysRunData.ADC_Buf[ADC_CHS_VBAT];
    g_tCanTxMsg.Data[4] = (uint8_t)(SysRunData.ADC_Buf[ADC_CHS_CURRENT_R]>>8);
	g_tCanTxMsg.Data[5] = (uint8_t)SysRunData.ADC_Buf[ADC_CHS_CURRENT_R];
    g_tCanTxMsg.Data[6] = (uint8_t)(SysRunData.ADC_Buf[ADC_CHS_CURRENT_L]>>8);
	g_tCanTxMsg.Data[7] = (uint8_t)SysRunData.ADC_Buf[ADC_CHS_CURRENT_L];
    ECAN_Transmit(&g_tCanTxMsg);	
}
/*
*********************************************************************************************************
*	函 数 名: CAN_TX_ErrorCode
*	功能说明: CAN发送错误代码
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void CAN_TX_ErrorCode(ERROR_CODE_E ErrorCode)
{
    /* 进行临界区保护，关闭中断 */
    //标准帧ID,0x375   
	g_tCanTxMsg.StdId = CAR_DOOR_ID;     //标准帧ID
	g_tCanTxMsg.RTR = CAN_RTR_DATA;//数据帧
	g_tCanTxMsg.IDE = CAN_ID_STD;  //标准帧
	
	g_tCanTxMsg.DLC = 0X02;				
	g_tCanTxMsg.Data[0] = 0;
	g_tCanTxMsg.Data[1] = ErrorCode;	
    ECAN_Transmit(&g_tCanTxMsg);	
}

void interrupt high_priority High_ISR(void)
{
    if(PIR5bits.WAKIF==1)//CAN总线活动唤醒中断
    {
        PIR5bits.WAKIF = 0; 
    }
    if(PIR5bits.RXB0IF==1)//接收缓冲区0接收到报文
    {
        PIR5bits.RXB0IF=0;      // 清接收中断标志     
        ECAN_Receive(&g_tCanRxMsg);

#if CAR_TYPE == RANGEROVER_17
     /*路虎揽胜运动版17款*/
    #if CTRL_LOGIC == NEG_LOGIC
        if ((g_tCanRxMsg.StdId == CAR_DOOR_ID) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (g_tCanRxMsg.DLC == 0x08))
        {
             /*左边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_LEFT_CTRL_BYTE]&FRONT_LEFT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_LEFT_CTRL_BYTE]&REAR_LEFT_CTRL_BIT) == 0))
            {
                LeftDoorOpen();
            }
            else 
            {
                LeftDoorClose();
            }   
            /*右边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_RIGHT_CTRL_BYTE]&FRONT_RIGHT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_RIGHT_CTRL_BYTE]&REAR_RIGHT_CTRL_BIT) == 0))
            {
                RightDoorOpen();
            }
            else 
            {
                RightDoorClose();
            }      
        }
    #else
        if ((g_tCanRxMsg.StdId == CAR_DOOR_ID) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (g_tCanRxMsg.DLC == 0x08))
        {
             /*左边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_LEFT_CTRL_BYTE]&FRONT_LEFT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_LEFT_CTRL_BYTE]&REAR_LEFT_CTRL_BIT) == 0))
            {
                LeftDoorClose();
            }
            else 
            {
                LeftDoorOpen();    
            }   
            /*右边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_RIGHT_CTRL_BYTE]&FRONT_RIGHT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_RIGHT_CTRL_BYTE]&REAR_RIGHT_CTRL_BIT) == 0))
            {
                RightDoorClose();   
            }
            else 
            {
                RightDoorOpen();
            }      
        }
    #endif
    
#elif CAR_TYPE == TRUMPCHI_GS8
     /*广汽传祺GS8*/
	#if CTRL_LOGIC == NEG_LOGIC
        if ((g_tCanRxMsg.StdId == CAR_DOOR_ID) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (g_tCanRxMsg.DLC == 0x08))
        {
             /*左边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_LEFT_CTRL_BYTE]&FRONT_LEFT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_LEFT_CTRL_BYTE]&REAR_LEFT_CTRL_BIT) == 0))
            {
                LeftDoorOpen();
            }
            else 
            {
                LeftDoorClose();
            }   
            /*右边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_RIGHT_CTRL_BYTE]&FRONT_RIGHT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_RIGHT_CTRL_BYTE]&REAR_RIGHT_CTRL_BIT) == 0))
            {
                RightDoorOpen();
            }
            else 
            {
                RightDoorClose();
            }      
        }
    #else
        if ((g_tCanRxMsg.StdId == CAR_DOOR_ID) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (g_tCanRxMsg.DLC == 0x08))
        {
             /*左边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_LEFT_CTRL_BYTE]&FRONT_LEFT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_LEFT_CTRL_BYTE]&REAR_LEFT_CTRL_BIT) == 0))
            {
                LeftDoorClose();
            }
            else 
            {
                LeftDoorOpen();    
            }   
            /*右边门检测*/
            if(((g_tCanRxMsg.Data[FRONT_RIGHT_CTRL_BYTE]&FRONT_RIGHT_CTRL_BIT) == 0) || ((g_tCanRxMsg.Data[REAR_RIGHT_CTRL_BYTE]&REAR_RIGHT_CTRL_BIT) == 0))
            {
                RightDoorClose();   
            }
            else 
            {
                RightDoorOpen();
            }      
        }
    #endif 
#elif CAR_TYPE == CADILLAC_ESCALADE
	
#endif	 
    }
}




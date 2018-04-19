/* 
 * File:   eacn.h
 * Author: Administrator
 *
 * Created on 2017年7月11日, 下午4:33
 */

#ifndef ECAN_H
#define	ECAN_H

#ifdef	__cplusplus
extern "C" {
#endif

/** 
  * @brief  CAN Tx message structure definition  
  */
#define CAN_Id_Standard             0X00  /*!< Standard Id */
#define CAN_Id_Extended             0X01  /*!< Extended Id */    
#define CAN_RTR_Data                0X00  /*!< Data frame */
#define CAN_RTR_Remote              0X01  /*!< Remote frame */
    
#define CAN_ID_STD                  CAN_Id_Standard           
#define CAN_ID_EXT                  CAN_Id_Extended
#define CAN_RTR_DATA                CAN_RTR_Data         
#define CAN_RTR_REMOTE              CAN_RTR_Remote
    
#define CAN_MODE_NORMAL  0  //CAN收发器正常模式
#define CAN_MODE_STANDBY 1  //CAN收发器待机模式

typedef enum
{
    INFO_ID_LEFT_PEDAL_OUT_NORMAL = 0,
    INFO_ID_LEFT_PEDAL_OUT_ERROR,  
    INFO_ID_LEFT_PEDAL_BACK_NORMAL,
    INFO_ID_LEFT_PEDAL_BACK_ERROR,
    INFO_ID_RIGHT_PEDAL_OUT_NORMAL,
    INFO_ID_RIGHT_PEDAL_OUT_ERROR,  
    INFO_ID_RIGHT_PEDAL_BACK_NORMAL,
    INFO_ID_RIGHT_PEDAL_BACK_ERROR,
}TEST_INFO_ID_E;
typedef struct
{
  uint16_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint16_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be transmitted. This parameter can be a value 
                        of @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the message that will 
                        be transmitted. This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be 
                        transmitted. This parameter can be a value between 
                        0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0 
                        to 0xFF. */
} CanTxMsg;

/** 
  * @brief  CAN Rx message structure definition  
  */

typedef struct
{
  uint16_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint16_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be received. This parameter can be a value of 
                        @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the received message.
                        This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to 
                        0xFF. */

  uint8_t FMI;     /*!< Specifies the index of the filter the message stored in 
                        the mailbox passes through. This parameter can be a 
                        value between 0 to 0xFF */
} CanRxMsg;

/*********************************************************************
*
*                        Function Prototypes 
*
*********************************************************************/
void ECAN_Init(void);
void CAN_SetMode(uint8_t mode);
void CAN_TX_Test(void);
void CAN_TX_TestInfo(TEST_INFO_ID_E TestInfoID);
#ifdef	__cplusplus
}
#endif

#endif	/* ECAN_H */


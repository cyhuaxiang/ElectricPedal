/* 
 * File:   remote_ctrl.h
 * Author: Administrator
 *
 * Created on 2017年9月27日, 下午9:19
 */

#ifndef REMOTE_CTRL_H
#define	REMOTE_CTRL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define KEY_FILTER_TIME   2
#define KEY_LONG_TIME     100			/* 单位10ms， 持续1秒，认为长按事件 */
   
typedef struct
{
	uint8_t  Count;			/* 滤波器计数器 */
	uint16_t LongCount;		/* 长按计数器 */
	uint16_t LongTime;		/* 按键按下持续时间, 0表示不检测长按 */
	uint8_t  State;			/* 按键当前状态（按下还是弹起） */
	uint8_t  RepeatSpeed;	/* 连续按键周期 */
	uint8_t  RepeatCount;	/* 连续按键计数器 */
}KEY_T;


/* 供外部调用的函数声明 */
void RemoteCtrl_Init(void);
void bsp_DetectKey(void);

#ifdef	__cplusplus
}
#endif

#endif	/* REMOTE_CTRL_H */


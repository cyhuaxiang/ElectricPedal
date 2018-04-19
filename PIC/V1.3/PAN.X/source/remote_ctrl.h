/* 
 * File:   remote_ctrl.h
 * Author: Administrator
 *
 * Created on 2017��9��27��, ����9:19
 */

#ifndef REMOTE_CTRL_H
#define	REMOTE_CTRL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define KEY_FILTER_TIME   2
#define KEY_LONG_TIME     100			/* ��λ10ms�� ����1�룬��Ϊ�����¼� */
   
typedef struct
{
	uint8_t  Count;			/* �˲��������� */
	uint16_t LongCount;		/* ���������� */
	uint16_t LongTime;		/* �������³���ʱ��, 0��ʾ����ⳤ�� */
	uint8_t  State;			/* ������ǰ״̬�����»��ǵ��� */
	uint8_t  RepeatSpeed;	/* ������������ */
	uint8_t  RepeatCount;	/* �������������� */
}KEY_T;


/* ���ⲿ���õĺ������� */
void RemoteCtrl_Init(void);
void bsp_DetectKey(void);

#ifdef	__cplusplus
}
#endif

#endif	/* REMOTE_CTRL_H */


/* 
 * File:   rly.h
 * Author: Administrator
 *
 * Created on 2017年7月13日, 上午11:56
 */

#ifndef RLY_H
#define	RLY_H

#ifdef	__cplusplus
extern "C" {
#endif

void RLY_Init(void);
void Pedal_Out(uint8_t dir);
void Pedal_Back(uint8_t dir);
void Pedal_Stop(uint8_t dir);


#ifdef	__cplusplus
}
#endif

#endif	/* RLY_H */


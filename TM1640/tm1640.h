
#ifndef _TM1640_H_
#define _TM1640_H_


#include "disp_iic.h"



//outBuff 数据从1开始， 0用于指令码
//brightness 0:熄灭 1-8 
extern void drive_tm1640_out(uint8_t* outBuff, uint8_t brightness);


#endif /* _TM1640_H_ */

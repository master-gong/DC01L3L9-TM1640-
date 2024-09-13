/**
* @file      TM1640.c
* @brief     TM1640 驱动程序.
* @author    mastergong
* @date      2021-10-27
* @version   001
* @copyright -
*/

#include "tm1640.h"
#include "queue_typedef.h"
#include "task_typedef.h"
#include "esp_system.h"




//显示接口 
//outBuff 数据从1开始， 0用于指令码
//brightness 0:熄灭 1-8 
void drive_tm1640_out(uint8_t* outBuff, uint8_t brightness)
{
   //-------亮度设置-----------
   if(brightness > 8){ //亮度设置
      brightness = 8;
   }
   outBuff[0] = 0x40;  	//普通模式   自动地址增加
   display_iic_write_data_LSB_nAck((char*)outBuff, 1, 1);
   outBuff[0] = 0xC0;
   display_iic_write_data_LSB_nAck((char*)outBuff, 17, 1);    
   if(brightness == 0){ //关闭显示
      outBuff[0] = 0x80;
   }else{
      brightness-=1;
      outBuff[0] = 0x88 | brightness;  //亮度设置
   } 
   display_iic_write_data_LSB_nAck((char*)outBuff, 1, 1);
}

#ifndef DISPLAY_DC01L3L9_H_
#define DISPLAY_DC01L3L9_H_

#include <stdint.h>
#include <stdbool.h>


#define SECOND_DC01L3L9_CODE 0x04

#define LED_SIGE_A     10
#define LED_SIGE_B     11
#define LED_SIGE_C     12
#define LED_SIGE_Cl    27
#define LED_SIGE_d     13
#define LED_SIGE_E     14
#define LED_SIGE_F     15
#define LED_SIGE_H     16
#define LED_SIGE_L     17
#define LED_SIGE_r     18
#define LED_SIGE_P     19
#define LED_SIGE_N     20
#define LED_SIGE_M_    21
#define LED_SIGE_U_    22
#define LED_SIGE_D_    23
#define LED_SIGE_Uo    24
#define LED_SIGE_Do    25
#define LED_SIGE_S     5
#define LED_SIGE_U     26
#define LED_SIGE_Z     28
#define LED_SIGE_Y     29
#define LED_SIGE_OFF   30
#define LED_SIGE_L_R   31


typedef union{
  uint16_t BYTE;
  struct{
    uint16_t  NTP_LED      :  1 ;  /* NTP结果反馈 */
    uint16_t  SECOND       :  1 ;  /* 秒点亮 */
    uint16_t  VERSIOON     :  1 ;  /* 版本号 */
    uint16_t  TEMP         :  1 ;  /* 温度*/
    uint16_t  MS           :  1 ;  /* 毫秒*/
    uint16_t  DATE_        :  1 ;  /* 月份 */
    uint16_t  AM           :  1 ;  /* AM */
    uint16_t  PM           :  1 ;  /* PM */
    uint16_t  ALARM        :  1 ;  /* 闹钟图标 */
  }BIT;
}_disp_sign;


typedef struct {
    uint8_t         grid_data[9+1] ;  //显示
    uint8_t         power;            //0xA5 显示
    uint16_t        luminance;        //亮度(0-7)
    _disp_sign      sign;

}_disp_buff_st;




extern void display_drive_out(_disp_buff_st* dispData);

#endif /* DISPLAY_DC01L3L9_H_ */
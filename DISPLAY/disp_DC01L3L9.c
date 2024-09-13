#include "disp_DC01L3L9.h"
#include "tm1640.h"

#include <string.h>
#include <stdio.h>

static const char DC01L3L9_code[]={
0xF9,  /* 0:  0 */
0x09,  /* 1:  1 */
0x73,  /* 2:  2 */
0x5B,  /* 3:  3 */
0x8B,  /* 4:  4 */
0xDA,  /* 5:  5 */
0xFA,  /* 6:  6 */
0x49,  /* 7:  7 */
0xFB,  /* 8:  8*/
0xDB,  /* 9:  9 */
0xEB,  /* 10: A */
0xBA,  /* 11: b */
0xF0,  /* 12: C */
0xDB,  /* 13: d */
0xF2,  /* 14: E */
0xE6,  /* 15: F */
0xAB,  /* 16: H */
0xB0,  /* 17: L */
0x22,  /* 18: r */  
0xE3,  /* 19：p */
0xE9,  /* 20：N */
0x02,  /* 21: - 中- */
0x40,  /* 22：- 上- */
0x10,  /* 23：_ 下- */
0xC3,  /* 24：o 上o */
0x3A,  /* 25：o 下o */
0xB9,  /* 26: U */
0x32,  /* 27：c */
0xD3,  /* 28：上o 下-*/
0x7A,  /* 29：下o 上-*/
0x00,  /* 30：  */
0x19,  /* 31： _I  */
};





//DC01L3L9 显示接口 
static void display_drive_tm1640_DC01L3L9(uint8_t* buff, uint8_t *dispData, _disp_sign* sign)
{
   uint8_t i;
   char data[9];
   //-------code码赋值----------
    for(i=0;i<9;i++){
        data[i] = DC01L3L9_code[dispData[i]];
    }

    //1
    buff[12] = data[0];
    buff[13] = data[0];
    //2
    buff[14] = data[1];
    buff[15] = data[1];
    //3
    buff[4] = data[2];
    buff[5] = data[2];
    //4
    buff[1] = data[3];
    buff[11] = data[3];
    //56
    buff[6] = data[4];
    buff[7] = data[5];
    //789
    buff[9] = data[6];
    buff[10] = data[7];
    buff[8] = data[8];

    //秒
    if(sign->BIT.SECOND){
        buff[4] |= SECOND_DC01L3L9_CODE;
        buff[14] |= SECOND_DC01L3L9_CODE;
    }
    //日期中间的-
    if(sign->BIT.DATE_){
        buff[5] |= SECOND_DC01L3L9_CODE;
        buff[15] |= SECOND_DC01L3L9_CODE;
    }
    //AM
    if(sign->BIT.ALARM){
      buff[12] |= SECOND_DC01L3L9_CODE;
    }
    //PM
    if(sign->BIT.PM){
      buff[13] |= SECOND_DC01L3L9_CODE;
    }
    //版本号
    if(sign->BIT.VERSIOON){
      buff[8] |= SECOND_DC01L3L9_CODE;
      buff[10] |= SECOND_DC01L3L9_CODE;
    } 
    //毫秒
    if(sign->BIT.MS){
      // buff[8] |= SECOND_DC01L3L9_CODE;
      buff[10] |= SECOND_DC01L3L9_CODE;
    }
    //温湿度.
    if(sign->BIT.TEMP){
        buff[8] |= SECOND_DC01L3L9_CODE;
    }
    //NTP联网结果
    if(sign->BIT.NTP_LED == 1){
        buff[7] |= SECOND_DC01L3L9_CODE;
    }
}



void display_drive_out(_disp_buff_st* dispData)
{
    uint8_t i, dispOutBuff[20];

    for(i=0;i<20;i++){
        dispOutBuff[i] = 0;
    }

    display_drive_tm1640_DC01L3L9(&dispOutBuff[1],dispData->grid_data , &dispData->sign);

    //brightness 0:熄灭 1-8 
    drive_tm1640_out(dispOutBuff, dispData->luminance + 1);
}

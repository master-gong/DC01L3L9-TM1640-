
#ifndef _DISP_IIC_H_
#define _DISP_IIC_H_


#include "driver/gpio.h"




#define DISP_SCL_GPIO  GPIO_NUM_13
#define DISP_SDA_GPIO  GPIO_NUM_12

#define DISP_SCL_SEL  (1ULL<<DISP_SCL_GPIO)
#define DISP_SDA_SEL  (1ULL<<DISP_SDA_GPIO)

#define SCL_DISP_SET   gpio_set_level(DISP_SCL_GPIO,1)
#define SCL_DISP_CRL   gpio_set_level(DISP_SCL_GPIO,0)
#define SDA_DISP_SET   gpio_set_level(DISP_SDA_GPIO,1)
#define SDA_DISP_CRL   gpio_set_level(DISP_SDA_GPIO,0)




extern void init_display_iic_gpio(void);

extern void display_iic_write_data_LSB(char* dataBuff,char length, char stop);  //1637
extern void display_iic_write_data(char subAdd, char* dataBuff,char length);

extern void display_iic_write_data_LSB_nAck(char* dataBuff,char length, char stop);    //1640

#endif

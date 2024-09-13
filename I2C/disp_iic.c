#include "disp_iic.h"




static void init_sda_out(void)
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT_OD; //GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = DISP_SDA_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}


static void init_sda_in(void)
{
    gpio_config_t io_conf;
    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask = DISP_SDA_SEL;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = 0;
    gpio_config(&io_conf);
}

static void init_scl_out(void)
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT_OD;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = DISP_SCL_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}



/***********************
函数功能：us延时
输入参数：无
输出参数：无
备    注：粗略延时
***********************/
static void delay_us(uint8_t z)
{ 
   while(z--){
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
   }
}

/***********************
函数功能：ms延时
输入参数：无
输出参数：无
备    注：粗略延时
***********************/
static void delay_ms(unsigned int time)
{
    unsigned int i;
    while(time--)  
    for(i=900;i>0;i--)
    delay_us(1); 
}

static void iic_start(void)
{
    init_sda_out();
    SDA_DISP_SET; 
    delay_us(4);
    SCL_DISP_SET;    
    delay_us(40);     
    SDA_DISP_CRL;         
    delay_us(4);         
    SCL_DISP_CRL;    
}

static void iic_stop(void)
{
    init_sda_out();
    SCL_DISP_CRL;
    delay_us(2);
    SDA_DISP_CRL;		
    delay_us(40);
    SCL_DISP_SET;		
    delay_us(10);        
    SDA_DISP_SET;            
    delay_us(40);       
}

static void iic_ack(void)
{

	SCL_DISP_CRL;
	init_sda_in();
	delay_us(10);
	SCL_DISP_SET;
    delay_us(40);
    SCL_DISP_CRL;
	delay_us(10);
	init_sda_out();
	
}

static void iic_write_byte(char txd)
{
    uint8_t i;
    init_sda_out();
    for(i = 0;i < 8; i ++)
    {
	delay_us(2);
    if((txd&0x80)>>7){ //0x80  1000 0000
	   SDA_DISP_SET;
    }else{
	   SDA_DISP_CRL;
    }
    txd<<=1; 	  
    delay_us(20);   
	SCL_DISP_SET;
	delay_us(45);  
	SCL_DISP_CRL;	
	delay_us(20); 
    }
}

static void iic_write_byte_LSB(char txd)
{
    uint8_t i;
    init_sda_out();
    for(i = 0;i < 8; i ++)
    {
	   delay_us(2);
    if(txd & 0x01){ //0x80  1000 0000
	   SDA_DISP_SET;
    }else{
	   SDA_DISP_CRL;
    }
    txd >>= 1; 	  
    delay_us(20);   
	SCL_DISP_SET;
	delay_us(45);  
	SCL_DISP_CRL;	
	delay_us(20); 
    }
}
 




void display_iic_write_data_LSB(char* dataBuff,char length, char stop)
{
	uint8_t cnt = 0;

	iic_start();
    for(cnt = 0; cnt < length; cnt++){
       iic_write_byte_LSB(*dataBuff++);     //发送字节
       iic_ack();
    }
    if(stop){
       iic_stop();//产生一个停止条件
    }
}

void display_iic_write_data_LSB_nAck(char* dataBuff,char length, char stop)
{
	uint8_t cnt = 0;

	iic_start();
    for(cnt = 0; cnt < length; cnt++){
       iic_write_byte_LSB(*dataBuff++);     //发送字节
    //    iic_ack();
    }
    if(stop){
       iic_stop();//产生一个停止条件
    }
}

void display_iic_write_data(char subAdd, char* dataBuff,char length)
{
	uint8_t cnt = 0;

	iic_start();
	iic_write_byte(subAdd & 0xfe);
    iic_ack();

    for(cnt = 0; cnt < length; cnt++){
       iic_write_byte(*dataBuff++);     //发送字节
       iic_ack();
    }
    iic_stop();//产生一个停止条件

}


void init_display_iic_gpio(void)
{
   init_sda_out();
   init_scl_out(); 
   SCL_DISP_SET;
   SDA_DISP_SET;
   delay_ms(10);	       //需要延时一小段时间，否则开显示会无响应
}


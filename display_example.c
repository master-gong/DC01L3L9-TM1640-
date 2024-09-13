#include "disp_iic.h"
#include "tm1640.h"
#include "disp_DC01L3L9.h"

static _disp_buff_st disp_data;    /* Display data */

static void disp_buff_clean(void)
{
    uint8_t i;
    // Clear display buffer
    disp_data.sign.BYTE = 0;
    for(i = 0; i < 10; i++){
        disp_data.grid_data[i] = LED_SIGE_OFF;
    }
}

/**
 * @brief       Show main task function.
 * @param[in]   pvParameters    Parameters passed to this task.
 * @return      none
 */
void task_display_test(void *pvParameters)
{

    init_display_iic_gpio();  // Initialize IIC pins
    disp_data.power = 0xA5; // Display on

    while(1){

        // Clear display buffer
        disp_buff_clean();                              
        // Assign display data
        // Output refresh
        if(disp_data.power == 0xA5){
            disp_data.luminance = 5; // Brightness
            disp_data.sign.BIT.SECOND = 1; 
            // 16:32:56  abc
            disp_data.grid_data[0] = 1;
            disp_data.grid_data[1] = 6;
            disp_data.grid_data[2] = 3;
            disp_data.grid_data[3] = 2;
            disp_data.grid_data[4] = 5;
            disp_data.grid_data[5] = 6;

            disp_data.grid_data[6] = LED_SIGE_A;
            disp_data.grid_data[7] = LED_SIGE_B;
            disp_data.grid_data[8] = LED_SIGE_C;
        }

        display_drive_out(&disp_data);

        // Delay
        vTaskDelay(500 / portTICK_RATE_MS);
    
    }

}
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>

#define S_STAT_START 0
#define S_MOVX_START 1
#define S_MOVY_START 2

volatile uint8 state_b;
volatile uint8 bit_count_b;

volatile uint8 bit_b;

volatile uint8 status_b;
volatile uint8 mov_x_b;
volatile uint8 mov_y_b;

volatile int32 loc_x_b;
volatile int32 loc_y_b;

volatile uint8 data_ready_b;

volatile uint32 time_prev_b;

void mouse_b_write(uint8 data){
	uint8 i;
	uint8 parity = 0;
	
    //Ensure that clock and data are floating
	SDAT_B_Write(1);
	SCLK_B_Write(1);
	CyDelayUs(200);
    
    //If the host wants to send data, it must first inhibit communication from the device by pulling Clock low.  
	SCLK_B_Write(0);
	CyDelayUs(200);
    
    //The host then pulls Data low 
	SDAT_B_Write(0);
	CyDelayUs(10);
    
    //and releases Clock.  
    //This is the "Request-to-Send" state and signals the device to start generating clock pulses.
    SCLK_B_Write(1);
    SDAT_B_Write(0);
    CyDelayUs(10); //The mouse needs this extra time for some reason...
    
	while (SCLK_B_Read() == 1){SDAT_B_Write(0);} /* wait for device to take control of clock */
    
    for (i = 0; i < 8; i++){
        //Write successive bits to the data line
        SDAT_B_Write((data & (1 << i)) != 0);
        parity += ((data & (1 << i)) != 0);
        //Wait a clock cycle
        while (SCLK_B_Read() == 0){;}
        while (SCLK_B_Read() == 1){;}
    }
    
    //Odd parity 
    SDAT_B_Write((parity % 2) == 0);
    //SDAT_B_Write(1);
    
    //Wait a clock cycle
    while (SCLK_B_Read() == 0){;}
    while (SCLK_B_Read() == 1){;}
    
    //Release the data and clock lines
    SDAT_B_Write(1);
    SCLK_B_Write(1);
}

void mouse_b_init(){
    //CHECK_B_Write(1);
    mouse_b_write(0xff);  // reset
    //CHECK_B_Write(0);
    CyDelay(8);//Wait for ACK
    
    //CHECK_B_Write(1);
    mouse_b_write(0xf3); //Set Sample Rate
    //CHECK_B_Write(0);
    
    CyDelay(2);
    
    //CHECK_B_Write(1);
    mouse_b_write(80); //Set sample rate to 80 (DEC)
    //CHECK_B_Write(0);
    
    CyDelay(2);
    
    //CHECK_B_Write(1);
    mouse_b_write(0xea); //Set  resolution
    //CHECK_B_Write(0);
    
    CyDelay(2);
    
    //CHECK_B_Write(1);
    mouse_b_write(0x02); //Set resolution to 4c/mm
    //CHECK_B_Write(0);
    
    CyDelay(2);
    
    //CHECK_B_Write(1);
    mouse_b_write(0xf4);
    //CHECK_B_Write(0);
}


void reset_sclk_b_isr(){
    state_b = S_STAT_START;
    bit_count_b = 0;
    mov_x_b = 0;
    mov_y_b = 0;
    status_b = 0;
    time_prev_b = Timer_ReadCounter();
}

CY_ISR(MY_SCLK_B_ISR){    
    //If the clock is high when the *falling* edge interrupt triggers,
    //obviously the interrupt was triggered falsely
    if (SCLK_B_Read() == 1){
        reset_sclk_b_isr();
        SCLK_B_ClearInterrupt();
        return;
    }
    
    //Reset if longer than 2*10*100uS has passed... 2ms
    if ((time_prev_b - Timer_ReadCounter()) > 10){
        reset_sclk_b_isr();
        bit_count_b++;
        SCLK_B_ClearInterrupt();
        return;
    }
    
    //CHECK_B_Write(1); //Indicate start of interrupt - for time measurement purposes
    
    bit_b = SDAT_B_Read();
    
    switch (state_b){
        case S_STAT_START:
            //First bit should be a 0
            if (bit_count_b == 0){
                bit_count_b++;
            } else if (bit_count_b < 9){ //Bits 1 to 8 are the data bits
                status_b |= (bit_b << (bit_count_b - 1));
                bit_count_b++;
            } else if (bit_count_b == 9){ //parity bit
                bit_count_b++;
            } else if (bit_count_b == 10){ //stop bit
                bit_count_b = 0;
                state_b = S_MOVX_START;
            }
            break;
            
        case S_MOVX_START: //We are looking at the movement data
            if (bit_count_b == 0){
                bit_count_b++;
            } else if (bit_count_b < 9){
                mov_x_b |= (bit_b << (bit_count_b - 1));
                bit_count_b++;
            } else if (bit_count_b == 9){
                bit_count_b++;
            } else if (bit_count_b == 10){
                bit_count_b = 0;
                state_b = S_MOVY_START;
            }
            break;
            
        case S_MOVY_START:
             if (bit_count_b == 0){
                bit_count_b++;
            } else if (bit_count_b < 9){
                mov_y_b |= (bit_b << (bit_count_b - 1));
                bit_count_b++;
            } else if (bit_count_b == 9){
                bit_count_b++;
            } else if (bit_count_b == 10){
                if (status_b & 0x10){ //X sign bit is set -- moving left
                    loc_x_b -= (255 - mov_x_b);
                } else {
                    loc_x_b += mov_x_b;
                }
                
                if (status_b & 0x20){ //Y sign bit is set -- moving down
                    loc_y_b -= (255 - mov_y_b);
                } else {
                    loc_y_b += mov_y_b;
                }
                data_ready_b++;
                reset_sclk_b_isr();
            }
            break;
    }
   
    time_prev_b = Timer_ReadCounter(); 
    SCLK_B_ClearInterrupt();
    
    //CHECK_B_Write(0);
}

/* [] END OF FILE */

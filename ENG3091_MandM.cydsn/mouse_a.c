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
#include <mouse_conf.h>

#define S_STAT_START 0
#define S_MOVX_START 1
#define S_MOVY_START 2

volatile uint8 state_a;
volatile uint8 bit_count_a;

volatile uint8 bit_a;

volatile uint8 status_a;
volatile uint8 mov_x_a;
volatile uint8 mov_y_a;

volatile int32 loc_x_a;
volatile int32 loc_y_a;

volatile uint8 data_ready_a;

volatile uint32 time_prev_a;

void mouse_a_write(uint8 data){
	uint8 i;
	uint8 parity = 0;
	
    //Ensure that clock and data are floating
	SDAT_A_Write(1);
	SCLK_A_Write(1);
	CyDelayUs(200);
    
    //If the host wants to send data, it must first inhibit communication from the device by pulling Clock low.  
	SCLK_A_Write(0);
	CyDelayUs(200);
    
    //The host then pulls Data low 
	SDAT_A_Write(0);
	CyDelayUs(10);
    
    //and releases Clock.  
    //This is the "Request-to-Send" state and signals the device to start generating clock pulses.
    SCLK_A_Write(1);
    SDAT_A_Write(0);
    CyDelayUs(10); //The mouse needs this extra time for some reason...
    
	while (SCLK_A_Read() == 1){SDAT_A_Write(0);} /* wait for device to take control of clock */
    
    for (i = 0; i < 8; i++){
        //Write successive bits to the data line
        SDAT_A_Write((data & (1 << i)) != 0);
        parity += ((data & (1 << i)) != 0);
        //Wait a clock cycle
        while (SCLK_A_Read() == 0){;}
        while (SCLK_A_Read() == 1){;}
    }
    
    //Odd parity 
    SDAT_A_Write((parity % 2) == 0);
    //SDAT_A_Write(1);
    
    //Wait a clock cycle
    while (SCLK_A_Read() == 0){;}
    while (SCLK_A_Read() == 1){;}
    
    //Release the data and clock lines
    SDAT_A_Write(1);
    SCLK_A_Write(1);
}


void mouse_a_init(){
        
    //CHECK_A_Write(1);
    mouse_a_write(0xff);  // reset
    //CHECK_A_Write(0);
    
    CyDelay(8);
    
    //Set sample rate
    //CHECK_A_Write(1);
    mouse_a_write(0xf3);
    //CHECK_A_Write(0);
    
    CyDelay(2);//Wait for ACK
    //Set to 40
    //CHECK_A_Write(1);
    mouse_a_write(M_SAMPLE);
    //CHECK_A_Write(0);
    
    CyDelay(2);
    
    //CHECK_A_Write(1);
    mouse_a_write(0xea); //Set resolution
    //CHECK_A_Write(0);
    
    CyDelay(2);
    
    //CHECK_A_Write(1);
    mouse_a_write(M_RES); //Set resolution to 4c/mm
    //CHECK_A_Write(0);
    
    
    //CHECK_A_Write(1);
    mouse_a_write(0xf4); //Begin streaming data
    //CHECK_A_Write(0);
    
    CyDelay(2);
    
}


void reset_sclk_a_isr(){
    state_a = S_STAT_START;
    bit_count_a = 0;
    mov_x_a = 0;
    mov_y_a = 0;
    status_a = 0;
    time_prev_a = Timer_ReadCounter();
}

CY_ISR(MY_SCLK_A_ISR){        
    
    
    //If the clock is high when the *falling* edge interrupt triggers,
    //obviously the interrupt was triggered falsely
    if (SCLK_A_Read() == 1){
        reset_sclk_a_isr();
        SCLK_A_ClearInterrupt();
        return;
    }
    
    //Reset if longer than 2*10*100uS has passed... 2ms
    if ((time_prev_a - Timer_ReadCounter()) > 10){
        reset_sclk_a_isr();
        bit_count_a++;
        SCLK_A_ClearInterrupt();
        return;
    }
    
    //CHECK_A_Write(1); //Indicate start of interrupt - for time measurement purposes
    
    bit_a = SDAT_A_Read();
    
    switch (state_a){
        case S_STAT_START:
            //First bit should be a 0
            if (bit_count_a == 0){
                bit_count_a++;
            } else if (bit_count_a < 9){ //Bits 1 to 8 are the data bits
                status_a |= (bit_a << (bit_count_a - 1));
                bit_count_a++;
            } else if (bit_count_a == 9){ //parity bit
                bit_count_a++;
            } else if (bit_count_a == 10){ //stop bit
                bit_count_a = 0;
                state_a = S_MOVX_START;
            }
            break;
            
        case S_MOVX_START: //We are looking at the movement data
            if (bit_count_a == 0){
                bit_count_a++;
            } else if (bit_count_a < 9){
                mov_x_a |= (bit_a << (bit_count_a - 1));
                bit_count_a++;
            } else if (bit_count_a == 9){
                bit_count_a++;
            } else if (bit_count_a == 10){
                bit_count_a = 0;
                state_a = S_MOVY_START;
            }
            break;
            
        case S_MOVY_START:
             if (bit_count_a == 0){
                bit_count_a++;
            } else if (bit_count_a < 9){
                mov_y_a |= (bit_a << (bit_count_a - 1));
                bit_count_a++;
            } else if (bit_count_a == 9){
                bit_count_a++;
            } else if (bit_count_a == 10){
                if (status_a & 0x10){ //X sign bit is set -- moving left
                    loc_x_a -= (255 - mov_x_a);
                } else {
                    loc_x_a += mov_x_a;
                }
                
                if (status_a & 0x20){ //Y sign bit is set -- moving down
                    loc_y_a -= (255 - mov_y_a);
                } else {
                    loc_y_a += mov_y_a;
                }
                data_ready_a++;
                reset_sclk_a_isr();
            }
            break;
    }
   
    time_prev_a = Timer_ReadCounter(); 
    SCLK_A_ClearInterrupt();
    
    //CHECK_A_Write(0);
}

/* [] END OF FILE */

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

/** HOW TO USE THIS MODULE **
 * 1. Start the compass with start_compass()
 * 2. Monitor the compass_ready variable, if it is true, then you
 *    can call compass_read() to refresh the compass data
 * 3. Read from compass x,y,z and heading to get the heading info
 */

/* Example code to put in main loop
//Read the compass when it is ready for reading
if (compass_ready){
    compass_ready = 0;
    compass_read();
    //Access compass_x, compass_y, etc.
}
*/

#include <project.h>
#include <compass.h>
#include <math.h>

int16 compass_x;
int16 compass_y;
int16 compass_z;
int16 compass_heading; //0-360 degrees
volatile uint8 compass_ready;

int16 original_compass_heading; //this makes our compass relative

// These calibration values can be found by plotting the x,y pairs
// whilst turning the compass through 360 degrees, then moving the 
// resulting circle to center on the origin
//AT HOME
//#define CALIBRATION_X -25
//#define CALIBRATION_Y 50
//AT THE LAB/ARENA
//#define CALIBRATION_X 25
//#define CALIBRATION_Y -25
#define CALIBRATION_X 40
#define CALIBRATION_Y -30
CY_ISR(DRDY_INTERRUPT){
    compass_ready = 1;
    Compass_DRDY_ISR_ClearPending();
}

//These are lookup tables storing sin and cos values in degrees
double SinDeg[360];
double CosDeg[360];

void calculate_circular_functions(){
    int i;
    for (i = 0; i < 360; i++){
        SinDeg[i] = sin((((double) i) - 180) * (M_PI / 180.0));
        CosDeg[i] = cos((((double) i) - 180) * (M_PI / 180.0));
    }
}

void start_compass(){
    compass_ready = 0;
    compass_x = 0;
    compass_y = 0;
    compass_z = 0;
    compass_heading = 0;
    original_compass_heading = 0;
    
    I2C_Start();
    //Write configuration register A
    I2C_MasterSendStart(COMPASS_ADDR, I2C_WRITE_XFER_MODE); 
    I2C_MasterWriteByte(COMPASS_REG_CONF_A);
    I2C_MasterWriteByte(COMPASS_DAT_CONF_A);
    I2C_MasterSendStop();
    //Write configuration register A    
    I2C_MasterSendStart(COMPASS_ADDR, I2C_WRITE_XFER_MODE); 
    I2C_MasterWriteByte(COMPASS_REG_CONF_B);
    I2C_MasterWriteByte(COMPASS_DAT_CONF_B);
    I2C_MasterSendStop();
    //Write mode register
    I2C_MasterSendStart(COMPASS_ADDR, I2C_WRITE_XFER_MODE); 
    I2C_MasterWriteByte(COMPASS_REG_MODE);
    I2C_MasterWriteByte(COMPASS_DAT_MODE);
    I2C_MasterSendStop();
    
    Compass_DRDY_ISR_StartEx(DRDY_INTERRUPT);
}


void compass_read(){
    uint8 data[6] = {0, 0, 0, 0, 0, 0};
    //Set the compass internal address pointer to xh
    I2C_MasterSendStart(COMPASS_ADDR, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x03);
    I2C_MasterSendStop();
    //Read six bytes
    I2C_MasterSendStart(COMPASS_ADDR, I2C_READ_XFER_MODE);
    data[0] = I2C_MasterReadByte(I2C_ACK_DATA);
    data[1] = I2C_MasterReadByte(I2C_ACK_DATA);
    data[2] = I2C_MasterReadByte(I2C_ACK_DATA);
    data[3] = I2C_MasterReadByte(I2C_ACK_DATA);
    data[4] = I2C_MasterReadByte(I2C_ACK_DATA);
    data[5] = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    
    compass_x = ((data[0] << 8) | data[1]);
    compass_z = (data[2] << 8) | data[3];//Bizarrely, the device reads x,z,y...
    compass_y = ((data[4] << 8) | data[5]);
    compass_heading = atan2((double) (compass_y + CALIBRATION_Y), 
                            (double) (compass_x + CALIBRATION_X)) * 
                            (180/M_PI) + 180 - original_compass_heading;
    if (compass_heading > 360){
        compass_heading -= 360;
    } else if (compass_heading < 0){
        compass_heading += 360;
    }
    compass_ready = 0;
}

/* [] END OF FILE */

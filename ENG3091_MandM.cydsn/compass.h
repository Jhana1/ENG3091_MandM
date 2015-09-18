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


#ifndef MY_COMPASS
    #include <project.h>
    
    #define COMPASS_ADDR 0x1E
    
    //Moving average, Measurement Rate, Measurement Mode
    //0-MA2-MR3-MM
    #define COMPASS_DAT_CONF_A 0b01110000
    #define COMPASS_REG_CONF_A 0x00
    //GN3-00000 (Gain Configuration)
    #define COMPASS_DAT_CONF_B 0b00100000
    #define COMPASS_REG_CONF_B 0x01
    
    //HS6-MD2
    #define COMPASS_DAT_MODE 0b00000000
    #define COMPASS_REG_MODE 0x02
    
    #define COMPASS_REG_XH 0x03
    
    #define COMPASS_REG_ZL 0x06
    
    void start_compass(void);
    void compass_read(void);
#endif

/* [] END OF FILE */

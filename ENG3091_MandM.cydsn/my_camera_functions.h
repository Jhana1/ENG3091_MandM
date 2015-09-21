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
#ifndef MY_MY_CAMERA_FUNCTIONS
    #include <project.h>
    #include <Camera.h>
    
    void init_camera();
    void capture_image();
    void capture_thresh_image();
    void set_gain_exposure(int setting);
    void clean_frame(int colour, float proportion, int row_limit); 
    
    uint8 PixelColour(uint8, uint8);
    void threshold_image();
    void threshold_black();
    
    int PixelLuminence(int x, int y);
    int identify_colour_instructions(int size);
    int identify_colour_gripper();
   
    enum
    {
        NONE=0,
        RED=1,
        GREEN=2,
        BLUE=3
    };
#endif
/* [] END OF FILE */

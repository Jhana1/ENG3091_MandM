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
#include <math.h>
#include <stdlib.h>

#define PI 3.14129

extern int32 loc_x_a;
extern int32 loc_y_a;

extern int32 loc_x_b;
extern int32 loc_y_b;

int32 ploc_x_a;
int32 ploc_y_a;

int32 ploc_x_b;
int32 ploc_y_b;

int32 location_x;
int32 location_y;
float angle;

//Mouse A's offset from the center of the robot
#define MOUSE_A_XOFF 2
#define MOUSE_A_YOFF 2
//Mouse B's offset from the center of the robot
#define MOUSE_B_XOFF 2
#define MOUSE_B_YOFF 2

void reset_navigation(){
    loc_x_a = 0;
    loc_y_a = 0;
    loc_x_b = 0;
    loc_y_b = 0;
    ploc_x_a = 0;
    ploc_y_a = 0;
    ploc_x_b = 0;
    ploc_y_b = 0;
    
    location_x = 0;
    location_y = 0;
    angle = 0;
}

/* Call this every x times per second to calculate the current position and heading*/
CY_ISR(REFRESH_POSITION){
    //Our delta values for each mouse
    int32 dloc_x_a = (loc_x_a - ploc_x_a);
    int32 dloc_y_a = (loc_y_a - ploc_y_a);
    int32 dloc_x_b = (loc_x_b - ploc_x_b);
    int32 dloc_y_b = (loc_y_b - ploc_y_b);
    
    //Set the previous values to the current ones for the next iteration
    ploc_x_a = loc_x_a;
    ploc_y_a = loc_y_a;
    ploc_x_b = loc_x_b;
    ploc_y_b = loc_y_b;
    
    //calculate new values for location_x and location_y using dloc_x and dloc_y
    //Using the method in the italian paper (Bonarini, Matteucci, Restelli)
    double aa = atan2((double) dloc_x_a, (double) dloc_y_a);
    double la;
    if (aa != 0 && aa != PI){
        la = dloc_y_a/sin(aa);
    } else {
        la = abs(dloc_x_a);
    }
    int32 dloc_x = (dloc_x_a + dloc_x_b) / 2;
    int32 dloc_y = (dloc_y_a + dloc_y_b) / 2;
    double dangle = atan2((double) dloc_x_a - dloc_x_b, (double) dloc_y_a - dloc_y_b);
}

/* [] END OF FILE */

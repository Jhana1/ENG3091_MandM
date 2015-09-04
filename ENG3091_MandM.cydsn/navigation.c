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

/******* IMPORTANT ***********
 * The mouse on the _left_ shall be entitled mouse A
 */

#include <project.h>
#include <math.h>
#include <stdlib.h>

#include <navigation.h>

//this is in mouse_a.c
extern volatile int32 loc_x_a;
extern volatile int32 loc_y_a;
extern volatile uint8 data_ready_a;
//this is in mouse_b.c
extern volatile int32 loc_x_b;
extern volatile int32 loc_y_b;
extern volatile uint8 data_ready_b;

//We store the navigation info here
struct Position location;

struct Position update_position(double dxl, double dyl, double dxr, double dyr);

//9.4cm = 94mm = 94*4 counts/mm = 376.0 counts
#define SEPARATION 376.0

double signum(double x){
    if (x >= 0){
        return 1.0; 
    } else {
        return -1.0;
    }
}

double myabs(double x){
    if (x >= 0){
        return x;
    } else {
        return -x;
    }
}

void refresh_position(){
    if (data_ready_a > 5 && data_ready_b > 5){
        struct Position delta = update_position((double) loc_x_a, (double) loc_y_a, (double) loc_x_b, (double) loc_y_b);
        
        loc_x_a = 0;
        loc_y_a = 0;
        data_ready_a = 0;
        
        loc_x_b = 0;
        loc_y_b = 0;
        data_ready_b = 0;
        
        location.x += delta.x;
        location.y += delta.y;
        location.angle += delta.angle;
    }
}
/* Call this every x times per second to calculate the current position and heading*/
struct Position update_position(double dxl, double dyl, double dxr, double dyr){
    ISR_CHECKP_Write(1); //for timing purposes
    //Let the A mouse be LEFT and the B mouse be RIGHT
    double rl, ll, rr, lr, al, ar;
    double xpl, xpr, ypl, ypr;
    
    struct Position delta;
    
    //If no change, don't bother going through this whole routine
    
    /*if (dxl == 0 && dyl == 0 && dxr == 0 && dyr == 0){
        nav_clock_ClearPending();
        ISR_CHECKP_Write(0);
        return;
    }*/
    
    //calculate new values for location_x and location_y using dloc_x and dloc_y
    //Using the method in the italian paper (Bonarini, Matteucci, Restelli)
    //alpha a and alpha b
    al = atan2(dyl, dxl); // Note that atan2 handles x = 0 correctly
    ar = atan2(dyr, dxr);
    
    //radius of arc a and b
    if ((al < .001 && al > -.001) || ((al < M_PI + .001) && (al > M_PI - .001))){
        ll = myabs(dxl);
    } else {
        ll = dyl/sin(al);
    }    
    
    if ((al < .001 && al > -.001) || ((ar < M_PI + .001) && (ar > M_PI - .001))){
        lr = myabs(dxr);
    } else {
        lr = dyr/sin(ar);
    }  
    
    //Take the absolute value of alpha a - alpha b to get gamma
    double gamma = myabs(al - ar);
    
    double dtheta = signum(dyr - dyl)*sqrt(ll*ll + lr*lr - 2.0*cos(gamma)*ll*lr) / SEPARATION;
    
    if (myabs(dtheta) < .001){ //dtheta == 0...
        xpr = 0;
        xpl = 0;
        ypl = ll;
        ypr = lr;
    } else { //dtheta != 0...
        rl = ll / myabs(dtheta);
        rr = lr / myabs(dtheta);
        
        double sdtheta = signum(dtheta);
    
        xpl = rl*(sin(al + dtheta) - sin(al))*sdtheta - SEPARATION/2;
        ypl = rl*(cos(al) - cos(al + dtheta))*sdtheta;
        
        xpr = rr*(sin(ar + dtheta) - sin(ar))*sdtheta + SEPARATION/2;
        ypr = rr*(cos(ar) - cos(ar + dtheta))*sdtheta;
    }
    
    
    double dx = (xpr + xpl)/2.0;
    double dy = (ypr + ypl)/2.0;
 
    double angle = location.angle + atan2(dy, dx);
    double length = sqrt(dx*dx + dy*dy);
    
    delta.x = length*cos(angle);
    delta.y = length*sin(angle);
    delta.angle = dtheta;
    /*
    if (location.angle > (2*M_PI)) location.angle -= (2*M_PI);
    if (location.angle < 0) location.angle += (2*M_PI);*/
    
    ISR_CHECKP_Write(0); 
    return delta;
}

void reset_navigation(){
    loc_x_a = 0;
    loc_y_a = 0;
    data_ready_a = 0;
    loc_x_b = 0;
    loc_y_b = 0;
    data_ready_b = 0;
    
    location.x = 0.0;
    location.y = 0.0;
    location.angle = 0.0;
}

void init_navigation(){
    reset_navigation();
}

/* [] END OF FILE */

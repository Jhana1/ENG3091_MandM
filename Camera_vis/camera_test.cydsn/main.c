#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <my_camera_functions.h>
#include <blob_stats.h>
#include <ultrasonic.h>

char display[2][20];
char RGB[] = "KRGB";
int16 disp = 0, m = 0, c = 0;
extern blob blobs[255];
extern uint8 RED_U; //116;
extern uint8 RED_V;//140;//162;
extern uint8 GREEN_U;//128;
extern uint8 GREEN_V;//102;
extern uint8 BLUE_U;//115 //138;//162;
extern uint8 BLUE_V;//124;//116;
void button_handle();

void image_stuff();
void image_stuff2();
void image_stuff3();
void image_stuff4();

int current_display = -1;
int centre_pixel = 44;

void handle_menus();
void button_handle2();

extern volatile uint16 ultra_distance;
extern int connected;

uint8 exposure, gain, bgain, rgain;
uint16 blobn;
int dis[3], stack[3];

int PWM_Val = 24;
// Exposure, White Balance, Gain, Gamma
CY_ISR(menu)
{
    button_handle2();
    
    but0_ClearPending();
}
CY_ISR(change)
{
    handle_menus();
    but1_ClearPending();
}

int main()
{
    CyDelay(3000);
    m = 1;
    int i = 0;
    LCD_Start();
    BLUE_Write(1);
    //Arm_Start();
    //Arm_WriteCompare(40);
    //CyDelay(4000);
    //Arm_WriteCompare(20);
    CyGlobalIntEnable;
    Button_Start();
    but0_StartEx(menu);
    but1_StartEx(change);
    
//    Arm_WriteCompare(18);
//    LCD_PosPrintString(0,0,"Bottom");
//    CyDelay(5000);
//    LCD_ClearDisplay();
//    Arm_WriteCompare(150);
//    LCD_PosPrintString(0,0,"Top");
//    CyDelay(5000);
//    Arm_WriteCompare(PWM_Val);
    
    LCD_PosPrintString(0,0,"try camera");
    init_camera();
    LCD_PosPrintString(0,0,"Camera Started");
    set_gain_exposure(2);
    
    
    //image_stuff3();
    //CyDelay(20000);
    USB_Start(0,USB_DWR_VDDD_OPERATION);
    while(!USB_GetConfiguration());
    USB_CDC_Init(); //enable receiving data from USB host
    while(!USB_DataIsReady()); //wait until data is received on USB for synchronisation
    for(;;)
    {
        image_stuff();
       
        if(disp == 8)
        {
            image_stuff4();
//            char l[] = {'N','C','L','R'};
//            LCD_ClearDisplay();
//            sprintf(display[0],"#:%d R:%c G:%c B:%c",blobn,l[dis[0]+1],l[dis[1]+1],l[dis[2]+1]);
//            LCD_PosPrintString(0,0,display[0]);
//            for(i = 0; i < 16; i++)
//            {
//                if(blobs[i].size >= 50);
//                    LCD_PosPutChar(1,i,RGB[blobs[i].colour]);
//            }
        }
        if(disp == 9)
        {
            LCD_ClearDisplay();
            sprintf(display[0],"x:%u xc:%lu",blobs[0].x_sum,blobs[0].x_sum/blobs[0].size);
            sprintf(display[1],"y:%u yc:%lu",blobs[0].y_sum,blobs[0].y_sum/blobs[0].size);
            LCD_PosPrintString(0,0,display[0]);
            LCD_PosPrintString(1,0,display[1]);
        }
    }
}

void button_handle()
{
    // Display Major Values, Resets Auto...
    //Camera_WriteReg(0x13,0b11100000); // Enable Auto Gain etc...
    switch(disp)
    {
        case(0) :
        //Exposure Increment
            exposure = Camera_ReadReg(0x10);
            Camera_WriteReg(0x10,exposure+5); 
            sprintf(display[0],"Exposure: %d",exposure + 5);
        break;
        case(1) :
        //Gain
        //Gain
            gain = Camera_ReadReg(0x00);
            Camera_WriteReg(0x00,gain+5);
            bgain = Camera_ReadReg(0x01);
            //Camera_WriteReg(0x01,bgain+5);
            sprintf(display[1],"Gain+B: %d",gain+5);
        break;
        case(2) :
        // Exposure Decrement
            exposure = Camera_ReadReg(0x10);
            Camera_WriteReg(0x10,exposure-1); 
            sprintf(display[0],"Exposure: %d",exposure - 1);
        break;
        case(3) :
        //Gain Decrement
            gain = Camera_ReadReg(0x00);
            Camera_WriteReg(0x00,gain-1);
            bgain = Camera_ReadReg(0x01);
            //Camera_WriteReg(0x01,bgain+5);
            sprintf(display[1],"Gain+B: %d",gain-1);
        break;
    } 
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,display[0]);
    LCD_PosPrintString(1,0,display[1]);
}

void image_stuff()
{
    int i;
    capture_image();
    //LCD_ClearDisplay();
    //LCD_PosPrintString(0,0,"Sending......");
    for(i=0;i<sizeof Camera_framebuffer;i+=64)
    {
        while(!USB_CDCIsReady()); //wait until USB is ready
        USB_PutData((uint8*)Camera_framebuffer+i,64); //send next 64 byte packet (maximum size)
    }
    //LCD_PosPrintString(0,0,"Sent....");
        threshold_image();
        clean_frame(RED,0.3,144/3);
        blob_detect();
        dis[0] = to_nearest_blob(RED,50,10,centre_pixel);
        dis[1] = to_nearest_blob(GREEN,50,10,centre_pixel);
        dis[2] = to_nearest_blob(BLUE,50,10,centre_pixel);
        blobn = blob_count(50);
        for(i=0;i<sizeof Camera_framebuffer;i+=64)
        {
            while(!USB_CDCIsReady()); //wait until USB is ready
            USB_PutData((uint8*)Camera_framebuffer+i,64); //send next 64 byte packet (maximum size)
        }
        //LCD_PosPutChar(1,15,RGB[identify_colour_instructions()]);
}

void image_stuff2()
{
    LCD_PosPrintString(0,0,"                ");
    LCD_PosPrintString(0,0,"Getting Image");
    capture_thresh_image();   
    LCD_PosPrintString(0,0,"Success!!!      ");
    char RGB[] = {'K', 'R', 'G', 'B'};
    int x = identify_colour_instructions(50);
    sprintf(display[1],"Colour: %d",x);
    LCD_PosPrintString(1,0,display[1]);
}
void image_stuff3()
{
    capture_thresh_image();
    while(identify_colour_instructions(100) == 0)
    {
        Arm_WriteCompare(++PWM_Val);
        CyDelay(1000);
        if(PWM_Val >= 50)
        {
            return;
        }
        sprintf(display[0],"Arm:%d, C:%d",PWM_Val,identify_colour_instructions(100));
        LCD_ClearDisplay();
        LCD_PosPrintString(0,0,display[0]);
        capture_thresh_image();
    }
    stack[0] = identify_colour_instructions(100);
    PWM_Val += 5;
    Arm_WriteCompare(PWM_Val);
    CyDelay(5000);
    capture_thresh_image();
    stack[1] = identify_colour_instructions(100);
    PWM_Val += 5;
    Arm_WriteCompare(PWM_Val);
    CyDelay(5000);
    capture_thresh_image();
    stack[2] = identify_colour_instructions(100);
    sprintf(display[0],"1:%d 2:%d 3:%d",stack[0],stack[1],stack[2]);
    LCD_ClearDisplay();
    LCD_PosPrintString(1,0,display[0]);
    //LCD_PosPrintString(1,0,"Done... Really.");
}

void button_handle2()
{
    switch(current_display)
    {
        //Red U Up
    case 0:
        RED_U += 5;
        sprintf(display[1],"Red U: %d",RED_U);
        break;
    case 1:
        //Red U Down
        RED_U--;
        sprintf(display[1],"Red U: %d",RED_U);
        break;
    case 2:
        //RED V UP
        RED_V += 5;
        sprintf(display[1],"Red V: %d",RED_V);
        break;
    case 3:
        //Red V Down
        RED_V--;
        sprintf(display[1],"Red V: %d",RED_V);
        break;
    case 4:
        //Green U Up
        GREEN_U += 5;
        sprintf(display[1],"Green U: %d",GREEN_U);
        break;
    case 5:
        //Green U Down
        GREEN_U--;
        sprintf(display[1],"Green U: %d",GREEN_U);
        break;
    case 6:
        //Green V Up
        GREEN_V += 5;
        sprintf(display[1],"Green V: %d",GREEN_V);
        break;
    case 7:
        //Green V Down
        GREEN_V--;
        sprintf(display[1],"Green V: %d",GREEN_V);
        break;
    case 8:
        //Blue U Up
        BLUE_U += 5;
        sprintf(display[1],"Blue U: %d",BLUE_U);
        break;
    case 9:
        //Green U Down
        BLUE_U--;
        sprintf(display[1],"Blue U: %d",BLUE_U);
        break;
    case 10:
        //Green V Up
        BLUE_V += 5;
        sprintf(display[1],"Blue V: %d",BLUE_V);
        break;
    case 11:
        //Green V Down
        BLUE_V--;
        sprintf(display[1],"Blue V: %d",BLUE_V);
        break;
    case 12:
        //Gain Up
        gain = Camera_ReadReg(0x00);
        gain += 5;
        Camera_WriteReg(0x00,gain);
        sprintf(display[1],"Gain: %d",gain);
        break;
    case 13:
        // Gain Down
        gain = Camera_ReadReg(0x00);
        gain--;
        Camera_WriteReg(0x00,gain);
        sprintf(display[1],"Gain: %d",gain);
        break;
    case 14:
        //BGain Up
        gain = Camera_ReadReg(0x01);
        gain += 5;
        Camera_WriteReg(0x01,gain);
        sprintf(display[1],"BGain: %d",gain);
        break;
    case 15:
        // BGain Down
        gain = Camera_ReadReg(0x01);
        gain--;
        Camera_WriteReg(0x01,gain);
        sprintf(display[1],"BGain: %d",gain);
        break;
    case 16:
        // RGain Up
        gain = Camera_ReadReg(0x02);
        gain += 5;
        Camera_WriteReg(0x02,gain);
        sprintf(display[1],"RGain: %d",gain);
        break;
    case 17:
        // RGain Down
        gain = Camera_ReadReg(0x02);
        gain--;
        Camera_WriteReg(0x02,gain);
        sprintf(display[1],"RGain: %d",gain);
        break;
    case 18:
        // Exposure Up
        exposure = Camera_ReadReg(0x10);
        exposure += 5;
        Camera_WriteReg(0x10,exposure);
        sprintf(display[1],"Exposure: %d",exposure);
        break;
    case 19:
        // Exposure Down
        exposure = Camera_ReadReg(0x10);
        exposure--;
        Camera_WriteReg(0x10,exposure);
        sprintf(display[1],"Exposure: %d",exposure);
        break;
    case 20:
        // Connectedness up
        connected++;
        sprintf(display[1],"Connect: %d",connected);
        break;
    case 21:
        connected--;
        sprintf(display[1],"Connect: %d",connected);
        break;
    case 22:
        centre_pixel--;
        sprintf(display[1],"Centre Pixel: %d",centre_pixel);
        break;
    case 23:
        centre_pixel++;
        sprintf(display[1],"Centre Pixel: %d",centre_pixel);
        break;
    }
    LCD_ClearDisplay();
    LCD_PosPrintString(1,0,display[1]);
}

void handle_menus()
{
    current_display = (current_display + 1)%24;
    switch(current_display)
    {
        //Red U Up
    case 0:
        sprintf(display[0],"Red U Up");
        break;
    case 1:
        //Red U Down
        sprintf(display[0],"Red U Down");
        break;
    case 2:
        //RED V UP
        sprintf(display[0],"Red V Up");
        break;
    case 3:
        //Red V Down
        sprintf(display[0],"Red V Down");
        break;
    case 4:
        //Green U Up
        sprintf(display[0],"Green U Up");
        break;
    case 5:
        //Green U Down
        sprintf(display[0],"Green U Down");
        break;
    case 6:
        //Green V Up
        sprintf(display[0],"Green V Up");
        break;
    case 7:
        //Green V Down
        sprintf(display[0],"Green V Down");
        break;
    case 8:
        //Blue U Up
        sprintf(display[0],"Blue U Up");
        break;
    case 9:
        //Green U Down
        sprintf(display[0],"Blue U Down");
        break;
    case 10:
        //Green V Up
        sprintf(display[0],"Blue V Up");
        break;
    case 11:
        //Green V Down
        sprintf(display[0],"Blue V Down");
        break;
    case 12:
        //Gain Up
        sprintf(display[0],"Gain Up");
        break;
    case 13:
        // Gain Down
        sprintf(display[0],"Gain Down");
        break;
    case 14:
        sprintf(display[0],"BGain Up");
        break;
    case 15:
        // BGain Down
        sprintf(display[0],"BGain Down");
        break;
    case 16:
        sprintf(display[0],"RGain Up");
        break;
    case 17:
        sprintf(display[0],"RGain Down");
        break;
    case 18:
        sprintf(display[0],"Exposure Up");
        break;
    case 19:
        sprintf(display[0],"Exposure Down");
        break;
    case 20:
        sprintf(display[0],"Connect Up");
        break;
    case 21:
        sprintf(display[0],"Connect Down");
        break;
    case 22:
        sprintf(display[0],"Center Left");
        break;
    case 23:
        sprintf(display[0],"Center Right");
        break;
    }
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,display[0]);
}
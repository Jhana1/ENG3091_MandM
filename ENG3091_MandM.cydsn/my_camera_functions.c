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
#include <my_camera_functions.h>
#include <blob_stats.h>


uint8 RED_U= 122;//116;
uint8 RED_V= 150;//140;//162;
uint8 GREEN_U= 130;//128;
uint8 GREEN_V= 120;//102;
uint8 BLUE_U= 140;//138;//162;
uint8 BLUE_V= 116;//124;//116;

extern blob *blobs;

void init_camera()
{
	Camera_Start();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Camera Actualy");
    Camera_WriteReg(0x1E,0b00000000); //Flip Image
    Camera_WriteReg(0x13,0b11100111); //Enable Auto Gain, WB, Exposure
    Camera_SyncFrame();
    LCD_PosPrintString(0,0,"Frame Sync Done");
	Camera_GetFrame(); //start frame capture
    LCD_PosPrintString(0,0,"Getting Frame!!");
	Camera_SyncFrame(); //wait until frame is fully captured before sending out over USB
    Camera_WriteReg(0x13,0b11100000);
	Camera_WriteReg(0x3F,0b00101111); // Edge Enhancement Factor and Threshold
    Camera_WriteReg(0x3E,0b00000011); // Edge Enhancement Control
    Camera_WriteReg(0x8C,0b10100000); // Denoise
}

void capture_image()
{
	Camera_SyncFrame();
	Camera_GetFrame();
	Camera_SyncFrame();
}

void capture_thresh_image()
{
	Camera_SyncFrame();
	Camera_GetFrame();
	Camera_SyncFrame();
	threshold_image();
	blob_detect();
}

void set_gain_exposure(int setting)
{
	switch(setting)
	{
		case 1:
			// Settings for Instructions
			Camera_WriteReg(0x10,65);
			Camera_WriteReg(0x00,60);
			break;
		case 2:
			// Settings for arena 1
			Camera_WriteReg(0x10,30);
			Camera_WriteReg(0x00,25);
			break;
		case 3:
			// Settings for arena 2
			Camera_WriteReg(0x10,48);
			Camera_WriteReg(0x00,25);
			break;
		default:
			Camera_WriteReg(0x10,0);
			Camera_WriteReg(0x10,0);
			break;
	}
}

    
    
uint8 PixelColour(uint8 x,uint8 y) //colour of pixel at (x,y)
{
    if(Camera_framebuffer[y][x][0]<RED_U   && Camera_framebuffer[y][x][2]>=RED_V)  return RED;
    if(Camera_framebuffer[y][x][0]<GREEN_U && Camera_framebuffer[y][x][2]<GREEN_V) return GREEN;
    if(Camera_framebuffer[y][x][0]>=BLUE_U && Camera_framebuffer[y][x][2]<BLUE_V)  return BLUE;
    return NONE;
}



//Camera_framebuffer[0][0] 
void threshold_image()
{
	uint8 locals[8];
	uint8 colours[4];
	uint8 pixel;
    int y, x, i;
    
    
    
	for(y = 0; y < 144; ++y)
	{
		for(x = 0; x < 88; ++x)
		{
            if(y == 0 || y == 143 || x == 0 || x == 87)
            {
                Camera_framebuffer[y][x][0] = 127;       
                Camera_framebuffer[y][x][2] = 127;
                Camera_framebuffer[y][x][1] = 0;
                Camera_framebuffer[y][x][3] = 0;
            }
            else
            {
			    locals[0] = PixelColour(x-1,y-1);
			    locals[1] = PixelColour(x-1,y);
			    locals[2] = PixelColour(x-1,y+1);
			    locals[3] = PixelColour(x,y-1);
			    locals[4] = PixelColour(x,y+1);
			    locals[5] = PixelColour(x+1,y-1);
			    locals[6] = PixelColour(x+1,y);
			    locals[7] = PixelColour(x+1,y+1);
			    for(i = 0; i < 8; ++i)
    			{
	    			colours[0] += locals[i] == NONE;
		    		colours[1] += locals[i] == RED;
			    	colours[2] += locals[i] == GREEN;
				    colours[3] += locals[i] == BLUE;
    			}
                Camera_framebuffer[y][x][1] = 127;
                Camera_framebuffer[y][x][3] = 127;
			    if(colours[1] >= 4)
			    {
				    pixel = RED;
				    Camera_framebuffer[y][x][0] = 0;
    				Camera_framebuffer[y][x][2] = 255;
                }
		    	else if(colours[2] >= 4)
    			{
	    			pixel = GREEN;
		    		Camera_framebuffer[y][x][0] = 0;
			    	Camera_framebuffer[y][x][2] = 0;
	    		}
			    else if(colours[3] >= 4)
			    {
    				pixel = BLUE;
	    			Camera_framebuffer[y][x][0] = 255;
		    		Camera_framebuffer[y][x][2] = 0;
			    }
    			else //if(colours[0] >= colours[1] && colours[0] >= colours[2] && colours[0] >= colours[3])
	    		{
		    		pixel = NONE;
			    	Camera_framebuffer[y][x][0] = 127;
				    Camera_framebuffer[y][x][2] = 127;
                    Camera_framebuffer[y][x][1] = 0;
                    Camera_framebuffer[y][x][3] = 0;
		    	}
			    for(i = 0; i < 8; ++i)
			    {
    				colours[i] = 0;
			    } 
            }
		}
	}
}


void clean_frame(int colour, float proportion, int row_limit)
{
    int y,x,count,index = 0;
    for(y = 0; y <= row_limit; y++)
    {
        count = 0;
        for(x = 0; x < 88; x++)
        {
            if(PixelColour(x,y) == colour)
            {
                count++;
            }
        }
        if(count >= proportion*88)
        {
            index = y;
        }
    }
    for(y = 0; y <= index; y++)
    {
        for(x = 0; x < 88; x++)
            {
                if(PixelColour(x,y) == colour)
                {
                    Camera_framebuffer[y][x][0] = 127;
			        Camera_framebuffer[y][x][2] = 127;
                    Camera_framebuffer[y][x][1] = 0;
                    Camera_framebuffer[y][x][3] = 0;
                }
            }
    }
}


int identify_colour_instructions(int size)
{
    int x;
    x = (blobs[0].size >= size) ? blobs[0].colour : -1;
    //PixelColour(88/2,144/2);
}

int identify_colour_gripper()
{
     return PixelColour(88/2,144);  
}


int PixelLuminence(int x, int y)
{
	return (Camera_framebuffer[y][x][1] > 127) && (Camera_framebuffer[y][x][3] > 127);
} 


void threshold_black()
{
	int y,x,k,i;
	for(y = 0; y < 144; y++)
	{
		for(x = 0; x < 88; x++)
		{
			k = 0;
			if(y == 0 || y == 143 || x == 0 || x == 143)
			{
				for(i = 0; i < 2; i++)
				{
					Camera_framebuffer[y][x][i] = 127;
                    Camera_framebuffer[y][x][i+1] = 255;
				}
            }
			else
            {
		    	k += PixelLuminence(x-1,y-1);
		    	k += PixelLuminence(x-1,y);
		    	k += PixelLuminence(x-1,y+1);
		    	k += PixelLuminence(x,y-1);
			   	k += PixelLuminence(x,y+1);
			   	k += PixelLuminence(x+1,y-1);
			   	k += PixelLuminence(x+1,y);
			   	k += PixelLuminence(x+1,y+1);
			}
			for(i = 0; i < 2; i++)
			{
                Camera_framebuffer[y][x][i] = 127;
				Camera_framebuffer[y][x][i+1] = 0;
			}
		}
	}
}
/* [] END OF FILE */

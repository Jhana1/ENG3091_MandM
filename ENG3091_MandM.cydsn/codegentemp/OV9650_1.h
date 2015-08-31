#ifndef OV9650_1_H
#define OV9650_1_H
#include <project.h>

//Framebuffer: holds a single image in UYVY format
//organised as 144 rows of 88 pixel pairs
//each pixel pair has 4 components: U, Y0, V, Y1
uint8 OV9650_1_framebuffer[144][88][4];

//Synchronise to rising edge of VSYNC
//ensures alignment of frame in memory
//this function is blocking
void OV9650_1_SyncFrame();

//Write a value to one of the camera's registers
void OV9650_1_WriteReg(const uint8 reg,const uint8 value);

//Read a value from one of the camera's registers
uint8 OV9650_1_ReadReg(const uint8 reg);

//Initialise the camera
void OV9650_1_Start();

//Start capturing a single frame into the framebuffer
//should be called while VSYNC is high
//this function is non-blocking
void OV9650_1_GetFrame();

//Continuously capture images into the framebuffer
//should be called while VSYNC is high
//this function is non-blocking
void OV9650_1_Stream();

//Stop continuous capture
//this function is non-blocking
void OV9650_1_StopStreaming();
#endif

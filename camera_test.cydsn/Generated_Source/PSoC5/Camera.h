#ifndef Camera_H
#define Camera_H
#include <project.h>

//Framebuffer: holds a single image in UYVY format
//organised as 144 rows of 88 pixel pairs
//each pixel pair has 4 components: U, Y0, V, Y1
uint8 Camera_framebuffer[144][88][4];

//Synchronise to rising edge of VSYNC
//ensures alignment of frame in memory
//this function is blocking
void Camera_SyncFrame();
//Write a value to one of the camera's registers
void Camera_WriteReg(const uint8 reg,const uint8 value);

//Read a value from one of the camera's registers
uint8 Camera_ReadReg(const uint8 reg);

//Initialise the camera
void Camera_Start();

//Start capturing a single frame into the framebuffer
//should be called while VSYNC is high
//this function is non-blocking
void Camera_GetFrame();

//Continuously capture images into the framebuffer
//should be called while VSYNC is high
//this function is non-blocking
void Camera_Stream();

//Stop continuous capture
//this function is non-blocking
void Camera_StopStreaming();
#endif

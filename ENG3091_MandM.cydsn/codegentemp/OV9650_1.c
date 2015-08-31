#include "OV9650_1.h"

extern const uint8 OV9650_1_settings[][2];
extern const uint8 OV9650_1_format[];
extern const uint8 OV9650_1_sxga[];
extern const uint8 OV9650_1_vga[];
extern const uint8 OV9650_1_qvga[];
extern const uint8 OV9650_1_cif[];
extern const uint8 OV9650_1_qcif[];

#define N_BUFFERS 16
#define BUFFER_SIZE 3168
static uint8 DMA_channel;
static uint8 DMA_TD[N_BUFFERS];

void OV9650_1_WriteReg(const uint8 reg,const uint8 value)
{
	while(OV9650_1_I2C_MasterSendStart(0x30,0)!=OV9650_1_I2C_MSTR_NO_ERROR);
    OV9650_1_I2C_MasterWriteByte(reg);
    OV9650_1_I2C_MasterWriteByte(value);
    OV9650_1_I2C_MasterSendStop();
}

uint8 OV9650_1_ReadReg(const uint8 reg)
{
	while(OV9650_1_I2C_MasterSendStart(0x30,0)!=OV9650_1_I2C_MSTR_NO_ERROR);
    OV9650_1_I2C_MasterWriteByte(reg);
    OV9650_1_I2C_MasterSendStop();
	
	while(OV9650_1_I2C_MasterSendStart(0x30,1)!=OV9650_1_I2C_MSTR_NO_ERROR);
    uint8 value=OV9650_1_I2C_MasterReadByte(OV9650_1_I2C_NAK_DATA);
    OV9650_1_I2C_MasterSendStop();
	return value;
}

void OV9650_1_SyncFrame()
{
	while(OV9650_1_VSYNC_Read());
	while(!OV9650_1_VSYNC_Read());
}

void OV9650_1_Start()
{
	OV9650_1_SIOD_SetDriveMode(OV9650_1_SIOD_DM_RES_UP); //turn on pull-up resistors on I2C pins
	OV9650_1_SIOC_SetDriveMode(OV9650_1_SIOC_DM_RES_UP);
	OV9650_1_I2C_Start();
	
	OV9650_1_WriteReg(0x12,0x80); //reset
	CyDelay(1);
	uint16 i;
	for(i=0;OV9650_1_settings[i][0]!=0xff;i++) OV9650_1_WriteReg(OV9650_1_settings[i][0],OV9650_1_settings[i][1]); //camera settings
	for(i=0;OV9650_1_format[i]!=0xff;i++) OV9650_1_WriteReg(OV9650_1_format[i],OV9650_1_qcif[i]); //qcif format (176x144)
	
	uint8 (*buffer)[BUFFER_SIZE]=(uint8(*)[BUFFER_SIZE])OV9650_1_framebuffer; //recast buffer for easier arithmetic
	DMA_channel=OV9650_1_DMA_DmaInitialize(1,1,HI16(CYDEV_PERIPH_BASE),HI16(CYDEV_SRAM_BASE)); //peripheral -> SRAM
	for(i=0;i<sizeof DMA_TD;i++) //set up TDs
	{
		DMA_TD[i]=CyDmaTdAllocate();
		CyDmaTdSetAddress(DMA_TD[i],LO16(OV9650_1_FIFO_dp__F0_REG),LO16((uint32)buffer[i]));
		if(i) CyDmaTdSetConfiguration(DMA_TD[i-1],BUFFER_SIZE,DMA_TD[i],TD_INC_DST_ADR);
	}
	CyDmaChPriority(DMA_channel,0); //ensure highest priority for DMA channel
}

static void DMA_Start()
{
	*(reg8*)OV9650_1_FIFO_dp__F0_REG;
	*(reg8*)OV9650_1_FIFO_dp__F0_REG;
	*(reg8*)OV9650_1_FIFO_dp__F0_REG;
	*(reg8*)OV9650_1_FIFO_dp__F0_REG; //clear fifo
	CyDmaClearPendingDrq(DMA_channel); //invalidate pending requests
	CyDmaChSetInitialTd(DMA_channel,DMA_TD[0]); //set initial TD
	CyDmaChEnable(DMA_channel,1); //enable channel (start streaming)
}

void OV9650_1_GetFrame()
{
	CyDmaTdSetConfiguration(DMA_TD[sizeof(DMA_TD)-1],BUFFER_SIZE,CY_DMA_DISABLE_TD,TD_INC_DST_ADR); //disable DMA channel after last TD completes
	DMA_Start();
}

void OV9650_1_Stream()
{
	CyDmaTdSetConfiguration(DMA_TD[sizeof(DMA_TD)-1],BUFFER_SIZE,DMA_TD[0],TD_INC_DST_ADR); //loop TDs
	DMA_Start();
}

void OV9650_1_StopStreaming()
{
	CyDmaChSetRequest(DMA_channel,CY_DMA_CPU_TERM_CHAIN);
}
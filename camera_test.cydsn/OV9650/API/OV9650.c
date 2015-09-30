#include "`$INSTANCE_NAME`.h"

extern const uint8 `$INSTANCE_NAME`_settings[][2];
extern const uint8 `$INSTANCE_NAME`_format[];
extern const uint8 `$INSTANCE_NAME`_sxga[];
extern const uint8 `$INSTANCE_NAME`_vga[];
extern const uint8 `$INSTANCE_NAME`_qvga[];
extern const uint8 `$INSTANCE_NAME`_cif[];
extern const uint8 `$INSTANCE_NAME`_qcif[];

#define N_BUFFERS 16
#define BUFFER_SIZE 3168
static uint8 DMA_channel;
static uint8 DMA_TD[N_BUFFERS];

void `$INSTANCE_NAME`_WriteReg(const uint8 reg,const uint8 value)
{
	while(`$INSTANCE_NAME`_I2C_MasterSendStart(0x30,0)!=`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR);
    `$INSTANCE_NAME`_I2C_MasterWriteByte(reg);
    `$INSTANCE_NAME`_I2C_MasterWriteByte(value);
    `$INSTANCE_NAME`_I2C_MasterSendStop();
}

uint8 `$INSTANCE_NAME`_ReadReg(const uint8 reg)
{
	while(`$INSTANCE_NAME`_I2C_MasterSendStart(0x30,0)!=`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR);
    `$INSTANCE_NAME`_I2C_MasterWriteByte(reg);
    `$INSTANCE_NAME`_I2C_MasterSendStop();
	
	while(`$INSTANCE_NAME`_I2C_MasterSendStart(0x30,1)!=`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR);
    uint8 value=`$INSTANCE_NAME`_I2C_MasterReadByte(`$INSTANCE_NAME`_I2C_NAK_DATA);
    `$INSTANCE_NAME`_I2C_MasterSendStop();
	return value;
}

void `$INSTANCE_NAME`_SyncFrame()
{
	while(`$INSTANCE_NAME`_VSYNC_Read());
	while(!`$INSTANCE_NAME`_VSYNC_Read());
}

void `$INSTANCE_NAME`_Start()
{
	`$INSTANCE_NAME`_SIOD_SetDriveMode(`$INSTANCE_NAME`_SIOD_DM_RES_UP); //turn on pull-up resistors on I2C pins
	`$INSTANCE_NAME`_SIOC_SetDriveMode(`$INSTANCE_NAME`_SIOC_DM_RES_UP);
	`$INSTANCE_NAME`_I2C_Start();
	
	`$INSTANCE_NAME`_WriteReg(0x12,0x80); //reset
	CyDelay(1);
	uint16 i;
	for(i=0;`$INSTANCE_NAME`_settings[i][0]!=0xff;i++) `$INSTANCE_NAME`_WriteReg(`$INSTANCE_NAME`_settings[i][0],`$INSTANCE_NAME`_settings[i][1]); //camera settings
	for(i=0;`$INSTANCE_NAME`_format[i]!=0xff;i++) `$INSTANCE_NAME`_WriteReg(`$INSTANCE_NAME`_format[i],`$INSTANCE_NAME`_qcif[i]); //qcif format (176x144)
	
	uint8 (*buffer)[BUFFER_SIZE]=(uint8(*)[BUFFER_SIZE])`$INSTANCE_NAME`_framebuffer; //recast buffer for easier arithmetic
	DMA_channel=`$INSTANCE_NAME`_DMA_DmaInitialize(1,1,HI16(CYDEV_PERIPH_BASE),HI16(CYDEV_SRAM_BASE)); //peripheral -> SRAM
	for(i=0;i<sizeof DMA_TD;i++) //set up TDs
	{
		DMA_TD[i]=CyDmaTdAllocate();
		CyDmaTdSetAddress(DMA_TD[i],LO16(`$INSTANCE_NAME`_FIFO_dp__F0_REG),LO16((uint32)buffer[i]));
		if(i) CyDmaTdSetConfiguration(DMA_TD[i-1],BUFFER_SIZE,DMA_TD[i],TD_INC_DST_ADR);
	}
	CyDmaChPriority(DMA_channel,0); //ensure highest priority for DMA channel
}

static void DMA_Start()
{
	*(reg8*)`$INSTANCE_NAME`_FIFO_dp__F0_REG;
	*(reg8*)`$INSTANCE_NAME`_FIFO_dp__F0_REG;
	*(reg8*)`$INSTANCE_NAME`_FIFO_dp__F0_REG;
	*(reg8*)`$INSTANCE_NAME`_FIFO_dp__F0_REG; //clear fifo
	CyDmaClearPendingDrq(DMA_channel); //invalidate pending requests
	CyDmaChSetInitialTd(DMA_channel,DMA_TD[0]); //set initial TD
	CyDmaChEnable(DMA_channel,1); //enable channel (start streaming)
}

void `$INSTANCE_NAME`_GetFrame()
{
	CyDmaTdSetConfiguration(DMA_TD[sizeof(DMA_TD)-1],BUFFER_SIZE,CY_DMA_DISABLE_TD,TD_INC_DST_ADR); //disable DMA channel after last TD completes
	DMA_Start();
}

void `$INSTANCE_NAME`_Stream()
{
	CyDmaTdSetConfiguration(DMA_TD[sizeof(DMA_TD)-1],BUFFER_SIZE,DMA_TD[0],TD_INC_DST_ADR); //loop TDs
	DMA_Start();
}

void `$INSTANCE_NAME`_StopStreaming()
{
	CyDmaChSetRequest(DMA_channel,CY_DMA_CPU_TERM_CHAIN);
}
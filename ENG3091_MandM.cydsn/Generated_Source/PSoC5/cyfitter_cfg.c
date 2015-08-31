/*******************************************************************************
* FILENAME: cyfitter_cfg.c
* 
* PSoC Creator  3.2
*
* DESCRIPTION:
* This file contains device initialization code.
* Except for the user defined sections in CyClockStartupError(), this file should not be modified.
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2015 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "cyfitter_cfg.h"

#define CY_NEED_CYCLOCKSTARTUPERROR 1


#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CYPACKED 
    #define CYPACKED_ATTR __attribute__ ((packed))
    #define CYALIGNED __attribute__ ((aligned))
    #define CY_CFG_UNUSED __attribute__ ((unused))
    #define CY_CFG_SECTION __attribute__ ((section(".psocinit")))
    
    #if defined(__ARMCC_VERSION)
        #define CY_CFG_MEMORY_BARRIER() __memory_changed()
    #else
        #define CY_CFG_MEMORY_BARRIER() __sync_synchronize()
    #endif
    
#elif defined(__ICCARM__)
    #include <intrinsics.h>

    #define CYPACKED __packed
    #define CYPACKED_ATTR 
    #define CYALIGNED _Pragma("data_alignment=4")
    #define CY_CFG_UNUSED _Pragma("diag_suppress=Pe177")
    #define CY_CFG_SECTION _Pragma("location=\".psocinit\"")
    
    #define CY_CFG_MEMORY_BARRIER() __DMB()
    
#else
    #error Unsupported toolchain
#endif


CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n);
CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n)
{
	(void)memset(s, 0, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}



/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u

#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* `#START CyClockStartupError` */

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

    /* `#END` */

    /* If nothing else, stop here since the clocks have not started         */
    /* correctly.                                                           */
    while(1) {}
}
#endif

#define CY_CFG_BASE_ADDR_COUNT 35u
CYPACKED typedef struct
{
	uint8 offset;
	uint8 value;
} CYPACKED_ATTR cy_cfg_addrvalue_t;



/*******************************************************************************
* Function Name: cfg_write_bytes32
********************************************************************************
* Summary:
*  This function is used for setting up the chip configuration areas that
*  contain relatively sparse data.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[]);
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[])
{
	/* For 32-bit little-endian architectures */
	uint32 i, j = 0u;
	for (i = 0u; i < CY_CFG_BASE_ADDR_COUNT; i++)
	{
		uint32 baseAddr = addr_table[i];
		uint8 count = (uint8)baseAddr;
		baseAddr &= 0xFFFFFF00u;
		while (count != 0u)
		{
			CY_SET_XTND_REG8((void CYFAR *)(baseAddr + data_table[j].offset), data_table[j].value);
			j++;
			count--;
		}
	}
}

/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*  Performs the initialization of all of the clocks in the device based on the
*  settings in the Clock tab of the DWR.  This includes enabling the requested
*  clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void ClockSetup(void);
static void ClockSetup(void)
{
	uint32 timeout;
	uint8 pllLock;


	/* Configure Digital Clocks based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG0_CFG0), 0x0000u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_DCFG0_CFG0 + 0x2u), 0x58u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG1_CFG0), 0x0001u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_DCFG1_CFG0 + 0x2u), 0x18u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG2_CFG0), 0x0257u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_DCFG2_CFG0 + 0x2u), 0x18u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG3_CFG0), 0x0257u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_DCFG3_CFG0 + 0x2u), 0x18u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG4_CFG0), 0x0257u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_DCFG4_CFG0 + 0x2u), 0x18u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG5_CFG0), 0x095Fu);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_DCFG5_CFG0 + 0x2u), 0x18u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_DCFG6_CFG0), 0x095Fu);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_DCFG6_CFG0 + 0x2u), 0x18u);

	/* Configure ILO based on settings from Clock DWR */
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_SLOWCLK_ILO_CR0), 0x06u);

	/* Configure IMO based on settings from Clock DWR */
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_FASTCLK_IMO_CR), 0x52u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_IMO_TR1), (CY_GET_XTND_REG8((void CYFAR *)CYREG_FLSHID_CUST_TABLES_IMO_USB)));

	/* Configure PLL based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_FASTCLK_PLL_P), 0x0708u);
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_FASTCLK_PLL_CFG0), 0x1251u);
	/* Wait up to 250us for the PLL to lock */
	pllLock = 0u;
	for (timeout = 250u / 10u; (timeout > 0u) && (pllLock != 0x03u); timeout--)
	{ 
		pllLock = 0x03u & ((uint8)((uint8)pllLock << 1) | ((CY_GET_XTND_REG8((void CYFAR *)CYREG_FASTCLK_PLL_SR) & 0x01u) >> 0));
		CyDelayCycles(10u * 48u); /* Delay 10us based on 48MHz clock */
	}
	/* If we ran out of time the PLL didn't lock so go to the error function */
	if (timeout == 0u)
	{
		CyClockStartupError(CYCLOCKSTART_PLL_ERROR);
	}

	/* Configure Bus/Master Clock based on settings from Clock DWR */
	CY_SET_XTND_REG16((void CYFAR *)(CYREG_CLKDIST_MSTR0), 0x0100u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_MSTR0), 0x07u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_BCFG0), 0x00u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_BCFG2), 0x48u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_MSTR0), 0x00u);

	/* Configure USB Clock based on settings from Clock DWR */
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_UCFG), 0x00u);
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CLKDIST_LD), 0x02u);

	CY_SET_XTND_REG8((void CYFAR *)(CYREG_PM_ACT_CFG2), ((CY_GET_XTND_REG8((void CYFAR *)CYREG_PM_ACT_CFG2) | 0x7Fu)));
}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
	uint8 bg_xover_inl_trim = CY_GET_XTND_REG8((void CYFAR *)(CYREG_FLSHID_MFG_CFG_BG_XOVER_INL_TRIM + 1u));
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_BG_DFT0), (bg_xover_inl_trim & 0x07u));
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_BG_DFT1), ((bg_xover_inl_trim >> 4) & 0x0Fu));
	CY_SET_XTND_REG8((void CYFAR *)CYREG_PUMP_CR0, 0x44u);
}


/*******************************************************************************
* Function Name: SetAnalogRoutingPumps
********************************************************************************
*
* Summary:
* Enables or disables the analog pumps feeding analog routing switches.
* Intended to be called at startup, based on the Vdda system configuration;
* may be called during operation when the user informs us that the Vdda voltage
* crossed the pump threshold.
*
* Parameters:
*  enabled - 1 to enable the pumps, 0 to disable the pumps
*
* Return:
*  void
*
*******************************************************************************/
void SetAnalogRoutingPumps(uint8 enabled)
{
	uint8 regValue = CY_GET_XTND_REG8((void CYFAR *)CYREG_PUMP_CR0);
	if (enabled != 0u)
	{
		regValue |= 0x00u;
	}
	else
	{
		regValue &= (uint8)~0x00u;
	}
	CY_SET_XTND_REG8((void CYFAR *)CYREG_PUMP_CR0, regValue);
}

#define CY_AMUX_UNUSED CYREG_BOOST_SR


/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:  
*   void
*
* Return:
*   void
*
*******************************************************************************/

void cyfitter_cfg(void)
{
	/* IOPINS0_0 Address: CYREG_PRT0_DR Size (bytes): 10 */
	static const uint8 CYCODE BS_IOPINS0_0_VAL[] = {
		0x03u, 0x00u, 0x00u, 0xE0u, 0xE3u, 0x00u, 0xE0u, 0x00u, 0x00u, 0x00u};

	/* IOPINS0_7 Address: CYREG_PRT12_DR Size (bytes): 10 */
	static const uint8 CYCODE BS_IOPINS0_7_VAL[] = {
		0x03u, 0x00u, 0x80u, 0x2Cu, 0xAFu, 0x00u, 0x2Cu, 0x00u, 0x00u, 0x00u};

	/* IOPINS0_8 Address: CYREG_PRT15_DR Size (bytes): 10 */
	static const uint8 CYCODE BS_IOPINS0_8_VAL[] = {
		0x00u, 0x00u, 0x20u, 0x18u, 0x18u, 0x00u, 0x18u, 0x00u, 0xC0u, 0x00u};

	/* IOPINS0_2 Address: CYREG_PRT2_DR Size (bytes): 10 */
	static const uint8 CYCODE BS_IOPINS0_2_VAL[] = {
		0x30u, 0x00u, 0x05u, 0x00u, 0x30u, 0x00u, 0x30u, 0x00u, 0x00u, 0x00u};

	/* IOPINS0_4 Address: CYREG_PRT4_DM0 Size (bytes): 8 */
	static const uint8 CYCODE BS_IOPINS0_4_VAL[] = {
		0xF0u, 0x03u, 0x03u, 0x00u, 0x03u, 0x00u, 0x00u, 0x01u};

	/* IOPINS0_5 Address: CYREG_PRT5_DM0 Size (bytes): 8 */
	static const uint8 CYCODE BS_IOPINS0_5_VAL[] = {
		0xD0u, 0xA3u, 0x73u, 0x00u, 0x82u, 0x00u, 0x00u, 0x00u};

	/* IOPINS0_6 Address: CYREG_PRT6_DM0 Size (bytes): 8 */
	static const uint8 CYCODE BS_IOPINS0_6_VAL[] = {
		0x1Fu, 0xF0u, 0xE0u, 0x00u, 0x10u, 0x00u, 0x00u, 0x00u};

#ifdef CYGlobalIntDisable
	/* Disable interrupts by default. Let user enable if/when they want. */
	CYGlobalIntDisable
#endif

	{
		static const uint32 CYCODE cy_cfg_addr_table[] = {
			0x40004503u, /* Base address: 0x40004500 Count: 3 */
			0x40004F08u, /* Base address: 0x40004F00 Count: 8 */
			0x4000520Eu, /* Base address: 0x40005200 Count: 14 */
			0x40006401u, /* Base address: 0x40006400 Count: 1 */
			0x40010103u, /* Base address: 0x40010100 Count: 3 */
			0x40010304u, /* Base address: 0x40010300 Count: 4 */
			0x40010413u, /* Base address: 0x40010400 Count: 19 */
			0x4001050Eu, /* Base address: 0x40010500 Count: 14 */
			0x40010632u, /* Base address: 0x40010600 Count: 50 */
			0x40010718u, /* Base address: 0x40010700 Count: 24 */
			0x40010907u, /* Base address: 0x40010900 Count: 7 */
			0x40010B03u, /* Base address: 0x40010B00 Count: 3 */
			0x40010C04u, /* Base address: 0x40010C00 Count: 4 */
			0x40010D0Au, /* Base address: 0x40010D00 Count: 10 */
			0x40010E13u, /* Base address: 0x40010E00 Count: 19 */
			0x40010F16u, /* Base address: 0x40010F00 Count: 22 */
			0x40011503u, /* Base address: 0x40011500 Count: 3 */
			0x40011704u, /* Base address: 0x40011700 Count: 4 */
			0x40011905u, /* Base address: 0x40011900 Count: 5 */
			0x40011A05u, /* Base address: 0x40011A00 Count: 5 */
			0x40011B0Au, /* Base address: 0x40011B00 Count: 10 */
			0x40014011u, /* Base address: 0x40014000 Count: 17 */
			0x40014112u, /* Base address: 0x40014100 Count: 18 */
			0x40014219u, /* Base address: 0x40014200 Count: 25 */
			0x40014319u, /* Base address: 0x40014300 Count: 25 */
			0x4001440Au, /* Base address: 0x40014400 Count: 10 */
			0x40014511u, /* Base address: 0x40014500 Count: 17 */
			0x40014608u, /* Base address: 0x40014600 Count: 8 */
			0x4001470Eu, /* Base address: 0x40014700 Count: 14 */
			0x4001480Eu, /* Base address: 0x40014800 Count: 14 */
			0x4001490Bu, /* Base address: 0x40014900 Count: 11 */
			0x40014C13u, /* Base address: 0x40014C00 Count: 19 */
			0x40014D0Eu, /* Base address: 0x40014D00 Count: 14 */
			0x40015003u, /* Base address: 0x40015000 Count: 3 */
			0x40015104u, /* Base address: 0x40015100 Count: 4 */
		};

		static const cy_cfg_addrvalue_t CYCODE cy_cfg_data_table[] = {
			{0x00u, 0x02u},
			{0x60u, 0x02u},
			{0x7Eu, 0x02u},
			{0x01u, 0x10u},
			{0x0Au, 0x4Bu},
			{0x0Du, 0x30u},
			{0x16u, 0x4Bu},
			{0x19u, 0x40u},
			{0x22u, 0x4Bu},
			{0x25u, 0x20u},
			{0x2Eu, 0x4Bu},
			{0x00u, 0x40u},
			{0x01u, 0xC0u},
			{0x04u, 0x03u},
			{0x11u, 0x20u},
			{0x14u, 0x30u},
			{0x20u, 0x03u},
			{0x21u, 0x02u},
			{0x28u, 0x02u},
			{0x29u, 0x80u},
			{0x30u, 0x10u},
			{0x31u, 0x10u},
			{0x78u, 0x08u},
			{0x79u, 0x18u},
			{0x7Cu, 0x40u},
			{0x87u, 0x0Du},
			{0x81u, 0x08u},
			{0xE0u, 0x80u},
			{0xE2u, 0x05u},
			{0xA1u, 0x08u},
			{0xE8u, 0x05u},
			{0xEAu, 0x02u},
			{0xECu, 0x08u},
			{0xC0u, 0x34u},
			{0xC9u, 0xFFu},
			{0xCAu, 0xFFu},
			{0xCBu, 0xFFu},
			{0xCFu, 0x01u},
			{0xD0u, 0x18u},
			{0xDAu, 0x04u},
			{0xDBu, 0x04u},
			{0xDDu, 0x06u},
			{0xDFu, 0x01u},
			{0xE0u, 0x40u},
			{0xE2u, 0x40u},
			{0xE4u, 0x40u},
			{0xE5u, 0x40u},
			{0xE6u, 0x80u},
			{0xE8u, 0x80u},
			{0xEAu, 0x80u},
			{0xECu, 0x80u},
			{0xEEu, 0x80u},
			{0x45u, 0x08u},
			{0x46u, 0x40u},
			{0x6Du, 0x10u},
			{0x6Fu, 0x91u},
			{0x75u, 0x40u},
			{0x77u, 0x04u},
			{0x83u, 0x04u},
			{0x89u, 0x40u},
			{0x8Fu, 0x80u},
			{0x95u, 0x10u},
			{0xA1u, 0x08u},
			{0xADu, 0x10u},
			{0xD0u, 0xC0u},
			{0xE2u, 0xC0u},
			{0x40u, 0x34u},
			{0x49u, 0xFFu},
			{0x4Au, 0xFFu},
			{0x4Bu, 0xFFu},
			{0x4Du, 0x83u},
			{0x4Eu, 0x03u},
			{0x4Fu, 0x01u},
			{0x50u, 0x18u},
			{0x5Au, 0x04u},
			{0x5Du, 0x06u},
			{0x5Fu, 0x01u},
			{0x60u, 0x40u},
			{0x62u, 0x40u},
			{0x64u, 0x40u},
			{0x65u, 0x40u},
			{0x66u, 0x80u},
			{0x68u, 0x80u},
			{0x6Au, 0x80u},
			{0x6Cu, 0x80u},
			{0x6Eu, 0x80u},
			{0x82u, 0x01u},
			{0x96u, 0x01u},
			{0xB6u, 0x01u},
			{0xBEu, 0x40u},
			{0xC0u, 0x31u},
			{0xC5u, 0xECu},
			{0xC6u, 0x02u},
			{0xC8u, 0x07u},
			{0xC9u, 0xFFu},
			{0xCAu, 0xFFu},
			{0xCBu, 0xFFu},
			{0xCDu, 0x83u},
			{0xCEu, 0x03u},
			{0xCFu, 0x01u},
			{0xD0u, 0x18u},
			{0xD4u, 0x01u},
			{0xD8u, 0x04u},
			{0xDAu, 0x04u},
			{0xDBu, 0x04u},
			{0xDDu, 0x66u},
			{0xDFu, 0x01u},
			{0xE0u, 0x40u},
			{0xE2u, 0x40u},
			{0xE4u, 0x40u},
			{0xE5u, 0x40u},
			{0xE6u, 0x80u},
			{0xE8u, 0x80u},
			{0xEAu, 0x80u},
			{0xECu, 0x80u},
			{0xEEu, 0x80u},
			{0x02u, 0x40u},
			{0x09u, 0x08u},
			{0x19u, 0x40u},
			{0x41u, 0x08u},
			{0x43u, 0x80u},
			{0x45u, 0x08u},
			{0x46u, 0x40u},
			{0x49u, 0x05u},
			{0x52u, 0x40u},
			{0x53u, 0x80u},
			{0x59u, 0x45u},
			{0x9Eu, 0x40u},
			{0xA1u, 0x08u},
			{0xAFu, 0x01u},
			{0xB7u, 0x10u},
			{0xC0u, 0x08u},
			{0xC2u, 0x04u},
			{0xD0u, 0xCAu},
			{0xD6u, 0x0Bu},
			{0xE0u, 0x80u},
			{0xE4u, 0x01u},
			{0xE8u, 0x04u},
			{0xECu, 0x08u},
			{0xEEu, 0x42u},
			{0xA2u, 0x08u},
			{0xAAu, 0x08u},
			{0xADu, 0x80u},
			{0xAFu, 0x20u},
			{0xB5u, 0x02u},
			{0xE0u, 0x80u},
			{0xE4u, 0x01u},
			{0xA1u, 0x80u},
			{0xA5u, 0x02u},
			{0xA7u, 0x20u},
			{0x38u, 0x80u},
			{0x3Eu, 0x40u},
			{0x58u, 0x04u},
			{0x5Fu, 0x01u},
			{0x1Du, 0x80u},
			{0xA5u, 0x02u},
			{0xA7u, 0x20u},
			{0xABu, 0x14u},
			{0xACu, 0x40u},
			{0xAEu, 0x02u},
			{0xAFu, 0x08u},
			{0xB1u, 0xC0u},
			{0xB4u, 0x20u},
			{0xEEu, 0x02u},
			{0x42u, 0x03u},
			{0x47u, 0xE0u},
			{0x48u, 0x20u},
			{0x49u, 0xFFu},
			{0x4Au, 0xFFu},
			{0x4Bu, 0xFFu},
			{0x4Fu, 0x83u},
			{0x5Au, 0x04u},
			{0x5Bu, 0x04u},
			{0x5Du, 0x08u},
			{0x5Fu, 0x21u},
			{0xAFu, 0x01u},
			{0xB1u, 0x01u},
			{0xD2u, 0x80u},
			{0xD9u, 0x04u},
			{0xDBu, 0x04u},
			{0xDCu, 0x80u},
			{0xDDu, 0x60u},
			{0xDFu, 0x21u},
			{0x26u, 0x02u},
			{0x2Du, 0x80u},
			{0x43u, 0x08u},
			{0x52u, 0x01u},
			{0x58u, 0x40u},
			{0x59u, 0x02u},
			{0x5Bu, 0x14u},
			{0x60u, 0x28u},
			{0x61u, 0x42u},
			{0x76u, 0x80u},
			{0x7Au, 0x20u},
			{0x7Fu, 0x20u},
			{0x82u, 0x81u},
			{0x89u, 0x02u},
			{0x8Cu, 0x08u},
			{0x8Eu, 0x20u},
			{0xCAu, 0x10u},
			{0xD0u, 0x02u},
			{0xD6u, 0x0Fu},
			{0xD8u, 0x0Fu},
			{0xDEu, 0x42u},
			{0xE0u, 0x80u},
			{0xE2u, 0x01u},
			{0xE4u, 0x04u},
			{0xEAu, 0x01u},
			{0xE4u, 0x80u},
			{0xE8u, 0x10u},
			{0xEAu, 0x02u},
			{0xEEu, 0x0Au},
			{0xA2u, 0x08u},
			{0xE4u, 0x80u},
			{0xE8u, 0x10u},
			{0xEAu, 0x02u},
			{0xEEu, 0x0Au},
			{0x2Eu, 0x01u},
			{0x36u, 0x01u},
			{0x58u, 0x04u},
			{0x5Cu, 0x08u},
			{0x5Fu, 0x11u},
			{0x10u, 0x02u},
			{0x18u, 0x01u},
			{0x7Au, 0x08u},
			{0x80u, 0x01u},
			{0x88u, 0x02u},
			{0xA2u, 0x08u},
			{0xC4u, 0x01u},
			{0xDEu, 0x04u},
			{0xE4u, 0x04u},
			{0xEAu, 0x01u},
			{0x0Au, 0x18u},
			{0x0Cu, 0x40u},
			{0x0Eu, 0x40u},
			{0x33u, 0x81u},
			{0x36u, 0x40u},
			{0x37u, 0x04u},
			{0x3Fu, 0x80u},
			{0x55u, 0x40u},
			{0x56u, 0x02u},
			{0x83u, 0x40u},
			{0x8Au, 0x04u},
			{0xC2u, 0xF0u},
			{0xCCu, 0xF0u},
			{0xCEu, 0x20u},
			{0xD4u, 0x40u},
			{0xD6u, 0x20u},
			{0xE2u, 0x20u},
			{0x30u, 0x20u},
			{0x60u, 0x08u},
			{0x61u, 0x80u},
			{0x66u, 0x20u},
			{0x9Eu, 0x02u},
			{0x9Fu, 0x05u},
			{0xA0u, 0x20u},
			{0xA5u, 0x40u},
			{0xA6u, 0x40u},
			{0xA7u, 0x80u},
			{0xAAu, 0x50u},
			{0xACu, 0x60u},
			{0xCCu, 0x10u},
			{0xD6u, 0x40u},
			{0xD8u, 0xC0u},
			{0xE8u, 0xA0u},
			{0xEAu, 0x40u},
			{0xECu, 0x10u},
			{0x10u, 0x80u},
			{0x12u, 0x80u},
			{0x3Eu, 0x10u},
			{0x53u, 0x20u},
			{0x58u, 0x02u},
			{0x5Cu, 0x02u},
			{0x63u, 0x40u},
			{0x67u, 0x40u},
			{0x83u, 0x20u},
			{0x8Bu, 0x20u},
			{0x8Cu, 0x08u},
			{0x9Cu, 0x08u},
			{0x9Eu, 0x20u},
			{0x9Fu, 0x05u},
			{0xA5u, 0xC0u},
			{0xA6u, 0x40u},
			{0xA7u, 0x80u},
			{0xAEu, 0x02u},
			{0xC4u, 0x10u},
			{0xCEu, 0x20u},
			{0xD4u, 0x20u},
			{0xD6u, 0xC0u},
			{0xD8u, 0xC0u},
			{0xE2u, 0x80u},
			{0xEEu, 0x10u},
			{0x18u, 0x10u},
			{0x19u, 0x04u},
			{0x1Bu, 0x20u},
			{0x1Du, 0x80u},
			{0x1Eu, 0x20u},
			{0x81u, 0x04u},
			{0x8Au, 0x10u},
			{0x96u, 0x10u},
			{0x9Bu, 0x20u},
			{0x9Fu, 0x05u},
			{0xA5u, 0x80u},
			{0xA6u, 0x40u},
			{0xA7u, 0x80u},
			{0xA8u, 0x80u},
			{0xACu, 0x02u},
			{0xADu, 0x40u},
			{0xAEu, 0x80u},
			{0xAFu, 0x40u},
			{0xB6u, 0x20u},
			{0xC6u, 0xF0u},
			{0xE4u, 0x80u},
			{0xE8u, 0x20u},
			{0xEAu, 0x40u},
			{0xECu, 0x10u},
			{0xEEu, 0x40u},
			{0x01u, 0x42u},
			{0x04u, 0x48u},
			{0x08u, 0x04u},
			{0x65u, 0x20u},
			{0x8Cu, 0x04u},
			{0x8Du, 0x40u},
			{0xC0u, 0x0Fu},
			{0xC2u, 0x08u},
			{0xD8u, 0x01u},
			{0xE2u, 0x0Au},
			{0x00u, 0x08u},
			{0x08u, 0x01u},
			{0x0Du, 0x02u},
			{0x5Bu, 0x08u},
			{0x60u, 0x20u},
			{0x9Du, 0x20u},
			{0xA4u, 0x04u},
			{0xACu, 0x04u},
			{0xB0u, 0x04u},
			{0xB1u, 0x02u},
			{0xB4u, 0x40u},
			{0xC0u, 0x08u},
			{0xC2u, 0x0Cu},
			{0xD6u, 0x02u},
			{0xD8u, 0x02u},
			{0xEAu, 0x03u},
			{0xEEu, 0x01u},
			{0x04u, 0x01u},
			{0x98u, 0x01u},
			{0x9Cu, 0x20u},
			{0x9Du, 0x20u},
			{0x9Fu, 0x08u},
			{0xA1u, 0x10u},
			{0xB5u, 0x12u},
			{0xC0u, 0x04u},
			{0x08u, 0x08u},
			{0x0Bu, 0x04u},
			{0x0Fu, 0x40u},
			{0x81u, 0x20u},
			{0x89u, 0x02u},
			{0x98u, 0x01u},
			{0x9Cu, 0x20u},
			{0x9Du, 0x20u},
			{0x9Fu, 0x08u},
			{0xA1u, 0x10u},
			{0xB4u, 0x01u},
			{0xC2u, 0x0Eu},
			{0xE0u, 0x01u},
			{0xEEu, 0x08u},
			{0x25u, 0x20u},
			{0x5Fu, 0x20u},
			{0x89u, 0x20u},
			{0x96u, 0x10u},
			{0x9Bu, 0x20u},
			{0x9Fu, 0x04u},
			{0xA3u, 0x20u},
			{0xAEu, 0x40u},
			{0xAFu, 0x81u},
			{0xB4u, 0x10u},
			{0xC8u, 0x20u},
			{0xD6u, 0x20u},
			{0xEAu, 0x40u},
			{0xEEu, 0x50u},
			{0x21u, 0x40u},
			{0x79u, 0x80u},
			{0x83u, 0x24u},
			{0x9Fu, 0x04u},
			{0xA3u, 0x20u},
			{0xAAu, 0x10u},
			{0xC8u, 0x10u},
			{0xDCu, 0x80u},
			{0xE2u, 0x80u},
			{0xE4u, 0x20u},
			{0xEAu, 0x80u},
			{0x13u, 0x28u},
			{0x14u, 0x20u},
			{0x72u, 0x20u},
			{0x78u, 0x01u},
			{0x7Du, 0x20u},
			{0x8Au, 0x20u},
			{0x98u, 0x81u},
			{0x99u, 0x02u},
			{0x9Cu, 0x20u},
			{0x9Fu, 0x08u},
			{0xA1u, 0x10u},
			{0xACu, 0x08u},
			{0xAFu, 0x44u},
			{0xB4u, 0x80u},
			{0xC4u, 0x0Eu},
			{0xDCu, 0x01u},
			{0xDEu, 0x03u},
			{0xE4u, 0x01u},
			{0xE8u, 0x08u},
			{0x0Cu, 0x80u},
			{0x57u, 0x80u},
			{0x60u, 0x80u},
			{0x75u, 0x02u},
			{0x83u, 0x80u},
			{0x88u, 0x80u},
			{0x98u, 0x80u},
			{0x99u, 0x02u},
			{0xABu, 0x20u},
			{0xC2u, 0x01u},
			{0xD4u, 0x02u},
			{0xD8u, 0x02u},
			{0xDEu, 0x04u},
			{0xE6u, 0x01u},
			{0x00u, 0x40u},
			{0x0Au, 0x40u},
			{0x0Eu, 0x40u},
			{0x00u, 0xEAu},
			{0x01u, 0x0Cu},
			{0x03u, 0xC0u},
			{0x10u, 0x01u},
		};



		CYPACKED typedef struct {
			void CYFAR *address;
			uint16 size;
		} CYPACKED_ATTR cfg_memset_t;


		CYPACKED typedef struct {
			void CYFAR *dest;
			const void CYCODE *src;
			uint16 size;
		} CYPACKED_ATTR cfg_memcpy_t;

		static const cfg_memset_t CYCODE cfg_memset_list [] = {
			/* address, size */
			{(void CYFAR *)(CYREG_I2C_XCFG), 25u},
			{(void CYFAR *)(CYREG_TMR0_CFG0), 48u},
			{(void CYFAR *)(CYREG_PRT1_DR), 16u},
			{(void CYFAR *)(CYREG_PRT3_DR), 16u},
			{(void CYFAR *)(CYDEV_UCFG_B0_P0_U0_BASE), 4096u},
			{(void CYFAR *)(CYDEV_UCFG_B1_P2_U0_BASE), 2048u},
			{(void CYFAR *)(CYDEV_UCFG_DSI0_BASE), 2560u},
			{(void CYFAR *)(CYDEV_UCFG_DSI12_BASE), 512u},
			{(void CYFAR *)(CYREG_BCTL0_MDCLK_EN), 32u},
		};

		/* IOPORT_7 Address: CYDEV_PRTDSI_PRT12_BASE Size (bytes): 6 */
		static const uint8 CYCODE BS_IOPORT_7_VAL[] = {
			0x23u, 0x24u, 0x00u, 0x00u, 0x03u, 0x00u};

		static const cfg_memcpy_t CYCODE cfg_memcpy_list [] = {
			/* dest, src, size */
			{(void CYFAR *)(CYDEV_PRTDSI_PRT12_BASE), BS_IOPORT_7_VAL, 6u},
		};

		uint8 CYDATA i;

		/* Zero out critical memory blocks before beginning configuration */
		for (i = 0u; i < (sizeof(cfg_memset_list)/sizeof(cfg_memset_list[0])); i++)
		{
			const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
			CYMEMZERO(ms->address, (size_t)(uint32)(ms->size));
		}

		/* Copy device configuration data into registers */
		for (i = 0u; i < (sizeof(cfg_memcpy_list)/sizeof(cfg_memcpy_list[0])); i++)
		{
			const cfg_memcpy_t CYCODE * CYDATA mc = &cfg_memcpy_list[i];
			void * CYDATA destPtr = mc->dest;
			const void CYCODE * CYDATA srcPtr = mc->src;
			uint16 CYDATA numBytes = mc->size;
			CYCONFIGCPYCODE(destPtr, srcPtr, numBytes);
		}

		cfg_write_bytes32(cy_cfg_addr_table, cy_cfg_data_table);

		/* Perform normal device configuration. Order is not critical for these items. */
		CYMEMZERO((void CYFAR *)(CYREG_PHUB_CFGMEM0_CFG0), 4u);

		/* Enable digital routing */
		CY_SET_XTND_REG8((void CYFAR *)CYREG_BCTL0_BANK_CTL, CY_GET_XTND_REG8((void CYFAR *)CYREG_BCTL0_BANK_CTL) | 0x02u);
		CY_SET_XTND_REG8((void CYFAR *)CYREG_BCTL1_BANK_CTL, CY_GET_XTND_REG8((void CYFAR *)CYREG_BCTL1_BANK_CTL) | 0x02u);

		/* Enable UDB array */
		CY_SET_XTND_REG8((void CYFAR *)CYREG_PM_ACT_CFG0, CY_GET_XTND_REG8((void CYFAR *)CYREG_PM_ACT_CFG0) | 0x40u);
		CY_SET_XTND_REG8((void CYFAR *)CYREG_PM_AVAIL_CR2, CY_GET_XTND_REG8((void CYFAR *)CYREG_PM_AVAIL_CR2) | 0x10u);
	}


	/* Perform second pass device configuration. These items must be configured in specific order after the regular configuration is done. */
	CYCONFIGCPYCODE((void CYFAR *)(CYREG_PRT0_DR), (const void CYCODE *)(BS_IOPINS0_0_VAL), 10u);
	CYCONFIGCPYCODE((void CYFAR *)(CYREG_PRT12_DR), (const void CYCODE *)(BS_IOPINS0_7_VAL), 10u);
	CYCONFIGCPYCODE((void CYFAR *)(CYREG_PRT15_DR), (const void CYCODE *)(BS_IOPINS0_8_VAL), 10u);
	CYCONFIGCPYCODE((void CYFAR *)(CYREG_PRT2_DR), (const void CYCODE *)(BS_IOPINS0_2_VAL), 10u);
	CYCONFIGCPYCODE((void CYFAR *)(CYREG_PRT4_DM0), (const void CYCODE *)(BS_IOPINS0_4_VAL), 8u);
	CYCONFIGCPYCODE((void CYFAR *)(CYREG_PRT5_DM0), (const void CYCODE *)(BS_IOPINS0_5_VAL), 8u);
	CYCONFIGCPYCODE((void CYFAR *)(CYREG_PRT6_DM0), (const void CYCODE *)(BS_IOPINS0_6_VAL), 8u);
	/* Switch Boost to the precision bandgap reference from its internal reference */
	CY_SET_REG8((void CYXDATA *)CYREG_BOOST_CR2, (CY_GET_REG8((void CYXDATA *)CYREG_BOOST_CR2) | 0x08u));

	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CACHE_CC_CTL), (((CYDEV_INSTRUCT_CACHE_ENABLED) != 0) ? 0x61u : 0x60u));
	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();
	/* Set Flash Cycles based on newly configured 24.00MHz Bus Clock. */
	CY_SET_XTND_REG8((void CYFAR *)(CYREG_CACHE_CC_CTL), (((CYDEV_INSTRUCT_CACHE_ENABLED) != 0) ? 0x81u : 0x80u));

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

	/* Configure alternate active mode */
	CYCONFIGCPY((void CYFAR *)CYDEV_PM_STBY_BASE, (const void CYFAR *)CYDEV_PM_ACT_BASE, 14u);
}
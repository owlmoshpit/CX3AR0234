/*
## Cypress Image Sensor Routines for XXXX sensor (cyu3imagesensor.c)
## ===========================
##
##  Copyright Cypress Semiconductor Corporation, 2013,
##  All Rights Reserved
##  UNPUBLISHED, LICENSED SOFTWARE.
##
##  CONFIDENTIAL AND PROPRIETARY INFORMATION
##  WHICH IS THE PROPERTY OF CYPRESS.
##
##  Use of this file is governed
##  by the license agreement included in the file
##
##     <install>/license/license.txt
##
##  where <install> is the Cypress software
##  installation root directory path.
##
## ===========================
*/

#include <cyu3error.h>
#include <cyu3i2c.h>
#include "cyu3imagesensor.h"
#include <cyu3utils.h>
//#include "cycx3_imagesensor.h"

/*Uncomment below line to enable UART debug messages during Sensor configuration*/
#define SENSOR_DEBUG

/* Misc Macros; Fill the correct I2C addresses below */
#define SENSOR_I2C_READ_ADDRESS         (0x31)
#define SENSOR_I2C_WRITE_ADDRESS        (0x30)

/* Register Addresses */


/* Structure to store the Address/Value pair for each
 * register to be updated.
 */
 
typedef struct CySensorReg8
{
    uint16_t regAddr;
    uint8_t regValue;
} CySensorReg8_t;

typedef struct CySensorReg16
{
    uint16_t regAddr;
    uint16_t regValue;
} CySensorReg16_t;

typedef struct CySensorReg32
{
    uint16_t regAddr;
    uint32_t regValue;
} CySensorReg32_t;

/* Configuration Settings for Sensor Initialization.
 * These values are specific to the image sensor being used.
 */
CySensorReg16_t SENSOR_BaseConfigurationSettings [] =
{
		 {0x302A, 0x0008},               //VT_PIX_CLK_DIV = 5
					{0x302C, 0x0001},               //VT_SYS_CLK_DIV = 6
					{0x302E, 0x0009},               //PRE_PLL_CLK_DIV = 2
					{0x3030, 0x00B6},               //PLL_MULTIPLIER = 50
					{0x3036, 0x0008},               //OP_PIX_CLK_DIV = 10
					{0x3038, 0x0002},               //OP_SYS_CLK_DIV = 6
					{0x30B0, 0x0028},           	//DIGITAL_TEST, bits 0x4000 = 0
					{0x31B0, 0x0066},               //FRAME_PREAMBLE = 48
					{0x31B2, 0x004D},               //LINE_PREAMBLE = 44
					//pixel clock = 22.5 MHz = 44.4 ns
					{0x31B4, 0x4207},               //MIPI_TIMING_0 = 8516  //T_HS_PREPARE = 2 = 88.8
					{0x31B6, 0x31D2},               //MIPI_TIMING_1 = 4294  //T_HS_ZERO = 6 = 266.4
					{0x31B8, 0x704B},               //MIPI_TIMING_2 = 12359
					{0x31BA, 0x0209},               //MIPI_TIMING_3 = 259
					{0x31BC, 0x0B07},               //MIPI_TIMING_4 = 1283
					{0x3354, 0x002A},               //MIPI_CNTRL = 43
					//[Timing_settings]
					{0x301A, 0x2058},               //RESET_REGISTER = 8280
					{0x31AE, 0x0204},               //SERIAL_FORMAT = 516
					{0x3002, 0x0044},               //Y_ADDR_START = 248
					{0x3004, 0x0008},               //X_ADDR_START = 328
					{0x3006, 0x047B},               //Y_ADDR_END = 967
					{0x3008, 0x0787},               //X_ADDR_END = 1607
					{0x300A, 0x0456},               //FRAME_LENGTH_LINES = 736
					{0x300C, 0x0264},               //LINE_LENGTH_PCK = 1012
					{0x3012, 0x014E},               //COARSE_INTEGRATION_TIME = 22
					{0x31AC, 0x0808},               //DATA_FORMAT_BITS = 2570
					{0x306E, 0x9010},               //DATAPATH_SELECT = 36880
					{0x30A2, 0x0001},               //X_ODD_INC = 1
					{0x30A6, 0x0001},               //Y_ODD_INC = 1
					{0x3082, 0x0003},               //OPERATION_MODE_CTRL = 3
					{0x3040, 0x0000},               //READ_MODE = 0
					{0x31D0, 0x0000},               //COMPANDING = 0
					{0x301A, 0x205C},               //RESET_REGISTER = 8284

};

					
/* Image sensor Configuration settings for Format : RAW8 Resolution : Resolution1  1920 x 1080 @100fps video stream  */
CySensorReg16_t ar0234_RAW8_Resolution1ConfigurationSettings [] =
{


		//Num Register writes = 32

		    {0x302A, 0x0008},               //VT_PIX_CLK_DIV = 5
			{0x302C, 0x0001},               //VT_SYS_CLK_DIV = 6
			{0x302E, 0x0009},               //PRE_PLL_CLK_DIV = 2
			{0x3030, 0x00B6},               //PLL_MULTIPLIER = 50
			{0x3036, 0x0008},               //OP_PIX_CLK_DIV = 10
			{0x3038, 0x0002},               //OP_SYS_CLK_DIV = 6
			{0x30B0, 0x0028},           	//DIGITAL_TEST, bits 0x4000 = 0
			{0x31B0, 0x0066},               //FRAME_PREAMBLE = 48
			{0x31B2, 0x004D},               //LINE_PREAMBLE = 44
			//pixel clock = 22.5 MHz = 44.4 ns
			{0x31B4, 0x4207},               //MIPI_TIMING_0 = 8516  //T_HS_PREPARE = 2 = 88.8
			{0x31B6, 0x31D2},               //MIPI_TIMING_1 = 4294  //T_HS_ZERO = 6 = 266.4
			{0x31B8, 0x704B},               //MIPI_TIMING_2 = 12359
			{0x31BA, 0x0209},               //MIPI_TIMING_3 = 259
			{0x31BC, 0x0B07},               //MIPI_TIMING_4 = 1283
			{0x3354, 0x002A},               //MIPI_CNTRL = 43
			//[Timing_settings]
			{0x301A, 0x2058},               //RESET_REGISTER = 8280
			{0x31AE, 0x0204},               //SERIAL_FORMAT = 516
			{0x3002, 0x0044},               //Y_ADDR_START = 248
			{0x3004, 0x0008},               //X_ADDR_START = 328
			{0x3006, 0x047B},               //Y_ADDR_END = 967
			{0x3008, 0x0787},               //X_ADDR_END = 1607
			{0x300A, 0x0456},               //FRAME_LENGTH_LINES = 736
			{0x300C, 0x0264},               //LINE_LENGTH_PCK = 1012
			{0x3012, 0x014E},               //COARSE_INTEGRATION_TIME = 22
			{0x31AC, 0x0808},               //DATA_FORMAT_BITS = 2570
			{0x306E, 0x9010},               //DATAPATH_SELECT = 36880
			{0x30A2, 0x0001},               //X_ODD_INC = 1
			{0x30A6, 0x0001},               //Y_ODD_INC = 1
			{0x3082, 0x0003},               //OPERATION_MODE_CTRL = 3
			{0x3040, 0x0000},               //READ_MODE = 0
			{0x31D0, 0x0000},               //COMPANDING = 0
			{0x301A, 0x205C},               //RESET_REGISTER = 8284



};

/* Image sensor Configuration settings for Format : RAW8 Resolution : Resolution1  1280 x 720 @120fps video stream  */

CySensorReg16_t ar0234_RAW8_Resolution2ConfigurationSettings [] =
{


		//Num Register writes = 32

		    {0x302A, 0x0008},               //VT_PIX_CLK_DIV = 5
			{0x302C, 0x0001},               //VT_SYS_CLK_DIV = 6
			{0x302E, 0x0002},               //PRE_PLL_CLK_DIV = 2
			{0x3030, 0x0028},               //PLL_MULTIPLIER = 50
			{0x3036, 0x0008},               //OP_PIX_CLK_DIV = 10
			{0x3038, 0x0002},               //OP_SYS_CLK_DIV = 6
			{0x30B0, 0x0028},           	//DIGITAL_TEST, bits 0x4000 = 0
			{0x31B0, 0x0066},               //FRAME_PREAMBLE = 48
			{0x31B2, 0x004D},               //LINE_PREAMBLE = 44
			//pixel clock = 22.5 MHz = 44.4 ns
			{0x31B4, 0x4207},               //MIPI_TIMING_0 = 8516  //T_HS_PREPARE = 2 = 88.8
			{0x31B6, 0x31D2},               //MIPI_TIMING_1 = 4294  //T_HS_ZERO = 6 = 266.4
			{0x31B8, 0x704B},               //MIPI_TIMING_2 = 12359
			{0x31BA, 0x0209},               //MIPI_TIMING_3 = 259
			{0x31BC, 0x0B07},               //MIPI_TIMING_4 = 1283
			{0x3354, 0x002A},               //MIPI_CNTRL = 43
			//[Timing_settings]
			{0x301A, 0x2058},               //RESET_REGISTER = 8280
			{0x31AE, 0x0204},               //SERIAL_FORMAT = 516
			{0x3002, 0x00F8},               //Y_ADDR_START = 248
			{0x3004, 0x0148},               //X_ADDR_START = 328
			{0x3006, 0x03C7},               //Y_ADDR_END = 967
			{0x3008, 0x0647},               //X_ADDR_END = 1607
			{0x300A, 0x02E0},               //FRAME_LENGTH_LINES = 736
			{0x300C, 0x02F7},               //LINE_LENGTH_PCK = 1012
			{0x3012, 0x010A},               //COARSE_INTEGRATION_TIME = 22
			{0x31AC, 0x0808},               //DATA_FORMAT_BITS = 2570
			{0x306E, 0x9010},               //DATAPATH_SELECT = 36880
			{0x30A2, 0x0001},               //X_ODD_INC = 1
			{0x30A6, 0x0001},               //Y_ODD_INC = 1
			{0x3082, 0x0003},               //OPERATION_MODE_CTRL = 3
			{0x3040, 0x0000},               //READ_MODE = 0
			{0x31D0, 0x0000},               //COMPANDING = 0
			{0x301A, 0x205C},               //RESET_REGISTER = 8284



};
/* Image sensor Configuration settings for Format : RAW8 Resolution : Resolution1  640 x 480 @200fps video stream  */

CySensorReg16_t ar0234_RAW8_Resolution3ConfigurationSettings [] =
{


		//Num Register writes = 32

		    {0x302A, 0x0008},               //VT_PIX_CLK_DIV = 5
			{0x302C, 0x0001},               //VT_SYS_CLK_DIV = 6
			{0x302E, 0x0002},               //PRE_PLL_CLK_DIV = 2
			{0x3030, 0x0028},               //PLL_MULTIPLIER = 50
			{0x3036, 0x0008},               //OP_PIX_CLK_DIV = 10
			{0x3038, 0x0002},               //OP_SYS_CLK_DIV = 6
			{0x30B0, 0x0028},           	//DIGITAL_TEST, bits 0x4000 = 0
			{0x31B0, 0x0066},               //FRAME_PREAMBLE = 48
			{0x31B2, 0x004D},               //LINE_PREAMBLE = 44
			//pixel clock = 22.5 MHz = 44.4 ns
			{0x31B4, 0x4207},               //MIPI_TIMING_0 = 8516  //T_HS_PREPARE = 2 = 88.8
			{0x31B6, 0x31D2},               //MIPI_TIMING_1 = 4294  //T_HS_ZERO = 6 = 266.4
			{0x31B8, 0x704B},               //MIPI_TIMING_2 = 12359
			{0x31BA, 0x0209},               //MIPI_TIMING_3 = 259
			{0x31BC, 0x0B07},               //MIPI_TIMING_4 = 1283
			{0x3354, 0x002A},               //MIPI_CNTRL = 43
			//[Timing_settings]
			{0x301A, 0x2058},               //RESET_REGISTER = 8280
			{0x31AE, 0x0204},               //SERIAL_FORMAT = 516
			{0x3002, 0x0170},               //Y_ADDR_START = 248
			{0x3004, 0x0288},               //X_ADDR_START = 328
			{0x3006, 0x034F},               //Y_ADDR_END = 967
			{0x3008, 0x0507},               //X_ADDR_END = 1607
			{0x300A, 0x01F0},               //FRAME_LENGTH_LINES = 736
			{0x300C, 0x02A1},               //LINE_LENGTH_PCK = 1012
			{0x3012, 0x012C},               //COARSE_INTEGRATION_TIME = 22
			{0x31AC, 0x0808},               //DATA_FORMAT_BITS = 2570
			{0x306E, 0x9010},               //DATAPATH_SELECT = 36880
			{0x30A2, 0x0001},               //X_ODD_INC = 1
			{0x30A6, 0x0001},               //Y_ODD_INC = 1
			{0x3082, 0x0003},               //OPERATION_MODE_CTRL = 3
			{0x3040, 0x0000},               //READ_MODE = 0
			{0x31D0, 0x0000},               //COMPANDING = 0
			{0x301A, 0x205C},               //RESET_REGISTER = 8284



};

/* Image sensor Configuration settings for Format : RAW8 Resolution : Resolution1  640 x 480 @30 video stream  */

CySensorReg16_t ar0234_RAW8_Resolution4ConfigurationSettings [] =
{


		//Num Register writes = 32

		    {0x302A, 0x0008},               //VT_PIX_CLK_DIV = 5
			{0x302C, 0x0001},               //VT_SYS_CLK_DIV = 6
			{0x302E, 0x0002},               //PRE_PLL_CLK_DIV = 2
			{0x3030, 0x0028},               //PLL_MULTIPLIER = 50
			{0x3036, 0x0008},               //OP_PIX_CLK_DIV = 10
			{0x3038, 0x0002},               //OP_SYS_CLK_DIV = 6
			{0x30B0, 0x0028},           	//DIGITAL_TEST, bits 0x4000 = 0
			{0x31B0, 0x0066},               //FRAME_PREAMBLE = 48
			{0x31B2, 0x004D},               //LINE_PREAMBLE = 44
			//pixel clock = 22.5 MHz = 44.4 ns
			{0x31B4, 0x4207},               //MIPI_TIMING_0 = 8516  //T_HS_PREPARE = 2 = 88.8
			{0x31B6, 0x31D2},               //MIPI_TIMING_1 = 4294  //T_HS_ZERO = 6 = 266.4
			{0x31B8, 0x704B},               //MIPI_TIMING_2 = 12359
			{0x31BA, 0x0209},               //MIPI_TIMING_3 = 259
			{0x31BC, 0x0B07},               //MIPI_TIMING_4 = 1283
			{0x3354, 0x002A},               //MIPI_CNTRL = 43
			//[Timing_settings]
			{0x301A, 0x2058},               //RESET_REGISTER = 8280
			{0x31AE, 0x0204},               //SERIAL_FORMAT = 516
			{0x3002, 0x0170},               //Y_ADDR_START = 248
			{0x3004, 0x0288},               //X_ADDR_START = 328
			{0x3006, 0x034F},               //Y_ADDR_END = 967
			{0x3008, 0x0507},               //X_ADDR_END = 1607
			{0x300A, 0x01F0},               //FRAME_LENGTH_LINES = 736
			{0x300C, 0x0462},               //LINE_LENGTH_PCK = 1012
			{0x3012, 0x00B4},               //COARSE_INTEGRATION_TIME = 22
			{0x31AC, 0x0808},               //DATA_FORMAT_BITS = 2570
			{0x306E, 0x9010},               //DATAPATH_SELECT = 36880
			{0x30A2, 0x0001},               //X_ODD_INC = 1
			{0x30A6, 0x0001},               //Y_ODD_INC = 1
			{0x3082, 0x0003},               //OPERATION_MODE_CTRL = 3
			{0x3040, 0x0000},               //READ_MODE = 0
			{0x31D0, 0x0000},               //COMPANDING = 0
			{0x301A, 0x205C},               //RESET_REGISTER = 8284



};




/* Image sensor Configuration settings for Format : RAW8 Resolution : Resolution1  1920 x 1080 @15 video stream  */


CySensorReg16_t ar0234_RAW8_Resolution5ConfigurationSettings [] =
{


		//Num Register writes = 32

		    {0x302A, 0x0008},               //VT_PIX_CLK_DIV = 5
			{0x302C, 0x0001},               //VT_SYS_CLK_DIV = 6
			{0x302E, 0x0002},               //PRE_PLL_CLK_DIV = 2
			{0x3030, 0x0028},               //PLL_MULTIPLIER = 50
			{0x3036, 0x0008},               //OP_PIX_CLK_DIV = 10
			{0x3038, 0x0002},               //OP_SYS_CLK_DIV = 6
			{0x30B0, 0x0028},           	//DIGITAL_TEST, bits 0x4000 = 0
			{0x31B0, 0x0066},               //FRAME_PREAMBLE = 48
			{0x31B2, 0x004D},               //LINE_PREAMBLE = 44
			//pixel clock = 22.5 MHz = 44.4 ns
			{0x31B4, 0x4207},               //MIPI_TIMING_0 = 8516  //T_HS_PREPARE = 2 = 88.8
			{0x31B6, 0x31D2},               //MIPI_TIMING_1 = 4294  //T_HS_ZERO = 6 = 266.4
			{0x31B8, 0x704B},               //MIPI_TIMING_2 = 12359
			{0x31BA, 0x0209},               //MIPI_TIMING_3 = 259
			{0x31BC, 0x0B07},               //MIPI_TIMING_4 = 1283
			{0x3354, 0x002A},               //MIPI_CNTRL = 43
			//[Timing_settings]
			{0x301A, 0x2058},               //RESET_REGISTER = 8280
			{0x31AE, 0x0204},               //SERIAL_FORMAT = 516
			{0x3002, 0x0044},               //Y_ADDR_START = 248
			{0x3004, 0x0008},               //X_ADDR_START = 328
			{0x3006, 0x047B},               //Y_ADDR_END = 967
			{0x3008, 0x0787},               //X_ADDR_END = 1607
			{0x300A, 0x0448},               //FRAME_LENGTH_LINES = 736
			{0x300C, 0x0FF7},               //LINE_LENGTH_PCK = 1012
			{0x3012, 0x01EF},               //COARSE_INTEGRATION_TIME = 22
			{0x31AC, 0x0808},               //DATA_FORMAT_BITS = 2570
			{0x306E, 0x9010},               //DATAPATH_SELECT = 36880
			{0x30A2, 0x0001},               //X_ODD_INC = 1
			{0x30A6, 0x0001},               //Y_ODD_INC = 1
			{0x3082, 0x0003},               //OPERATION_MODE_CTRL = 3
			{0x3040, 0x0000},               //READ_MODE = 0
			{0x31D0, 0x0000},               //COMPANDING = 0
			{0x301A, 0x205C},               //RESET_REGISTER = 8284



};


/*
 * Function to read one or more 8-bit registers from the Image Sensor.
 */
CyU3PReturnStatus_t 
I2C_SensorRead(
		uint16_t regAddr, 
		uint8_t count, 
		uint8_t *buf)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    CyU3PI2cPreamble_t preamble;
    uint8_t cnt=0;

    for(cnt=0; cnt<3 ; cnt++)
    {
        preamble.buffer[1] = CY_U3P_GET_MSB (regAddr);
        preamble.buffer[2] = CY_U3P_GET_LSB (regAddr);
        preamble.buffer[3] = SENSOR_I2C_READ_ADDRESS; /* Slave address: Read operation */
        preamble.buffer[0] = SENSOR_I2C_WRITE_ADDRESS; /* Slave address: write operation */
        preamble.length = 4;
        preamble.ctrlMask = 0x0004;

        status = CyU3PI2cReceiveBytes (&preamble, buf, count,0);
        CyU3PThreadSleep(1);
        if (status == CY_U3P_SUCCESS)
        {
            break;
        }
#ifdef SENSOR_DEBUG
        else
            CyU3PDebugPrint(4,"\r\nImageSensorSensorRead Failed addr=0x%x",regAddr);
#endif
    }
    return status;
}
/*
 * Function to write one or more 8-bit registers on the Image Sensor.
 */
CyU3PReturnStatus_t
I2C_SensorWrite(
		uint16_t regAddr,
		uint16_t count, 
		uint8_t *buf)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    CyU3PI2cPreamble_t preamble;
    uint8_t cnt=0;

    for(cnt=0; cnt<3 ; cnt++)
    {
        preamble.buffer[1] = CY_U3P_GET_MSB (regAddr);
        preamble.buffer[2] = CY_U3P_GET_LSB (regAddr);
        preamble.buffer[0] = SENSOR_I2C_WRITE_ADDRESS; /* Slave address: write operation */
        preamble.length = 3;
        preamble.ctrlMask = 0x0000;

        status = CyU3PI2cTransmitBytes (&preamble, buf, count,0);
        CyU3PThreadSleep(1);
        if (status == CY_U3P_SUCCESS)
        {
            break;
        }
#ifdef SENSOR_DEBUG
        else
            CyU3PDebugPrint(4,"\r\nImageSensorSensorWrite Failed addr=0x%x",regAddr);
#endif
    }
    return status;
}

/*
 *Function to clear or set the field bits in a 8-bit register based on the fieldValue parameter.
 */
CyU3PReturnStatus_t 
SensorWriteRegisterField (
		uint16_t RegAddr, 
		uint8_t Field,
		CyBool_t FieldValue)
{
    uint8_t WRBuff;
    uint8_t RDBuff;
    uint8_t CamRegVal;

	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    status = I2C_SensorRead(RegAddr, 1, &RDBuff);
    CamRegVal = RDBuff;

    CamRegVal = ((CamRegVal & (~(Field)))| FieldValue);

    WRBuff= CamRegVal;
#ifdef SENSOR_DEBUG
    CyU3PDebugPrint(4,"\r\n0x%x = 0x%x\r\n",RegAddr,WRBuff);
#endif

    status = I2C_SensorWrite(RegAddr, 1, &WRBuff);
    
    return status;
}

/*
 * Function to initialize all 8-bit sensor registers associated with a specific configuration.
 */
CyU3PReturnStatus_t
Sensor_WriteConfigurationSettings_Reg8 (
        CySensorReg8_t *configSettings,
        uint16_t        configSettingsSize)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint16_t regCounter = 0;
    uint8_t  rwBuffer[2];

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint (4, "\r\nWriting Configuration Settings:");
#endif

    for (regCounter = 0; ((regCounter < configSettingsSize) && (status == CY_U3P_SUCCESS)); regCounter++)
    {
#ifdef SENSOR_DEBUG
        CyU3PDebugPrint (4, "\r\nRegister = 0x%x: Value = 0x%x",
                configSettings[regCounter].regAddr,
                configSettings[regCounter].regValue);
#endif

        rwBuffer[0] = configSettings[regCounter].regValue;
        status = I2C_SensorWrite (configSettings[regCounter].regAddr, 1, rwBuffer);
    }

    return status;
}

/*
 * Function to initialize all 16-bit sensor registers associated with a specific configuration.
 */
CyU3PReturnStatus_t
Sensor_WriteConfigurationSettings_Reg16 (
        CySensorReg16_t *configSettings,
        uint16_t         configSettingsSize)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint16_t regCounter = 0;
    uint8_t  rwBuffer[2];
    CyU3PI2cError_t error;

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint (4, "\r\nWriting Configuration Settings:");
#endif

    for (regCounter = 0; ((regCounter < configSettingsSize) && (status == CY_U3P_SUCCESS)); regCounter++)
    {
#ifdef SENSOR_DEBUG
        CyU3PDebugPrint (4, "\r\nRegister = 0x%x: Value = 0x%x",
                configSettings[regCounter].regAddr,
                configSettings[regCounter].regValue);
#endif

        rwBuffer[0] = CY_U3P_GET_MSB (configSettings[regCounter].regValue);
        rwBuffer[1] = CY_U3P_GET_LSB (configSettings[regCounter].regValue);
        status = I2C_SensorWrite (configSettings[regCounter].regAddr, 2, rwBuffer);
        if(status)
        {
        	CyU3PI2cGetErrorCode (&error);

        	CyU3PDebugPrint(4,"sensor_write error %x \n\r",error);
        }
    }


    return status;
}

/*
 * Function to initialize all 32-bit sensor registers associated with a specific configuration.
 */
CyU3PReturnStatus_t
Sensor_WriteConfigurationSettings_Reg32 (
        CySensorReg32_t *configSettings,
        uint16_t         configSettingsSize)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    uint16_t regCounter = 0;
    uint8_t  rwBuffer[4];

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint (4, "\r\nWriting Configuration Settings:");
#endif

    for (regCounter = 0; ((regCounter < configSettingsSize) && (status == CY_U3P_SUCCESS)); regCounter++)
    {
#ifdef SENSOR_DEBUG
        CyU3PDebugPrint (4, "\r\nRegister = 0x%x: Value = 0x%x",
                configSettings[regCounter].regAddr,
                configSettings[regCounter].regValue);
#endif

        rwBuffer[0] = CY_U3P_DWORD_GET_BYTE3 (configSettings[regCounter].regValue);
        rwBuffer[1] = CY_U3P_DWORD_GET_BYTE2 (configSettings[regCounter].regValue);
        rwBuffer[2] = CY_U3P_DWORD_GET_BYTE1 (configSettings[regCounter].regValue);
        rwBuffer[3] = CY_U3P_DWORD_GET_BYTE0 (configSettings[regCounter].regValue);
        status = I2C_SensorWrite (configSettings[regCounter].regAddr, 4, rwBuffer);
    }

    return status;
}

					
	
/* 
 *Configure the image Sensor to generate RAW8 Format video stream with Resolution : Resolution1 1920 x 1080
 */
CyU3PReturnStatus_t 
CyCx3_Set_ar0234_RAW8_Resolution1(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(ar0234_RAW8_Resolution1ConfigurationSettings))/(sizeof(CySensorReg16_t));
    status =  Sensor_WriteConfigurationSettings_Reg16(ar0234_RAW8_Resolution1ConfigurationSettings, configSize);
    
    return status;
}

/*
 *Configure the image Sensor to generate RAW8 Format video stream with Resolution : Resolution1 1280 x 720
 */
CyU3PReturnStatus_t
CyCx3_Set_ar0234_RAW8_Resolution2(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(ar0234_RAW8_Resolution2ConfigurationSettings))/(sizeof(CySensorReg16_t));
    status =  Sensor_WriteConfigurationSettings_Reg16(ar0234_RAW8_Resolution2ConfigurationSettings, configSize);
    if(status != CY_U3P_SUCCESS)
    {
    	CyU3PDebugPrint(4,"Sensor_WriteConfigurationSettings_Reg16: error %x\n\r",status);
    }

    return status;
}


/*
 *Configure the image Sensor to generate RAW8 Format video stream with Resolution : Resolution1 640 x 480
 */
CyU3PReturnStatus_t
CyCx3_Set_ar0234_RAW8_Resolution3(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(ar0234_RAW8_Resolution3ConfigurationSettings))/(sizeof(CySensorReg16_t));
    status =  Sensor_WriteConfigurationSettings_Reg16(ar0234_RAW8_Resolution3ConfigurationSettings, configSize);
    if(status != CY_U3P_SUCCESS)
    {
    	CyU3PDebugPrint(4,"Sensor_WriteConfigurationSettings_Reg16: error %x\n\r",status);
    }

    return status;
}

/*
 *Configure the image Sensor to generate RAW8 Format video stream with Resolution : Resolution1 640 x 480
 */
CyU3PReturnStatus_t
CyCx3_Set_ar0234_RAW8_Resolution4(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(ar0234_RAW8_Resolution4ConfigurationSettings))/(sizeof(CySensorReg16_t));
    status =  Sensor_WriteConfigurationSettings_Reg16(ar0234_RAW8_Resolution4ConfigurationSettings, configSize);
    if(status != CY_U3P_SUCCESS)
    {
    	CyU3PDebugPrint(4,"Sensor_WriteConfigurationSettings_Reg16: error %x\n\r",status);
    }

    return status;
}

/*
 *Configure the image Sensor to generate RAW8 Format video stream with Resolution : Resolution1 640 x 480
 */

CyU3PReturnStatus_t
CyCx3_Set_ar0234_RAW8_Resolution5(
		void)
{
    uint16_t configSize;
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

    configSize = (sizeof(ar0234_RAW8_Resolution5ConfigurationSettings))/(sizeof(CySensorReg16_t));
    status =  Sensor_WriteConfigurationSettings_Reg16(ar0234_RAW8_Resolution5ConfigurationSettings, configSize);
    if(status != CY_U3P_SUCCESS)
    {
    	CyU3PDebugPrint(4,"Sensor_WriteConfigurationSettings_Reg16: error %x\n\r",status);
    }

    return status;
}



/*
 * Function to initialize the image sensor. This is called at start-up.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorInit(
		void)
{
	uint16_t configSize;

#ifdef SENSOR_DEBUG
    CyU3PDebugPrint(4,"\r\n Sensor Initialization");
#endif

    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;

	configSize = (sizeof(SENSOR_BaseConfigurationSettings))/(sizeof(CySensorReg16_t));
    status = Sensor_WriteConfigurationSettings_Reg16(SENSOR_BaseConfigurationSettings, configSize);
	
	/*Include any other I2C write required during Sensor Init here*/

    return status;
}

/*
 * Function to put Image Sensor to Sleep for power saving.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorSleep(
		void)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    CyU3PI2cError_t error;
    status = I2C_SensorWrite (0x301A, 2, 0x205C);
            if(status)
            {
            	CyU3PI2cGetErrorCode (&error);

            	CyU3PDebugPrint(4,"sensor_write error %x \n\r",error);
            }


    return status;
}

/*
 * Function to wakeup Image Sensor from sleep.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorWakeup(
		void)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    CyU3PI2cError_t error;
        status = I2C_SensorWrite (0x301A, 2, 0x205C);
                if(status)
                {
                	CyU3PI2cGetErrorCode (&error);

                	CyU3PDebugPrint(4,"sensor_write error %x \n\r",error);
                }
    return status;
}

/*
 * Function to trigger auto-focus setting on the image sensor.
 */
CyU3PReturnStatus_t 
CyCx3ImageSensorTriggerAutofocus (
		void)
{
    CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
    return status;
}


/* End of file */

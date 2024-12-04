
The following is the code for `cycx3_videostreaming.c` generated with the cx3config.cycx utility.  What seems wrong is the 
resolutions the probe control structures are pointing to.  The resolutions for the image sensor (CyCx3UvcAppImageSensorSetVideoResolution)
look correct, but the probe control structures are pointing to the wrong resolutions.  

When I plug the camera into my computer I'm able to stream images at the resolutions defined in the probe control structures, but I need 
the resolutions at the image sensor level to be correct.  

I've tried changing the probe control structures to point to the correct resolutions, but then the camera doesn't stream images.  Is there a
way to change the configurations so that the probe control structures point to the correct resolutions? 

Resources: 

Here are some of the other threads and KBA that are related. 


Infineon Threads about our board: 
  * Long Thread with multiple issues. https://community.infineon.com/t5/USB-superspeed-peripherals/Test-and-booting-the-CX3-for-the-AR0234-Image-Sensor/td-p/791889
  * Request for Sensor Specific Firmware: https://community.infineon.com/t5/USB-superspeed-peripherals/CX3-firmware-for-the-AR0234-Image-Sensor/td-p/755001
  * https://community.infineon.com/t5/USB-superspeed-peripherals/Firmware-debugging-for-OnSemi-AR0234-Image-Sensor/td-p/887845

Infineon Threads about Similar Boards
  * https://community.infineon.com/t5/USB-superspeed-peripherals/CX3-MIPI-Configuration-Error-for-image-sensor-AR0234/td-p/616719

Infineon KBA
  * https://community.infineon.com/t5/Knowledge-Base-Articles/EZ-USB-CX3-Interfacing-with-the-onsemi-AR0234CS-sensor-KBA236855/ta-p/402602


Github with code: 
  * https://github.com/owlmoshpit/CX3AR0234 


```C
/*
 ## Cypress CX3 Video Streaming Control Source File (cycx3_videostreaming.c)
 ## ===========================
 ##
 ##  Copyright Cypress Semiconductor Corporation, 2018-2023,
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

#include "cyu3system.h"
#include "cyu3os.h"
#include "cyu3dma.h"
#include "cyu3error.h"
#include "cyu3usb.h"
#include "cyu3utils.h"
#include "cyu3socket.h"
#include "sock_regs.h"
#include "cycx3_videostreaming.h"
#include "cycx3_uvc.h"
#include "cyu3mipicsi.h"
#include "cyu3imagesensor.h"
#include "cycx3_imagesensor.h"

/***********************************************************************************************
 ***************************** MIPI Configuration Parameters (HS and SS) ***********************
 **********************************************************************************************/

/* MIPI Configuration parameters to interface with ar0234_RAW8_Resolution2 :  (1280 x 720 @ 120.0 fps) */
CyU3PMipicsiCfg_t mipiConfig_ar0234_RAW8_Resolution2 =  
{
    CY_U3P_MIPIOUT_DW_16,       /* MIPI out parallel width packing */
    4,                          /* Number of CSI data lanes. */
    2,                          /* PLL clock input divider. */
    119,                         /* PLL clock feedback divider. */
    CY_U3P_CSI_PLL_FRS_250_500M, /* PLL clock range. */  
    CY_U3P_CSI_PLL_CLK_DIV_4,     /* Divider for clock used to detect CSI LP<->HS transition. */
    CY_U3P_CSI_PLL_CLK_DIV_4,	/* Divider for clock used on the parallel GPIF interface. */
    0x00,		                /* Reserved */
    0x00,                       /* Reserved */
    0x00,                       /* Reserved */
    100                        /* Delay on the parallel output buffer of CSI interface. */
};

/* MIPI Configuration parameters to interface with ar0234_RAW8_Resolution4 :  (640 x 480 @ 120.0 fps) */
CyU3PMipicsiCfg_t mipiConfig_ar0234_RAW8_Resolution4 =  
{
    CY_U3P_MIPIOUT_DW_16,       /* MIPI out parallel width packing */
    4,                          /* Number of CSI data lanes. */
    2,                          /* PLL clock input divider. */
    119,                         /* PLL clock feedback divider. */
    CY_U3P_CSI_PLL_FRS_250_500M, /* PLL clock range. */  
    CY_U3P_CSI_PLL_CLK_DIV_4,     /* Divider for clock used to detect CSI LP<->HS transition. */
    CY_U3P_CSI_PLL_CLK_DIV_4,	/* Divider for clock used on the parallel GPIF interface. */
    0x00,		                /* Reserved */
    0x00,                       /* Reserved */
    0x00,                       /* Reserved */
    100                        /* Delay on the parallel output buffer of CSI interface. */
};

/* MIPI Configuration parameters to interface with ar0234_RAW8_Resolution5 :  (1920 x 1080 @ 120.0 fps) */
CyU3PMipicsiCfg_t mipiConfig_ar0234_RAW8_Resolution5 =  
{
    CY_U3P_MIPIOUT_DW_16,       /* MIPI out parallel width packing */
    4,                          /* Number of CSI data lanes. */
    2,                          /* PLL clock input divider. */
    119,                         /* PLL clock feedback divider. */
    CY_U3P_CSI_PLL_FRS_250_500M, /* PLL clock range. */  
    CY_U3P_CSI_PLL_CLK_DIV_4,     /* Divider for clock used to detect CSI LP<->HS transition. */
    CY_U3P_CSI_PLL_CLK_DIV_4,	/* Divider for clock used on the parallel GPIF interface. */
    0x00,		                /* Reserved */
    0x00,                       /* Reserved */
    0x00,                       /* Reserved */
    100                        /* Delay on the parallel output buffer of CSI interface. */
};

/* [ ] */

#ifdef STILL_CAPTURE_ENABLE

/*	Set the still image resolutions through this function. This function lists all the
 *  supported resolutions in SuperSpeed and HighSpeed. The frame index of resolutions
 *  supported in Still Capture can be different from the frame index of resolutions supported
 *  in Video streaming.
 */
void
CyCx3UvcAppImageSensorSetStillResolution(
		uint8_t format_index,
        uint8_t resolution_index        
        )
{
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	switch (CyU3PUsbGetSpeed ())
	{
	case CY_U3P_SUPER_SPEED:
		switch (format_index)
		{
		default:
			break;
		}
		break;
			
	case CY_U3P_HIGH_SPEED:
		switch (format_index)
		{
		default:
			break;
		}
		break;
	default:
	   	break;		
	}
}		

#endif

/*	Set the video resolution through this function. This function lists all the
 *  supported resolutions in SuperSpeed and HighSpeed. The frame index of resolutions
 *  supported in Still Capture can be different from the frame index of resolutions supported
 *  in Video streaming.
 */
void
CyCx3UvcAppImageSensorSetVideoResolution(
		uint8_t         formatIndex,
        uint8_t 		resolutionIndex
        )
{
	CyU3PReturnStatus_t status = CY_U3P_SUCCESS;
	switch (CyU3PUsbGetSpeed ())
	{
	case CY_U3P_SUPER_SPEED:
		switch (formatIndex)
		{
		case SS_YUY2_INDEX:
			switch(resolutionIndex)
			{
			case 0x01:
				/* Write Resolution5Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_ar0234_RAW8_Resolution5, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				/*Set MIPI PHY Time Delay (or THS_Settle) value for CX3's MIPI Decoder depending on THS-Prepare and THS-Zero parameters*/	
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,17); */
				
				/* Set the GPIF bus width */ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 1920 x 1080 @ 120.0 fps*/
				CyCx3_Set_ar0234_RAW8_Resolution5();
				break; 
			case 0x02:
				/* Write Resolution2Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_ar0234_RAW8_Resolution2, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				/*Set MIPI PHY Time Delay (or THS_Settle) value for CX3's MIPI Decoder depending on THS-Prepare and THS-Zero parameters*/	
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,17); */
				
				/* Set the GPIF bus width */ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 1280 x 720 @ 120.0 fps*/
				CyCx3_Set_ar0234_RAW8_Resolution2();
				break; 
			case 0x03:
				/* Write Resolution4Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_ar0234_RAW8_Resolution4, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				/*Set MIPI PHY Time Delay (or THS_Settle) value for CX3's MIPI Decoder depending on THS-Prepare and THS-Zero parameters*/	
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,17); */
				
				/* Set the GPIF bus width */ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 640 x 480 @ 120.0 fps*/
				CyCx3_Set_ar0234_RAW8_Resolution4();
				break; 
			
			default:
				break;
			}
			break;
		
		default:
			break;
		}
		break;
			
	case CY_U3P_HIGH_SPEED:
		switch (formatIndex)
		{
		case HS_YUY2_INDEX:
			switch(resolutionIndex)
			{
			case 0x01:
				/* Write Resolution4Settings */
				#ifndef FX3_STREAMING
				status = CyU3PMipicsiSetIntfParams (&mipiConfig_ar0234_RAW8_Resolution4, CyFalse);
				if (status != CY_U3P_SUCCESS)
				{
					CyU3PDebugPrint (4, "\n\rUSBStpCB:SetIntfParams SS1 Err = 0x%x", status);
				}
				
				
				/* CyU3PMipicsiSetPhyTimeDelay(1,17); */
				
				/*Set the GPIF bus width*/ 
				CyCx3SwitchGpifBusWidth(16);
				#endif

				/*Set image sensor configuration for 640 x 480 @ 120.0 fps*/
				CyCx3_Set_ar0234_RAW8_Resolution4();
				break; 
			default:
    			break;
			}
			break;
				
		default:
			break;
		}
		break;
	default:
		break;
	}
}

/*Returns the pointer to the Probe Control structure for the corresponding frame index.*/
uint8_t * 
CyCx3UvcAppGetProbeControlData (
        CyU3PUSBSpeed_t usbConType,
        uint8_t         formatIndex,
        uint8_t 		frameIndex
        )

{
	switch(usbConType) 
	{
	case CY_U3P_SUPER_SPEED:
		switch (formatIndex)
		{
		case SS_YUY2_INDEX:	
			switch(frameIndex)
			{	
			case 0x01:
				/* Send probe control structure corresponding to 960 x 1080 @120.0 fps */
       			return ((uint8_t *) glRAW8_YUY2Resolution5ProbeCtrl);
			case 0x02:
				/* Send probe control structure corresponding to 640 x 720 @120.0 fps */
       			return ((uint8_t *) glRAW8_YUY2Resolution2ProbeCtrl);
			case 0x03:
				/* Send probe control structure corresponding to 320 x 480 @120.0 fps */
       			return ((uint8_t *) glRAW8_YUY2Resolution4ProbeCtrl);	        				
       		default:
       			break;	
			}
			break;
		default:
			break;
        }
		break;
	case CY_U3P_HIGH_SPEED:
       	switch (formatIndex)
		{
		case HS_YUY2_INDEX:	
			switch(frameIndex)
			{    
			case 0x01:
				/*Send probe control structure corresponding to 320 x 480 @120.0 fps */
            	return ((uint8_t *) glRAW8_YUY2Resolution4ProbeCtrl_HS);	
   			}
			break;
       		
		default:
			break;
       	}
		break;
	default:
		break;
	}

    return NULL;
}

/*END OF FILE*/
```
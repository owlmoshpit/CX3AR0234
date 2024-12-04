/*
## Cypress USB 3.0 Platform descriptor file 
## ===========================
##
##  Copyright Cypress Semiconductor Corporation, 2013-2014,
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


/* This file contains the USB enumeration descriptors for the CX3 Video Streaming application example.
 * The descriptor arrays must be 32 byte aligned if the D-cache is turned on. If the linker
 * used is not capable of supporting the aligned feature for this, then dynamically allocated
 * buffer must be used, and the descriptor must be loaded into it. */

#include "cycx3_uvc.h"
#include "cyu3mipicsi.h"
#include "cycx3_videostreaming.h"

/* Standard Device Descriptor for USB 3 */
const uint8_t CyCx3USB30DeviceDscr[] =
{
    0x12,                               /* Descriptor size */
    CY_U3P_USB_DEVICE_DESCR,            /* Device descriptor type */
    0x00, 0x03,                         /* USB 3.0 */
    0xEF,                               /* Device class */
    0x02,                               /* Device Sub-class */
    0x01,                               /* Device protocol */
    0x09,                               /* Maxpacket size for EP0 : 2^9 */
    0xB4, 0x04,                         /* Vendor ID */
    0xC3, 0x00,                         /* Product ID */
    0x00, 0x00,                         /* Device release number */
    0x01,                               /* Manufacture string index */
    0x02,                               /* Product string index */
    0x00,                               /* Serial number string index */
    0x01                                /* Number of configurations */
};

/* Standard Device Descriptor for USB 2 */
const uint8_t CyCx3USB20DeviceDscr[] =
{
    0x12,                               /* Descriptor size */
    CY_U3P_USB_DEVICE_DESCR,            /* Device descriptor type */
    0x10, 0x02,                         /* USB 2.1 */
    0xEF,                               /* Device class */
    0x02,                               /* Device sub-class */
    0x01,                               /* Device protocol */
    0x40,                               /* Maxpacket size for EP0 : 64 bytes */
    0xB4, 0x04,                         /* Vendor ID */
    0xC3, 0x00,                         /* Product ID */
    0x00, 0x00,                         /* Device release number */
    0x01,                               /* Manufacture string index */
    0x02,                               /* Product string index */
    0x00,                               /* Serial number string index */
    0x01                                /* Number of configurations */
};

/* Binary Device Object Store (BOS) Descriptor */
const uint8_t CyCx3USBBOSDscr[] =
{
    0x05,                               /* Descriptor size */
    CY_U3P_BOS_DESCR,                   /* Device descriptor type */
    0x16, 0x00,                         /* Length of this descriptor and all sub descriptors */
    0x02,                               /* Number of device capability descriptors */

    /* USB 2.0 Extension */
    0x07,                               /* Descriptor size */
    CY_U3P_DEVICE_CAPB_DESCR,           /* Device capability type descriptor */
    CY_U3P_USB2_EXTN_CAPB_TYPE,         /* USB 2.1 extension capability type */
    0x02, 0x00, 0x00, 0x00,             /* Supported device level features - LPM support */

    /* SuperSpeed Device Capability */
    0x0A,                               /* Descriptor size */
    CY_U3P_DEVICE_CAPB_DESCR,           /* Device capability type descriptor */
    CY_U3P_SS_USB_CAPB_TYPE,            /* SuperSpeed device capability type */
    0x00,                               /* Supported device level features  */
    0x0E, 0x00,                         /* Speeds supported by the device : SS, HS and FS */
    0x03,                               /* Functionality support */
    0x00,                               /* U1 device exit latency */
    0x00, 0x00                          /* U2 device exit latency */
};

/* Standard Device Qualifier Descriptor */
const uint8_t CyCx3USBDeviceQualDscr[] =
{
    0x0A,                               /* descriptor size */
    CY_U3P_USB_DEVQUAL_DESCR,           /* Device qualifier descriptor type */
    0x00, 0x02,                         /* USB 2.0 */
    0xEF,                               /* Device class */
    0x02,                               /* Device sub-class */
    0x01,                               /* Device protocol */
    0x40,                               /* Maxpacket size for EP0 : 64 bytes */
    0x01,                               /* Number of configurations */
    0x00                                /* Reserved */
};

/* Standard Super Speed Configuration Descriptor */
const uint8_t CyCx3USBSSConfigDscr[] =
{
    /* Configuration Descriptor*/
    0x09,                               /* Descriptor Size */
    CY_U3P_USB_CONFIG_DESCR,            /* Configuration Descriptor Type */
    SS_TOTAL_SIZE_CONFIG_DSCR_L,        /* Length of this descriptor and all sub descriptors - low Byte */
	SS_TOTAL_SIZE_CONFIG_DSCR_H,        /* Length of this descriptor and all sub descriptors - high Byte */
    0x02,                               /* Number of interfaces */
    0x01,                               /* Configuration number */
    0x03,                               /* Configuration string index */
    0xC0,                               /* Config characteristics - Self Powered */
    0x0C,                               /* Max power consumption of device (in 8mA unit) : 96mA */

    /* Interface Association Descriptor */
    0x08,                               /* Descriptor Size */
    CX3_INTRFC_ASSN_DESCR,              /* Interface Association Descriptor Type */
    0x00,                               /* Interface number of the VideoControl interface 
                                           that is associated with this function*/
    0x02,                               /* Number of contiguous Video interfaces that are 
                                           associated with this function */
    0x0E,                               /* Video Interface Class Code: CC_VIDEO */
    0x03,                               /* Subclass code: SC_VIDEO_INTERFACE_COLLECTION*/
    0x00,                               /* Protocol: PC_PROTOCOL_UNDEFINED*/
    0x00,                               /* String Descriptor index for interface */

    /* Standard Video Control Interface Descriptor (Interface 0, Alternate Setting 0)*/
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x00,                               /* Index of this Interface */
    0x00,                               /* Alternate setting number */
    0x01,                               /* Number of end points - 1 Interrupt Endpoint*/
    0x0E,                               /* Video Interface Class Code: CC_VIDEO  */
    0x01,                               /* Interface sub class: SC_VIDEOCONTROL */
    0x00,                               /* Interface protocol code: PC_PROTOCOL_UNDEFINED.*/
    0x00,                               /* Interface descriptor string index */

    /* Class specific VC Interface Header Descriptor */
    0x0D,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class Specific Interface Descriptor type: CS_INTERFACE */
    0x01,                               /* Descriptor Sub type: VC_HEADER */
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x01,                         /* Revision of UVC class spec: 1.0 - Legacy version */
    0x50, 0x00,                         /* Total size of class specific descriptors*/
#else
    0x10, 0x01,                         /* Revision of UVC class spec: 1.1 - Minimum version required 
                                           for USB Compliance. Not supported on Windows XP*/
    0x51, 0x00,                         /* Total Size of class specific descriptors 
                                           (till Output terminal) */                                       
#endif

    0x00, 0x6C, 0xDC, 0x02,             /* Clock frequency : 48MHz(Deprecated) */
    0x01,                               /* Number of streaming interfaces */
    0x01,                               /*VideoStreaming interface 1 belongs to this 
                                          VideoControl interface*/

    /* Input (Camera) Terminal Descriptor */
    0x12,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* CS_INTERFACE */
    0x02,                               /* VC_INPUT_TERMINAL subtype */
    0x01,                               /* ID of this input terminal */
    0x01, 0x02,                         /* ITT_CAMERA type. This terminal is a camera 
                                           terminal representing the CCD sensor*/
    0x00,                               /* No association terminal */
    0x00,                               /* Unused */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */

    /* Processing Unit Descriptor */
#ifdef CX3_UVC_1_0_SUPPORT
	0x0C,                               /* Descriptor size*/
#else
    0x0D,                               /* Descriptor size */
#endif
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x05,                               /* Processing Unit Descriptor type: VC_PROCESSING_UNIT*/
    0x02,                               /* ID of this unit */
    0x01,                               /* Source ID: 1: Connected to input terminal */
    0x00, 0x40,                         /* Digital multiplier */
    0x03,                               /* Size of controls field for this terminal: 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String desc index: Not used */
#ifndef CX3_UVC_1_0_SUPPORT    
    0x00,                               /* Analog Video Standards Supported: None */
#endif
    
    /* Extension Unit Descriptor */
    0x1C,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x06,                               /* Extension Unit Descriptor type */
    0x03,                               /* ID of this terminal */
    0xFF, 0xFF, 0xFF, 0xFF,             /* 16 byte GUID */
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x00,                               /* Number of controls in this terminal */
    0x01,                               /* Number of input pins in this terminal */
    0x02,                               /* Source ID : 2 : Connected to Proc Unit */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String descriptor index : Not used */

    /* Output Terminal Descriptor */
    0x09,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x03,                               /* Output Terminal Descriptor type */
    0x04,                               /* ID of this terminal */
    0x01, 0x01,                         /* USB Streaming terminal type */
    0x00,                               /* No association terminal */
    0x03,                               /* Source ID : 3 : Connected to Extn Unit */
    0x00,                               /* String desc index : Not used */

    /* Video Control Status Interrupt Endpoint Descriptor */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_CONTROL_STATUS,              /* Endpoint address and description: EP-2 IN */
    CY_U3P_USB_EP_INTR,                 /* Interrupt End point Type */
    0x40, 0x00,                         /* Max packet size: 64 bytes */
    0x01,                               /* Servicing interval */

    /* Super Speed Endpoint Companion Descriptor */
    0x06,                               /* Descriptor size */
    CY_U3P_SS_EP_COMPN_DESCR,           /* SS Endpoint Companion Descriptor Type */
    0x00,                               /* Max no. of packets in a Burst: 1 */
    0x00,                               /* Attribute: N.A. */
    0x40,                               /* Bytes per interval: 1024 */
    0x00,

    /* Class Specific Interrupt Endpoint Descriptor */
    0x05,                               /* Descriptor size */
    0x25,                               /* Class Specific Endpoint Descriptor Type */
    CY_U3P_USB_EP_INTR,                 /* End point Sub Type */
    0x40, 0x00,                         /* Max packet size = 64 bytes */

    /* Standard Video Streaming Interface Descriptor (Interface 1, Alternate Setting 0) */
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x01,                               /* Interface number: 1 */
    0x00,                               /* Alternate setting number: 0 */
    0x01,                               /* Number of end points: 1 Bulk Endpoint */
    0x0E,                               /* Interface class : CC_VIDEO */
    0x02,                               /* Interface sub class : SC_VIDEOSTREAMING */
    0x00,                               /* Interface protocol code : PC_PROTOCOL_UNDEFINED */
    0x00,                               /* Interface descriptor string index */

    /* Class-specific Video Streaming Input Header Descriptor */
   	0x0D + SS_NO_OF_VIDEO_FORMATS_SUPPORTED,/* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS I/f Type */
    0x01,                               /* Descriptor Subtype: Input Header */
    SS_NO_OF_VIDEO_FORMATS_SUPPORTED,    /* 1 format desciptor follows */
    SS_TOTAL_SIZE_VS_CLASS_DSCR_L,      /* Total size of Class specific VS descr -Low Byte*/
	SS_TOTAL_SIZE_VS_CLASS_DSCR_H,      /* Total size of Class specific VS descr -High Byte*/
	CX3_EP_BULK_VIDEO,                  /* EP address for BULK video data: EP 3 IN */
    0x00,                               /* No dynamic format change supported */
    0x04,                               /* Output terminal ID : 4 */
    0x00,                               /* No Still image capture method supported */
    0x00,                               /* Hardware trigger NOT supported */
    0x00,                               /* Hardware to initiate still image capture not supported */
    0x01,                               /* Size of controls field : 1 byte */
    0x00,								/* YUY2 Format*/
   
#ifndef Y8
    /* Class specific VS format descriptor - YUY2 */
    0x1B,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
    0x04,                               /* Subtype : VS_FORMAT */
    SS_YUY2_INDEX,                               /* Format desciptor index */
    SS_YUY2_TOTAL_NO_OF_RES,                     /* Number of Frame Descriptors that follow this descriptor: 4 */
    
    /* GUID, globally unique identifier used to identify streaming-encoding format*/
    0x59, 0x55, 0x59, 0x32, 
	0x00, 0x00, 0x10, 0x00, 
	0x80, 0x00, 0x00, 0xAA, 
	0x00, 0x38, 0x9B, 0x71, 
	 
    0x10,                               /* Number of bits per pixel: 16*/
    0x01,                               /* Optimum Frame Index for this stream: 1  (Resolution1) */
    0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
    0x00,                               /* Y dimension of the picture aspect ratio: Non-interlaced */
    0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
    0x00,                               /* duplication of the video stream restriction: 0 - no restriction */

    /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 1 , Resolution1 960 x 1080 @ 100.0 fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype:  frame interface*/
    0x01,                               /* Frame Descriptor Index: 1 */
    0x00,                               /* No Still image capture method supported */
    0xc0,0x03,                         /* Width in pixel:  960 */	
    0x38,0x04,                         /* Height in pixel: 1080 */
    0x00,0x80,0xe0,0x62,             /* Min bit rate (bits/s): 960 x 1080 x 16 x 100.0 = 1658880000 */
    0x00,0x80,0xe0,0x62,             /* Max bit rate (bits/s): Fixed rate so same as Min */
    0x00,0xa4,0x1f,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 960 x 1080 x 2 */
    0x9f,0x86,0x01,0x00,             /* Default frame interval (in 100ns units): (1/ 100.0)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x9f,0x86,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */
   
    /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 2 , Resolution2 640 x 720 @ 120.0 fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype:  frame interface*/
    0x02,                               /* Frame Descriptor Index: 2 */
    0x00,                               /* No Still image capture method supported */
    0x80,0x02,                         /* Width in pixel:  640 */	
    0xd0,0x02,                         /* Height in pixel: 720 */
    0x00,0x00,0xbc,0x34,             /* Min bit rate (bits/s): 640 x 720 x 16 x 120.0 = 884736000 */
    0x00,0x00,0xbc,0x34,             /* Max bit rate (bits/s): Fixed rate so same as Min */
    0x00,0x10,0x0e,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 640 x 720 x 2 */
    0x85,0x45,0x01,0x00,             /* Default frame interval (in 100ns units): (1/ 120.0)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x85,0x45,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */
   
    /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 3 , Resolution4 320 x 480 @ 120.0 fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype:  frame interface*/
    0x03,                               /* Frame Descriptor Index: 3 */
    0x00,                               /* No Still image capture method supported */
    0x40,0x01,                         /* Width in pixel:  320 */	
    0xe0,0x01,                         /* Height in pixel: 480 */
    0x00,0x00,0x94,0x11,             /* Min bit rate (bits/s): 320 x 480 x 16 x 120.0 = 294912000 */
    0x00,0x00,0x94,0x11,             /* Max bit rate (bits/s): Fixed rate so same as Min */
    0x00,0xb0,0x04,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 480 x 2 */
    0x85,0x45,0x01,0x00,             /* Default frame interval (in 100ns units): (1/ 120.0)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x85,0x45,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */
   
    /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 4 , Resolution5 960 x 1080 @ 15.0 fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype:  frame interface*/
    0x04,                               /* Frame Descriptor Index: 4 */
    0x00,                               /* No Still image capture method supported */
    0xc0,0x03,                         /* Width in pixel:  960 */	
    0x38,0x04,                         /* Height in pixel: 1080 */
    0x00,0xe0,0xd4,0x0e,             /* Min bit rate (bits/s): 960 x 1080 x 16 x 15.0 = 248832000 */
    0x00,0xe0,0xd4,0x0e,             /* Max bit rate (bits/s): Fixed rate so same as Min */
    0x00,0xa4,0x1f,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 960 x 1080 x 2 */
    0x2a,0x2c,0x0a,0x00,             /* Default frame interval (in 100ns units): (1/ 15.0)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x2a,0x2c,0x0a,0x00,             /* Frame interval 3: Same as Default frame interval */
   
#else
    /* Class specific VS format descriptor - YUY2 */
       0x1B,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
       0x04,                               /* Subtype : VS_FORMAT */
       SS_YUY2_INDEX,                               /* Format desciptor index */
       SS_YUY2_TOTAL_NO_OF_RES,                     /* Number of Frame Descriptors that follow this descriptor: 4 */

       /* GUID, globally unique identifier used to identify streaming-encoding format: Y8  */
             /* GUID, globally unique identifier used to identify streaming-encoding format*/
          	    0x59,0x38,0x20,0x20,//Y8
          	    0x00,0x00,0x10,0x00,
          	    0x80,0x00,0x00,0xAA,
          	    0x00,0x38,0x9B,0x71,

       0x08,                               /* Number of bits per pixel: 16*/
       0x01,                               /* Optimum Frame Index for this stream: 1  (Resolution1) */
       0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
       0x00,                               /* Y dimension of the picture aspect ratio: Non-interlaced */
       0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
       0x00,                               /* duplication of the video stream restriction: 0 - no restriction */

       /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 1 , Resolution1 960 x 1080 @ 100.0 fps*/
       0x1E,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
       0x05,                               /* Subtype:  frame interface*/
       0x01,                               /* Frame Descriptor Index: 1 */
       0x00,                               /* No Still image capture method supported */
       0x80,0x07,                         /* Width in pixel:  1920 */
       0x38,0x04,                         /* Height in pixel: 1080 */
       0x00,0x80,0xe0,0x62,             /* Min bit rate (bits/s): 960 x 1080 x 16 x 100.0 = 1658880000 */
       0x00,0x80,0xe0,0x62,             /* Max bit rate (bits/s): Fixed rate so same as Min */
       0x00,0xa4,0x1f,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 960 x 1080 x 2 */
       0x9f,0x86,0x01,0x00,             /* Default frame interval (in 100ns units): (1/ 100.0)x10^7 */
       0x01,                               /* Frame interval type : No of discrete intervals */
       0x9f,0x86,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */

       /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 2 , Resolution2 640 x 720 @ 120.0 fps*/
       0x1E,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
       0x05,                               /* Subtype:  frame interface*/
       0x02,                               /* Frame Descriptor Index: 2 */
       0x00,                               /* No Still image capture method supported */
       0x00,0x05,                         /* Width in pixel:  1280 */
       0xd0,0x02,                         /* Height in pixel: 720 */
       0x00,0x00,0xbc,0x34,             /* Min bit rate (bits/s): 640 x 720 x 16 x 120.0 = 884736000 */
       0x00,0x00,0xbc,0x34,             /* Max bit rate (bits/s): Fixed rate so same as Min */
       0x00,0x10,0x0e,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 640 x 720 x 2 */
       0x85,0x45,0x01,0x00,             /* Default frame interval (in 100ns units): (1/ 120.0)x10^7 */
       0x01,                               /* Frame interval type : No of discrete intervals */
       0x85,0x45,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */

       /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 3 , Resolution4 320 x 480 @ 120.0 fps*/
       0x1E,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
       0x05,                               /* Subtype:  frame interface*/
       0x03,                               /* Frame Descriptor Index: 3 */
       0x00,                               /* No Still image capture method supported */
       0x80,0x02,                         /* Width in pixel:  640 */
       0xe0,0x01,                         /* Height in pixel: 480 */
       0x00,0x00,0x94,0x11,             /* Min bit rate (bits/s): 320 x 480 x 16 x 120.0 = 294912000 */
       0x00,0x00,0x94,0x11,             /* Max bit rate (bits/s): Fixed rate so same as Min */
       0x00,0xb0,0x04,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 480 x 2 */
       0x85,0x45,0x01,0x00,             /* Default frame interval (in 100ns units): (1/ 120.0)x10^7 */
       0x01,                               /* Frame interval type : No of discrete intervals */
       0x85,0x45,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */

       /* Class specific VS Frame Descriptor - YUY2 Format, frameIndex - 4 , Resolution5 960 x 1080 @ 15.0 fps*/
       0x1E,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
       0x05,                               /* Subtype:  frame interface*/
       0x04,                               /* Frame Descriptor Index: 4 */
       0x00,                               /* No Still image capture method supported */
       0x80,0x07,                         /* Width in pixel:  1920 */
       0x38,0x04,                         /* Height in pixel: 1080 */
       0x00,0xe0,0xd4,0x0e,             /* Min bit rate (bits/s): 960 x 1080 x 16 x 15.0 = 248832000 */
       0x00,0xe0,0xd4,0x0e,             /* Max bit rate (bits/s): Fixed rate so same as Min */
       0x00,0xa4,0x1f,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 960 x 1080 x 2 */
       0x2a,0x2c,0x0a,0x00,             /* Default frame interval (in 100ns units): (1/ 15.0)x10^7 */
       0x01,                               /* Frame interval type : No of discrete intervals */
       0x2a,0x2c,0x0a,0x00,             /* Frame interval 3: Same as Default frame interval */
#endif

	/* Color matching descriptor -  YUY2 */
	0x06,
	0x24,
	0x0D,
	0x00,
	0x00,
	0x00,
    
    
    
    /* Endpoint Descriptor for BULK Streaming Video Data */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_BULK_VIDEO,                  /* Endpoint address and description: EP 3 IN */
    CY_U3P_USB_EP_BULK,                 /* BULK End point */
    CX3_EP_BULK_VIDEO_PKT_SIZE_L,       /* CX3_EP_BULK_VIDEO_PKT_SIZE_L */
    CX3_EP_BULK_VIDEO_PKT_SIZE_H,       /* CX3_EP_BULK_VIDEO_PKT_SIZE_H */
    0x00,                               /* Servicing interval for data transfers */

    /* Super Speed Endpoint Companion Descriptor */
    0x06,                               /* Descriptor size */
    CY_U3P_SS_EP_COMPN_DESCR,           /* SS Endpoint Companion Descriptor Type */
    0x0F,                               /* Max number of packets per burst: 12 */
    0x00,                               /* Attribute: Streams not defined */
    0x00,                               /* No meaning for bulk */
    0x00
};

/* Standard High Speed Configuration Descriptor */
const uint8_t CyCx3USBHSConfigDscr[] =
{
    /* Configuration descriptor */
    0x09,                               /* Descriptor size */
    CY_U3P_USB_CONFIG_DESCR,            /* Configuration descriptor type */
    0xF2,0x00,                            /* Length of this descriptor and all sub descriptors */
    0x02,                               /* Number of interfaces */
    0x01,                               /* Configuration number */
    0x04,                               /* Configuration string index */
    0xC0,                               /* Config characteristics - self powered */
    0x32,                               /* Max power consumption of device (in 2mA unit) : 100mA */

    /* Interface Association Descriptor */
    0x08,                               /* Descriptor Size */
    CX3_INTRFC_ASSN_DESCR,              /* Interface Association Descriptor Type */
    0x00,                               /* Interface number of the VideoControl interface 
                                           that is associated with this function*/
    0x02,                               /* Number of contiguous Video interfaces that are 
                                           associated with this function */
    0x0E,                               /* Video Interface Class Code: CC_VIDEO */
    0x03,                               /* Subclass code: SC_VIDEO_INTERFACE_COLLECTION*/
    0x00,                               /* Protocol: PC_PROTOCOL_UNDEFINED*/
    0x00,                               /* String Descriptor index for interface */

    /* Standard Video Control Interface Descriptor (Interface 0, Alternate Setting 0)*/
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x00,                               /* Index of this Interface */
    0x00,                               /* Alternate setting number */
    0x01,                               /* Number of end points - 1 Interrupt Endpoint*/
    0x0E,                               /* Video Interface Class Code: CC_VIDEO  */
    0x01,                               /* Interface sub class: SC_VIDEOCONTROL */
    0x00,                               /* Interface protocol code: PC_PROTOCOL_UNDEFINED.*/
    0x00,                               /* Interface descriptor string index */

    /* Class specific VC Interface Header Descriptor */
    0x0D,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class Specific Interface Descriptor type: CS_INTERFACE */
    0x01,                               /* Descriptor Sub type: VC_HEADER */
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x01,                         /* Revision of UVC class spec: 1.0 - Legacy version */
    0x50, 0x00,                         /* Total Size of class specific descriptors*/
#else
    0x10, 0x01,                         /* Revision of UVC class spec: 1.1 - Minimum version required 
                                           for USB Compliance. Not supported on Windows XP*/    
    0x51, 0x00,                         /* Total Size of class specific descriptors 
                                           (till Output terminal) */                                           
#endif
    0x00, 0x6C, 0xDC, 0x02,             /* Clock frequency : 48MHz(Deprecated) */
    0x01,                               /* Number of streaming interfaces */
    0x01,                               /*VideoStreaming interface 1 belongs to this 
                                          VideoControl interface*/

    /* Input (Camera) Terminal Descriptor */
    0x12,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* CS_INTERFACE */
    0x02,                               /* VC_INPUT_TERMINAL subtype */
    0x01,                               /* ID of this input terminal */
    0x01, 0x02,                         /* ITT_CAMERA type. This terminal is a camera 
                                           terminal representing the CCD sensor*/
    0x00,                               /* No association terminal */
    0x00,                               /* Unused */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */

    /* Processing Unit Descriptor */
#ifdef CX3_UVC_1_0_SUPPORT
	0x0C,                               /* Descriptor size*/
#else
    0x0D,                               /* Descriptor size */
#endif
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x05,                               /* Processing Unit Descriptor type: VC_PROCESSING_UNIT*/
    0x02,                               /* ID of this unit */
    0x01,                               /* Source ID: 1: Conencted to input terminal */
    0x00, 0x40,                         /* Digital multiplier */
    0x03,                               /* Size of controls field for this terminal: 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String desc index: Not used */
#ifndef CX3_UVC_1_0_SUPPORT    
    0x00,                               /* Analog Video Standards Supported: None */
#endif

    /* Extension Unit Descriptor */
    0x1C,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x06,                               /* Extension Unit Descriptor type */
    0x03,                               /* ID of this terminal */
    0xFF, 0xFF, 0xFF, 0xFF,             /* 16 byte GUID */
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x00,                               /* Number of controls in this terminal */
    0x01,                               /* Number of input pins in this terminal */
    0x02,                               /* Source ID : 2 : Connected to Proc Unit */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String descriptor index : Not used */

    /* Output Terminal Descriptor */
    0x09,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x03,                               /* Output Terminal Descriptor type */
    0x04,                               /* ID of this terminal */
    0x01, 0x01,                         /* USB Streaming terminal type */
    0x00,                               /* No association terminal */
    0x03,                               /* Source ID : 3 : Connected to Extn Unit */
    0x00,                               /* String desc index : Not used */

    /* Video Control Status Interrupt Endpoint Descriptor */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_CONTROL_STATUS,              /* Endpoint address and description: EP-2 IN */
    CY_U3P_USB_EP_INTR,                 /* Interrupt End point Type */
    0x40, 0x00,                         /* Max packet size: 64 bytes */
    0x01,                               /* Servicing interval */

    /* Class Specific Interrupt Endpoint Descriptor */
    0x05,                               /* Descriptor size */
    0x25,                               /* Class specific endpoint descriptor type */
    CY_U3P_USB_EP_INTR,                 /* End point sub type */
    0x40,0x00,                          /* Max packet size = 64 bytes */

    /* Standard Video Streaming Interface Descriptor (Interface 1, Alternate Setting 0) */
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface descriptor type */
    0x01,                               /* Interface number: 1 */
    0x00,                               /* Alternate setting number: 0 */
    0x01,                               /* Number of end points: 1 Bulk endopoint*/
    0x0E,                               /* Interface class : CC_VIDEO */
    0x02,                               /* Interface sub class : SC_VIDEOSTREAMING */
    0x00,                               /* Interface protocol code : PC_PROTOCOL_UNDEFINED */
    0x00,                               /* Interface descriptor string index */

    /* Class-specific Video Streaming Input Header Descriptor */
    0x0D + HS_NO_OF_VIDEO_FORMATS_SUPPORTED,/* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface type */
    0x01,                               /* Descriptor subtype : Input Header */
    HS_NO_OF_VIDEO_FORMATS_SUPPORTED,   /* Number of video formats supported */
    HS_TOTAL_SIZE_VS_CLASS_DSCR_L,		/* Total size of class specific VS descr LSB */
    HS_TOTAL_SIZE_VS_CLASS_DSCR_H,      /* Total size of class specific VS descr MSB */
    CX3_EP_BULK_VIDEO,                  /* EP address for BULK video data: EP 3 IN  */
    0x00,                               /* No dynamic format change supported */
    0x04,                               /* Output terminal ID : 4 */
    0x00,         /* No Still image capture method supported */
    0x00,                               /* Hardware trigger not supported */
    0x00,                               /* Hardware to initiate still image capture not supported*/
    0x01,                               /* Size of controls field : 1 byte */
    0x00,								/* YUY2 Format*/
    
#ifndef Y8
    /* Class specific Uncompressed VS format descriptor - YUY2 */
    0x1B,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
    0x04,                               /* Subtype : VS_FORMAT */
    HS_YUY2_INDEX,                               /* Format desciptor index */
    HS_YUY2_TOTAL_NO_OF_RES,                               /* Number of Frame Descriptors that follow this descriptor: 3 */
    
    /* GUID, globally unique identifier used to identify streaming-encoding format: YUY2  */
    0x59, 0x55, 0x59, 0x32, 
	0x00, 0x00, 0x10, 0x00, 
	0x80, 0x00, 0x00, 0xAA, 
	0x00, 0x38, 0x9B, 0x71, 
	 
    0x10,                               /* Number of bits per pixel: 16*/
    0x01,                               /* Optimum Frame Index for this stream: 2 (720p) */
    0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
    0x00,                               /* Y dimension of the pictuer aspect ratio: Non-interlaced */
    0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
    0x00,                               /* duplication of the video stream restriction: 0 - no restriction */
    
    /* Class specific Uncompressed VS Frame Descriptor 3 - Resolution4 320 x 480 @ 120.0 fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype:  frame interface*/
    0x01,                               /* Frame Descriptor Index: 1 */
    0x00,                               /* No Still image capture method supported */
    0x40,0x01,                         /* Width in pixel:  320 */	
    0xe0,0x01,                         /* Height in pixel: 480 */
    0x00,0x00,0x94,0x11,             /* Min bit rate (bits/s): 320 x 480 x 16 x 120.0 = 294912000 */
    0x00,0x00,0x94,0x11,             /* Max bit rate (bits/s): Fixed rate so same as Min */
    0x00,0xb0,0x04,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 480 x 2 */
    0x85,0x45,0x01,0x00,             /* Default frame interval (in 100ns units): (1/120.0)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x85,0x45,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */
   
    /* Class specific Uncompressed VS Frame Descriptor 4 - Resolution5 960 x 1080 @ 15.0 fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype:  frame interface*/
    0x02,                               /* Frame Descriptor Index: 2 */
    0x00,                               /* No Still image capture method supported */
    0xc0,0x03,                         /* Width in pixel:  960 */	
    0x38,0x04,                         /* Height in pixel: 1080 */
    0x00,0xe0,0xd4,0x0e,             /* Min bit rate (bits/s): 960 x 1080 x 16 x 15.0 = 248832000 */
    0x00,0xe0,0xd4,0x0e,             /* Max bit rate (bits/s): Fixed rate so same as Min */
    0x00,0xa4,0x1f,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 960 x 1080 x 2 */
    0x2a,0x2c,0x0a,0x00,             /* Default frame interval (in 100ns units): (1/15.0)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x2a,0x2c,0x0a,0x00,             /* Frame interval 3: Same as Default frame interval */
   

#else

    /* Class specific Uncompressed VS format descriptor - YUY2 */
       0x1B,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
       0x04,                               /* Subtype : VS_FORMAT */
       HS_YUY2_INDEX,                               /* Format desciptor index */
       HS_YUY2_TOTAL_NO_OF_RES,                               /* Number of Frame Descriptors that follow this descriptor: 3 */

       /* GUID, globally unique identifier used to identify streaming-encoding format: Y8  */
       /* GUID, globally unique identifier used to identify streaming-encoding format*/
    	    0x59,0x38,0x20,0x20,//Y8
    	    0x00,0x00,0x10,0x00,
    	    0x80,0x00,0x00,0xAA,
    	    0x00,0x38,0x9B,0x71,

       0x08,                               /* Number of bits per pixel: 16*/
       0x01,                               /* Optimum Frame Index for this stream: 2 (720p) */
       0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
       0x00,                               /* Y dimension of the pictuer aspect ratio: Non-interlaced */
       0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
       0x00,                               /* duplication of the video stream restriction: 0 - no restriction */

       /* Class specific Uncompressed VS Frame Descriptor 3 - Resolution4 320 x 480 @ 120.0 fps*/
       0x1E,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
       0x05,                               /* Subtype:  frame interface*/
       0x01,                               /* Frame Descriptor Index: 1 */
       0x00,                               /* No Still image capture method supported */
       0x80,0x02,                         /* Width in pixel:  640 */
       0xe0,0x01,                         /* Height in pixel: 480 */
       0x00,0x00,0x94,0x11,             /* Min bit rate (bits/s): 320 x 480 x 16 x 120.0 = 294912000 */
       0x00,0x00,0x94,0x11,             /* Max bit rate (bits/s): Fixed rate so same as Min */
       0x00,0xb0,0x04,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 480 x 2 */
       0x85,0x45,0x01,0x00,             /* Default frame interval (in 100ns units): (1/120.0)x10^7 */
       0x01,                               /* Frame interval type : No of discrete intervals */
       0x85,0x45,0x01,0x00,             /* Frame interval 3: Same as Default frame interval */

       /* Class specific Uncompressed VS Frame Descriptor 4 - Resolution5 960 x 1080 @ 15.0 fps*/
       0x1E,                               /* Descriptor size */
       CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
       0x05,                               /* Subtype:  frame interface*/
       0x02,                               /* Frame Descriptor Index: 2 */
       0x00,                               /* No Still image capture method supported */
       0x80,0x07,                         /* Width in pixel:  1920 */
       0x38,0x04,                         /* Height in pixel: 1080 */
       0x00,0xe0,0xd4,0x0e,             /* Min bit rate (bits/s): 960 x 1080 x 16 x 15.0 = 248832000 */
       0x00,0xe0,0xd4,0x0e,             /* Max bit rate (bits/s): Fixed rate so same as Min */
       0x00,0xa4,0x1f,0x00,             /* Maximum video or still frame size in bytes(Deprecated): 960 x 1080 x 2 */
       0x2a,0x2c,0x0a,0x00,             /* Default frame interval (in 100ns units): (1/15.0)x10^7 */
       0x01,                               /* Frame interval type : No of discrete intervals */
       0x2a,0x2c,0x0a,0x00,             /* Frame interval 3: Same as Default frame interval */

#endif
	/* Color matching descriptor -  YUY2 */
	0x06,
	0x24,
	0x0D,
	0x00,
	0x00,
	0x00,


    /* Endpoint descriptor for Bulk streaming video data */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_BULK_VIDEO,                  /* Endpoint address and description: EP 3 IN */
    CY_U3P_USB_EP_BULK,                 /* BULK End point */
    0x00,                               /* Packet Size: 512 bytes */
    0x02,
    0x00                                /* Servicing interval for data transfers */
};

/* Standard Full Speed Configuration Descriptor*/
/*The below Full Speed Configuration Descriptor is dummy descriptor. The CX3 Project Tool does not create Full Speed Configuration Descriptor*/
const uint8_t CyCx3USBFSConfigDscr[] =
{
    /* Configuration descriptor */
    0x09,                               /* Descriptor size */
    CY_U3P_USB_CONFIG_DESCR,            /* Configuration descriptor type */
#ifdef CX3_UVC_1_0_SUPPORT
    0xEB,0x00,                          /* Length of this descriptor and all sub descriptors */
#else
    0xEC,0x00,                          /* Length of this descriptor and all sub descriptors */
#endif
    0x02,                               /* Number of interfaces */
    0x01,                               /* Configuration number */
    0x05,                               /* Configuration string index */
    0xC0,                               /* Config characteristics - self powered */
    0x32,                               /* Max power consumption of device (in 2mA unit) : 100mA */

    /* Interface Association Descriptor */
    0x08,                               /* Descriptor Size */
    CX3_INTRFC_ASSN_DESCR,              /* Interface Association Descriptor Type */
    0x00,                               /* Interface number of the VideoControl interface 
                                           that is associated with this function*/
    0x02,                               /* Number of contiguous Video interfaces that are 
                                           associated with this function */
    0x0E,                               /* Video Interface Class Code: CC_VIDEO */
    0x03,                               /* Subclass code: SC_VIDEO_INTERFACE_COLLECTION*/
    0x00,                               /* Protocol: PC_PROTOCOL_UNDEFINED*/
    0x00,                               /* String Descriptor index for interface */

    /* Standard Video Control Interface Descriptor (Interface 0, Alternate Setting 0)*/
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x00,                               /* Index of this Interface */
    0x00,                               /* Alternate setting number */
    0x01,                               /* Number of end points - 1 Interrupt Endpoint*/
    0x0E,                               /* Video Interface Class Code: CC_VIDEO  */
    0x01,                               /* Interface sub class: SC_VIDEOCONTROL */
    0x00,                               /* Interface protocol code: PC_PROTOCOL_UNDEFINED.*/
    0x00,                               /* Interface descriptor string index */

    /* Class specific VC Interface Header Descriptor */
    0x0D,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class Specific Interface Descriptor type: CS_INTERFACE */
    0x01,                               /* Descriptor Sub type: VC_HEADER */
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x01,                         /* Revision of UVC class spec: 1.0 - Legacy version */
    0x50, 0x00,                         /* Total Size of class specific descriptors 
                                           (till Output terminal) */
#else
    0x10, 0x01,                         /* Revision of UVC class spec: 1.1 - Minimum version required 
                                           for USB Compliance. Not supported on Windows XP*/
    0x51, 0x00,                         /* Total Size of class specific descriptors 
                                           (till Output terminal) */
#endif
    0x00, 0x6C, 0xDC, 0x02,             /* Clock frequency : 48MHz(Deprecated) */
    0x01,                               /* Number of streaming interfaces */
    0x01,                               /*VideoStreaming interface 1 belongs to this 
                                          VideoControl interface*/

    /* Input (Camera) Terminal Descriptor */
    0x12,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* CS_INTERFACE */
    0x02,                               /* VC_INPUT_TERMINAL subtype */
    0x01,                               /* ID of this input terminal */
    0x01, 0x02,                         /* ITT_CAMERA type. This terminal is a camera 
                                           terminal representing the CCD sensor*/
    0x00,                               /* No association terminal */
    0x00,                               /* Unused */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */

    /* Processing Unit Descriptor */
#ifdef CX3_UVC_1_0_SUPPORT
    0x0C,                               /* Descriptor size */
#else
    0x0D,                               /* Descriptor size */
#endif    
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x05,                               /* Processing Unit Descriptor type: VC_PROCESSING_UNIT*/
    0x02,                               /* ID of this unit */
    0x01,                               /* Source ID: 1: Conencted to input terminal */
    0x00, 0x40,                         /* Digital multiplier */
    0x03,                               /* Size of controls field for this terminal: 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String desc index: Not used */
#ifndef CX3_UVC_1_0_SUPPORT
    0x00,                               /* Analog Video Standards Supported: None */
#endif    

    
    /* Extension Unit Descriptor */
    0x1C,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x06,                               /* Extension Unit Descriptor type */
    0x03,                               /* ID of this terminal */
    0xFF, 0xFF, 0xFF, 0xFF,             /* 16 byte GUID */
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x00,                               /* Number of controls in this terminal */
    0x01,                               /* Number of input pins in this terminal */
    0x02,                               /* Source ID : 2 : Connected to Proc Unit */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String descriptor index : Not used */

    /* Output Terminal Descriptor */
    0x09,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x03,                               /* Output Terminal Descriptor type */
    0x04,                               /* ID of this terminal */
    0x01, 0x01,                         /* USB Streaming terminal type */
    0x00,                               /* No association terminal */
    0x03,                               /* Source ID : 3 : Connected to Extn Unit */
    0x00,                               /* String desc index : Not used */

    /* Video Control Status Interrupt Endpoint Descriptor */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_CONTROL_STATUS,              /* Endpoint address and description: EP-2 IN */
    CY_U3P_USB_EP_INTR,                 /* Interrupt End point Type */
    0x40, 0x00,                         /* Max packet size: 64 bytes */
    0x01,                               /* Servicing interval */

    /* Class Specific Interrupt Endpoint Descriptor */
    0x05,                               /* Descriptor size */
    0x25,                               /* Class specific endpoint descriptor type */
    CY_U3P_USB_EP_INTR,                 /* End point sub type */
    0x40,0x00,                          /* Max packet size = 64 bytes */

    /* Standard Video Streaming Interface Descriptor (Interface 1, Alternate Setting 0) */
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface descriptor type */
    0x01,                               /* Interface number: 1 */
    0x00,                               /* Alternate setting number: 0 */
    0x01,                               /* Number of end points: 1 Bulk end point*/
    0x0E,                               /* Interface class : CC_VIDEO */
    0x02,                               /* Interface sub class : SC_VIDEOSTREAMING */
    0x00,                               /* Interface protocol code : PC_PROTOCOL_UNDEFINED */
    0x00,                               /* Interface descriptor string index */

    /* Class-specific Video Streaming Input Header Descriptor */
    0x0E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface type */
    0x01,                               /* Descriptor subType : Input Header */
    0x01,                               /* 1 format descriptor follows */
    0x65, 0x00,                         /* Total size of class specific VS descr */
    CX3_EP_BULK_VIDEO,                  /* EP address for BULK video data: EP 3 IN  */
    0x00,                               /* No dynamic format change supported */
    0x04,                               /* Output terminal ID : 4 */
    0x00,                               /* No Still image capture method supported */
    0x00,                               /* Hardware trigger not supported */
    0x00,                               /* Hardware to initiate still image capture not supported*/
    0x01,                               /* Size of controls field : 1 byte */
    0x00,                               /* D2 : Compression quality supported - No compression */

    /* Class specific VS format descriptor */
    0x1B,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
    0x04,                               /* Subtype : VS_FORMAT */
    0x01,                               /* Format desciptor index */
    0x02,                               /* Number of Frame Descriptors that follow this descriptor: 2 */
    /* GUID, globally unique identifier used to identify streaming-encoding format: YUY2  */
    0x59, 0x55, 0x59, 0x32,             /*MEDIASUBTYPE_YUY2 GUID: 32595559-0000-0010-8000-00AA00389B71 */
    0x00, 0x00, 0x10, 0x00,
    0x80, 0x00, 0x00, 0xAA,
    0x00, 0x38, 0x9B, 0x71,
    0x10,                               /* Number of bits per pixel: 16*/
    0x02,                               /* Optimum Frame Index for this stream: 1 (320x240) */
    0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
    0x00,                               /* Y dimension of the pictuer aspect ratio: Non-interlaced */
    0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
    0x00,                               /* duplication of the video stream restriction: 0 - no restriction */

   /* Class specific Uncompressed VS Frame Descriptor 1 - 320x240@5fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype: Uncompressed frame interface*/
    0x01,                               /* Frame Descriptor Index: 1 */
    0x00,                               /* No Still image capture method supported */
    0x40, 0x01,                         /* Width in pixel:  320 */
    0xF0, 0x00,                         /* Height in pixel: 240 */
    0x00, 0xC0, 0x5D, 0x00,             /* Min bit rate (bits/s): 320 x 240 x 2 x 5 x 8 = 6144000 */
    0x00, 0xC0, 0x5D, 0x00,             /* Max bit rate (bits/s): Fixed rate so same as Min  */
    0x00, 0x58, 0x02, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 240 x 2*/
    0x80, 0x84, 0x1E, 0x00,             /* Default frame interval (in 100ns units): (1/5)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x80, 0x84, 0x1E, 0x00,             /* Frame interval 3: Same as Default frame interval */

    /* Class specific Uncompressed VS frame descriptor 2 - 320 x 240 @2fps - Needed only for compliance. 
     * The USBCV30 USB 2.0 UVC Tests 'Standard VS Interface Descriptor Test - Device Configured' and 
     * 'Standard VS Interface Descriptor Test - Device Addressed', Fail if only one VS Frame descriptor 
     * is provided. 
     */
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype:  frame interface*/
    0x02,                               /* Frame Descriptor Index: 1 */
    0x00,                               /* No Still image capture method supported */
    0x40, 0x01,                         /* Width in pixel:  320 */
    0xF0, 0x00,                         /* Height in pixel: 240 */
    0x00, 0x80, 0x25, 0x00,             /* Min bit rate (bits/s): 320 x 240 x 2 x 2 x 8 = 2457600 */
    0x00, 0x80, 0x25, 0x00,             /* Max bit rate (bits/s): Fixed rate so same as Min  */
    0x00, 0x58, 0x02, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 240 x 2*/
    0x40, 0x4B, 0x4C, 0x00,             /* Default frame interval (in 100ns units): (1/5)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x40, 0x4B, 0x4C, 0x00,             /* Frame interval 3: Same as Default frame interval */

    /* Endpoint descriptor for Bulk streaming video data */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_BULK_VIDEO,                  /* Endpoint address and description: EP 3 IN */
    CY_U3P_USB_EP_BULK,                 /* BULK End point */
    0x40,                               /* EP Packet Size: 64 bytes */
    0x00,
    0x00                                /* Servicing interval for data transfers */
};

/* Standard product string descriptor */
#ifndef FX3_STREAMING
const uint8_t CyCx3USBProductDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'C', 0x00,                          /* Product Descriptor String */
    'X', 0x00,
    '3', 0x00,
    '-', 0x00,
    'U', 0x00,
    'V', 0x00,
    'C', 0x00
};

#else
const uint8_t CyCx3USBProductDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'F', 0x00,                          /* Product Descriptor String */
    'X', 0x00,
    '3', 0x00,
    '-', 0x00,
    'U', 0x00,
    'V', 0x00,
    'C', 0x00
};
#endif

/* Standard language ID string descriptor */
const uint8_t CyCx3USBStringLangIDDscr[] =
{
    0x04,                               /* Descriptor size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    0x09,0x04                           /* Language ID supported */
};


/* Standard manufacturer string descriptor */
const uint8_t CyCx3USBManufactureDscr[] =
{
    0x10,                               /* Descriptor size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'C',0x00,                           /* Manufacturer String */
    'y',0x00,
    'p',0x00,
    'r',0x00,
    'e',0x00,
    's',0x00,
    's',0x00
};



/* Standard product string descriptor */
const uint8_t CyCx3USBConfigSSDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'U', 0x00,                          /* Super-Speed Configuration Descriptor */
    'S', 0x00,
    'B', 0x00,
    '-', 0x00,
    '3', 0x00,
    '.', 0x00,
    '0', 0x00
};
/* Standard product string descriptor */
const uint8_t CyCx3USBConfigHSDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'U', 0x00,                          /* High-Speed Configuration Descriptor */
    'S', 0x00,
    'B', 0x00,
    '-', 0x00,
    '2', 0x00,
    '.', 0x00,
    '1', 0x00
};
/* Standard product string descriptor */
const uint8_t CyCx3USBConfigFSDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'U', 0x00,                          /* Full-Speed Configuration Descriptor */
    'S', 0x00,
    'B', 0x00,
    '-', 0x00,
    '1', 0x00,
    '.', 0x00,
    '1', 0x00
};

/**********************************************************************************************************
 ****************** SS UVC Probe control structure corresponding to each format and frame *****************
 **********************************************************************************************************/

/*
 * UVC Probe Control Settings: This array holds the data that is sent by CX3 as response to a UVC
 * VS_PROBE_CONTROL request.
 */

/* UVC Probe Control Settings */
uint8_t glProbeCtrl[CX3_UVC_MAX_PROBE_SETTING] = {
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    0x01,                               /* Use 1st Video format index */
    0x01,                               /* Use 1st Video frame index */
    0x0A, 0x8B, 0x02, 0x00,             /* Desired frame interval in 100ns */
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
    0x00, 0x48, 0x3F, 0x00,             /* Max video frame size in bytes */ 
#ifdef CX3_UVC_1_0_SUPPORT 
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 32KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,             /* No. of bytes device can rx in single payload: 32KB */
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};

/* UVC Probe Control Settings corresponding to YUY2 video stream with Resolution1 960 x 1080 @ 100.0 fps*/
uint8_t const glYUY2Resolution1ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING] = {
    0x00, 0x00,                           /* bmHint : No fixed parameters */
    SS_YUY2_INDEX,                        /* Use 1st Video format index */
    0x01,                               /* Use 1st Video frame index */
    0x9f,0x86,0x01,0x00,             /* Desired frame interval in 100ns = (1/ 100.0)x10^7 */
    0x00, 0x00,                           /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                           /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                           /* Compression quality control */
    0x00, 0x00,                           /* Window size for average bit rate */
    0x00, 0x00,                           /* Internal video streaming i/f latency in ms */
    0x00,0xa4,0x1f,0x00,             /* Max video frame size in bytes = 960 x 1080 x 2 */ 
#ifdef CX3_UVC_1_0_SUPPORT 
    0x00, 0x90, 0x00, 0x00                /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,               /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,               /* Device Clock */
    0x00,                                 /* Framing Information - Ignored for uncompressed format*/
    0x00,                                 /* Preferred payload format version */
    0x00,                                 /* Minimum payload format version */
    0x00                                  /* Maximum payload format version */
#endif
};

/* UVC Probe Control Settings corresponding to YUY2 video stream with Resolution2 640 x 720 @ 120.0 fps*/
uint8_t const glYUY2Resolution2ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING] = {
    0x00, 0x00,                           /* bmHint : No fixed parameters */
    SS_YUY2_INDEX,                        /* Use 1st Video format index */
    0x02,                               /* Use 1st Video frame index */
    0x85,0x45,0x01,0x00,             /* Desired frame interval in 100ns = (1/ 120.0)x10^7 */
    0x00, 0x00,                           /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                           /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                           /* Compression quality control */
    0x00, 0x00,                           /* Window size for average bit rate */
    0x00, 0x00,                           /* Internal video streaming i/f latency in ms */
    0x00,0x10,0x0e,0x00,             /* Max video frame size in bytes = 640 x 720 x 2 */ 
#ifdef CX3_UVC_1_0_SUPPORT 
    0x00, 0x90, 0x00, 0x00                /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,               /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,               /* Device Clock */
    0x00,                                 /* Framing Information - Ignored for uncompressed format*/
    0x00,                                 /* Preferred payload format version */
    0x00,                                 /* Minimum payload format version */
    0x00                                  /* Maximum payload format version */
#endif
};

/* UVC Probe Control Settings corresponding to YUY2 video stream with Resolution4 320 x 480 @ 120.0 fps*/
uint8_t const glYUY2Resolution4ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING] = {
    0x00, 0x00,                           /* bmHint : No fixed parameters */
    SS_YUY2_INDEX,                        /* Use 1st Video format index */
    0x03,                               /* Use 1st Video frame index */
    0x85,0x45,0x01,0x00,             /* Desired frame interval in 100ns = (1/ 120.0)x10^7 */
    0x00, 0x00,                           /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                           /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                           /* Compression quality control */
    0x00, 0x00,                           /* Window size for average bit rate */
    0x00, 0x00,                           /* Internal video streaming i/f latency in ms */
    0x00,0xb0,0x04,0x00,             /* Max video frame size in bytes = 320 x 480 x 2 */ 
#ifdef CX3_UVC_1_0_SUPPORT 
    0x00, 0x90, 0x00, 0x00                /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,               /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,               /* Device Clock */
    0x00,                                 /* Framing Information - Ignored for uncompressed format*/
    0x00,                                 /* Preferred payload format version */
    0x00,                                 /* Minimum payload format version */
    0x00                                  /* Maximum payload format version */
#endif
};

/* UVC Probe Control Settings corresponding to YUY2 video stream with Resolution5 960 x 1080 @ 15.0 fps*/
uint8_t const glYUY2Resolution5ProbeCtrl[CX3_UVC_MAX_PROBE_SETTING] = {
    0x00, 0x00,                           /* bmHint : No fixed parameters */
    SS_YUY2_INDEX,                        /* Use 1st Video format index */
    0x04,                               /* Use 1st Video frame index */
    0x2a,0x2c,0x0a,0x00,             /* Desired frame interval in 100ns = (1/ 15.0)x10^7 */
    0x00, 0x00,                           /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                           /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                           /* Compression quality control */
    0x00, 0x00,                           /* Window size for average bit rate */
    0x00, 0x00,                           /* Internal video streaming i/f latency in ms */
    0x00,0xa4,0x1f,0x00,             /* Max video frame size in bytes = 960 x 1080 x 2 */ 
#ifdef CX3_UVC_1_0_SUPPORT 
    0x00, 0x90, 0x00, 0x00                /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,               /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,               /* Device Clock */
    0x00,                                 /* Framing Information - Ignored for uncompressed format*/
    0x00,                                 /* Preferred payload format version */
    0x00,                                 /* Minimum payload format version */
    0x00                                  /* Maximum payload format version */
#endif
};


/**********************************************************************************************************
 ****************** HS UVC Probe control structure corresponding to each format and frame *****************
 **********************************************************************************************************/
/* UVC Probe Control Setting - YUY2Resolution4 320 x 480 @ 120.0 fps*/
uint8_t const glYUY2Resolution4ProbeCtrl_HS[CX3_UVC_MAX_PROBE_SETTING] = {
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    HS_YUY2_INDEX,                      /* Use 1st Video format index */
    0x01,                               /* Use 1st Video frame index */
    0x85,0x45,0x01,0x00,             /* Desired frame interval in 100ns = (1/120.0)x10^7 */
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
    0x00,0xb0,0x04,0x00,             /* Max video frame size in bytes = 320 x 480 x 2 */ 
#ifdef CX3_UVC_1_0_SUPPORT 
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,             /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};

/* UVC Probe Control Setting - YUY2Resolution5 960 x 1080 @ 15.0 fps*/
uint8_t const glYUY2Resolution5ProbeCtrl_HS[CX3_UVC_MAX_PROBE_SETTING] = {
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    HS_YUY2_INDEX,                      /* Use 1st Video format index */
    0x02,                               /* Use 1st Video frame index */
    0x2a,0x2c,0x0a,0x00,             /* Desired frame interval in 100ns = (1/15.0)x10^7 */
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
    0x00,0xa4,0x1f,0x00,             /* Max video frame size in bytes = 960 x 1080 x 2 */ 
#ifdef CX3_UVC_1_0_SUPPORT 
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,             /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};

/* [ ] */



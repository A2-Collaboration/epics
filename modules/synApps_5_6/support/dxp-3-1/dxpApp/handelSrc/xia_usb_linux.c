/*
 * Original author: Mark Rivers, University of Chicago
 *
 * Copyright (c) 2009-2011 XIA LLC
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, 
 * with or without modification, are permitted provided 
 * that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer.
 *   * Redistributions in binary form must reproduce the 
 *     above copyright notice, this list of conditions and the 
 *     following disclaimer in the documentation and/or other 
 *     materials provided with the distribution.
 *   * Neither the name of XIA LLC 
 *     nor the names of its contributors may be used to endorse 
 *     or promote products derived from this software without 
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 *
 * $Id$
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <usb.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <string.h>

#include "Dlldefs.h"
#include "usblib.h"
#include "handel_errors.h"
#include "handel_log.h"
#include "xia_handel.h"

#include "xia_usb2.h"
#include "xia_usb2_errors.h"
#include "xia_usb2_private.h"

#define FALSE    0
#define TRUE    (!0)

#ifndef byte_t
#define byte_t        unsigned char
#endif

#ifndef bool
#define bool int
#endif

#define XIA_USB2_SMALL_READ_PACKET_SIZE 512

static int xia_usb2__send_setup_packet(HANDLE h, unsigned long addr,
                                       unsigned long n_bytes, byte_t rw_flag);
static struct usb_dev_handle        *xia_usb_handle = NULL;
static struct usb_device            *xia_usb_device = NULL;


/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb_open(char *device, HANDLE *hDevice)
{
    int                           device_number;
    struct usb_bus                *p;
    struct usb_device             *q;
    int                           found = -1;
    int                           rv = 0;
    static int                    first = TRUE;

    if (xia_usb_handle != NULL) return 0;   /* if not first just return, leaving the old device open */

    device_number = device[strlen(device) - 1] - '0';

    /* Must be original XIA USB 1.0 card */
    if (xia_usb_handle == NULL) {
        if (first) {
            usb_init();
            usb_set_debug(0);
            usb_find_busses();
            usb_find_devices();
            first = FALSE;
        }

        p = usb_get_busses();
        while ((p != NULL) && (xia_usb_handle == NULL) && (rv == 0)) {
            q = p->devices;
            while ((q != NULL) && (xia_usb_handle == NULL) && (rv == 0)) {
                if ((q->descriptor.idVendor == 0x10e9) && (q->descriptor.idProduct == 0x0700)) {
                    found++;
                    if (found == device_number) {
                        xia_usb_device = q;
                        xia_usb_handle = usb_open(xia_usb_device);
                        if (xia_usb_handle == NULL) {
                            rv = -1;
                        } else {
                            rv = usb_set_configuration(xia_usb_handle, 
                                                       xia_usb_device->config[0].bConfigurationValue);
                            if (rv == 0) {
                                rv = usb_claim_interface(xia_usb_handle, 0);
                                rv = usb_reset(xia_usb_handle);
                                sprintf(info_string, "Found USB 1.0 board");
                                xiaLogInfo("xia_usb_open", info_string);
                            }
                        }
                    }
                }
                q = q->next;
            }
            p = p->next;
        }
    }
    if ((xia_usb_handle == NULL) || (rv != 0)) {
        *hDevice = 0;
        if (rv == 0) rv = -99;
    } else {
        *hDevice = 1;
    }

    return rv;
}


/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb2_open(int device_number, HANDLE *hDevice)
{
    struct usb_bus                *p;
    struct usb_device            *q;
    int                            found = -1;
    int                            rv = 0;
    static int                    first = TRUE;

    if (xia_usb_handle != NULL) return 0; /* if not first just return, leaving the old device open  */


    /* Must be new XIA USB 2.0 card */
    if (xia_usb_handle == NULL) {
        if (first) {
            usb_init();
            usb_set_debug(0);
            usb_find_busses();
            usb_find_devices();
            first = FALSE;
        }
        p = usb_get_busses();
        while ((p != NULL) && (xia_usb_handle == NULL) && (rv == 0)) {
            q = p->devices;
            while ((q != NULL) && (xia_usb_handle == NULL) && (rv == 0)) {
                if ((q->descriptor.idVendor == 0x10e9) && 
                    ((q->descriptor.idProduct == 0x0701) ||
                     (q->descriptor.idProduct == 0x0702) ||
                     (q->descriptor.idProduct == 0x0703))) {
                    found++;
                    if (found == device_number) {
                        xia_usb_device = q;
                        xia_usb_handle = usb_open(xia_usb_device);
                        if (xia_usb_handle == NULL) {
                            rv = -1;
                        } else {
                            rv = usb_set_configuration(xia_usb_handle, 
                                                       xia_usb_device->config[0].bConfigurationValue);
                            if (rv == 0) {
                                rv = usb_claim_interface(xia_usb_handle, 0);
                                rv = usb_reset(xia_usb_handle);
                                sprintf(info_string, "Found USB 2.0 board, product=0x%x", q->descriptor.idProduct);
                                xiaLogInfo("xia_usb2_open", info_string);
                            }
                        }
                    }
                }
                q = q->next;
            }
            p = p->next;
        }
    }
    
    if ((xia_usb_handle == NULL) || (rv != 0)) {
        *hDevice = 0;
        if (rv == 0) rv = -99;
    } else {
        *hDevice = 1;
    }

    return rv;
}

/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb_close(HANDLE hDevice)
{
    int rv = 0;
    
    /* This does a reset of the USB device before closing it.  This is needed for USB2 on Linux
     * or the next time that XIA software is run it cannot open the device correctly */
    if (hDevice && xia_usb_handle) {
        rv |= usb_release_interface(xia_usb_handle, 0);
        rv |= usb_close(xia_usb_handle);
        xia_usb_handle = NULL;
        xia_usb_device = NULL;
    }

    return rv;
}

/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb2_close(HANDLE hDevice)
{
    return(xia_usb_close(hDevice));
}

/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb_read(long address, long nWords, char *device, unsigned short *buffer)
{
    int             n_bytes;
    HANDLE          hDevice;
    unsigned char   ctrlBuffer[64];        /* [CTRL_SIZE]; */
    unsigned char   lo_address, hi_address, lo_count, hi_count;
    int             rv = 0;
    
    rv = xia_usb_open(device, &hDevice);            /* Get handle to USB device */
    if (rv != 0) {
        sprintf(info_string, "Failed to open device %s", device);
        xiaLogError("xia_usb_read", info_string, XIA_MD);
        return 1;
    }


    n_bytes = (nWords * 2);

    hi_address = (unsigned char)(address >> 8);
    lo_address = (unsigned char)(address & 0x00ff);
    hi_count = (unsigned char)(n_bytes >> 8);
    lo_count = (unsigned char)(n_bytes & 0x00ff);

    memset(ctrlBuffer, 0, 64);
    ctrlBuffer[0] = lo_address;
    ctrlBuffer[1] = hi_address;
    ctrlBuffer[2] = lo_count;
    ctrlBuffer[3] = hi_count;
    ctrlBuffer[4] = (unsigned char)0x01;

    rv = usb_bulk_write(xia_usb_handle, OUT1 | USB_ENDPOINT_OUT, (char*)ctrlBuffer, CTRL_SIZE, 10000);
    if (rv != CTRL_SIZE) {
        sprintf(info_string, "usb_bulk_read returned %d should be %d", rv, CTRL_SIZE);
        xiaLogError("xia_usb_read", info_string, XIA_MD);
        return 14;
    }

    rv = usb_bulk_read(xia_usb_handle, IN2 | USB_ENDPOINT_IN, (char*)buffer, n_bytes, 10000);
    if (rv != n_bytes) {
        sprintf(info_string, "usb_bulk_read returned %d should be %d", rv, n_bytes);
        xiaLogError("xia_usb_read", info_string, XIA_MD);
        return 2;
    }

    return 0;

}


/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb2_read(HANDLE h, unsigned long addr,
                                     unsigned long n_bytes,
                                     byte_t *buf)
{
    int     status = 0;

    if (xia_usb_handle == NULL) {
        return XIA_USB2_NULL_HANDLE;
    }

    if (n_bytes == 0) {
        return XIA_USB2_ZERO_BYTES;
    }

    if (buf == NULL) {
        return XIA_USB2_NULL_BUFFER;
    }

    if (n_bytes < XIA_USB2_SMALL_READ_PACKET_SIZE) {
        byte_t big_packet[XIA_USB2_SMALL_READ_PACKET_SIZE];  

        status = xia_usb2__send_setup_packet(0, addr,
                                         XIA_USB2_SMALL_READ_PACKET_SIZE,
                                         XIA_USB2_SETUP_FLAG_READ);

        if (status != XIA_USB2_SUCCESS) {
            return status;
        }

        status = usb_bulk_read(xia_usb_handle, XIA_USB2_READ_EP | USB_ENDPOINT_IN, (char*)big_packet, 
                               XIA_USB2_SMALL_READ_PACKET_SIZE, 10000);
        if (status != XIA_USB2_SMALL_READ_PACKET_SIZE) {
            sprintf(info_string, "usb_bulk_read returned %d should be %d", status, XIA_USB2_SMALL_READ_PACKET_SIZE);
            xiaLogError("xia_usb2_read", info_string, XIA_MD);
            return XIA_USB2_XFER;
        }
        memcpy(buf, &big_packet, n_bytes);
   } else {
        status = xia_usb2__send_setup_packet(0, addr, n_bytes, XIA_USB2_SETUP_FLAG_READ);

        if (status != XIA_USB2_SUCCESS) {
            return status;
        }

        status = usb_bulk_read(xia_usb_handle, XIA_USB2_READ_EP | USB_ENDPOINT_IN, (char*)buf, 
                               n_bytes, 10000);
        if (status != n_bytes) {
            sprintf(info_string, "usb_bulk_read returned %d should be %ld", status, n_bytes);
            xiaLogError("xia_usb2_read", info_string, XIA_MD);
            return XIA_USB2_XFER;
        }
    }

    return XIA_USB2_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb_write(long address, long nWords, char *device, unsigned short *buffer)
{
    int                     n_bytes;
    HANDLE                  hDevice;
    int                     rv = 0;
    unsigned char           ctrlBuffer[64];            /* [CTRL_SIZE]; */
    unsigned char           lo_address, hi_address, lo_count, hi_count;
    
    rv = xia_usb_open(device, &hDevice);            /* Get handle to USB device */
    if (rv != 0) {
        sprintf(info_string, "Failed to open %s", device);
        xiaLogError("xia_usb_write", info_string, XIA_MD);
        return 1;
    }


    n_bytes = (nWords * 2);

    hi_address = (unsigned char)(address >> 8);
    lo_address = (unsigned char)(address & 0x00ff);
    hi_count = (unsigned char)(n_bytes >> 8);
    lo_count = (unsigned char)(n_bytes & 0x00ff);

    memset(ctrlBuffer, 0, 64);
    ctrlBuffer[0] = lo_address;
    ctrlBuffer[1] = hi_address;
    ctrlBuffer[2] = lo_count;
    ctrlBuffer[3] = hi_count;
    ctrlBuffer[4] = (unsigned char)0x00;

    rv = usb_bulk_write(xia_usb_handle, OUT1 | USB_ENDPOINT_OUT, (char*)ctrlBuffer, CTRL_SIZE, 10000);
    if (rv != CTRL_SIZE) {
        sprintf(info_string, "usb_bulk_write returned %d should be %d", rv, CTRL_SIZE);
        xiaLogError("xia_usb_write", info_string, XIA_MD);
        return 14;
    }

    rv = usb_bulk_write(xia_usb_handle, OUT2 | USB_ENDPOINT_OUT, (char*)buffer, n_bytes, 10000);
    if (rv != n_bytes) {
        sprintf(info_string, "usb_bulk_write returned %d should be %d", rv, n_bytes);
        xiaLogError("xia_usb_write", info_string, XIA_MD);
        return 15;
    }
    return 0;
} 
    
    
    
/*---------------------------------------------------------------------------------------*/
XIA_EXPORT int XIA_API xia_usb2_write(HANDLE h, unsigned long addr,
                                      unsigned long n_bytes,
                                      byte_t *buf)
{    
    int     status;

    if (xia_usb_handle == NULL) {
        return XIA_USB2_NULL_HANDLE;
    }

    if (n_bytes == 0) {
        return XIA_USB2_ZERO_BYTES;
    }

    if (buf == NULL) {
        return XIA_USB2_NULL_BUFFER;
    }

    status = xia_usb2__send_setup_packet(0, addr, n_bytes, XIA_USB2_SETUP_FLAG_WRITE);

    if (status != XIA_USB2_SUCCESS) {
        return status;
    }

    status = usb_bulk_write(xia_usb_handle, XIA_USB2_WRITE_EP | USB_ENDPOINT_OUT, (char*)buf, 
                            n_bytes, 10000);

    if (status != n_bytes) {
        sprintf(info_string, "usb_bulk_write returned %d should be %ld", status, n_bytes);
        xiaLogError("xia_usb2_write", info_string, XIA_MD);
        return XIA_USB2_XFER;
    }

    return XIA_USB2_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * @brief Sends an XIA-specific setup packet to the "setup" endpoint. This
 * is the first stage of our two-part process for transferring data to
 * and from the board.
 */
static int xia_usb2__send_setup_packet(HANDLE h, unsigned long addr,
                                       unsigned long n_bytes, byte_t rw_flag)
{
    int             status;

    byte_t          pkt[XIA_USB2_SETUP_PACKET_SIZE];

    pkt[0] = (byte_t)(addr & 0xFF);
    pkt[1] = (byte_t)((addr >> 8) & 0xFF);
    pkt[2] = (byte_t)(n_bytes & 0xFF);
    pkt[3] = (byte_t)((n_bytes >> 8) & 0xFF);
    pkt[4] = (byte_t)((n_bytes >> 16) & 0xFF);
    pkt[5] = (byte_t)((n_bytes >> 24) & 0xFF);
    pkt[6] = rw_flag;
    pkt[7] = (byte_t)((addr >> 16) & 0xFF);
    pkt[8] = (byte_t)((addr >> 24) & 0xFF);

    status = usb_bulk_write(xia_usb_handle, XIA_USB2_SETUP_EP | USB_ENDPOINT_OUT, (char*)pkt, XIA_USB2_SETUP_PACKET_SIZE, 10000);
    if (status != XIA_USB2_SETUP_PACKET_SIZE) {
        sprintf(info_string, "usb_bulk_write returned %d should be %d", status, XIA_USB2_SETUP_PACKET_SIZE);
        xiaLogError("xia_usb2__send_setup_packet", info_string, XIA_MD);
        return XIA_USB2_XFER;
    }

    return XIA_USB2_SUCCESS;
}


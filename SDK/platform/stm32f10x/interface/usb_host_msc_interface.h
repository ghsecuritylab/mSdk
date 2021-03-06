/*
 * usb_interface.h
 *
 *  Created on: Dec 25, 2012
 *      Author: XxXx
 */

#ifndef USB_INTERFACE_H_
#define USB_INTERFACE_H_

#include "api/gpio_api.h"

#define USBMSC_DRIVE_RETRY     4
#define USB_TIMEOUT_MILLISECS 3000

void _usb_msc_host_init(unsigned int instance, new_gpio* StatusLed);
void _usb_msc_host_idle(unsigned int instance);
void _usb_msc_host_ioctl(void *ctrl, unsigned int  command,  unsigned int *buffer);
unsigned int USBMSCReadBlock(void *_ctrl, void *ptr, unsigned long block,
                              unsigned int nblks);
unsigned int USBMSCWriteBlock(void *_ctrl, void *ptr, unsigned long block,
                              unsigned int nblks);

#ifdef HEADER_INCLUDE_C_FILES
#include "usb_interface.c"
#endif

#endif /* USB_INTERFACE_H_ */

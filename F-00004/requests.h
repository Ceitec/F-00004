/* Name: requests.h
 * Project: custom-class, a basic USB example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-09
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

/* This header is shared between the firmware and the host software. It
 * defines the USB request numbers (and optionally data types) used to
 * communicate between the host and the device.
 */

#ifndef __REQUESTS_H_INCLUDED__
#define __REQUESTS_H_INCLUDED__

#define LED_RQ_SET_STATUS    1
/* Set the LED status. Control-OUT.
 * The requested status is passed in the "wValue" field of the control
 * transfer. No OUT data is sent. Bit 0 of the low byte of wValue controls
 * the LED.
 */

#define LED_RQ_GET_STATUS    2
/* Get the current LED status. Control-IN.
 * This control transfer involves a 1 byte data phase where the device sends
 * the current status to the host. The status is in bit 0 of the byte.
 */

#define USB_LED_POWER_SET	1
#define USB_LED_POWER_ASK	2

#define USB_LED_LEFT_SET	3
#define USB_LED_LEFT_ASK	4

#define USB_LED_RIGHT_SET	5
#define USB_LED_RIGHT_ASK	6

#define USB_LED_OK_SET		7
#define USB_LED_OK_ASK		8


#define SET_OK 0
#define SET_NOK 100


#define USB_LED_POWER_PORT	PORTB		//Pøiøadi pin
#define USB_LED_POWER_PIN	PB0		//Pøiøadi pin

#define USB_LED_LEFT_PORT	PORTB		//Pøiøadi pin
#define USB_LED_LEFT_PIN	PB1		//Pøiøadi pin

#define USB_LED_RIGHT_PORT	PORTB		//Pøiøadi pin
#define USB_LED_RIGHT_PIN	PB2		//Pøiøadi pin

#define USB_LED_OK_PORT		PORTB		//Pøiøadi pin
#define USB_LED_OK_PIN		PB3		//Pøiøadi pin




#endif /* __REQUESTS_H_INCLUDED__ */

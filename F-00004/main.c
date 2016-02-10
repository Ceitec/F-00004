/* Name: main.c
 * Project: hid-custom-rq example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-07
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

/*
This example should run on most AVRs with only little changes. No special
hardware resources except INT0 are used. You may have to change usbconfig.h for
different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
at least be connected to INT0 as well.
We assume that an LED is connected to port B bit 0. If you connect it to a
different port or bit, change the macros below:
*/
#define LED_PORT_DDR        DDRB
#define LED_PORT_OUTPUT     PORTB
#define LED_BIT             0

#define F_CPU 15000000



#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "USB/usbdrv.h"
#include "USB/oddebug.h"        /* This is also an example for using debug macros */
#include "requests.h"       /* The custom request numbers we use */
#include "joystick.h"		/* Knihovna pro joystick ovládání */
#include <avr/sfr_defs.h>
/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

/*
Makra
*/


/*
PROGMEM const char usbHidReportDescriptor[22] = {   / * USB report descriptor * /
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};*/
PROGMEM const char usbHidReportDescriptor[22] = {   /* USB report descriptor */
	0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
	0x09, 0x04,                    // USAGE (Vendor Usage 1)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x09, 0x00,                    //   USAGE (Undefined)
	0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
	0xc0                           // END_COLLECTION
};
/* The descriptor above is a dummy only, it silences the drivers. The report
 * it describes consists of one byte of undefined data.
 * We don't transfer our data through HID reports, we use custom requests
 * instead.
 */

/* ------------------------------------------------------------------------- */

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t *rq = (void *)data;
	switch (rq->bRequest)
	{
		case USB_LED_POWER_SET :
			if((rq->wValue.bytes[0] & 0x01) == 0x01)
			{    /* set LED */
				bit_is_set(USB_LED_POWER_PORT, USB_LED_POWER_PIN);
				return SET_OK;
			}
			else if((rq->wValue.bytes[0] & 0x00) == 0x00)
			{                          /* clear LED */
				bit_is_clear(USB_LED_POWER_PORT, USB_LED_POWER_PIN);
				return SET_OK;
			}
			else
			{
				return SET_NOK;
			}
			break;
		case USB_LED_POWER_ASK :
		
			break;
	
        /*if ()
        {
        }
           
		else if(rq->bRequest == CUSTOM_RQ_GET_STATUS)
		{
            static uchar dataBuffer[1];     / * buffer must stay valid when usbFunctionSetup returns * /
            dataBuffer[0] = ((LED_PORT_OUTPUT & _BV(LED_BIT)) != 0);
            usbMsgPtr = dataBuffer;         / * tell the driver which data to return * /
            return 1;                       / * tell the driver to send 1 byte * /
        }
		else{
        / * calss requests USBRQ_HID_GET_REPORT and USBRQ_HID_SET_REPORT are
         * not implemented since we never call them. The operating system
         * won't call them either because our descriptor defines no meaning.
         * /*/
    }
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* ------------------------------------------------------------------------- */

int main()
{
	uchar	i=0;

    wdt_enable(WDTO_1S);
    
    usbInit();
    
	usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    
    for (i=0; i<250; i++)
    {         /* fake USB disconnect for > 500 ms */
        wdt_reset();
        _delay_ms(2);
    }
    usbDeviceConnect();
    //LED_PORT_DDR |= _BV(LED_BIT);   /* make the LED bit an output */
    sei();
    //DBG1(0x01, 0, 0);       /* debug output: main loop starts */
    while (1)
    {
        wdt_reset();
        usbPoll();
		
	}
}

/* ------------------------------------------------------------------------- */

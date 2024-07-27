/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ULTRASONIC driver
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "gpio.h"
#include "std_types.h"
#include "icu.h"

#define TRIGGER_PORT PORTB_ID
#define TRIGGER_PIN PIN5_ID

extern volatile uint8 g_edgeCount;
extern uint16 g_time;

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
